
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
     BOOL_LITERAL = 262,
     INT = 263,
     FLOAT = 264,
     BOOL = 265,
     STRING = 266,
     PRINT = 267,
     IF = 268,
     ELSE = 269,
     RETURN = 270,
     VOID = 271,
     EQ = 272,
     NE = 273,
     LE = 274,
     GE = 275,
     LT = 276,
     GT = 277,
     AND = 278,
     OR = 279,
     NOT = 280,
     EXPONENT = 281,
     CAST = 282,
     UMINUS = 283
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
    bool boolean;
    struct ASTNode* node;



/* Line 214 of yacc.c  */
#line 164 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 176 "parser.tab.c"

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   610

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNRULES -- Number of states.  */
#define YYNSTATES  172

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    32,     2,     2,
      35,    36,    30,    28,    39,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
       2,    27,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
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
      25,    26,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    19,    27,    36,    38,
      40,    42,    44,    46,    48,    52,    55,    60,    62,    65,
      67,    69,    71,    73,    75,    78,    82,    85,    89,    91,
      95,    99,   103,   107,   113,   119,   125,   131,   138,   145,
     156,   167,   172,   180,   182,   186,   192,   200,   206,   208,
     210,   212,   214,   216,   221,   225,   230,   234,   238,   242,
     246,   250,   254,   258,   262,   266,   270,   274,   278,   282,
     286,   289,   292,   297,   301,   303
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    45,    -1,    46,    -1,    45,    46,    -1,
      47,     5,    35,    48,    36,    37,    50,    38,    -1,    47,
       5,    35,    36,    37,    50,    38,    -1,    47,     5,    35,
      16,    36,    37,    50,    38,    -1,     8,    -1,     9,    -1,
      10,    -1,    11,    -1,    16,    -1,    49,    -1,    48,    39,
      49,    -1,    47,     5,    -1,    47,     5,    40,    41,    -1,
      51,    -1,    50,    51,    -1,    54,    -1,    55,    -1,    58,
      -1,    57,    -1,    52,    -1,    59,    42,    -1,    15,    59,
      42,    -1,    15,    42,    -1,    37,    50,    38,    -1,    51,
      -1,     8,     5,    42,    -1,     9,     5,    42,    -1,    10,
       5,    42,    -1,    11,     5,    42,    -1,     8,     5,    27,
      59,    42,    -1,     9,     5,    27,    59,    42,    -1,    10,
       5,    27,    59,    42,    -1,    11,     5,    27,    59,    42,
      -1,     8,     5,    40,     3,    41,    42,    -1,     9,     5,
      40,     3,    41,    42,    -1,     8,     5,    40,     3,    41,
      27,    37,    56,    38,    42,    -1,     9,     5,    40,     3,
      41,    27,    37,    56,    38,    42,    -1,     5,    27,    59,
      42,    -1,     5,    40,    59,    41,    27,    59,    42,    -1,
      59,    -1,    56,    39,    59,    -1,    13,    35,    59,    36,
      53,    -1,    13,    35,    59,    36,    53,    14,    53,    -1,
      12,    35,    59,    36,    42,    -1,     3,    -1,     4,    -1,
       7,    -1,     6,    -1,     5,    -1,     5,    40,    59,    41,
      -1,    35,    59,    36,    -1,    35,    47,    36,    59,    -1,
      59,    28,    59,    -1,    59,    29,    59,    -1,    59,    30,
      59,    -1,    59,    31,    59,    -1,    59,    32,    59,    -1,
      59,    26,    59,    -1,    59,    23,    59,    -1,    59,    24,
      59,    -1,    59,    21,    59,    -1,    59,    22,    59,    -1,
      59,    19,    59,    -1,    59,    20,    59,    -1,    59,    17,
      59,    -1,    59,    18,    59,    -1,    29,    59,    -1,    25,
      59,    -1,     5,    35,    60,    36,    -1,     5,    35,    36,
      -1,    59,    -1,    60,    39,    59,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    59,    59,    63,    64,    68,    71,    74,    80,    81,
      82,    83,    84,    88,    89,    93,    94,    98,    99,   103,
     104,   105,   106,   107,   108,   112,   113,   118,   119,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   140,   141,   147,   148,   153,   154,   160,   165,   166,
     167,   168,   169,   170,   171,   172,   175,   176,   177,   178,
     179,   180,   183,   184,   187,   188,   189,   190,   191,   192,
     195,   196,   199,   200,   204,   205
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "FLOAT_LITERAL", "ID",
  "STRING_LITERAL", "BOOL_LITERAL", "INT", "FLOAT", "BOOL", "STRING",
  "PRINT", "IF", "ELSE", "RETURN", "VOID", "EQ", "NE", "LE", "GE", "LT",
  "GT", "AND", "OR", "NOT", "EXPONENT", "'='", "'+'", "'-'", "'*'", "'/'",
  "'%'", "CAST", "UMINUS", "'('", "')'", "'{'", "'}'", "','", "'['", "']'",
  "';'", "$accept", "program", "func_list", "func_decl", "type",
  "param_list", "param", "stmt_list", "stmt", "return_stmt", "block",
  "decl", "assign", "init_list", "if_stmt", "print_stmt", "expr",
  "arg_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    61,    43,    45,
      42,    47,    37,   282,   283,    40,    41,   123,   125,    44,
      91,    93,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    47,    47,
      47,    47,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    51,    51,    51,    51,    52,    52,    53,    53,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    56,    56,    57,    57,    58,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    60,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     8,     7,     8,     1,     1,
       1,     1,     1,     1,     3,     2,     4,     1,     2,     1,
       1,     1,     1,     1,     2,     3,     2,     3,     1,     3,
       3,     3,     3,     5,     5,     5,     5,     6,     6,    10,
      10,     4,     7,     1,     3,     5,     7,     5,     1,     1,
       1,     1,     1,     4,     3,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     8,     9,    10,    11,    12,     0,     2,     3,     0,
       1,     4,     0,     0,    12,     0,     0,     0,    13,     0,
       0,    15,     0,     0,     0,    48,    49,    52,    51,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    23,    19,    20,    22,    21,     0,     0,     0,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    52,    26,     0,    71,    70,     0,     0,     6,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    24,    16,     0,     7,     0,    73,
      74,     0,     0,     0,     0,    29,     0,     0,    30,     0,
      31,     0,    32,     0,     0,     0,    25,     0,    54,    68,
      69,    66,    67,    64,    65,    62,    63,    61,    56,    57,
      58,    59,    60,     5,    41,    72,     0,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    55,    75,     0,
      33,     0,    34,     0,    35,    36,    47,     0,    28,    45,
      53,     0,     0,    37,     0,    38,     0,     0,    42,     0,
       0,    27,    46,     0,    43,     0,     0,     0,     0,    39,
      44,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    17,    18,    40,    41,    42,
     149,    43,    44,   163,    45,    46,    47,    91
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -37
static const yytype_int16 yypact[] =
{
      75,   -37,   -37,   -37,   -37,   -37,    10,    75,   -37,    54,
     -37,   -37,    29,    -3,    41,    51,    74,    36,   -37,    52,
     282,    53,    62,    75,   282,   -37,   -37,    27,   -37,   -37,
      95,    96,    97,   100,    82,    84,    45,   166,   166,   315,
     103,   -37,   -37,   -37,   -37,   -37,   -37,   334,    79,   282,
     -37,   139,   166,   130,   166,   -15,   -12,   -16,    26,   166,
     166,   -21,   -37,   351,   213,   -37,    85,   502,   -37,   -37,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   -37,   -37,   175,   -37,   368,   -37,
     562,    42,   470,   166,   119,   -37,   166,   126,   -37,   166,
     -37,   166,   -37,   522,   542,   166,   -37,   166,   -37,   177,
     177,    66,    66,    66,    66,   213,   578,   104,   131,   131,
     104,   104,   104,   -37,   -37,   -37,   166,   112,   385,    99,
     402,   115,   419,   436,   111,   247,   486,   -37,   562,   166,
     -37,    31,   -37,    34,   -37,   -37,   -37,   282,   -37,   144,
     -37,   453,   123,   -37,   138,   -37,   211,   247,   -37,   166,
     166,   -37,   -37,   -17,   562,    -7,   125,   166,   134,   -37,
     562,   -37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -37,   -37,   -37,   182,    43,   -37,   169,   -20,   -31,   -37,
      37,   -37,   -37,    33,   -37,   -37,   -36,   -37
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      63,    64,    65,    67,    51,     1,     2,     3,     4,    69,
      10,    99,    93,    14,    53,    96,    88,    90,    92,   105,
      69,   166,   167,   103,   104,    94,   100,    95,    97,    86,
      98,   168,   167,    15,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    25,    26,
      61,    28,    29,   101,    52,    69,    16,   128,   152,    12,
     130,   154,    53,   132,    13,   133,    16,    54,   102,   136,
      37,   137,    22,   153,    38,    23,   155,    19,   125,    21,
      39,   126,    66,     1,     2,     3,     4,    62,    20,    24,
     138,     5,    78,    48,    79,    80,    81,    82,    83,    49,
      55,    56,    57,   151,   148,    58,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    59,    36,    60,
      85,   107,   129,   164,   164,    69,   148,   156,    37,   131,
      78,   170,    38,    25,    26,    61,    28,    29,    39,   139,
     141,    68,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,   146,    36,    37,   143,    78,   157,    38,
     159,    81,    82,    83,    37,    39,    89,   169,    38,    25,
      26,    61,    28,    29,    39,   160,   171,    87,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    11,
      36,    37,    50,   165,   162,    38,    72,    73,    74,    75,
      37,    39,     0,    78,    38,    79,    80,    81,    82,    83,
      39,     0,     0,   123,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,     0,    36,     0,     0,     0,
      70,    71,    72,    73,    74,    75,    37,     0,     0,    78,
      38,    79,    80,    81,    82,    83,    39,     0,     0,   161,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,     0,     0,     0,    38,     0,     0,     0,
       0,     0,    39,     0,   147,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,    38,     0,     0,     0,     0,     0,    39,    25,    26,
      61,    28,    29,     1,     2,     3,     4,     0,     0,     0,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     0,     0,     0,    38,     0,     0,     0,     0,     0,
      39,    70,    71,    72,    73,    74,    75,    76,    77,     0,
      78,     0,    79,    80,    81,    82,    83,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    84,    78,     0,    79,
      80,    81,    82,    83,     0,    70,    71,    72,    73,    74,
      75,    76,    77,   106,    78,     0,    79,    80,    81,    82,
      83,     0,    70,    71,    72,    73,    74,    75,    76,    77,
     124,    78,     0,    79,    80,    81,    82,    83,     0,    70,
      71,    72,    73,    74,    75,    76,    77,   140,    78,     0,
      79,    80,    81,    82,    83,     0,    70,    71,    72,    73,
      74,    75,    76,    77,   142,    78,     0,    79,    80,    81,
      82,    83,     0,    70,    71,    72,    73,    74,    75,    76,
      77,   144,    78,     0,    79,    80,    81,    82,    83,     0,
      70,    71,    72,    73,    74,    75,    76,    77,   145,    78,
       0,    79,    80,    81,    82,    83,     0,    70,    71,    72,
      73,    74,    75,    76,    77,   158,    78,     0,    79,    80,
      81,    82,    83,    70,    71,    72,    73,    74,    75,    76,
      77,   127,    78,     0,    79,    80,    81,    82,    83,    70,
      71,    72,    73,    74,    75,    76,    77,   150,    78,     0,
      79,    80,    81,    82,    83,     0,     0,     0,   108,    70,
      71,    72,    73,    74,    75,    76,    77,     0,    78,     0,
      79,    80,    81,    82,    83,     0,     0,     0,   134,    70,
      71,    72,    73,    74,    75,    76,    77,     0,    78,     0,
      79,    80,    81,    82,    83,     0,     0,     0,   135,    70,
      71,    72,    73,    74,    75,    76,    77,     0,    78,     0,
      79,    80,    81,    82,    83,    70,    71,    72,    73,    74,
      75,    76,     0,     0,    78,     0,    79,    80,    81,    82,
      83
};

static const yytype_int16 yycheck[] =
{
      36,    37,    38,    39,    24,     8,     9,    10,    11,    40,
       0,    27,    27,    16,    35,    27,    52,    53,    54,    40,
      51,    38,    39,    59,    60,    40,    42,    42,    40,    49,
      42,    38,    39,    36,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     3,     4,
       5,     6,     7,    27,    27,    86,    13,    93,    27,     5,
      96,    27,    35,    99,    35,   101,    23,    40,    42,   105,
      25,   107,    36,    42,    29,    39,    42,    36,    36,     5,
      35,    39,    39,     8,     9,    10,    11,    42,    37,    37,
     126,    16,    26,    40,    28,    29,    30,    31,    32,    37,
       5,     5,     5,   139,   135,     5,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    35,    15,    35,
      41,    36,     3,   159,   160,   156,   157,   147,    25,     3,
      26,   167,    29,     3,     4,     5,     6,     7,    35,    27,
      41,    38,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    42,    15,    25,    41,    26,    14,    29,
      37,    30,    31,    32,    25,    35,    36,    42,    29,     3,
       4,     5,     6,     7,    35,    37,    42,    38,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     7,
      15,    25,    23,   160,   157,    29,    19,    20,    21,    22,
      25,    35,    -1,    26,    29,    28,    29,    30,    31,    32,
      35,    -1,    -1,    38,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    25,    -1,    -1,    26,
      29,    28,    29,    30,    31,    32,    35,    -1,    -1,    38,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    37,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    35,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      35,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      26,    -1,    28,    29,    30,    31,    32,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    42,    26,    -1,    28,
      29,    30,    31,    32,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    42,    26,    -1,    28,    29,    30,    31,
      32,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      42,    26,    -1,    28,    29,    30,    31,    32,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    42,    26,    -1,
      28,    29,    30,    31,    32,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    42,    26,    -1,    28,    29,    30,
      31,    32,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    42,    26,    -1,    28,    29,    30,    31,    32,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    42,    26,
      -1,    28,    29,    30,    31,    32,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    42,    26,    -1,    28,    29,
      30,    31,    32,    17,    18,    19,    20,    21,    22,    23,
      24,    41,    26,    -1,    28,    29,    30,    31,    32,    17,
      18,    19,    20,    21,    22,    23,    24,    41,    26,    -1,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    26,    -1,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    26,    -1,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    26,    -1,
      28,    29,    30,    31,    32,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    26,    -1,    28,    29,    30,    31,
      32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,     9,    10,    11,    16,    44,    45,    46,    47,
       0,    46,     5,    35,    16,    36,    47,    48,    49,    36,
      37,     5,    36,    39,    37,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    15,    25,    29,    35,
      50,    51,    52,    54,    55,    57,    58,    59,    40,    37,
      49,    50,    27,    35,    40,     5,     5,     5,     5,    35,
      35,     5,    42,    59,    59,    59,    47,    59,    38,    51,
      17,    18,    19,    20,    21,    22,    23,    24,    26,    28,
      29,    30,    31,    32,    42,    41,    50,    38,    59,    36,
      59,    60,    59,    27,    40,    42,    27,    40,    42,    27,
      42,    27,    42,    59,    59,    40,    42,    36,    36,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    38,    42,    36,    39,    41,    59,     3,
      59,     3,    59,    59,    36,    36,    59,    59,    59,    27,
      42,    41,    42,    41,    42,    42,    42,    37,    51,    53,
      41,    59,    27,    42,    27,    42,    50,    14,    42,    37,
      37,    38,    53,    56,    59,    56,    38,    39,    38,    42,
      59,    42
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
#line 59 "parser.y"
    { root = (yyvsp[(1) - (1)].node); (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 63 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 64 "parser.y"
    { (yyval.node) = createFuncList((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 68 "parser.y"
    {
        (yyval.node) = createFuncDecl((yyvsp[(1) - (8)].str), (yyvsp[(2) - (8)].str), (yyvsp[(4) - (8)].node), (yyvsp[(7) - (8)].node));
    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 71 "parser.y"
    {
        (yyval.node) = createFuncDecl((yyvsp[(1) - (7)].str), (yyvsp[(2) - (7)].str), NULL, (yyvsp[(6) - (7)].node));
    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 74 "parser.y"
    {
        (yyval.node) = createFuncDecl((yyvsp[(1) - (8)].str), (yyvsp[(2) - (8)].str), NULL, (yyvsp[(7) - (8)].node));
    ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 80 "parser.y"
    { (yyval.str) = "int"; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 81 "parser.y"
    { (yyval.str) = "float"; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 82 "parser.y"
    { (yyval.str) = "bool"; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 83 "parser.y"
    { (yyval.str) = "string"; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 84 "parser.y"
    { (yyval.str) = "void"; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 88 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 89 "parser.y"
    { (yyval.node) = createParamList((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 93 "parser.y"
    { (yyval.node) = createParam((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 94 "parser.y"
    { (yyval.node) = createArrayParam((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].str)); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 98 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 99 "parser.y"
    { (yyval.node) = createStmtList((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 108 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 112 "parser.y"
    { (yyval.node) = createReturn((yyvsp[(2) - (3)].node)); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    { (yyval.node) = createReturn(NULL); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 118 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 119 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    { (yyval.node) = createDecl("int", (yyvsp[(2) - (3)].str)); free((yyvsp[(2) - (3)].str)); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 125 "parser.y"
    { (yyval.node) = createDecl("float", (yyvsp[(2) - (3)].str)); free((yyvsp[(2) - (3)].str)); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 126 "parser.y"
    { (yyval.node) = createDecl("bool", (yyvsp[(2) - (3)].str)); free((yyvsp[(2) - (3)].str)); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 127 "parser.y"
    { (yyval.node) = createDecl("string", (yyvsp[(2) - (3)].str)); free((yyvsp[(2) - (3)].str)); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    { (yyval.node) = createDeclInit("int", (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node)); free((yyvsp[(2) - (5)].str)); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 129 "parser.y"
    { (yyval.node) = createDeclInit("float", (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node)); free((yyvsp[(2) - (5)].str)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    { (yyval.node) = createDeclInit("bool", (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node)); free((yyvsp[(2) - (5)].str)); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    { (yyval.node) = createDeclInit("string", (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node)); free((yyvsp[(2) - (5)].str)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
    { (yyval.node) = createArrayDecl("int", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].num)); free((yyvsp[(2) - (6)].str)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 133 "parser.y"
    { (yyval.node) = createArrayDecl("float", (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].num)); free((yyvsp[(2) - (6)].str)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 134 "parser.y"
    { (yyval.node) = createArrayInitDecl("int", (yyvsp[(2) - (10)].str), (yyvsp[(4) - (10)].num), (yyvsp[(8) - (10)].node)); free((yyvsp[(2) - (10)].str)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 135 "parser.y"
    { (yyval.node) = createArrayInitDecl("float", (yyvsp[(2) - (10)].str), (yyvsp[(4) - (10)].num), (yyvsp[(8) - (10)].node)); free((yyvsp[(2) - (10)].str)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    { (yyval.node) = createAssign((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node)); free((yyvsp[(1) - (4)].str)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    { (yyval.node) = createArrayAssign((yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node)); free((yyvsp[(1) - (7)].str)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 148 "parser.y"
    { (yyval.node) = createInitList((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    { (yyval.node) = createIf((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), NULL); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    { (yyval.node) = createIf((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    { (yyval.node) = createPrint((yyvsp[(3) - (5)].node)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    { (yyval.node) = createNum((yyvsp[(1) - (1)].num)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 166 "parser.y"
    { (yyval.node) = createFloat((yyvsp[(1) - (1)].floats)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    { (yyval.node) = createBool((yyvsp[(1) - (1)].boolean)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 168 "parser.y"
    { (yyval.node) = createString((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    { (yyval.node) = createVar((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 170 "parser.y"
    { (yyval.node) = createArrayAccess((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node)); free((yyvsp[(1) - (4)].str)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 171 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 172 "parser.y"
    { (yyval.node) = createCast((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].node)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 175 "parser.y"
    { (yyval.node) = createBinOp(BINOP_ADD, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 176 "parser.y"
    { (yyval.node) = createBinOp(BINOP_SUB, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 177 "parser.y"
    { (yyval.node) = createBinOp(BINOP_MUL, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 178 "parser.y"
    { (yyval.node) = createBinOp(BINOP_DIV, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 179 "parser.y"
    { (yyval.node) = createBinOp(BINOP_MOD, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 180 "parser.y"
    { (yyval.node) = createBinOp(BINOP_EXP, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    { (yyval.node) = createBinOp(BINOP_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    { (yyval.node) = createBinOp(BINOP_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 187 "parser.y"
    { (yyval.node) = createRelop(RELOP_LT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    { (yyval.node) = createRelop(RELOP_GT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    { (yyval.node) = createRelop(RELOP_LE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    { (yyval.node) = createRelop(RELOP_GE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    { (yyval.node) = createRelop(RELOP_EQ, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    { (yyval.node) = createRelop(RELOP_NE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    { (yyval.node) = createUnaryOp(UNOP_NEG, (yyvsp[(2) - (2)].node)); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    { (yyval.node) = createUnaryOp(UNOP_NOT, (yyvsp[(2) - (2)].node)); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    { (yyval.node) = createFuncCall((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node)); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 200 "parser.y"
    { (yyval.node) = createFuncCall((yyvsp[(1) - (3)].str), NULL); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 204 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 205 "parser.y"
    { (yyval.node) = createArgList((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2089 "parser.tab.c"
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
#line 208 "parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Syntax Error at line %d: %s (near \"%s\")\n",
            yylineno, s, yytext ? yytext : "<null>");
}

