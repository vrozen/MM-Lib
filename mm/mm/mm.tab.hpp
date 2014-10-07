/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 0,
     ID = 258,
     PRIVATE = 259,
     IN = 260,
     OUT = 261,
     INOUT = 262,
     EXTERN = 263,
     PASSIVE = 264,
     AUTO = 265,
     USER = 266,
     START = 267,
     PUSH = 268,
     PULL = 269,
     ALL = 270,
     ANY = 271,
     FROM = 272,
     TO = 273,
     OF = 274,
     EQ = 275,
     NE = 276,
     LT = 277,
     GT = 278,
     LE = 279,
     GE = 280,
     AND = 281,
     OR = 282,
     NOT = 283,
     TRUE = 284,
     FALSE = 285,
     ACTIVE = 286,
     ASSERT = 287,
     DELETE = 288,
     ACTIVATE = 289,
     DISABLE = 290,
     ENABLE = 291,
     PREVENT = 292,
     TRIGGER = 293,
     FAIL = 294,
     VIOLATE = 295,
     MODIFY = 296,
     STEP = 297,
     AT = 298,
     MAX = 299,
     DICE = 300,
     ALIAS = 301,
     DOT = 302,
     PER = 303,
     REF = 304,
     DOT_GT = 305,
     SUB_GT = 306,
     LCURLY = 307,
     RCURLY = 308,
     COLON = 309,
     RANGE = 310,
     PERCENT = 311,
     SOURCE = 312,
     DRAIN = 313,
     POOL = 314,
     GATE = 315,
     CONVERTER = 316,
     SUB = 317,
     ADD = 318,
     MUL = 319,
     DIV = 320,
     FPVAL = 321,
     STRING = 322,
     ADDITION = 323,
     UNM = 324,
     RPAREN = 325,
     LPAREN = 326
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 49 "mm.ypp"

  MM::UINT32                         val;     //unsinged long
  MM::CHAR                         * str;     //string
  MM::Name                         * name;    //name
  MM::Program                      * program; //program
  MM::Transformation               * t;       //transformation
  MM::Vector<MM::Transformation *> * tList;   //list of transformations
  MM::Element                      * element; //element
  MM::Vector<MM::Element*>         * eList;   //list of elements
  MM::Exp                          * exp;     //expression
  MM::NodeBehavior::IO               io;      //io
  MM::NodeBehavior::When             when;    //when
  MM::NodeBehavior::Act              act;     //act
  MM::NodeBehavior::How              how;     //how



/* Line 1685 of yacc.c  */
#line 141 "mm.tab.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

