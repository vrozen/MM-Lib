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
     PASSIVE = 263,
     AUTO = 264,
     USER = 265,
     START = 266,
     PUSH = 267,
     PULL = 268,
     ALL = 269,
     ANY = 270,
     FROM = 271,
     TO = 272,
     OF = 273,
     EQ = 274,
     NE = 275,
     LT = 276,
     GT = 277,
     LE = 278,
     GE = 279,
     AND = 280,
     OR = 281,
     NOT = 282,
     TRUE = 283,
     FALSE = 284,
     ACTIVE = 285,
     ASSERT = 286,
     DELETE = 287,
     ACTIVATE = 288,
     DISABLE = 289,
     ENABLE = 290,
     PREVENT = 291,
     TRIGGER = 292,
     FAIL = 293,
     VIOLATE = 294,
     MODIFY = 295,
     STEP = 296,
     AT = 297,
     MAX = 298,
     DICE = 299,
     ALIAS = 300,
     DOT = 301,
     PER = 302,
     REF = 303,
     DOT_GT = 304,
     SUB_GT = 305,
     LCURLY = 306,
     RCURLY = 307,
     COLON = 308,
     RANGE = 309,
     PERCENT = 310,
     SOURCE = 311,
     DRAIN = 312,
     POOL = 313,
     GATE = 314,
     CONVERTER = 315,
     SUB = 316,
     ADD = 317,
     MUL = 318,
     DIV = 319,
     FPVAL = 320,
     STRING = 321,
     ADDITION = 322,
     UNM = 323,
     RPAREN = 324,
     LPAREN = 325
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
#line 140 "mm.tab.hpp"
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

