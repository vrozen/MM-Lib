/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 34 "mm.ypp"

  #include "YYLTYPE.h"
  #include "mm.h"
  
  //FIXME: globals should be instance data
  //TODO: add a Parser abstraction (a.k.a. re-entrant parsing)
  extern MM::Machine * mm;      //TODO: each machine has a parser
  extern MM::Program * program; //TODO: attribute of parser
  extern int yylineno;          //TODO: attribute of parser
  extern int yycolumn;          //TODO: attribute of parser
  int yylex();                  //TODO: method of parser
  void yyerror(char * s);       //TODO: method of parser


/* Line 189 of yacc.c  */
#line 87 "mm.tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
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



/* Line 214 of yacc.c  */
#line 211 "mm.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 236 "mm.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   290

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNRULES -- Number of states.  */
#define YYNSTATES  125

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   325

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    15,    18,    19,
      27,    35,    43,    54,    63,    67,    70,    76,    82,    87,
      93,    96,    98,   100,   102,   104,   105,   107,   109,   111,
     113,   114,   116,   118,   119,   121,   123,   124,   127,   128,
     131,   132,   137,   138,   141,   142,   145,   146,   149,   150,
     154,   158,   162,   166,   170,   174,   178,   182,   186,   190,
     194,   198,   201,   204,   207,   211,   215,   219,   221,   223,
     225,   227,   230,   232,   234,   235
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      72,     0,    -1,    73,    -1,    73,    74,    -1,    -1,    75,
      36,    -1,    75,    37,    -1,    75,    76,    -1,    -1,    77,
      78,    79,    80,    55,    88,    84,    -1,    77,    78,    79,
      80,    56,    88,    84,    -1,    77,    78,    79,    80,    58,
      88,    84,    -1,    77,    78,    79,    80,    57,    88,    84,
      81,    82,    83,    -1,    77,    78,    79,    80,    59,    88,
      85,    86,    -1,    77,    45,    88,    -1,    88,    88,    -1,
      88,    43,    87,    46,    88,    -1,    88,    60,    87,    47,
      88,    -1,    88,    48,    75,    49,    -1,    33,    88,    51,
      87,    65,    -1,    34,    88,    -1,     5,    -1,     6,    -1,
       7,    -1,     8,    -1,    -1,     9,    -1,    10,    -1,    11,
      -1,    12,    -1,    -1,    14,    -1,    13,    -1,    -1,    16,
      -1,    15,    -1,    -1,    39,    64,    -1,    -1,    40,    64,
      -1,    -1,    66,    70,    87,    69,    -1,    -1,    19,    88,
      -1,    -1,    17,    88,    -1,    -1,    18,    88,    -1,    -1,
      87,    27,    87,    -1,    87,    28,    87,    -1,    87,    24,
      87,    -1,    87,    26,    87,    -1,    87,    23,    87,    -1,
      87,    25,    87,    -1,    87,    22,    87,    -1,    87,    20,
      87,    -1,    87,    61,    87,    -1,    87,    60,    87,    -1,
      87,    62,    87,    -1,    87,    63,    87,    -1,    68,    87,
      -1,    29,    87,    -1,    87,    54,    -1,    64,    44,    64,
      -1,    70,    87,    69,    -1,    64,    53,    64,    -1,    64,
      -1,    30,    -1,    31,    -1,    15,    -1,    32,    88,    -1,
      42,    -1,    88,    -1,    -1,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   112,   112,   116,   117,   121,   122,   125,   126,   130,
     131,   132,   133,   135,   137,   138,   139,   142,   145,   146,
     147,   154,   155,   156,   157,   158,   162,   163,   164,   165,
     166,   170,   171,   172,   176,   177,   178,   182,   183,   187,
     188,   192,   193,   197,   198,   202,   203,   207,   208,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   241
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "NEWLINE", "PRIVATE", "IN", "OUT",
  "INOUT", "PASSIVE", "AUTO", "USER", "START", "PUSH", "PULL", "ALL",
  "ANY", "FROM", "TO", "OF", "EQ", "PRINT", "NE", "LT", "GT", "LE", "GE",
  "AND", "OR", "NOT", "TRUE", "FALSE", "ACTIVE", "ASSERT", "DELETE",
  "ACTIVATE", "MODIFY", "STEP", "SIGNAL", "AT", "MAX", "DICE", "ALIAS",
  "DOT", "PER", "REF", "DOT_GT", "SUB_GT", "LCURLY", "RCURLY", "COMMA",
  "COLON", "ATSIGN", "RANGE", "PERCENT", "SOURCE", "DRAIN", "POOL", "GATE",
  "CONVERTER", "SUB", "ADD", "MUL", "DIV", "FPVAL", "STRING", "ADDITION",
  "SUBSUB", "UNM", "RPAREN", "LPAREN", "$accept", "program",
  "transformationList", "transformation", "elementList", "element", "io",
  "when", "act", "how", "at", "max", "add", "of", "from", "to", "exp",
  "name", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    73,    74,    74,    75,    75,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    77,    77,    77,    77,    78,    78,    78,    78,
      78,    79,    79,    79,    80,    80,    80,    81,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     2,     2,     0,     7,
       7,     7,    10,     8,     3,     2,     5,     5,     4,     5,
       2,     1,     1,     1,     1,     0,     1,     1,     1,     1,
       0,     1,     1,     0,     1,     1,     0,     2,     0,     2,
       0,     4,     0,     2,     0,     2,     0,     2,     0,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     3,     3,     3,     1,     1,     1,
       1,     2,     1,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     8,     1,     3,    25,    75,    21,    22,    23,
      24,     0,     0,     5,     6,     7,    30,     0,     0,    20,
      26,    27,    28,    29,     0,    33,    74,     8,    74,    15,
      74,    14,    32,    31,    36,    70,    74,    68,    69,     0,
      72,    67,    74,    74,     0,    73,    25,     0,     0,    35,
      34,     0,    62,    71,     0,     0,    61,     0,    74,    74,
      74,    74,    74,    74,    74,    74,     0,    63,    74,    74,
      74,    74,    18,     0,    19,     0,     0,     0,     0,     0,
      64,    66,    65,    56,    55,    53,    51,    54,    52,    49,
      50,    16,    58,    57,    59,    60,    17,    44,    44,    44,
      44,    46,     0,     9,    10,    38,    11,     0,    48,    43,
       0,    40,    45,     0,    13,    37,     0,    42,    47,    39,
       0,    12,    74,     0,    41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     4,     5,    15,    16,    25,    34,    51,
     111,   117,   121,   103,   108,   114,    44,    45
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -90
static const yytype_int16 yypact[] =
{
     -90,    18,    22,   -90,   -90,   253,   -90,   -90,   -90,   -90,
     -90,    17,    17,   -90,   -90,   -90,    -8,    21,   -18,   -90,
     -90,   -90,   -90,   -90,    17,    12,    48,   -90,    48,   -90,
      48,   -90,   -90,   -90,    20,   -90,    48,   -90,   -90,    17,
     -90,   -39,    48,    48,   168,   -90,   138,   178,   155,   -90,
     -90,    27,   -90,   -90,   -26,   -25,   -90,    97,    48,    48,
      48,    48,    48,    48,    48,    48,    17,   -90,    48,    48,
      48,    48,   -90,    17,   -90,    17,    17,    17,    17,    17,
     -90,   -90,   -90,   -31,   -31,   -31,   -31,   -31,   -31,   222,
     222,   -90,   -46,   -46,   -14,   -14,   -90,    23,    23,    23,
      23,    35,    17,   -90,   -90,    19,   -90,    17,    39,   -90,
      -4,    25,   -90,    17,   -90,   -90,    -2,    -7,   -90,   -90,
      -3,   -90,    48,   107,   -90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -90,   -90,   -90,   -90,    49,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -89,   -90,   -90,   -15,    -5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int8 yytable[] =
{
      17,    20,    21,    22,    23,    54,    18,    19,    67,   104,
     105,   106,    29,    47,    55,    48,    70,    71,     3,    31,
       6,    52,    -2,    67,     6,    32,    33,    56,    57,    68,
      69,    70,    71,    30,    53,    49,    50,    24,    80,    81,
      67,    17,   102,    83,    84,    85,    86,    87,    88,    89,
      90,     6,   107,    92,    93,    94,    95,   113,   110,   120,
     115,    91,   119,    35,    26,   116,     0,   122,    96,    27,
      97,    98,    99,   100,   101,     0,    46,    36,    37,    38,
      39,    28,    75,    76,    77,    78,    79,     0,     0,     0,
      40,     0,     0,     0,     0,     0,     0,   109,     0,     0,
       0,     0,   112,     0,     0,     0,     0,   123,   118,     0,
       0,     0,    41,     0,     0,     0,    42,    58,    43,    59,
      60,    61,    62,    63,    64,    65,     0,    58,     0,    59,
      60,    61,    62,    63,    64,    65,     0,     0,     0,     0,
       0,     6,     0,     7,     8,     9,    10,     0,     0,     0,
       0,    67,     0,     0,     0,     0,     0,    68,    69,    70,
      71,    67,     0,     0,     0,     0,    82,    68,    69,    70,
      71,    11,    12,     0,     0,    58,   124,    59,    60,    61,
      62,    63,    64,    65,     0,     0,     0,    72,    58,     0,
      59,    60,    61,    62,    63,    64,    65,     0,    58,     0,
      59,    60,    61,    62,    63,    64,    65,     0,     0,    67,
       0,     0,     0,     0,    66,    68,    69,    70,    71,     0,
      74,     0,    67,     0,     0,    73,     0,     0,    68,    69,
      70,    71,    67,     0,     0,     0,     0,     0,    68,    69,
      70,    71,    58,     0,    59,    60,    61,    62,    63,     0,
       0,     0,     0,     0,     0,     0,     6,     0,     7,     8,
       9,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     0,
       0,     0,    68,    69,    70,    71,    11,    12,     0,    13,
      14
};

static const yytype_int8 yycheck[] =
{
       5,     9,    10,    11,    12,    44,    11,    12,    54,    98,
      99,   100,    17,    28,    53,    30,    62,    63,     0,    24,
       3,    36,     0,    54,     3,    13,    14,    42,    43,    60,
      61,    62,    63,    51,    39,    15,    16,    45,    64,    64,
      54,    46,    19,    58,    59,    60,    61,    62,    63,    64,
      65,     3,    17,    68,    69,    70,    71,    18,    39,    66,
      64,    66,    64,    15,    43,    40,    -1,    70,    73,    48,
      75,    76,    77,    78,    79,    -1,    27,    29,    30,    31,
      32,    60,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,
      -1,    -1,   107,    -1,    -1,    -1,    -1,   122,   113,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    68,    20,    70,    22,
      23,    24,    25,    26,    27,    28,    -1,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,     3,    -1,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    54,    -1,    -1,    -1,    -1,    69,    60,    61,    62,
      63,    33,    34,    -1,    -1,    20,    69,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    49,    20,    -1,
      22,    23,    24,    25,    26,    27,    28,    -1,    20,    -1,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    46,    60,    61,    62,    63,    -1,
      65,    -1,    54,    -1,    -1,    47,    -1,    -1,    60,    61,
      62,    63,    54,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    20,    -1,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    33,    34,    -1,    36,
      37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    72,    73,     0,    74,    75,     3,     5,     6,     7,
       8,    33,    34,    36,    37,    76,    77,    88,    88,    88,
       9,    10,    11,    12,    45,    78,    43,    48,    60,    88,
      51,    88,    13,    14,    79,    15,    29,    30,    31,    32,
      42,    64,    68,    70,    87,    88,    75,    87,    87,    15,
      16,    80,    87,    88,    44,    53,    87,    87,    20,    22,
      23,    24,    25,    26,    27,    28,    46,    54,    60,    61,
      62,    63,    49,    47,    65,    55,    56,    57,    58,    59,
      64,    64,    69,    87,    87,    87,    87,    87,    87,    87,
      87,    88,    87,    87,    87,    87,    88,    88,    88,    88,
      88,    88,    19,    84,    84,    84,    84,    17,    85,    88,
      39,    81,    88,    18,    86,    64,    40,    82,    88,    64,
      66,    83,    70,    87,    69
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 112 "mm.ypp"
    { program = mm->createProgram((yyvsp[(1) - (1)].tList)); (yyval.program) = program;  ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 116 "mm.ypp"
    { (yyvsp[(1) - (2)].tList)->add((yyvsp[(2) - (2)].t)); (yyval.tList) = (yyvsp[(1) - (2)].tList);                 ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 117 "mm.ypp"
    { (yyval.tList) = mm->createTransformationVector(); ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 121 "mm.ypp"
    { (yyval.t) = mm->createModification((yyvsp[(1) - (2)].eList)); ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 122 "mm.ypp"
    { (yyval.t) = mm->createTransition((yyvsp[(1) - (2)].eList));   ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 125 "mm.ypp"
    { (yyvsp[(1) - (2)].eList)->add((yyvsp[(2) - (2)].element)); (yyval.eList) = (yyvsp[(1) - (2)].eList);           ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 126 "mm.ypp"
    { (yyval.eList) = mm->createElementVector();  ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 130 "mm.ypp"
    { (yyval.element) = mm->createSourceNode((yyvsp[(1) - (7)].io),(yyvsp[(2) - (7)].when),(yyvsp[(6) - (7)].name)); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 131 "mm.ypp"
    { (yyval.element) = mm->createDrainNode((yyvsp[(1) - (7)].io),(yyvsp[(2) - (7)].when),(yyvsp[(4) - (7)].how),(yyvsp[(6) - (7)].name));  ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 132 "mm.ypp"
    { (yyval.element) = mm->createGateNode((yyvsp[(1) - (7)].io),(yyvsp[(2) - (7)].when),(yyvsp[(3) - (7)].act),(yyvsp[(4) - (7)].how),(yyvsp[(6) - (7)].name)); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 134 "mm.ypp"
    { (yyval.element) = mm->createPoolNode((yyvsp[(1) - (10)].io),(yyvsp[(2) - (10)].when),(yyvsp[(3) - (10)].act),(yyvsp[(4) - (10)].how),(yyvsp[(6) - (10)].name),(yyvsp[(7) - (10)].name),(yyvsp[(8) - (10)].val),(yyvsp[(9) - (10)].val),(yyvsp[(10) - (10)].exp)); ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 136 "mm.ypp"
    { (yyval.element) = mm->createConverterNode((yyvsp[(1) - (8)].io),(yyvsp[(2) - (8)].when),(yyvsp[(6) - (8)].name),(yyvsp[(7) - (8)].name),(yyvsp[(8) - (8)].name)); ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 137 "mm.ypp"
    { (yyval.element) = mm->createRefNode((yyvsp[(1) - (3)].io),(yyvsp[(3) - (3)].name)); ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 138 "mm.ypp"
    { (yyval.element) = mm->createDeclaration((yyvsp[(1) - (2)].name),(yyvsp[(2) - (2)].name)); ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 139 "mm.ypp"
    { MM::Name * preName = (yyvsp[(1) - (5)].name)->getPreName();
                                   (yyvsp[(1) - (5)].name)->setPreName(MM_NULL); //prevent double free
                                   (yyval.element) = mm->createStateEdge(preName,(yyvsp[(1) - (5)].name),(yyvsp[(3) - (5)].exp),(yyvsp[(5) - (5)].name)); ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 142 "mm.ypp"
    { MM::Name * preName = (yyvsp[(1) - (5)].name)->getPreName();
                                   (yyvsp[(1) - (5)].name)->setPreName(MM_NULL); //prevent double free
                                   (yyval.element) = mm->createFlowEdge(preName,(yyvsp[(1) - (5)].name),(yyvsp[(3) - (5)].exp),(yyvsp[(5) - (5)].name));  ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 145 "mm.ypp"
    { (yyval.element) = mm->createDefinition((yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].eList)); ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 146 "mm.ypp"
    { (yyval.element) = mm->createAssertion(&(yylsp[(1) - (5)]),(yyvsp[(2) - (5)].name),(yyvsp[(4) - (5)].exp),(yyvsp[(5) - (5)].str)); free(yylval.str); ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 147 "mm.ypp"
    { (yyval.element) = mm->createDeletion(&(yylsp[(1) - (2)]),(yyvsp[(2) - (2)].name)); ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 154 "mm.ypp"
    { (yyval.io) = MM::NodeBehavior::IO_PRIVATE;   ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 155 "mm.ypp"
    { (yyval.io) = MM::NodeBehavior::IO_IN;        ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 156 "mm.ypp"
    { (yyval.io) = MM::NodeBehavior::IO_OUT;       ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 157 "mm.ypp"
    { (yyval.io) = MM::NodeBehavior::IO_INOUT;     ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 158 "mm.ypp"
    { (yyval.io) = MM::NodeBehavior::IO_PRIVATE;   ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 162 "mm.ypp"
    { (yyval.when) = MM::NodeBehavior::WHEN_PASSIVE; ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 163 "mm.ypp"
    { (yyval.when) = MM::NodeBehavior::WHEN_AUTO;    ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 164 "mm.ypp"
    { (yyval.when) = MM::NodeBehavior::WHEN_USER;    ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 165 "mm.ypp"
    { (yyval.when) = MM::NodeBehavior::WHEN_START;   ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 166 "mm.ypp"
    { (yyval.when) = MM::NodeBehavior::WHEN_PASSIVE; ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 170 "mm.ypp"
    { (yyval.act) = MM::NodeBehavior::ACT_PULL; ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 171 "mm.ypp"
    { (yyval.act) = MM::NodeBehavior::ACT_PUSH; ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 172 "mm.ypp"
    { (yyval.act) = MM::NodeBehavior::ACT_PULL; ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 176 "mm.ypp"
    { (yyval.how) = MM::NodeBehavior::HOW_ANY; ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 177 "mm.ypp"
    { (yyval.how) = MM::NodeBehavior::HOW_ALL; ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 178 "mm.ypp"
    { (yyval.how) = MM::NodeBehavior::HOW_ANY; ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 182 "mm.ypp"
    { (yyval.val) = (MM::UINT32) yylval.val / 100; ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 183 "mm.ypp"
    { (yyval.val) = 0;                             ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 187 "mm.ypp"
    { (yyval.val) = (MM::UINT32) yylval.val / 100; ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 188 "mm.ypp"
    { (yyval.val) = 0;                             ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 192 "mm.ypp"
    { (yyval.exp) = mm->createOverrideExp(&(yylsp[(2) - (4)]),(yyvsp[(3) - (4)].exp),&(yylsp[(4) - (4)]));;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 193 "mm.ypp"
    { (yyval.exp) = MM_NULL; ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 197 "mm.ypp"
    { (yyval.name) = (yyvsp[(2) - (2)].name);      ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 198 "mm.ypp"
    { (yyval.name) = MM_NULL; ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 202 "mm.ypp"
    { (yyval.name) = (yyvsp[(2) - (2)].name);      ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 203 "mm.ypp"
    { (yyval.name) = MM_NULL; ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 207 "mm.ypp"
    { (yyval.name) = (yyvsp[(2) - (2)].name);      ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 208 "mm.ypp"
    { (yyval.name) = MM_NULL; ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 212 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_AND,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 213 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_OR,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp));  ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 214 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_GT,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp));  ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 215 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_GE,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp));  ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 216 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_LT,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp));  ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 217 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_LE,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp));  ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 218 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_NEQ,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 219 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_EQ,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp));  ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 220 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_ADD,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 221 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_SUB,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 222 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_MUL,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 223 "mm.ypp"
    { (yyval.exp) = mm->createBinExp((yyvsp[(1) - (3)].exp),MM::Operator::OP_DIV,&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 224 "mm.ypp"
    { (yyval.exp) = mm->createUnExp(MM::Operator::OP_UNM,&(yylsp[(1) - (2)]),(yyvsp[(2) - (2)].exp));     ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 225 "mm.ypp"
    { (yyval.exp) = mm->createUnExp(MM::Operator::OP_NOT,&(yylsp[(1) - (2)]),(yyvsp[(2) - (2)].exp));     ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 226 "mm.ypp"
    { (yyval.exp) = mm->createUnExp(MM::Operator::OP_PERCENT,&(yylsp[(1) - (2)]),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 227 "mm.ypp"
    { (yyval.exp) = MM_NULL;                             /* FIXME */ ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 228 "mm.ypp"
    { (yyval.exp) = mm->createOverrideExp(&(yylsp[(1) - (3)]),(yyvsp[(2) - (3)].exp),&(yylsp[(3) - (3)]));                ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 229 "mm.ypp"
    { (yyval.exp) = mm->createRangeValExp((yyvsp[(1) - (3)].val),&(yylsp[(1) - (3)]),&(yylsp[(2) - (3)]),(yyvsp[(3) - (3)].val),&(yylsp[(3) - (3)]));         ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 230 "mm.ypp"
    { (yyval.exp) = mm->createNumberValExp((yyvsp[(1) - (1)].val),&(yylsp[(1) - (1)]));                   ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 231 "mm.ypp"
    { (yyval.exp) = mm->createBooleanValExp(MM_TRUE,&(yylsp[(1) - (1)]));             ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 232 "mm.ypp"
    { (yyval.exp) = mm->createBooleanValExp(MM_FALSE,&(yylsp[(1) - (1)]));            ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 233 "mm.ypp"
    { (yyval.exp) = mm->createAllExp(&(yylsp[(1) - (1)]));                            ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 234 "mm.ypp"
    { (yyval.exp) = mm->createActiveExp(&(yylsp[(1) - (2)]),(yyvsp[(2) - (2)].name));                      ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 235 "mm.ypp"
    { (yyval.exp) = mm->createAliasExp(&(yylsp[(1) - (1)]));                          ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 236 "mm.ypp"
    { (yyval.exp) = mm->createVarExp((yyvsp[(1) - (1)].name));                             ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 237 "mm.ypp"
    { (yyval.exp) = mm->createOneExp(&(yylsp[(0) - (0)]));                            ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 241 "mm.ypp"
    { (yyval.name) = mm->createName(yylval.str, &(yylsp[(1) - (1)])); free(yylval.str); ;}
    break;



/* Line 1464 of yacc.c  */
#line 2152 "mm.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 244 "mm.ypp"

MM::Machine * mm;      //TODO: create an instance and use its parser
MM::Program * program; //TODO: parser attribute

extern FILE * yyin;
extern struct yy_buffer_state;
typedef yy_buffer_state *YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_buffer(char *, size_t);

/*int main(int argc, const char * argv[])
{
  mm->eval((MM::CHAR const *)argv[1]);
  for(int i =0; i<20; i++)
  {
    mm->step();
  }
  return 0;
}*/

MM::Program * MM_parse(MM::Machine * machine, const MM::CHAR * input)
{
  mm = machine;
  yy_scan_buffer((char*)input, strlen(input));    
  yyparse();  
  return program;
}

MM::Program * MM_parseFile(MM::Machine * machine, const MM::CHAR * file)
{
  mm = machine;

  yyin = fopen(file, "r");
  if(!yyin)
  {
    fprintf(stderr, "error reading file %s\n", file);
  }
  else
  {
    yyparse();
  }

  return program;
}

void yyerror(char * msg)
{
  fprintf(stderr, "line %d, %d: %s\n", yylineno, yycolumn, msg);
}
