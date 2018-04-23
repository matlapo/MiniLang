/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_TAB_C_INCLUDED
# define YY_YY_PARSER_TAB_C_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 35 "tiny.y" /* yacc.c:1915  */

	#include "tree.h"

#line 48 "parser.tab.c" /* yacc.c:1915  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tINTVAL = 258,
    tFLOATVAL = 259,
    tBOOLVAL = 260,
    tIDENTIFIER = 261,
    tSTRINGVAL = 262,
    tOR = 263,
    tAND = 264,
    tNEQ = 265,
    tEQ = 266,
    tVAR = 267,
    tINT = 268,
    tFLOAT = 269,
    tSTRING = 270,
    tBOOLEAN = 271,
    tWHILE = 272,
    tIF = 273,
    tELSE = 274,
    tREAD = 275,
    tPRINT = 276
  };
#endif
/* Tokens.  */
#define tINTVAL 258
#define tFLOATVAL 259
#define tBOOLVAL 260
#define tIDENTIFIER 261
#define tSTRINGVAL 262
#define tOR 263
#define tAND 264
#define tNEQ 265
#define tEQ 266
#define tVAR 267
#define tINT 268
#define tFLOAT 269
#define tSTRING 270
#define tBOOLEAN 271
#define tWHILE 272
#define tIF 273
#define tELSE 274
#define tREAD 275
#define tPRINT 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 43 "tiny.y" /* yacc.c:1915  */

	int intval;
    float floatval;
	char *string;
    EXP *expval;
    STM *stmtval;
    STMS *stmtsval;
    DECL *declval;
    DECLS *declsval;
    PROG *progval;

#line 114 "parser.tab.c" /* yacc.c:1915  */
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


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_C_INCLUDED  */
