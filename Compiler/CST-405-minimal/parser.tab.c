
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 2 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char *yytext;
extern int yylineno;
void yyerror(const char* s);
ASTNode* root = NULL;


/* Line 189 of yacc.c  */
#line 90 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
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
     NUM = 258,
     FLOAT_LITERAL = 259,
     ID = 260,
     STRING_LITERAL = 261,
     CHAR_LITERAL = 262,
     BOOL_LITERAL = 263,
     INT = 264,
     FLOAT = 265,
     BOOL = 266,
     CHAR = 267,
     STRING = 268,
     PRINT = 269,
     IF = 270,
     ELSE = 271,
     RETURN = 272,
     VOID = 273,
     WHILE = 274,
     RETRY = 275,
     BACKOFF = 276,
     ONFAIL = 277,
     BREAK = 278,
     EQ = 279,
     NE = 280,
     LE = 281,
     GE = 282,
     LT = 283,
     GT = 284,
     AND = 285,
     OR = 286,
     NOT = 287,
     EXPONENT = 288,
     CAST = 289,
     UMINUS = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 19 "parser.y"

    int num;
    float floats;
    char* str;
    char character;
    bool boolean;
    struct ASTNode* node;



/* Line 214 of yacc.c  */
#line 172 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 184 "parser.tab.c"

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
# if YYENABLE_NLS
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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   772

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNRULES -- Number of states.  */
#define YYNSTATES  224

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    39,     2,     2,
      42,    43,    37,    35,    48,    36,     2,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    49,
       2,    34,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    40,
      41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    19,    27,    36,    38,
      40,    42,    44,    46,    48,    52,    56,    60,    64,    68,
      70,    74,    77,    82,    84,    87,    89,    91,    93,    95,
      97,    99,   101,   103,   106,   110,   113,   116,   120,   122,
     126,   130,   134,   138,   142,   148,   154,   160,   166,   172,
     179,   186,   193,   204,   215,   226,   231,   239,   241,   245,
     251,   259,   265,   271,   281,   289,   301,   307,   309,   311,
     313,   315,   317,   319,   324,   328,   333,   337,   341,   345,
     349,   353,   357,   361,   365,   369,   373,   377,   381,   385,
     389,   392,   395,   400,   404,   406
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    52,    -1,    53,    -1,    52,    53,    -1,
      54,     5,    42,    55,    43,    44,    57,    45,    -1,    54,
       5,    42,    43,    44,    57,    45,    -1,    54,     5,    42,
      18,    43,    44,    57,    45,    -1,     9,    -1,    10,    -1,
      11,    -1,    12,    -1,    13,    -1,    18,    -1,     9,    46,
      47,    -1,    10,    46,    47,    -1,    11,    46,    47,    -1,
      12,    46,    47,    -1,    13,    46,    47,    -1,    56,    -1,
      55,    48,    56,    -1,    54,     5,    -1,    54,     5,    46,
      47,    -1,    58,    -1,    57,    58,    -1,    62,    -1,    63,
      -1,    68,    -1,    65,    -1,    66,    -1,    59,    -1,    67,
      -1,    60,    -1,    69,    49,    -1,    17,    69,    49,    -1,
      17,    49,    -1,    23,    49,    -1,    44,    57,    45,    -1,
      58,    -1,     9,     5,    49,    -1,    10,     5,    49,    -1,
      11,     5,    49,    -1,    12,     5,    49,    -1,    13,     5,
      49,    -1,     9,     5,    34,    69,    49,    -1,    10,     5,
      34,    69,    49,    -1,    11,     5,    34,    69,    49,    -1,
      12,     5,    34,    69,    49,    -1,    13,     5,    34,    69,
      49,    -1,     9,     5,    46,     3,    47,    49,    -1,    10,
       5,    46,     3,    47,    49,    -1,    12,     5,    46,     3,
      47,    49,    -1,     9,     5,    46,     3,    47,    34,    44,
      64,    45,    49,    -1,    10,     5,    46,     3,    47,    34,
      44,    64,    45,    49,    -1,    12,     5,    46,     3,    47,
      34,    44,    64,    45,    49,    -1,     5,    34,    69,    49,
      -1,     5,    46,    69,    47,    34,    69,    49,    -1,    69,
      -1,    64,    48,    69,    -1,    15,    42,    69,    43,    61,
      -1,    15,    42,    69,    43,    61,    16,    61,    -1,    19,
      42,    69,    43,    61,    -1,    20,    42,     3,    43,    61,
      -1,    20,    42,     3,    48,    21,    34,     3,    43,    61,
      -1,    20,    42,     3,    43,    61,    22,    61,    -1,    20,
      42,     3,    48,    21,    34,     3,    43,    61,    22,    61,
      -1,    14,    42,    69,    43,    49,    -1,     3,    -1,     4,
      -1,     8,    -1,     7,    -1,     6,    -1,     5,    -1,     5,
      46,    69,    47,    -1,    42,    69,    43,    -1,    42,    54,
      43,    69,    -1,    69,    35,    69,    -1,    69,    36,    69,
      -1,    69,    37,    69,    -1,    69,    38,    69,    -1,    69,
      39,    69,    -1,    69,    33,    69,    -1,    69,    30,    69,
      -1,    69,    31,    69,    -1,    69,    28,    69,    -1,    69,
      29,    69,    -1,    69,    26,    69,    -1,    69,    27,    69,
      -1,    69,    24,    69,    -1,    69,    25,    69,    -1,    36,
      69,    -1,    32,    69,    -1,     5,    42,    70,    43,    -1,
       5,    42,    43,    -1,    69,    -1,    70,    48,    69,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    61,    61,    65,    66,    70,    73,    76,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    96,
      97,   101,   102,   106,   107,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   123,   124,   128,   133,   134,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   159,   160,   166,   167,   172,
     173,   179,   184,   185,   186,   187,   192,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   208,   209,   210,   211,
     212,   213,   216,   217,   220,   221,   222,   223,   224,   225,
     228,   229,   232,   233,   237,   238
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "FLOAT_LITERAL", "ID",
  "STRING_LITERAL", "CHAR_LITERAL", "BOOL_LITERAL", "INT", "FLOAT", "BOOL",
  "CHAR", "STRING", "PRINT", "IF", "ELSE", "RETURN", "VOID", "WHILE",
  "RETRY", "BACKOFF", "ONFAIL", "BREAK", "EQ", "NE", "LE", "GE", "LT",
  "GT", "AND", "OR", "NOT", "EXPONENT", "'='", "'+'", "'-'", "'*'", "'/'",
  "'%'", "CAST", "UMINUS", "'('", "')'", "'{'", "'}'", "'['", "']'", "','",
  "';'", "$accept", "program", "func_list", "func_decl", "type",
  "param_list", "param", "stmt_list", "stmt", "return_stmt", "break_stmt",
  "block", "decl", "assign", "init_list", "if_stmt", "while_stmt",
  "retry_stmt", "print_stmt", "expr", "arg_list", 0
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
     285,   286,   287,   288,    61,    43,    45,    42,    47,    37,
     289,   290,    40,    41,   123,   125,    91,    93,    44,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    59,    59,    60,    61,    61,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    67,    67,    67,    67,    68,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    70,    70
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     8,     7,     8,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       3,     2,     4,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     2,     2,     3,     1,     3,
       3,     3,     3,     3,     5,     5,     5,     5,     5,     6,
       6,     6,    10,    10,    10,     4,     7,     1,     3,     5,
       7,     5,     5,     9,     7,    11,     5,     1,     1,     1,
       1,     1,     1,     4,     3,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     8,     9,    10,    11,    12,    13,     0,     2,     3,
       0,     0,     0,     0,     0,     0,     1,     4,     0,    14,
      15,    16,    17,    18,     0,    13,     0,     0,     0,    19,
       0,     0,    21,     0,     0,     0,    67,    68,    72,    71,
      70,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    23,    30,    32,
      25,    26,    28,    29,    31,    27,     0,     0,     0,    20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    72,    35,     0,     0,     0,    36,    91,    90,     0,
       0,     6,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,    22,     0,
       7,     0,    93,    94,     0,     0,     0,     0,    39,     0,
       0,    40,     0,    41,     0,     0,    42,     0,    43,     0,
       0,     0,    34,     0,     0,     0,    74,    88,    89,    86,
      87,    84,    85,    82,    83,    81,    76,    77,    78,    79,
      80,     5,    55,    92,     0,    73,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,    95,     0,    44,     0,    45,     0,    46,    47,     0,
      48,    66,     0,    38,    59,    73,    61,    62,     0,     0,
       0,    49,     0,    50,     0,    51,     0,     0,     0,     0,
      56,     0,     0,     0,    37,    60,    64,     0,     0,    57,
       0,     0,     0,     0,     0,     0,     0,    63,    52,    58,
      53,    54,     0,    65
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    28,    29,    56,   183,    58,
      59,   184,    60,    61,   208,    62,    63,    64,    65,    66,
     114
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -144
static const yytype_int16 yypact[] =
{
     132,   -27,    -6,    25,    26,    38,  -144,    61,   132,  -144,
      80,    30,    66,    78,    85,    90,  -144,  -144,    79,  -144,
    -144,  -144,  -144,  -144,    -1,    60,    87,   124,   -41,  -144,
      94,   377,    93,   103,   132,   377,  -144,  -144,    72,  -144,
    -144,  -144,   144,   146,   151,   157,   158,   137,   139,    84,
     142,   145,   115,   104,   104,   417,   163,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,   436,   147,   377,  -144,
     206,   104,    92,   104,   -31,   -21,   -13,   -20,    31,   104,
     104,   -26,  -144,   453,   104,   189,  -144,   208,  -144,   150,
     637,  -144,  -144,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,  -144,  -144,   249,
    -144,   470,  -144,   717,   -16,   589,   104,   193,  -144,   104,
     194,  -144,   104,  -144,   104,   195,  -144,   104,  -144,   657,
     677,   104,  -144,   697,    15,   104,  -144,   251,   251,   122,
     122,   122,   122,   208,   733,   167,   152,   152,   167,   167,
     167,  -144,  -144,  -144,   104,   169,   487,   154,   504,   159,
     521,   538,   160,   555,   155,   335,   613,   335,   335,   201,
    -144,   717,   104,  -144,    32,  -144,    45,  -144,  -144,    68,
    -144,  -144,   377,  -144,   211,  -144,  -144,   202,   196,   572,
     184,  -144,   187,  -144,   205,  -144,   292,   335,   335,   236,
    -144,   104,   104,   104,  -144,  -144,  -144,   197,    56,   717,
      74,    82,   335,   216,   104,   218,   221,   228,  -144,   717,
    -144,  -144,   335,  -144
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,   263,     9,  -144,   239,   -34,     6,  -144,
    -144,  -129,  -144,  -144,  -143,  -144,  -144,  -144,  -144,   -49,
    -144
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      83,    70,    33,   116,    87,    88,    90,    34,     1,     2,
       3,     4,     5,   119,   124,   117,    72,    25,   118,    11,
     131,   122,   111,   113,   115,   120,   125,   153,   121,   126,
     129,   130,   154,    27,   109,   133,   123,    57,   186,   187,
      12,    57,    26,    27,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   168,   210,
     211,    16,    92,   169,    89,   127,   190,   156,   205,   206,
     158,    13,    14,   160,    57,   161,    92,    19,   163,   192,
     128,   191,   166,   217,    15,    18,   170,    36,    37,    81,
      39,    40,    41,   223,   193,    36,    37,    81,    39,    40,
      41,   213,   194,    30,   214,   171,    71,    36,    37,    81,
      39,    40,    41,    20,    72,    92,    53,   195,    73,   215,
      54,    24,   214,   189,    53,    21,    55,   216,    54,    32,
     214,    31,    22,    82,    55,   112,    53,    23,    35,    67,
      54,     1,     2,     3,     4,     5,    55,    68,   196,    74,
       6,    75,   209,   209,   209,   101,    76,   102,   103,   104,
     105,   106,    77,    78,    86,   219,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    79,
      49,    80,    50,    51,    84,   101,    52,    85,    57,   104,
     105,   106,   134,   135,   108,    53,   157,   159,   162,    54,
     101,   174,    92,   172,   181,    55,   176,   179,    91,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,   188,    49,   198,    50,    51,   197,   201,    52,
     199,   202,    93,    94,    95,    96,    97,    98,    53,   207,
     212,   101,    54,   102,   103,   104,   105,   106,    55,   203,
     222,   110,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,   218,    49,   220,    50,    51,
     221,    17,    52,    69,     0,     0,     0,    95,    96,    97,
      98,    53,     0,     0,   101,    54,   102,   103,   104,   105,
     106,    55,     0,     0,   151,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,     0,    49,
       0,    50,    51,     0,     0,    52,     0,     0,     0,     0,
       0,     0,     0,     0,    53,     0,     0,     0,    54,     0,
       0,     0,     0,     0,    55,     0,     0,   204,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,    49,     0,    50,    51,     0,     0,    52,     0,
       0,     0,     0,     0,     0,     0,     0,    53,     0,     0,
       0,    54,     0,     0,     0,     0,     0,    55,     0,   182,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     0,    49,     0,    50,    51,     0,     0,
      52,     0,     0,     0,     0,     0,     0,     0,     0,    53,
       0,     0,     0,    54,     0,     0,     0,     0,     0,    55,
      36,    37,    81,    39,    40,    41,     1,     2,     3,     4,
       5,     0,     0,     0,     0,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
       0,     0,     0,    54,     0,     0,     0,     0,     0,    55,
      93,    94,    95,    96,    97,    98,    99,   100,     0,   101,
       0,   102,   103,   104,   105,   106,     0,    93,    94,    95,
      96,    97,    98,    99,   100,   107,   101,     0,   102,   103,
     104,   105,   106,     0,    93,    94,    95,    96,    97,    98,
      99,   100,   132,   101,     0,   102,   103,   104,   105,   106,
       0,    93,    94,    95,    96,    97,    98,    99,   100,   152,
     101,     0,   102,   103,   104,   105,   106,     0,    93,    94,
      95,    96,    97,    98,    99,   100,   173,   101,     0,   102,
     103,   104,   105,   106,     0,    93,    94,    95,    96,    97,
      98,    99,   100,   175,   101,     0,   102,   103,   104,   105,
     106,     0,    93,    94,    95,    96,    97,    98,    99,   100,
     177,   101,     0,   102,   103,   104,   105,   106,     0,    93,
      94,    95,    96,    97,    98,    99,   100,   178,   101,     0,
     102,   103,   104,   105,   106,     0,    93,    94,    95,    96,
      97,    98,    99,   100,   180,   101,     0,   102,   103,   104,
     105,   106,     0,    93,    94,    95,    96,    97,    98,    99,
     100,   200,   101,     0,   102,   103,   104,   105,   106,     0,
       0,     0,     0,     0,     0,     0,   155,    93,    94,    95,
      96,    97,    98,    99,   100,     0,   101,     0,   102,   103,
     104,   105,   106,     0,     0,     0,     0,     0,     0,     0,
     185,    93,    94,    95,    96,    97,    98,    99,   100,     0,
     101,     0,   102,   103,   104,   105,   106,     0,     0,     0,
     136,    93,    94,    95,    96,    97,    98,    99,   100,     0,
     101,     0,   102,   103,   104,   105,   106,     0,     0,     0,
     164,    93,    94,    95,    96,    97,    98,    99,   100,     0,
     101,     0,   102,   103,   104,   105,   106,     0,     0,     0,
     165,    93,    94,    95,    96,    97,    98,    99,   100,     0,
     101,     0,   102,   103,   104,   105,   106,     0,     0,     0,
     167,    93,    94,    95,    96,    97,    98,    99,   100,     0,
     101,     0,   102,   103,   104,   105,   106,    93,    94,    95,
      96,    97,    98,    99,     0,     0,   101,     0,   102,   103,
     104,   105,   106
};

static const yytype_int16 yycheck[] =
{
      49,    35,    43,    34,    53,    54,    55,    48,     9,    10,
      11,    12,    13,    34,    34,    46,    42,    18,    49,    46,
      46,    34,    71,    72,    73,    46,    46,    43,    49,    49,
      79,    80,    48,    24,    68,    84,    49,    31,   167,   168,
      46,    35,    43,    34,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,    43,   202,
     203,     0,    56,    48,    55,    34,    34,   116,   197,   198,
     119,    46,    46,   122,    68,   124,    70,    47,   127,    34,
      49,    49,   131,   212,    46,     5,   135,     3,     4,     5,
       6,     7,     8,   222,    49,     3,     4,     5,     6,     7,
       8,    45,    34,    43,    48,   154,    34,     3,     4,     5,
       6,     7,     8,    47,    42,   109,    32,    49,    46,    45,
      36,    42,    48,   172,    32,    47,    42,    45,    36,     5,
      48,    44,    47,    49,    42,    43,    32,    47,    44,    46,
      36,     9,    10,    11,    12,    13,    42,    44,   182,     5,
      18,     5,   201,   202,   203,    33,     5,    35,    36,    37,
      38,    39,     5,     5,    49,   214,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    42,
      17,    42,    19,    20,    42,    33,    23,    42,   182,    37,
      38,    39,     3,    43,    47,    32,     3,     3,     3,    36,
      33,    47,   196,    34,    49,    42,    47,    47,    45,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    21,    17,    22,    19,    20,    16,    44,    23,
      34,    44,    24,    25,    26,    27,    28,    29,    32,     3,
      43,    33,    36,    35,    36,    37,    38,    39,    42,    44,
      22,    45,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    49,    17,    49,    19,    20,
      49,     8,    23,    34,    -1,    -1,    -1,    26,    27,    28,
      29,    32,    -1,    -1,    33,    36,    35,    36,    37,    38,
      39,    42,    -1,    -1,    45,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    17,
      -1,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    45,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    -1,    19,    20,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    42,    -1,    44,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    17,    -1,    19,    20,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    42,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      -1,    35,    36,    37,    38,    39,    -1,    24,    25,    26,
      27,    28,    29,    30,    31,    49,    33,    -1,    35,    36,
      37,    38,    39,    -1,    24,    25,    26,    27,    28,    29,
      30,    31,    49,    33,    -1,    35,    36,    37,    38,    39,
      -1,    24,    25,    26,    27,    28,    29,    30,    31,    49,
      33,    -1,    35,    36,    37,    38,    39,    -1,    24,    25,
      26,    27,    28,    29,    30,    31,    49,    33,    -1,    35,
      36,    37,    38,    39,    -1,    24,    25,    26,    27,    28,
      29,    30,    31,    49,    33,    -1,    35,    36,    37,    38,
      39,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
      49,    33,    -1,    35,    36,    37,    38,    39,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    49,    33,    -1,
      35,    36,    37,    38,    39,    -1,    24,    25,    26,    27,
      28,    29,    30,    31,    49,    33,    -1,    35,    36,    37,
      38,    39,    -1,    24,    25,    26,    27,    28,    29,    30,
      31,    49,    33,    -1,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,    -1,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    38,    39,    24,    25,    26,
      27,    28,    29,    30,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    11,    12,    13,    18,    51,    52,    53,
      54,    46,    46,    46,    46,    46,     0,    53,     5,    47,
      47,    47,    47,    47,    42,    18,    43,    54,    55,    56,
      43,    44,     5,    43,    48,    44,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    17,
      19,    20,    23,    32,    36,    42,    57,    58,    59,    60,
      62,    63,    65,    66,    67,    68,    69,    46,    44,    56,
      57,    34,    42,    46,     5,     5,     5,     5,     5,    42,
      42,     5,    49,    69,    42,    42,    49,    69,    69,    54,
      69,    45,    58,    24,    25,    26,    27,    28,    29,    30,
      31,    33,    35,    36,    37,    38,    39,    49,    47,    57,
      45,    69,    43,    69,    70,    69,    34,    46,    49,    34,
      46,    49,    34,    49,    34,    46,    49,    34,    49,    69,
      69,    46,    49,    69,     3,    43,    43,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    45,    49,    43,    48,    47,    69,     3,    69,     3,
      69,    69,     3,    69,    43,    43,    69,    43,    43,    48,
      69,    69,    34,    49,    47,    49,    47,    49,    49,    47,
      49,    49,    44,    58,    61,    47,    61,    61,    21,    69,
      34,    49,    34,    49,    34,    49,    57,    16,    22,    34,
      49,    44,    44,    44,    45,    61,    61,     3,    64,    69,
      64,    64,    43,    45,    48,    45,    45,    61,    49,    69,
      49,    49,    22,    61
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

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
# if YYLTYPE_IS_TRIVIAL
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 61 "parser.y"
    { root = (yyvsp[(1) - (1)].node); (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 65 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 66 "parser.y"
    { (yyval.node) = createFuncList((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 70 "parser.y"
    {
        (yyval.node) = createFuncDecl((yyvsp[(1) - (8)].str), (yyvsp[(2) - (8)].str), (yyvsp[(4) - (8)].node), (yyvsp[(7) - (8)].node));
    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 73 "parser.y"
    {
        (yyval.node) = createFuncDecl((yyvsp[(1) - (7)].str), (yyvsp[(2) - (7)].str), NULL, (yyvsp[(6) - (7)].node));
    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 76 "parser.y"
    {
        (yyval.node) = createFuncDecl((yyvsp[(1) - (8)].str), (yyvsp[(2) - (8)].str), NULL, (yyvsp[(7) - (8)].node));
    ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 82 "parser.y"
    { (yyval.str) = "int"; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 83 "parser.y"
    { (yyval.str) = "float"; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 84 "parser.y"
    { (yyval.str) = "bool"; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 85 "parser.y"
    { (yyval.str) = "char"; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 86 "parser.y"
    { (yyval.str) = "string"; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 87 "parser.y"
    { (yyval.str) = "void"; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 88 "parser.y"
    { (yyval.str) = "int[]"; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 89 "parser.y"
    { (yyval.str) = "float[]"; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 90 "parser.y"
    { (yyval.str) = "bool[]"; ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 91 "parser.y"
    { (yyval.str) = "char[]"; ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 92 "parser.y"
    { (yyval.str) = "string[]"; ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    { (yyval.node) = createParamList((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 101 "parser.y"
    { (yyval.node) = createParam((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 102 "parser.y"
    { (yyval.node) = createArrayParam((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].str)); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 107 "parser.y"
    { (yyval.node) = createStmtList((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 119 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 123 "parser.y"
    { (yyval.node) = createReturn((yyvsp[(2) - (3)].node)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    { (yyval.node) = createReturn(NULL); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    { (yyval.node) = createBreak(); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 133 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 134 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 139 "parser.y"
    { (yyval.node) = createDecl("int", (yyvsp[(2) - (3)].str)); free((yyvsp[(2) - (3)].str)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    { (yyval.node) = createDecl("float", (yyvsp[(2) - (3)].str)); free((yyvsp[(2) - (3)].str)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 141 "parser.y"
    { (yyval.node) = createDecl("bool", (yyvsp[(2) - (3)].str)); free((yyvsp[(2) - (3)].str)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    { (yyval.node) = createDecl("char", (yyvsp[(2) - (3)].str)); free((yyvsp[(2) - (3)].str)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 143 "parser.y"
    { (yyval.node) = createDecl("string", (yyvsp[(2) - (3)].str)); free((yyvsp[(2) - (3)].str)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 144 "parser.y"
    { (yyval.node) = createDeclInit("int", (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node)); free((yyvsp[(2) - (5)].str)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 145 "parser.y"
    { (yyval.node) = createDeclInit("float", (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node)); free((yyvsp[(2) - (5)].str)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 146 "parser.y"
    { (yyval.node) = createDeclInit("bool", (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node)); free((yyvsp[(2) - (5)].str)); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    { (yyval.node) = createDeclInit("char", (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node)); free((yyvsp[(2) - (5)].str)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 148 "parser.y"
    { (yyval.node) = createDeclInit("string", (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node)); free((yyvsp[(2) - (5)].str)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    { (yyval.node) = createArrayDecl("int", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].num)); free((yyvsp[(2) - (6)].str)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 150 "parser.y"
    { (yyval.node) = createArrayDecl("float", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].num)); free((yyvsp[(2) - (6)].str)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    { (yyval.node) = createArrayDecl("char", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].num)); free((yyvsp[(2) - (6)].str)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 152 "parser.y"
    { (yyval.node) = createArrayInitDecl("int", (yyvsp[(2) - (10)].str), (yyvsp[(4) - (10)].num), (yyvsp[(8) - (10)].node)); free((yyvsp[(2) - (10)].str)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    { (yyval.node) = createArrayInitDecl("float", (yyvsp[(2) - (10)].str), (yyvsp[(4) - (10)].num), (yyvsp[(8) - (10)].node)); free((yyvsp[(2) - (10)].str)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 154 "parser.y"
    { (yyval.node) = createArrayInitDecl("char", (yyvsp[(2) - (10)].str), (yyvsp[(4) - (10)].num), (yyvsp[(8) - (10)].node)); free((yyvsp[(2) - (10)].str)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    { (yyval.node) = createAssign((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node)); free((yyvsp[(1) - (4)].str)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
    { (yyval.node) = createArrayAssign((yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node)); free((yyvsp[(1) - (7)].str)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 166 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    { (yyval.node) = createInitList((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 172 "parser.y"
    { (yyval.node) = createIf((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), NULL); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 174 "parser.y"
    { (yyval.node) = createIf((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 179 "parser.y"
    { (yyval.node) = createWhile((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    { (yyval.node) = createRetry((yyvsp[(3) - (5)].num), 0, (yyvsp[(5) - (5)].node), NULL); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 185 "parser.y"
    { (yyval.node) = createRetry((yyvsp[(3) - (9)].num), (yyvsp[(7) - (9)].num), (yyvsp[(9) - (9)].node), NULL); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    { (yyval.node) = createRetry((yyvsp[(3) - (7)].num), 0, (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 187 "parser.y"
    { (yyval.node) = createRetry((yyvsp[(3) - (11)].num), (yyvsp[(7) - (11)].num), (yyvsp[(9) - (11)].node), (yyvsp[(11) - (11)].node)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    { (yyval.node) = createPrint((yyvsp[(3) - (5)].node)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    { (yyval.node) = createNum((yyvsp[(1) - (1)].num)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 198 "parser.y"
    { (yyval.node) = createFloat((yyvsp[(1) - (1)].floats)); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    { (yyval.node) = createBool((yyvsp[(1) - (1)].boolean)); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 200 "parser.y"
    { (yyval.node) = createChar((yyvsp[(1) - (1)].character)); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 201 "parser.y"
    { (yyval.node) = createString((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 202 "parser.y"
    { (yyval.node) = createVar((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    { (yyval.node) = createArrayAccess((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node)); free((yyvsp[(1) - (4)].str)); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 204 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 205 "parser.y"
    { (yyval.node) = createCast((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].node)); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 208 "parser.y"
    { (yyval.node) = createBinOp(BINOP_ADD, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 209 "parser.y"
    { (yyval.node) = createBinOp(BINOP_SUB, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    { (yyval.node) = createBinOp(BINOP_MUL, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 211 "parser.y"
    { (yyval.node) = createBinOp(BINOP_DIV, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    { (yyval.node) = createBinOp(BINOP_MOD, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 213 "parser.y"
    { (yyval.node) = createBinOp(BINOP_EXP, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 216 "parser.y"
    { (yyval.node) = createBinOp(BINOP_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 217 "parser.y"
    { (yyval.node) = createBinOp(BINOP_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 220 "parser.y"
    { (yyval.node) = createRelop(RELOP_LT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 221 "parser.y"
    { (yyval.node) = createRelop(RELOP_GT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 222 "parser.y"
    { (yyval.node) = createRelop(RELOP_LE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 223 "parser.y"
    { (yyval.node) = createRelop(RELOP_GE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 224 "parser.y"
    { (yyval.node) = createRelop(RELOP_EQ, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 225 "parser.y"
    { (yyval.node) = createRelop(RELOP_NE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 228 "parser.y"
    { (yyval.node) = createUnaryOp(UNOP_NEG, (yyvsp[(2) - (2)].node)); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 229 "parser.y"
    { (yyval.node) = createUnaryOp(UNOP_NOT, (yyvsp[(2) - (2)].node)); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 232 "parser.y"
    { (yyval.node) = createFuncCall((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node)); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
    { (yyval.node) = createFuncCall((yyvsp[(1) - (3)].str), NULL); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 237 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 238 "parser.y"
    { (yyval.node) = createArgList((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2285 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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



/* Line 1675 of yacc.c  */
#line 241 "parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Syntax Error at line %d: %s (near \"%s\")\n",
            yylineno, s, yytext ? yytext : "<null>");
}

