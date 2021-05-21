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

#ifndef YY_YY_LANGUAGE_TAB_H_INCLUDED
# define YY_YY_LANGUAGE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    POSNUMBER = 259,
    COMMA = 260,
    SEMICOL = 261,
    QUE = 262,
    VERT = 263,
    COL = 264,
    LB = 265,
    RB = 266,
    LP = 267,
    RP = 268,
    EQ = 269,
    LT = 270,
    GT = 271,
    AND = 272,
    OR = 273,
    NOT = 274,
    START = 275,
    END = 276,
    IF = 277,
    IFEND = 278,
    ELSE = 279,
    ELSEND = 280,
    ADD = 281,
    SUBTRACT = 282,
    MOD = 283,
    MULTIPLY = 284,
    DIVIDE = 285,
    POINT = 286,
    RECTANGLE = 287,
    ASSIGN = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 28 "language.y" /* yacc.c:1909  */

    int value;
    char* id;
    struct Node *node;
    struct Constant *constant;
    struct Identifier * identifier;

#line 96 "language.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LANGUAGE_TAB_H_INCLUDED  */
