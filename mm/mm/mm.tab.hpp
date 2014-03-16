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
     ID = 258,
     NEWLINE = 259,
     PRIVATE = 260,
     IN = 261,
     OUT = 262,
     INOUT = 263,
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
     PRINT = 276,
     NE = 277,
     LT = 278,
     GT = 279,
     LE = 280,
     GE = 281,
     AND = 282,
     OR = 283,
     NOT = 284,
     TRUE = 285,
     FALSE = 286,
     ACTIVE = 287,
     ASSERT = 288,
     DELETE = 289,
     ACTIVATE = 290,
     MODIFY = 291,
     STEP = 292,
     SIGNAL = 293,
     AT = 294,
     MAX = 295,
     DICE = 296,
     ALIAS = 297,
     DOT = 298,
     PER = 299,
     REF = 300,
     DOT_GT = 301,
     SUB_GT = 302,
     LCURLY = 303,
     RCURLY = 304,
     COMMA = 305,
     COLON = 306,
     ATSIGN = 307,
     RANGE = 308,
     PERCENT = 309,
     SOURCE = 310,
     DRAIN = 311,
     POOL = 312,
     GATE = 313,
     CONVERTER = 314,
     SUB = 315,
     ADD = 316,
     MUL = 317,
     DIV = 318,
     FPVAL = 319,
     STRING = 320,
     ADDITION = 321,
     SUBSUB = 322,
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
#line 139 "mm.tab.hpp"
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

