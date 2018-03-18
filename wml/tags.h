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
#ifndef WML_TAGS
#define WML_TAGS

#ifndef WML_TOKENS
#include <tokens.h>
#endif /* WML_TOKENS */

#define WML_TAGS_MIN WMLT_A
#define WML_TAGS_MAX WMLT_WML
static char *wml_tags[(WML_TAGS_MAX - WML_TAGS_MIN) + 1] = {
/* 0x1C */ "a",
/* 0x1D */ "td",
/* 0x1E */ "tr",
/* 0x1F */ "table",
/* 0x20 */ "p",
/* 0x21 */ "postfield",
/* 0x22 */ "anchor",
/* 0x23 */ "access",
/* 0x24 */ "b",
/* 0x25 */ "big",
/* 0x26 */ "br",
/* 0x27 */ "card",
/* 0x28 */ "do",
/* 0x29 */ "em",
/* 0x2A */ "fieldset",
/* 0x2B */ "go",
/* 0x2C */ "head",
/* 0x2D */ "i",
/* 0x2E */ "img",
/* 0x2F */ "input",
/* 0x30 */ "meta",
/* 0x31 */ "noop",
/* 0x32 */ "prev",
/* 0x33 */ "onevent",
/* 0x34 */ "optgroup",
/* 0x35 */ "option",
/* 0x36 */ "refresh",
/* 0x37 */ "select",
/* 0x38 */ "small",
/* 0x39 */ "strong",
/* 0x3A */ NULL,
/* 0x3B */ "template",
/* 0x3C */ "timer",
/* 0x3D */ "u",
/* 0x3E */ "setvar",
/* 0x3F */ "wml",
};
#define WML_TAG_DESC(a) (((a>=WML_TAGS_MIN)&&(a<=WML_TAGS_MAX))?wml_tags[(a-WML_TAGS_MIN)]:NULL)

#define WML_SATTR_MIN WMLS_ACCEPT_CHARSET
#define WML_SATTR_MAX WMLS_HTTP_EQUIV_EXPIRES
static char *wml_start_attributes[(WML_SATTR_MAX - WML_SATTR_MIN) + 1] = {
/* 0x05 */ "accept-charset",
/* 0x06 */ "align=\"bottom\"",
/* 0x07 */ "align=\"center\"",
/* 0x08 */ "align=\"middle\"",
/* 0x09 */ NULL,
/* 0x0A */ "align=\"right\"",
/* 0x0B */ "align=\"top\"",
/* 0x0C */ "alt",
/* 0x0D */ "content",
/* 0x0E */ NULL,
/* 0x0F */ "domain",
/* 0x10 */ "emptyok=\"false\"",
/* 0x11 */ "emptyok-\"true\"",
/* 0x12 */ "format",
/* 0x13 */ "height",
/* 0x14 */ "hspace",
/* 0x15 */ "ivalue",
/* 0x16 */ "iname",
/* 0x17 */ NULL,
/* 0x18 */ "label",
/* 0x19 */ "localsrc",
/* 0x1A */ "maxlength",
/* 0x1B */ "method=\"get\"",
/* 0x1C */ "method=\"post\"",
/* 0x1D */ "mode=\"nowrap\"",
/* 0x1E */ "mode=\"wrap\"",
/* 0x1F */ "multiple=\"false\"",
/* 0x20 */ "multiple=\"true\"",
/* 0x21 */ "name",
/* 0x22 */ "newcontext=\"false\"",
/* 0x23 */ "newcontext=\"true\"",
/* 0x24 */ "onpick",
/* 0x25 */ "onenterbackward",
/* 0x26 */ "onenterforward",
/* 0x27 */ "ontimer",
/* 0x28 */ "optional=\"false\"",
/* 0x29 */ "optional=\"true\"",
/* 0x2A */ "path",
/* 0x2B */ NULL,
/* 0x2C */ NULL,
/* 0x2D */ NULL,
/* 0x2E */ "scheme",
/* 0x2F */ "sendreferer=\"false\"",
/* 0x30 */ "sendreferer=\"true\"",
/* 0x31 */ "size",
/* 0x32 */ "src",
/* 0x33 */ "ordered=\"true\"",
/* 0x34 */ "ordered=\"false\"",
/* 0x35 */ "tabindex",
/* 0x36 */ "title",
/* 0x37 */ "type",
/* 0x38 */ "type=\"accept\"",
/* 0x39 */ "type=\"delete\"",
/* 0x3A */ "type=\"help\"",
/* 0x3B */ "type=\"password\"",
/* 0x3C */ "type=\"onpick\"",
/* 0x3D */ "type=\"onenterbackward\"",
/* 0x3E */ "type=\"onenterforward\"",
/* 0x3F */ "type=\"ontimer\"",
/* 0x40 */ NULL,
/* 0x41 */ NULL,
/* 0x42 */ NULL,
/* 0x43 */ NULL,
/* 0x44 */ NULL,
/* 0x45 */ NULL,
/* 0x46 */ "type=\"prev\"",
/* 0x47 */ "type=\"reset\"",
/* 0x48 */ "type=\"text\"",
/* 0x49 */ "type=\"vnd\"",
/* 0x4A */ "href",
/* 0x4B */ "href=\"http://",
/* 0x4C */ "href=\"https://",
/* 0x4D */ "value",
/* 0x4E */ "vspace",
/* 0x4F */ "width",
/* 0x50 */ "xml:lang",
/* 0x51 */ NULL,
/* 0x52 */ "align",
/* 0x53 */ "columns",
/* 0x54 */ "class",
/* 0x55 */ "id",
/* 0x56 */ "forua=\"false\"",
/* 0x57 */ "forua=\"true\"",
/* 0x58 */ "src=\"http://",
/* 0x59 */ "src=\"https://",
/* 0x5A */ "http-equiv",
/* 0x5B */ "http-equiv=\"Content-Type\"",
/* 0x5C */ "content=\"application/vnd.wap.wmlc;charset=",
/* 0x5D */ "http-equiv=\"Expires\""
};
#define WML_SATTR_DESC(a) (((a>=WML_SATTR_MIN)&&(a<=WML_SATTR_MAX))?wml_start_attributes[(a-WML_SATTR_MIN)]:NULL)

#define WML_VATTR_MIN WMLA_COM
#define WML_VATTR_MAX WMLA_WWW
static char *wml_value_attributes[(WML_VATTR_MAX - WML_VATTR_MIN) + 1] = {
/* 0x85 */ ".com/",
/* 0x86 */ ".edu/",
/* 0x87 */ ".net/",
/* 0x88 */ ".org/",
/* 0x89 */ "accept",
/* 0x8A */ "bottom",
/* 0x8B */ "clear",
/* 0x8C */ "delete",
/* 0x8D */ "help",
/* 0x8E */ "http://",
/* 0x8F */ "http://www.",
/* 0x90 */ "https://",
/* 0x91 */ "https://www.",
/* 0x92 */ NULL,
/* 0x93 */ "middle",
/* 0x94 */ "nowrap",
/* 0x95 */ "onpick",
/* 0x96 */ "onenterbackward",
/* 0x97 */ "onenterforward",
/* 0x98 */ "ontimer",
/* 0x99 */ "options",
/* 0x9A */ "password",
/* 0x9B */ "reset",
/* 0x9C */ NULL,
/* 0x9D */ "text",
/* 0x9E */ "top",
/* 0x9F */ "unknown",
/* 0xA0 */ "wrap",
/* 0xA1 */ "www.",
};
#define WML_VATTR_DESC(a) (((a>=WML_VATTR_MIN)&&(a<=WML_VATTR_MAX))?wml_value_attributes[(a-WML_VATTR_MIN)]:NULL)

#endif /* WML_TAGS */
