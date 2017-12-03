/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_LEXER_THEME_PARSER_H_INCLUDED
# define YY_YY_LEXER_THEME_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 35 "lexer/theme-parser.y" /* glr.c:197  */

#include "theme.h"
#include "xrmoptions.h"
#include "css-colors.h"

typedef struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
  char *filename;
} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1 /* alert the parser that we have our own definition */

# define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                 \
      if (N)                                                           \
        {                                                              \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;       \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;     \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;        \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;      \
          (Current).filename     = YYRHSLOC (Rhs, 1).filename;         \
        }                                                              \
      else                                                             \
        { /* empty RHS */                                              \
          (Current).first_line   = (Current).last_line   =             \
            YYRHSLOC (Rhs, 0).last_line;                               \
          (Current).first_column = (Current).last_column =             \
            YYRHSLOC (Rhs, 0).last_column;                             \
          (Current).filename  = NULL;                        /* new */ \
        }                                                              \
    while (0)

#line 79 "lexer/theme-parser.h" /* glr.c:197  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_END = 0,
    T_ERROR = 1,
    T_ERROR_PROPERTY = 2,
    T_ERROR_SECTION = 3,
    T_ERROR_NAMESTRING = 4,
    T_ERROR_DEFAULTS = 5,
    T_ERROR_INCLUDE = 6,
    T_ERROR_ARGB_SPEC = 7,
    T_INT = 258,
    T_DOUBLE = 259,
    T_STRING = 260,
    T_PROP_NAME = 261,
    T_COLOR_NAME = 262,
    T_NAME_ELEMENT = 263,
    T_BOOLEAN = 264,
    T_COLOR = 265,
    T_LINK = 266,
    T_ELEMENT = 267,
    T_POS_CENTER = 268,
    T_POS_EAST = 269,
    T_POS_WEST = 270,
    T_POS_NORTH = 271,
    T_POS_SOUTH = 272,
    T_NONE = 273,
    T_BOLD = 274,
    T_ITALIC = 275,
    T_UNDERLINE = 276,
    T_STRIKETHROUGH = 277,
    T_SMALLCAPS = 278,
    T_DASH = 279,
    T_SOLID = 280,
    T_UNIT_PX = 281,
    T_UNIT_EM = 282,
    T_UNIT_CH = 283,
    T_UNIT_PERCENT = 284,
    T_ANGLE_DEG = 285,
    T_ANGLE_GRAD = 286,
    T_ANGLE_RAD = 287,
    T_ANGLE_TURN = 288,
    ORIENTATION_HORI = 289,
    ORIENTATION_VERT = 290,
    T_COL_RGBA = 291,
    T_COL_HSL = 292,
    T_COL_HWB = 293,
    T_COL_CMYK = 294,
    T_PARENT_LEFT = 295,
    T_PARENT_RIGHT = 296,
    T_COMMA = 297,
    T_OPTIONAL_COMMA = 298,
    T_FORWARD_SLASH = 299,
    T_PERCENT = 300,
    T_LIST_OPEN = 301,
    T_LIST_CLOSE = 302,
    T_BOPEN = 303,
    T_BCLOSE = 304,
    T_PSEP = 305,
    T_PCLOSE = 306,
    T_NSEP = 307,
    T_SSEP = 308,
    T_NAME_PREFIX = 309,
    T_WHITESPACE = 310,
    T_PDEFAULTS = 311,
    T_CONFIGURATION = 312,
    T_COLOR_TRANSPARENT = 313,
    T_INHERIT = 314
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 137 "lexer/theme-parser.y" /* glr.c:197  */

	int           ival;
	double        fval;
    char          *sval;
    int           bval;
    WindowLocation wloc;
    ThemeColor    colorval;
    ThemeWidget   *theme;
    GList         *list;
    Property      *property;
    GHashTable    *property_list;
    RofiDistance      distance;

#line 173 "lexer/theme-parser.h" /* glr.c:197  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (const char *what);

#endif /* !YY_YY_LEXER_THEME_PARSER_H_INCLUDED  */
