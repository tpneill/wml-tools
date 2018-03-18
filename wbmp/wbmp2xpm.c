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

int main(int argc, char **argv)
{
	FILE *in, *out;
	int c, i, j, width, height, line, block, offset;
	char of[256], *p;

	if(argc != 2) {
		fprintf(stderr, "Usage: %s <file.wbmp>\n", argv[0]);
		exit(1);
	}

	if(!(in = fopen(argv[1], "r"))) {
		fprintf(stderr, "Can't open %s for reading\n", argv[1]);
		exit(1);
	}

	strcpy(of, argv[1]);
	if((p = strrchr(of, '.'))) {
		p++;
		*(p++) = 'x';
		*(p++) = 'p';
		*(p++) = 'm';
		*p = '\0';
	} else
		strcat(of, ".xpm");

	if(!(out = fopen(of, "w"))) {
		fprintf(stderr, "Can't open %s for writing\n", of);
		exit(1);
	}

	i = getc(in);
	j = getc(in);
	width = getc(in);
	height = getc(in);

	fprintf(out, "/* XPM */\nstatic char *xpm[] = {\n");
	fprintf(out, "\"%d %d 2 1\",\n", width, height);
	fprintf(out, "\"a c #000000\",\n");
	fprintf(out, "\"b c #ffffff\",\n");

	for(line = 0; line < height; line++) {
		fputc('"', out);
		for(block = 0; block < width; block += 8) {
			c = getc(in);
			for(offset = 0; (offset<8)&&((offset+block)<width); offset++) {
				if((c & (1 << (7 - offset))))
					fputc('b', out);
				else
					fputc('a', out);
			}
		}
		fputc('"', out);
		if(line != (height - 1))
			fputc(',', out);
		fputc('\n', out);
	}

	fprintf(out, "};\n");

	fclose(out);
	fclose(in);

	return 0;
}
