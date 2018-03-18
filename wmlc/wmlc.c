/*
   wml-tools 

   Copyright (C) 1999-2018 Thomas Neill (tneill@pwot.co.uk)

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 3
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#define WML_NO_CLOSURES
#include <wml/tokens.h>
#include <wml/tags.h>
#undef WML_NO_CLOSURES

#define WHITESPACE " \t\n\r"

FILE *out;

void crashBurn(void)
{
	fflush(out);
	fprintf(stderr, "FATAL: Compile failed\n");
	fclose(out);
	exit(1);
}

int tagHasClosure(int tag)
{
	int i;

	for(i = 0; wml_no_closure_tags[i] > 0; i++) {
		if(tag == wml_no_closure_tags[i])
			return 0;
	}

	return 1;
}

int getTagIndex(const char *tagText)
{
	int i;

	for(i = 0; i < ((WML_TAGS_MAX - WML_TAGS_MIN)+1); i++) {
		if(wml_tags[i]) {
			if(strcmp(tagText, wml_tags[i]) == 0)
				return (i + WML_TAGS_MIN);
		}
	}

	return -1;
}

int getSattrIndex(const char *attrText)
{
	int i;

	for(i = 0; i < ((WML_SATTR_MAX - WML_SATTR_MIN)+1); i++) {
		if(wml_start_attributes[i]) {
			if(strcmp(attrText, wml_start_attributes[i]) == 0)
				return (i + WML_SATTR_MIN);
		}
	}

	return -1;
}

void outputString(char *str)
{
	int justPassedWhitespace = 0;

	fputc(WMLC_INLINE_STRING, out);

	while(*str != '\0') {
		if(strchr(WHITESPACE, *str)) {
			if(justPassedWhitespace == 0) {
				fputc(' ', out);
				justPassedWhitespace = 1;
			}
		} else {
			fputc(*str, out);
			justPassedWhitespace = 0;
		}
		str++;
	}

	fputc(WMLC_INLINE_STRING_END, out);
}

void compileAttributes(xmlAttrPtr attributes)
{
	xmlNodePtr val;
	int sattrNum;
	char buffer[256];

	while(attributes) {
		val = attributes->children;
		if(strcmp(val->name, "text") != 0) {
			fprintf(stderr, "Parse error: can't handle non plaintext attribute values\n");
			crashBurn();
		}

		/*
		  This is rather nasty. There are many attribute tags, but some
		  can only ever have two values or so and these only exist for
		  those values. We need to check for those first.

		  There also tags which take the start portion of an attribute
		  and follow it with an inline string, such as WMLA_HREF_HTTP
		  which expands to href="http:// and should be followed by
		  the rest of the url.

		  There also many ways of doing things here. Say your attribute
		  reads :
		            href="http://www.site.com/"

		  You could compile this to :

		            WMLS_HREF WMLC_INLINE_STRING "http://www.site.com/" WMLC_INLINE_STRING_END

                            WMLS_HREF_HTTP WMLC_INLINE_STRING "www.site.com" WMLC_INLINE_STRING_END

			    WMLS_HREF WMLA_HTTP_WWW WMLC_INLINE_STRING "site.com" WMLC_INLINE_STRING_END

                            WMLS_HREF WMLA_HTTP_WWW WMLC_INLINE_STRING "site" WMLC_INLINE_STRING_END WMLA_COM

		  and all are valid. However, we should be aiming for the shortest
		  bytecode, which is the last option.

		  At the moment we assume one code for the full attribute or the
		  attribute name and an inline string as that at least lets it all
		  compile, even if it's not the most efficient.
		*/
		sprintf(buffer, "%s=\"%s\"", attributes->name, val->content);

		if((sattrNum = getSattrIndex(buffer)) >= 0) {
			fputc(sattrNum, out);
		} else if((sattrNum = getSattrIndex(attributes->name)) >= 0) {
			fputc(sattrNum, out);
			outputString(val->content);
		} else {
			fprintf(stderr, "Parse error: unknown attribute %s (%s)\n", attributes->name, buffer);
			crashBurn();
		}

		attributes = attributes->next;
	}

	fputc(WMLTC_END, out);
}

void compileTags(xmlNodePtr node)
{
	int tagVal, tagNum = -1;

	while(node) {
		if(strcmp("text", node->name) == 0) {
			outputString(node->content);
		} else {
			if((tagNum = getTagIndex(node->name)) < 0) {
				fprintf(stderr, "Parse error: unknown tag %s\n", node->name);
				crashBurn();
			}

			tagVal = tagNum;
			
			if(node->properties)
				tagVal |= WMLTC_ATTRIBUTES;
			
			if(node->children)
				tagVal |= WMLTC_CONTENT;
			
			fputc(tagVal, out);
			
			if(node->properties)
				compileAttributes(node->properties);
			
			if(node->children)
				compileTags(node->children);
			
			if(tagHasClosure(tagNum))
				fputc(WMLTC_END, out);
		}

		node = node->next;
	}
}

char *buildOutputFilename(char *oldFilename)
{
	static char newFilename[256];
	
	sprintf(newFilename, "%sc", oldFilename);

	return newFilename;
}

int main(int argc, char **argv)
{
	xmlDocPtr doc;
	char *inf, *outf;

	/*
	  This next line is just purley to shut GCC up
	*/
	inf = wml_value_attributes[0];

	if(argc == 2) {
		inf = argv[1];
		outf = buildOutputFilename(inf);
	} else if(argc == 3) {
		inf = argv[1];
		outf = argv[2];
	} else {
		fprintf(stderr, "Usage: %s file.wml [output.wmlc]\n", argv[0]);
		exit(1);
	}

	doc = xmlParseFile(inf);
	if(!doc) {
		fprintf(stderr, "Couldn't parse %s as a valid XML document\n", inf);
		exit(1);
	}

	if(!(out = fopen(outf, "w"))) {
		fprintf(stderr, "Couldn't open %s for writing\n", outf);
		exit(1);
	}

	/*
	  Set the version numbers, charset and string table length (0)
	*/
	fputc(0x01, out);
	fputc(0x04, out);
	fputc(0x6A, out);
	fputc(0x00, out);

	compileTags(doc->children);

	fclose(out);

	return 0;
}
