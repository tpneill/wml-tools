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
#include <string.h>
#define WML_NO_CLOSURES
#include <wml/tokens.h>
#include <wml/tags.h>
#undef WML_NO_CLOSURES

FILE *in;
FILE *out;

int depth;

unsigned char *stringTable;
int stringTableLength;

void crashBurn(void)
{
	fflush(out);
	fprintf(stderr, "\nFATAL: Decompile halted at byte %lu.\n", ftell(in));
	fclose(in);
	fclose(out);
	exit(1);
}

inline char *stringTableRef(int idx)
{
	return (idx<=stringTableLength)?(&stringTable[idx]):NULL;
}

void parseString(void)
{
	int input;

	while((input = getc(in)) != WMLC_INLINE_STRING_END)
		fputc(input, out);
}

void parseValueAttributes(void)
{
        int input, ref;
        char *vattr, *st;

        while(1==1) {
                input = getc(in);

		if(input == WMLG_STR_T) {
			ref = getc(in);
			if((st = stringTableRef(ref))) {
				fprintf(out, "%s", st);
			} else {
				fprintf(stderr, "Parse error: string table entry %d referenced but invalid.\n",
					ref);
			}
		} else if((input == WMLG_EXT_T_2)||(input == WMLG_EXT_T_1)||(input == WMLG_EXT_T_0)) {
			ref = getc(in);
			if((st = stringTableRef(ref))) {
				fprintf(out, "$(%s)", st);
			} else {
				fprintf(stderr, "Parse error: string table entry %d referenced but invalid.\n",
					ref);
			}
		} else if((input == WMLG_EXT_I_2)||(input == WMLG_EXT_I_1)||(input == WMLG_EXT_I_0)) {
			fprintf(out, "$(");
			parseString();
			fprintf(out, ")");
		} else if(input == WMLC_INLINE_STRING) {
                        parseString();
                } else if((vattr = WML_VATTR_DESC(input))) {
                        fputs(vattr, out);
                } else {
                        ungetc(input, in);
                        return;
                }
        }
}


void parseAttributes(void)
{
	int input, ref;
	char *attr, *st;

	while((input = getc(in)) != WMLTC_END) {
		if(input == WMLG_STR_T) {
			ref = getc(in);
			if((st = stringTableRef(ref))) {
				fprintf(out, "%s", st);
			} else {
				fprintf(stderr, "Parse error: string table entry %d referenced but invalid.\n",
					ref);
				crashBurn();
			}
		} else {
			if(!(attr = WML_SATTR_DESC(input))) {
				fprintf(stderr, "Parse error: expected attribute, got 0x%x.\n", input);
				crashBurn();
			}
			
			if(!(strchr(attr, '"'))) {
				fprintf(out, " %s=\"", attr);
				parseValueAttributes();
				fprintf(out, "\"");
			} else {
				fprintf(out, " %s", attr);
				if(attr[strlen(attr)-1] != '"') {
					parseValueAttributes();
					fprintf(out, "\"");
				}
			}
		}
	}
}
		

void parseTags(void)
{
	int input, tag, content, attributes, ref;
	char *st;

	while((input = getc(in)) != EOF) {
		/*
		  Codes we can come across at this point could be :

		    * WMLC_INLINE_STRING - Inline strings
		    * WMLG_STR_T - String table references
		    * WMLG_EXT_T_? - Inline variables, a bit like environment variables I think
		    * WMLG_EXT_I_? - Inline variables but named as inline strings
		    * Tags
		    * (there might be more, but I don't think so)

		  We need to check for all of them
		*/

		/* Case 1: An inline string. Just print it out. */
		if(input == WMLC_INLINE_STRING) {
			fprintf(out, "%*s", (depth * 2), "");
			parseString();
			fputc('\n', out);

		/* Case 2: A string table reference. Find it and print it. */
		} else if(input == WMLG_STR_T) {
			ref = getc(in);
			if((st = stringTableRef(ref))) {
				fprintf(out, "%*s%s\n", (depth * 2), "", st);
			} else {
				fprintf(stderr, "Parse error: string table entry %d referenced but invalid.\n",
					ref);
			}

		/* Case 3: A variable reference from the string table. Find, format and print. */
		} else if((input == WMLG_EXT_T_2)||(input == WMLG_EXT_T_1)||(input == WMLG_EXT_T_0)) {
			ref = getc(in);
			if((st = stringTableRef(ref))) {
				fprintf(out, "%*s$(%s)\n", (depth * 2), "", st);
			} else {
				fprintf(stderr, "Parse error: string table entry %d referenced but invalid.\n",
					ref);
			}

		/* Case 4: A variable reference as an inline string. Format and print. */
		} else if((input == WMLG_EXT_I_2)||(input == WMLG_EXT_I_1)||(input == WMLG_EXT_I_0)) {
			fprintf(out, "%*s$(", (depth * 2), "");
			parseString();
			fprintf(out, ")\n");

		/* Case 5: A tag. Find out what one and decode. */
		} else {
			tag = (input & WMLTC_TAG_VALUE);
			content = (input & WMLTC_CONTENT);
			attributes = (input & WMLTC_ATTRIBUTES);

			if(input == WMLTC_END)
				return;

			if(!(WML_TAG_DESC(tag))) {
				fprintf(stderr, "Parse error: expected tag, got 0x%x (0x%x).\n",
					input, tag);
				crashBurn();
			}
			
			fprintf(out, "%*s<%s", (depth * 2), "", WML_TAG_DESC(tag));
			
			if(attributes)
				parseAttributes();

			if(content) {
				fprintf(out, ">\n");
				depth++;
				parseTags();
				depth--;
				fprintf(out, "%*s</%s>\n", (depth * 2), "", WML_TAG_DESC(tag));
			} else
				fprintf(out, "/>\n");

		}
	}
}

char *buildNewFilename(char *old)
{
	static char str[256];

	strcpy(str, old);
	if(str[strlen(old) - 1] == 'c')
		str[strlen(old) - 1] = '\0';
	else
		strcat(str, ".wml");

	return str;
}

int main(int argc, char **argv)
{
	int wbxmlVersion, wmlVersion, charset, i, j;
	char *inf, *outf;

	if(argc == 2) {
		inf = argv[1];
		outf = buildNewFilename(inf);
	} else if(argc == 3) {
		inf = argv[1];
		outf = argv[2];
	} else {
		fprintf(stderr, "Usage: %s file.wmlc [output.wml]\n", argv[0]);
		exit(1);
	}

	if(!(in = fopen(inf, "r"))) {
		fprintf(stderr, "Can't open %s for reading\n", inf);
		exit(1);
	}

	if(!(out = fopen(outf, "w"))) {
		fprintf(stderr, "Can't open %s for writing\n", outf);
		exit(1);
	}

	depth = 0;
	wbxmlVersion = getc(in);
	wmlVersion = getc(in);

	if((wbxmlVersion != 1) || (wmlVersion != 4)) {
		fprintf(stderr, "Wrong version numbers (got %d %d, expected %d %d)\n", wbxmlVersion, wmlVersion, 1, 4);
		crashBurn();
	}

	/*
	  I don't have the charset codes, so I don't know how to handle this.
	  Just read it and hope for UTF-8
	*/
	charset = getc(in);

	if((stringTableLength = getc(in)) > 0) {
		if(!(stringTable = (char*)malloc(stringTableLength))) {
			fprintf(stderr, "String table allocation failed\n");
			crashBurn();
		}

		for(i = 0; i < stringTableLength; i++)
			stringTable[i] = getc(in);
	}

	/*
	  We should now expect to start parsing tags, so spit out the XML
	  and DTD headers.
	*/
	fputs("<?xml version=\"1.0\"?>\n", out);
        fputs("<!DOCTYPE wml PUBLIC \"-//WAPFORUM//DTD WML 1.1//EN\" \"http://www.wapforum.org/DTD/wml_1.1.xml\">\n\n", out);

	parseTags();

	return 0;
}
