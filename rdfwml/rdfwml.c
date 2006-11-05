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

#ifdef CGI_BIN
void wmlError(char *error)
{
	puts("<?xml version=\"1.0\"?>");
	puts("<!DOCTYPE wml PUBLIC \"-//WAPFORUM//DTD WML 1.1//EN\" \"http://www.wapforum.org/DTD/wml_1.1.xml\">");
	puts("<wml>");
	puts("  <template>");
	puts("    <do type=\"accept\" label=\"Back\">");
	puts("      <prev/>");
	puts("    </do>");
	puts("  </template>");
	puts("  <card id=\"init\" title=\"Error\">");
	printf("    <p>%s</p>\n", error);
	puts("  </card>");
	puts("</wml>");
}
#endif /* CGI_BIN */

void outputString(char *str)
{
	while(*str != '\0') {
		switch(*str) {
			case '$':
				printf("$$");
				break;
			case '<':
				printf("&lt;");
				break;
			case '>':
				printf("&gt;");
				break;
			default:
				putchar(*str);
				break;
		}
		str++;
	}
}

void parseChannel(xmlNodePtr channel)
{
	xmlNodePtr node, on;

	for(node = channel; node != NULL; node = node->next) {
		if(strcasecmp("title", node->name) == 0) {
			on = node->children;
			if(strcasecmp("text", on->name) == 0)
				printf("    <p><b>%s</b></p>\n", on->content);
		}
	}
}

void parseHeadline(xmlNodePtr item)
{
	xmlNodePtr node, on;

	for(node = item; node != NULL; node = node->next) {
		if(strcasecmp("title", node->name) == 0) {
			on = node->children;
			if(strcasecmp("text", on->name) == 0)
				printf("    <p align=\"center\">----</p>\n");
				printf("    <p>");
				outputString(on->content);
				printf("</p>\n");
		}
	}

}

void parseRdf(xmlNodePtr rdf)
{
	xmlNodePtr node;
	xmlNodePtr basenode;
	xmlNodePtr subnode;

	puts("<?xml version=\"1.0\"?>");
	puts("<!DOCTYPE wml PUBLIC \"-//WAPFORUM//DTD WML 1.1//EN\" \"http://www.wapforum.org/DTD/wml_1.1.xml\">");
	puts("<wml>");
	puts("  <template>");
	puts("    <do type=\"accept\" label=\"Back\">");
	puts("      <prev/>");
	puts("    </do>");
	puts("  </template>");
	puts("  <card id=\"init\" title=\"Headlines\">");

	basenode = rdf;
	/* Skip everything which is not an element node */
	while (basenode->type != XML_ELEMENT_NODE) {
	  basenode = basenode->next;
	}

	for (node = basenode->children; node != NULL; node = node->next) {
	  if(strcasecmp("channel", node->name) == 0) {
	    parseChannel(node->children);
	    for (subnode = node->children; subnode != NULL; subnode = subnode->next) {
	      /* RSS has a different tree structure */
	      if (strcasecmp("item", subnode->name) == 0) {
		parseHeadline(subnode->children);
	      }
	    }
	  } else {
	    if (strcasecmp("item", node->name) == 0) {
	      parseHeadline(node->children);
	    }
	  }
	}

	puts("  </card>");
	puts("</wml>");
}

int main(int argc, char **argv)
{
	xmlDocPtr rdf;
	char *filename;
#ifdef CGI_BIN

	printf("Content-type: text/vnd.wap.wml\n\n");

	if(!(filename = getenv("QUERY_STRING"))) {
		wmlError("No channel file requested.");
		exit(0);
	}

	if(strchr(filename, '/') || strchr(filename, '%')) {
		wmlError("No channel file requested.");
		exit(0);
	}
#else
	if(argc != 2) {
		fprintf(stderr, "Usage: %s file.rdf\n", argv[0]);
		exit(1);
	}

	filename = argv[1];
#endif /* CGI_BIN */

	rdf = xmlParseFile(filename);
	if(!rdf) {
#ifdef CGI_BIN
		wmlError("Error parsing channel file.");
		exit(0);
#else
		fprintf(stderr, "Couldn't parse %s as a valid XML document\n", argv[1]);
		exit(1);
#endif /* CGI_BIN */
	}

	parseRdf(rdf->children);

	exit(0);
}
