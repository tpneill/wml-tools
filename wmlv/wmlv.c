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

#define TA_NONE      0
#define TA_BOLD      1
#define TA_UNDERLINE 2
#define TA_ITALIC    4

#define ANSI_RESET "\033[00m"
#define ANSI_BOLD  "\033[01m"
#define ANSI_UNDER "\033[04m"

#define USE_ANSI 1

int debug = 0;

int dumpNodeIndent = 0;

void dumpNode(xmlNodePtr node)
{
	while(node) {
		fprintf(stderr, "%*s == %s\n", dumpNodeIndent, "", node->name);
		if(node->children) {
			dumpNodeIndent += 2;
			dumpNode(node->children);
			dumpNodeIndent -= 2;
		}
		node = node->next;
	}
}

void showNode(xmlNodePtr node, int textAttr)
{
	char *attr;
	int nTextAttr = textAttr;
	int oTextAttr;

	while(node) {
		oTextAttr = nTextAttr;
		if(strcmp(node->name, "p") == 0) {
			/* Should check for alignment (attr = xmlGetProp(node, "align")) */
			if(node->content)
				puts(node->content);
		} else if(strcmp(node->name, "a") == 0) {
			if((attr = xmlGetProp(node, "name"))) {
				/* Subreference - ignore for now */
			} else if((attr = xmlGetProp(node, "href"))) {
				/* Link */
				printf("[A:%s]", attr);
				nTextAttr |= TA_UNDERLINE;
			}
		} else if(strcmp(node->name, "b") == 0) {
			nTextAttr |= TA_BOLD;
		} else if(strcmp(node->name, "img") == 0) {
			if((attr = xmlGetProp(node, "alt")))
				printf("[IMG: %s]", attr);
			else
				printf("[IMG]");
		} else if(strcmp(node->name, "br") == 0) {
			printf("\n");
			if(node->content)
				puts(node->content);
		} else if(strcmp(node->name, "text") == 0) {
			if(node->content) {
#ifdef USE_ANSI
				if((textAttr & TA_UNDERLINE))
					printf("%s", ANSI_UNDER);
				if((textAttr & TA_BOLD))
					printf("%s", ANSI_BOLD);
				printf("%s", node->content);
				if((textAttr & TA_BOLD)||(textAttr & TA_UNDERLINE))
					printf("%s", ANSI_RESET);
#else /* USE_ANSI */
				if((textAttr & TA_UNDERLINE))
					putchar('_');
				if((textAttr & TA_BOLD))
					putchar('*');
				printf("%s", node->content);
				if((textAttr & TA_BOLD))
					putchar('*');
				if((textAttr & TA_UNDERLINE))
					putchar('_');
#endif /* USE_ANSI */
			}
		} else
			printf("\n#! : %s\n", node->name);

		if(node->children)
			showNode(node->children, nTextAttr);

		nTextAttr = oTextAttr;
		node = node->next;
	}
}

void showCard(xmlNodePtr cardNode)
{
	if(!cardNode)
		printf("showCard(): cardNode == NULL\n");
	else {
		printf("------------------------------------------\n");
		printf("Card: %s (id: %s)\n", xmlGetProp(cardNode, "title"),
		       xmlGetProp(cardNode, "id"));
		printf("------------------------------------------\n\n");
		showNode(cardNode->children, TA_NONE);
		printf("\n------------------------------------------\n");
	}
}

xmlNodePtr findCard(xmlNodePtr node, char *id)
{
	xmlNodePtr card;

	while(node) {
		if(strcmp(node->name, "card") == 0) {
			if(id) {
				if(strcmp(xmlGetProp(node, "id"), id) == 0)
					return node;
			} else
				return node;
		}

		if(node->children) {
			if((card = findCard(node->children, id)))
				return card;
		}

		node = node->next;
	}

	return NULL;
}

int main(int argc, char **argv)
{
	char *filename, *card;
	xmlDocPtr doc;

	if(argc == 2) {
		filename = argv[1];
		card = NULL;
	} else if(argc == 3) {
		filename = argv[1];
		card = argv[2];
	} else {
		fprintf(stderr, "Usage: %s file.wml [card ID]\n", argv[0]);
		exit(1);
	}

	doc = xmlParseFile(filename);
	if(!doc) {
		fprintf(stderr, "Couldn't parse %s as a valid XML document\n", filename);
		exit(1);
	}

	if(debug)
		dumpNode(doc->children);

	showCard(findCard(doc->children, card));

	return 0;
}
