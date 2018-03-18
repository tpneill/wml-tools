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
#ifndef WML_TOKENS
#define WML_TOKENS

/* Global tokens */

#define WMLG_STR_I       0x03
#define WMLG_LITERAL     0x04
#define WMLG_EXT_I_0     0x40
#define WMLG_EXT_I_1     0x41
#define WMLG_EXT_I_2     0x42
#define WMLG_EXT_T_0     0x80
#define WMLG_EXT_T_1     0x81
#define WMLG_EXT_T_2     0x82
#define WMLG_STR_T       0x83
#define WMLG_EXT_0       0xC0 /* Reserved */
#define WMLG_EXT_1       0xC1 /* Reserved */
#define WMLG_EXT_2       0xC2 /* Reserved */

/* Tag tokens */

#define WMLT_A          0x1C
#define WMLT_ANCHOR     0x22
#define WMLT_ACCESS     0x23
#define WMLT_B          0x24
#define WMLT_BIG        0x25
#define WMLT_BR         0x26
#define WMLT_CARD       0x27
#define WMLT_DO         0x28
#define WMLT_EM         0x29
#define WMLT_FIELDSET   0x2A
#define WMLT_GO         0x2B
#define WMLT_HEAD       0x2C
#define WMLT_I          0x2D
#define WMLT_IMG        0x2E
#define WMLT_INPUT      0x2F
#define WMLT_META       0x30
#define WMLT_NOOP       0x31
#define WMLT_P          0x20
#define WMLT_POSTFIELD  0x21
#define WMLT_PREV       0x32
#define WMLT_ONEVENT    0x33
#define WMLT_OPTGROUP   0x34
#define WMLT_OPTION     0x35
#define WMLT_REFRESH    0x36
#define WMLT_SELECT     0x37
#define WMLT_SETVAR     0x3E
#define WMLT_SMALL      0x38
#define WMLT_STRONG     0x39
#define WMLT_TABLE      0x1F
#define WMLT_TD         0x1D
#define WMLT_TEMPLATE   0x3B
#define WMLT_TIMER      0x3C
#define WMLT_TR         0x1E
#define WMLT_U          0x3D
#define WMLT_WML        0x3F

#define WMLTC_ATTRIBUTES 0x80
#define WMLTC_CONTENT    0x40
#define WMLTC_END        0x01
#define WMLTC_TAG_VALUE  (~(WMLTC_ATTRIBUTES|WMLTC_CONTENT))

/* Attribute start tokens */

#define WMLS_ACCEPT_CHARSET          0x05
#define WMLS_ALIGN                   0x52
#define WMLS_ALIGN_BOTTOM            0x06
#define WMLS_ALIGN_CENTER            0x07
#define WMLS_ALIGN_MIDDLE            0x08
#define WMLS_ALIGN_RIGHT             0x0A
#define WMLS_ALIGN_TOP               0x0B
#define WMLS_ALT                     0x0C
#define WMLS_CLASS                   0x54
#define WMLS_COLUMNS                 0x53
#define WMLS_CONTENT                 0x0D
#define WMLS_CONTENT_WMLC            0x5C
#define WMLS_DOMAIN                  0x0F
#define WMLS_EMPTYOK_FALSE           0x10
#define WMLS_EMPTYOK_TRUE            0x11
#define WMLS_FORMAT                  0x12
#define WMLS_FORUA_FALSE             0x56
#define WMLS_FORUA_TRUE              0x57
#define WMLS_HEIGHT                  0x13
#define WMLS_HREF                    0x4A
#define WMLS_HREF_HTTP               0x4B
#define WMLS_HREF_HTTPS              0x4C
#define WMLS_HSPACE                  0x14
#define WMLS_HTTP_EQUIV              0x5A
#define WMLS_HTTP_EQUIV_CONTENT_TYPE 0x5B
#define WMLS_HTTP_EQUIV_EXPIRES      0x5D
#define WMLS_ID                      0x55
#define WMLS_IVALUE                  0x15
#define WMLS_INAME                   0x16
#define WMLS_LABEL                   0x18
#define WMLS_LOCALSRC                0x19
#define WMLS_MAXLENGTH               0x1A
#define WMLS_METHOD_GET              0x1B
#define WMLS_METHOD_POST             0x1C
#define WMLS_MODE_NOWRAP             0x1D
#define WMLS_MODE_WRAP               0x1E
#define WMLS_MULTIPLE_FALSE          0x1F
#define WMLS_MULTIPLE_TRUE           0x20
#define WMLS_NAME                    0x21
#define WMLS_NEWCONTEXT_FALSE        0x22
#define WMLS_NEWCONTEXT_TRUE         0x23
#define WMLS_ONENTERBACKWARD         0x25
#define WMLS_ONENTERFORWARD          0x26
#define WMLS_ONPICK                  0x24
#define WMLS_ONTIMER                 0x27
#define WMLS_OPTIONAL_FALSE          0x28
#define WMLS_OPTIONAL_TRUE           0x29
#define WMLS_PATH                    0x2A
#define WMLS_SCHEME                  0x2E
#define WMLS_SENDREFERER_FALSE       0x2F
#define WMLS_SENDREFERER_TRUE        0x30
#define WMLS_SIZE                    0x31
#define WMLS_SRC                     0x32
#define WMLS_SRC_HTTP                0x58
#define WMLS_SRC_HTTPS               0x59
#define WMLS_ORDERED_TRUE            0x33
#define WMLS_ORDERED_FALSE           0x34
#define WMLS_TABINDEX                0x35
#define WMLS_TITLE                   0x36
#define WMLS_TYPE                    0x37
#define WMLS_TYPE_ACCEPT             0x38
#define WMLS_TYPE_DELETE             0x39
#define WMLS_TYPE_HELP               0x3A
#define WMLS_TYPE_PASSWORD           0x3B
#define WMLS_TYPE_ONPICK             0x3C
#define WMLS_TYPE_ONENTERBACKWARD    0x3D
#define WMLS_TYPE_ONENTERFORWARD     0x3E
#define WMLS_TYPE_ONTIMER            0x3F
#define WMLS_TYPE_PREV               0x46
#define WMLS_TYPE_RESET              0x47
#define WMLS_TYPE_TEXT               0x48
#define WMLS_TYPE_VND                0x49
#define WMLS_VALUE                   0x4D
#define WMLS_VSPACE                  0x4E
#define WMLS_WIDTH                   0x4F
#define WMLS_XML_LANG                0x50

/* Attribute value tokens */

#define WMLA_COM              0x85
#define WMLA_EDU              0x86
#define WMLA_NET              0x87
#define WMLA_ORG              0x88
#define WMLA_ACCEPT           0x89
#define WMLA_BOTTOM           0x8A
#define WMLA_CLEAR            0x8B
#define WMLA_DELETE           0x8C
#define WMLA_HELP             0x8D
#define WMLA_HTTP             0x8E
#define WMLA_HTTP_WWW         0x8F
#define WMLA_HTTPS            0x90
#define WMLA_HTTPS_WWW        0x91
#define WMLA_MIDDLE           0x93
#define WMLA_NOWRAP           0x94
#define WMLA_ONENTERBACKWARD  0x96
#define WMLA_ONENTERFORWARD   0x97
#define WMLA_ONPICK           0x95
#define WMLA_ONTIMER          0x98
#define WMLA_OPTIONS          0x99
#define WMLA_PASSWORD         0x9A
#define WMLA_RESET            0x9B
#define WMLA_TEXT             0x9D
#define WMLA_TOP              0x9E
#define WMLA_UNKNOWN          0x9F
#define WMLA_WRAP             0xA0
#define WMLA_WWW              0xA1

/* Misc */

#define WMLC_INLINE_STRING     0x03
#define WMLC_INLINE_STRING_END 0x00

#ifdef WML_NO_CLOSURES
/* No closure tags */
static int wml_no_closure_tags[] = {
	WMLT_BR, WMLT_NOOP, WMLT_PREV, WMLT_IMG, WMLT_META, WMLT_TIMER, WMLT_SETVAR, -1
};
#endif /* WML_NO_CLOSURES */

#endif /* WML_TOKENS */
