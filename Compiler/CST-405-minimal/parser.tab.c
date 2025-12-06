/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "semantic.h"
#include "symtab.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char *yytext;
extern int yylineno;
void yyerror(const char* s);
ASTNode* root = NULL;

#line 89 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_FLOAT_LITERAL = 4,              /* FLOAT_LITERAL  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 7,               /* CHAR_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 8,               /* BOOL_LITERAL  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_BOOL = 11,                      /* BOOL  */
  YYSYMBOL_CHAR = 12,                      /* CHAR  */
  YYSYMBOL_STRING = 13,                    /* STRING  */
  YYSYMBOL_PRINT = 14,                     /* PRINT  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_VOID = 18,                      /* VOID  */
  YYSYMBOL_WHILE = 19,                     /* WHILE  */
  YYSYMBOL_RETRY = 20,                     /* RETRY  */
  YYSYMBOL_BACKOFF = 21,                   /* BACKOFF  */
  YYSYMBOL_ONFAIL = 22,                    /* ONFAIL  */
  YYSYMBOL_BREAK = 23,                     /* BREAK  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_NE = 25,                        /* NE  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_GE = 27,                        /* GE  */
  YYSYMBOL_LT = 28,                        /* LT  */
  YYSYMBOL_GT = 29,                        /* GT  */
  YYSYMBOL_AND = 30,                       /* AND  */
  YYSYMBOL_OR = 31,                        /* OR  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_EXPONENT = 33,                  /* EXPONENT  */
  YYSYMBOL_34_ = 34,                       /* '='  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_39_ = 39,                       /* '%'  */
  YYSYMBOL_UMINUS = 40,                    /* UMINUS  */
  YYSYMBOL_CAST = 41,                      /* CAST  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* '{'  */
  YYSYMBOL_45_ = 45,                       /* '}'  */
  YYSYMBOL_46_ = 46,                       /* '['  */
  YYSYMBOL_47_ = 47,                       /* ']'  */
  YYSYMBOL_48_ = 48,                       /* ','  */
  YYSYMBOL_49_ = 49,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_program = 51,                   /* program  */
  YYSYMBOL_func_list = 52,                 /* func_list  */
  YYSYMBOL_func_decl = 53,                 /* func_decl  */
  YYSYMBOL_type = 54,                      /* type  */
  YYSYMBOL_param_list = 55,                /* param_list  */
  YYSYMBOL_param = 56,                     /* param  */
  YYSYMBOL_stmt_list = 57,                 /* stmt_list  */
  YYSYMBOL_stmt = 58,                      /* stmt  */
  YYSYMBOL_return_stmt = 59,               /* return_stmt  */
  YYSYMBOL_break_stmt = 60,                /* break_stmt  */
  YYSYMBOL_block = 61,                     /* block  */
  YYSYMBOL_decl = 62,                      /* decl  */
  YYSYMBOL_assign = 63,                    /* assign  */
  YYSYMBOL_init_list = 64,                 /* init_list  */
  YYSYMBOL_if_stmt = 65,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 66,                /* while_stmt  */
  YYSYMBOL_retry_stmt = 67,                /* retry_stmt  */
  YYSYMBOL_print_stmt = 68,                /* print_stmt  */
  YYSYMBOL_expr = 69,                      /* expr  */
  YYSYMBOL_arg_list = 70                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   759

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    63,    63,    67,    68,    72,    75,    78,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    98,
      99,   103,   104,   108,   109,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   130,   131,   135,   140,   141,
     146,   153,   160,   167,   174,   181,   190,   199,   208,   217,
     226,   233,   240,   247,   254,   261,   272,   283,   302,   303,
     308,   309,   315,   320,   321,   322,   323,   328,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   344,   345,   346,
     347,   348,   349,   352,   353,   356,   357,   358,   359,   360,
     361,   364,   365,   368,   372,   379,   380
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "FLOAT_LITERAL",
  "ID", "STRING_LITERAL", "CHAR_LITERAL", "BOOL_LITERAL", "INT", "FLOAT",
  "BOOL", "CHAR", "STRING", "PRINT", "IF", "ELSE", "RETURN", "VOID",
  "WHILE", "RETRY", "BACKOFF", "ONFAIL", "BREAK", "EQ", "NE", "LE", "GE",
  "LT", "GT", "AND", "OR", "NOT", "EXPONENT", "'='", "'+'", "'-'", "'*'",
  "'/'", "'%'", "UMINUS", "CAST", "'('", "')'", "'{'", "'}'", "'['", "']'",
  "','", "';'", "$accept", "program", "func_list", "func_decl", "type",
  "param_list", "param", "stmt_list", "stmt", "return_stmt", "break_stmt",
  "block", "decl", "assign", "init_list", "if_stmt", "while_stmt",
  "retry_stmt", "print_stmt", "expr", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-128)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     276,   -43,   -22,    44,    48,    52,  -128,   100,   276,  -128,
     104,     2,    73,    75,    81,    83,  -128,  -128,    90,  -128,
    -128,  -128,  -128,  -128,     3,    91,   110,   143,     0,  -128,
     112,   346,   145,   129,   276,   346,   144,  -128,  -128,    49,
    -128,  -128,  -128,   191,   192,   194,   195,   203,   167,   176,
      61,   197,   198,   185,   424,   424,   408,   132,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,   443,   189,   346,
    -128,   175,  -128,   424,   367,   424,   -26,   -15,   -16,    36,
      -7,   424,   424,   -40,  -128,   460,   424,   239,  -128,   177,
    -128,   200,    88,  -128,  -128,   424,   424,   424,   424,   424,
     424,   424,   424,   424,   424,   424,   424,   424,   424,  -128,
    -128,   218,  -128,   477,  -128,   704,    53,   596,   424,   241,
    -128,   424,   242,  -128,   424,  -128,   424,   248,  -128,   424,
    -128,   644,   664,   424,  -128,   684,   122,   424,  -128,   220,
     220,    69,    69,    69,    69,   177,   720,   219,   124,   124,
     219,   219,   219,  -128,  -128,  -128,   424,   227,   494,   230,
     511,   232,   528,   545,   235,   562,   234,   304,   620,   304,
     304,   269,  -128,   704,   424,  -128,    -2,  -128,    37,  -128,
    -128,    38,  -128,  -128,   346,  -128,   275,  -128,  -128,   270,
     262,   579,   251,  -128,   254,  -128,   255,  -128,   261,   304,
     304,   297,  -128,   424,   424,   424,  -128,  -128,  -128,   258,
     -23,   704,   121,   127,   304,   253,   424,   271,   273,   282,
    -128,   704,  -128,  -128,   304,  -128
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     8,     9,    10,    11,    12,    13,     0,     2,     3,
       0,     0,     0,     0,     0,     0,     1,     4,     0,    14,
      15,    16,    17,    18,     0,    13,     0,     0,     0,    19,
       0,     0,    21,     0,     0,     0,     0,    68,    69,    73,
      72,    71,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    23,    30,
      32,    25,    26,    28,    29,    31,    27,     0,     0,     0,
      20,     0,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,    36,     0,     0,     0,    37,    92,
      91,     0,     0,     6,    24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      22,     0,     7,     0,    94,    95,     0,     0,     0,     0,
      40,     0,     0,    41,     0,    42,     0,     0,    43,     0,
      44,     0,     0,     0,    35,     0,     0,     0,    75,    89,
      90,    87,    88,    85,    86,    83,    84,    82,    77,    78,
      79,    80,    81,     5,    56,    93,     0,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    76,    96,     0,    45,     0,    46,     0,    47,
      48,     0,    49,    67,     0,    39,    60,    74,    62,    63,
       0,     0,     0,    50,     0,    51,     0,    52,     0,     0,
       0,     0,    57,     0,     0,     0,    38,    61,    65,     0,
       0,    58,     0,     0,     0,     0,     0,     0,     0,    64,
      53,    59,    54,    55,     0,    66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -128,  -128,  -128,   317,   -17,  -128,   292,   -34,   -31,  -128,
    -128,  -125,  -128,  -128,  -127,  -128,  -128,  -128,  -128,   -45,
    -128
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    28,    29,    57,   185,    59,
      60,   186,    61,    62,   210,    63,    64,    65,    66,    67,
     116
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,    71,    74,    11,    58,    85,   133,    27,   118,    89,
      90,    92,     1,     2,     3,     4,     5,    27,   124,   121,
     119,    25,   215,   120,    12,   216,    94,   129,   113,   115,
     117,   122,   192,   125,   123,   111,   131,   132,    58,    91,
      94,   135,   130,    33,   188,   189,    26,   193,    34,    19,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,    37,    38,    83,    40,    41,    42,
     126,   194,   196,   158,   207,   208,   160,   212,   213,   162,
      94,   163,   127,    73,   165,   128,   195,   197,   168,   219,
      13,    74,   172,    54,    14,    75,   155,    55,    15,   225,
      16,   156,   103,    56,   104,   105,   106,   107,   108,    18,
      84,   173,    95,    96,    97,    98,    99,   100,   101,   102,
      20,   103,    21,   104,   105,   106,   107,   108,    22,   191,
      23,   138,    24,    36,    30,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    32,    50,
     198,    51,    52,    58,    31,    53,    35,   103,   211,   211,
     211,   106,   107,   108,    54,   170,   217,    94,    55,   216,
     171,   221,   218,    69,    56,   216,    36,    93,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    68,    50,    72,    51,    52,    76,    77,    53,    78,
      79,    95,    96,    97,    98,    99,   100,    54,    80,    81,
     103,    55,   104,   105,   106,   107,   108,    56,    82,    36,
     112,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    88,    50,   110,    51,    52,    86,
      87,    53,   136,   137,   159,   161,    97,    98,    99,   100,
      54,   164,   103,   103,    55,   104,   105,   106,   107,   108,
      56,   174,    36,   153,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,   176,    50,   178,
      51,    52,   181,   183,    53,     1,     2,     3,     4,     5,
     190,   199,   200,    54,     6,   203,   201,    55,   204,   205,
     209,   214,   220,    56,   224,    36,   206,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
     222,    50,   223,    51,    52,    17,    70,    53,     0,     0,
       0,     0,     0,     0,     0,     0,    54,     0,     0,     0,
      55,     0,     0,     0,     0,     0,    56,    36,   184,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,     0,    50,     0,    51,    52,     0,     0,    53,
      37,    38,    83,    40,    41,    42,     0,     0,    54,     0,
       0,     0,    55,     0,     0,     0,     0,     0,    56,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
       0,     0,     0,    55,     0,     0,     0,     0,     0,    56,
     114,    37,    38,    83,    40,    41,    42,     1,     2,     3,
       4,     5,     0,     0,     0,     0,     6,    37,    38,    83,
      40,    41,    42,     0,     0,     0,     0,     0,     0,     0,
      54,     0,     0,     0,    55,     0,     0,     0,     0,     0,
      56,     0,     0,     0,     0,     0,    54,     0,     0,     0,
      55,     0,     0,     0,     0,     0,    56,    95,    96,    97,
      98,    99,   100,   101,   102,     0,   103,     0,   104,   105,
     106,   107,   108,     0,    95,    96,    97,    98,    99,   100,
     101,   102,   109,   103,     0,   104,   105,   106,   107,   108,
       0,    95,    96,    97,    98,    99,   100,   101,   102,   134,
     103,     0,   104,   105,   106,   107,   108,     0,    95,    96,
      97,    98,    99,   100,   101,   102,   154,   103,     0,   104,
     105,   106,   107,   108,     0,    95,    96,    97,    98,    99,
     100,   101,   102,   175,   103,     0,   104,   105,   106,   107,
     108,     0,    95,    96,    97,    98,    99,   100,   101,   102,
     177,   103,     0,   104,   105,   106,   107,   108,     0,    95,
      96,    97,    98,    99,   100,   101,   102,   179,   103,     0,
     104,   105,   106,   107,   108,     0,    95,    96,    97,    98,
      99,   100,   101,   102,   180,   103,     0,   104,   105,   106,
     107,   108,     0,    95,    96,    97,    98,    99,   100,   101,
     102,   182,   103,     0,   104,   105,   106,   107,   108,     0,
      95,    96,    97,    98,    99,   100,   101,   102,   202,   103,
       0,   104,   105,   106,   107,   108,     0,     0,     0,     0,
       0,     0,     0,   157,    95,    96,    97,    98,    99,   100,
     101,   102,     0,   103,     0,   104,   105,   106,   107,   108,
       0,     0,     0,     0,     0,     0,     0,   187,    95,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,   108,     0,     0,     0,   166,    95,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,   108,     0,     0,     0,   167,    95,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,   108,     0,     0,     0,   169,    95,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,   108,    95,    96,    97,    98,    99,   100,
     101,     0,     0,   103,     0,   104,   105,   106,   107,   108
};

static const yytype_int16 yycheck[] =
{
      31,    35,    42,    46,    35,    50,    46,    24,    34,    54,
      55,    56,     9,    10,    11,    12,    13,    34,    34,    34,
      46,    18,    45,    49,    46,    48,    57,    34,    73,    74,
      75,    46,    34,    49,    49,    69,    81,    82,    69,    56,
      71,    86,    49,    43,   169,   170,    43,    49,    48,    47,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,     3,     4,     5,     6,     7,     8,
      34,    34,    34,   118,   199,   200,   121,   204,   205,   124,
     111,   126,    46,    34,   129,    49,    49,    49,   133,   214,
      46,    42,   137,    32,    46,    46,    43,    36,    46,   224,
       0,    48,    33,    42,    35,    36,    37,    38,    39,     5,
      49,   156,    24,    25,    26,    27,    28,    29,    30,    31,
      47,    33,    47,    35,    36,    37,    38,    39,    47,   174,
      47,    43,    42,     1,    43,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,     5,    17,
     184,    19,    20,   184,    44,    23,    44,    33,   203,   204,
     205,    37,    38,    39,    32,    43,    45,   198,    36,    48,
      48,   216,    45,    44,    42,    48,     1,    45,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    46,    17,    49,    19,    20,     5,     5,    23,     5,
       5,    24,    25,    26,    27,    28,    29,    32,     5,    42,
      33,    36,    35,    36,    37,    38,    39,    42,    42,     1,
      45,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    49,    17,    47,    19,    20,    42,
      42,    23,     3,    43,     3,     3,    26,    27,    28,    29,
      32,     3,    33,    33,    36,    35,    36,    37,    38,    39,
      42,    34,     1,    45,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    47,    17,    47,
      19,    20,    47,    49,    23,     9,    10,    11,    12,    13,
      21,    16,    22,    32,    18,    44,    34,    36,    44,    44,
       3,    43,    49,    42,    22,     1,    45,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      49,    17,    49,    19,    20,     8,    34,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    42,     1,    44,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    17,    -1,    19,    20,    -1,    -1,    23,
       3,     4,     5,     6,     7,     8,    -1,    -1,    32,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    18,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    42,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,    -1,    35,    36,
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
      24,    25,    26,    27,    28,    29,    30,    31,    49,    33,
      -1,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    -1,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    43,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    43,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    43,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    35,
      36,    37,    38,    39,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    -1,    35,    36,    37,    38,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    10,    11,    12,    13,    18,    51,    52,    53,
      54,    46,    46,    46,    46,    46,     0,    53,     5,    47,
      47,    47,    47,    47,    42,    18,    43,    54,    55,    56,
      43,    44,     5,    43,    48,    44,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      17,    19,    20,    23,    32,    36,    42,    57,    58,    59,
      60,    62,    63,    65,    66,    67,    68,    69,    46,    44,
      56,    57,    49,    34,    42,    46,     5,     5,     5,     5,
       5,    42,    42,     5,    49,    69,    42,    42,    49,    69,
      69,    54,    69,    45,    58,    24,    25,    26,    27,    28,
      29,    30,    31,    33,    35,    36,    37,    38,    39,    49,
      47,    57,    45,    69,    43,    69,    70,    69,    34,    46,
      49,    34,    46,    49,    34,    49,    34,    46,    49,    34,
      49,    69,    69,    46,    49,    69,     3,    43,    43,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    45,    49,    43,    48,    47,    69,     3,
      69,     3,    69,    69,     3,    69,    43,    43,    69,    43,
      43,    48,    69,    69,    34,    49,    47,    49,    47,    49,
      49,    47,    49,    49,    44,    58,    61,    47,    61,    61,
      21,    69,    34,    49,    34,    49,    34,    49,    57,    16,
      22,    34,    49,    44,    44,    44,    45,    61,    61,     3,
      64,    69,    64,    64,    43,    45,    48,    45,    45,    61,
      49,    69,    49,    49,    22,    61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    59,    59,    60,    61,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    63,    63,    64,    64,
      65,    65,    66,    67,    67,    67,    67,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     8,     7,     8,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       3,     2,     4,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     3,     2,     2,     3,     1,
       3,     3,     3,     3,     3,     5,     5,     5,     5,     5,
       6,     6,     6,    10,    10,    10,     4,     7,     1,     3,
       5,     7,     5,     5,     9,     7,    11,     5,     1,     1,
       1,     1,     1,     1,     4,     3,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: func_list  */
#line 63 "parser.y"
              { root = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 1391 "parser.tab.c"
    break;

  case 3: /* func_list: func_decl  */
#line 67 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1397 "parser.tab.c"
    break;

  case 4: /* func_list: func_list func_decl  */
#line 68 "parser.y"
                                { (yyval.node) = createFuncList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1403 "parser.tab.c"
    break;

  case 5: /* func_decl: type ID '(' param_list ')' '{' stmt_list '}'  */
#line 72 "parser.y"
                                                 {
        (yyval.node) = createFuncDecl((yyvsp[-7].str), (yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node));
    }
#line 1411 "parser.tab.c"
    break;

  case 6: /* func_decl: type ID '(' ')' '{' stmt_list '}'  */
#line 75 "parser.y"
                                        {
        (yyval.node) = createFuncDecl((yyvsp[-6].str), (yyvsp[-5].str), NULL, (yyvsp[-1].node));
    }
#line 1419 "parser.tab.c"
    break;

  case 7: /* func_decl: type ID '(' VOID ')' '{' stmt_list '}'  */
#line 78 "parser.y"
                                             {
        (yyval.node) = createFuncDecl((yyvsp[-7].str), (yyvsp[-6].str), NULL, (yyvsp[-1].node));
    }
#line 1427 "parser.tab.c"
    break;

  case 8: /* type: INT  */
#line 84 "parser.y"
              { (yyval.str) = "int"; }
#line 1433 "parser.tab.c"
    break;

  case 9: /* type: FLOAT  */
#line 85 "parser.y"
              { (yyval.str) = "float"; }
#line 1439 "parser.tab.c"
    break;

  case 10: /* type: BOOL  */
#line 86 "parser.y"
              { (yyval.str) = "bool"; }
#line 1445 "parser.tab.c"
    break;

  case 11: /* type: CHAR  */
#line 87 "parser.y"
              { (yyval.str) = "char"; }
#line 1451 "parser.tab.c"
    break;

  case 12: /* type: STRING  */
#line 88 "parser.y"
              { (yyval.str) = "string"; }
#line 1457 "parser.tab.c"
    break;

  case 13: /* type: VOID  */
#line 89 "parser.y"
              { (yyval.str) = "void"; }
#line 1463 "parser.tab.c"
    break;

  case 14: /* type: INT '[' ']'  */
#line 90 "parser.y"
                      { (yyval.str) = "int[]"; }
#line 1469 "parser.tab.c"
    break;

  case 15: /* type: FLOAT '[' ']'  */
#line 91 "parser.y"
                      { (yyval.str) = "float[]"; }
#line 1475 "parser.tab.c"
    break;

  case 16: /* type: BOOL '[' ']'  */
#line 92 "parser.y"
                      { (yyval.str) = "bool[]"; }
#line 1481 "parser.tab.c"
    break;

  case 17: /* type: CHAR '[' ']'  */
#line 93 "parser.y"
                      { (yyval.str) = "char[]"; }
#line 1487 "parser.tab.c"
    break;

  case 18: /* type: STRING '[' ']'  */
#line 94 "parser.y"
                      { (yyval.str) = "string[]"; }
#line 1493 "parser.tab.c"
    break;

  case 19: /* param_list: param  */
#line 98 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1499 "parser.tab.c"
    break;

  case 20: /* param_list: param_list ',' param  */
#line 99 "parser.y"
                                { (yyval.node) = createParamList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1505 "parser.tab.c"
    break;

  case 21: /* param: type ID  */
#line 103 "parser.y"
                                { (yyval.node) = createParam((yyvsp[-1].str), (yyvsp[0].str)); }
#line 1511 "parser.tab.c"
    break;

  case 22: /* param: type ID '[' ']'  */
#line 104 "parser.y"
                                { (yyval.node) = createArrayParam((yyvsp[-3].str), (yyvsp[-2].str)); }
#line 1517 "parser.tab.c"
    break;

  case 23: /* stmt_list: stmt  */
#line 108 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1523 "parser.tab.c"
    break;

  case 24: /* stmt_list: stmt_list stmt  */
#line 109 "parser.y"
                                { (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1529 "parser.tab.c"
    break;

  case 33: /* stmt: expr ';'  */
#line 121 "parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1535 "parser.tab.c"
    break;

  case 34: /* stmt: error ';'  */
#line 122 "parser.y"
                                { 
          reportSpecificError(ERROR_MISSING_SEMICOLON, "");
          yyerrok; 
          (yyval.node) = NULL; 
      }
#line 1545 "parser.tab.c"
    break;

  case 35: /* return_stmt: RETURN expr ';'  */
#line 130 "parser.y"
                                { (yyval.node) = createReturn((yyvsp[-1].node)); }
#line 1551 "parser.tab.c"
    break;

  case 36: /* return_stmt: RETURN ';'  */
#line 131 "parser.y"
                                { (yyval.node) = createReturn(NULL); }
#line 1557 "parser.tab.c"
    break;

  case 37: /* break_stmt: BREAK ';'  */
#line 135 "parser.y"
                                { (yyval.node) = createBreak(); }
#line 1563 "parser.tab.c"
    break;

  case 38: /* block: '{' stmt_list '}'  */
#line 140 "parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1569 "parser.tab.c"
    break;

  case 39: /* block: stmt  */
#line 141 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1575 "parser.tab.c"
    break;

  case 40: /* decl: INT ID ';'  */
#line 146 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-1].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-1].str));
          }
          (yyval.node) = createDecl("int", (yyvsp[-1].str)); 
          free((yyvsp[-1].str)); 
      }
#line 1587 "parser.tab.c"
    break;

  case 41: /* decl: FLOAT ID ';'  */
#line 153 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-1].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-1].str));
          }
          (yyval.node) = createDecl("float", (yyvsp[-1].str)); 
          free((yyvsp[-1].str)); 
      }
#line 1599 "parser.tab.c"
    break;

  case 42: /* decl: BOOL ID ';'  */
#line 160 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-1].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-1].str));
          }
          (yyval.node) = createDecl("bool", (yyvsp[-1].str)); 
          free((yyvsp[-1].str)); 
      }
#line 1611 "parser.tab.c"
    break;

  case 43: /* decl: CHAR ID ';'  */
#line 167 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-1].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-1].str));
          }
          (yyval.node) = createDecl("char", (yyvsp[-1].str)); 
          free((yyvsp[-1].str)); 
      }
#line 1623 "parser.tab.c"
    break;

  case 44: /* decl: STRING ID ';'  */
#line 174 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-1].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-1].str));
          }
          (yyval.node) = createDecl("string", (yyvsp[-1].str)); 
          free((yyvsp[-1].str)); 
      }
#line 1635 "parser.tab.c"
    break;

  case 45: /* decl: INT ID '=' expr ';'  */
#line 181 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-3].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-3].str));
          }
          char* exprType = getExpressionType((yyvsp[-1].node));
          checkAssignmentType("int", exprType);
          (yyval.node) = createDeclInit("int", (yyvsp[-3].str), (yyvsp[-1].node)); 
          free((yyvsp[-3].str)); 
      }
#line 1649 "parser.tab.c"
    break;

  case 46: /* decl: FLOAT ID '=' expr ';'  */
#line 190 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-3].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-3].str));
          }
          char* exprType = getExpressionType((yyvsp[-1].node));
          checkAssignmentType("float", exprType);
          (yyval.node) = createDeclInit("float", (yyvsp[-3].str), (yyvsp[-1].node)); 
          free((yyvsp[-3].str)); 
      }
#line 1663 "parser.tab.c"
    break;

  case 47: /* decl: BOOL ID '=' expr ';'  */
#line 199 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-3].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-3].str));
          }
          char* exprType = getExpressionType((yyvsp[-1].node));
          checkAssignmentType("bool", exprType);
          (yyval.node) = createDeclInit("bool", (yyvsp[-3].str), (yyvsp[-1].node)); 
          free((yyvsp[-3].str)); 
      }
#line 1677 "parser.tab.c"
    break;

  case 48: /* decl: CHAR ID '=' expr ';'  */
#line 208 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-3].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-3].str));
          }
          char* exprType = getExpressionType((yyvsp[-1].node));
          checkAssignmentType("char", exprType);
          (yyval.node) = createDeclInit("char", (yyvsp[-3].str), (yyvsp[-1].node)); 
          free((yyvsp[-3].str)); 
      }
#line 1691 "parser.tab.c"
    break;

  case 49: /* decl: STRING ID '=' expr ';'  */
#line 217 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-3].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-3].str));
          }
          char* exprType = getExpressionType((yyvsp[-1].node));
          checkAssignmentType("string", exprType);
          (yyval.node) = createDeclInit("string", (yyvsp[-3].str), (yyvsp[-1].node)); 
          free((yyvsp[-3].str)); 
      }
#line 1705 "parser.tab.c"
    break;

  case 50: /* decl: INT ID '[' NUM ']' ';'  */
#line 226 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-4].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-4].str));
          }
          (yyval.node) = createArrayDecl("int", (yyvsp[-4].str), (yyvsp[-2].num)); 
          free((yyvsp[-4].str)); 
      }
#line 1717 "parser.tab.c"
    break;

  case 51: /* decl: FLOAT ID '[' NUM ']' ';'  */
#line 233 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-4].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-4].str));
          }
          (yyval.node) = createArrayDecl("float", (yyvsp[-4].str), (yyvsp[-2].num)); 
          free((yyvsp[-4].str)); 
      }
#line 1729 "parser.tab.c"
    break;

  case 52: /* decl: CHAR ID '[' NUM ']' ';'  */
#line 240 "parser.y"
                                { 
          if (isInCurrentScope((yyvsp[-4].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-4].str));
          }
          (yyval.node) = createArrayDecl("char", (yyvsp[-4].str), (yyvsp[-2].num)); 
          free((yyvsp[-4].str)); 
      }
#line 1741 "parser.tab.c"
    break;

  case 53: /* decl: INT ID '[' NUM ']' '=' '{' init_list '}' ';'  */
#line 247 "parser.y"
                                                      { 
          if (isInCurrentScope((yyvsp[-8].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-8].str));
          }
          (yyval.node) = createArrayInitDecl("int", (yyvsp[-8].str), (yyvsp[-6].num), (yyvsp[-2].node)); 
          free((yyvsp[-8].str)); 
      }
#line 1753 "parser.tab.c"
    break;

  case 54: /* decl: FLOAT ID '[' NUM ']' '=' '{' init_list '}' ';'  */
#line 254 "parser.y"
                                                      { 
          if (isInCurrentScope((yyvsp[-8].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-8].str));
          }
          (yyval.node) = createArrayInitDecl("float", (yyvsp[-8].str), (yyvsp[-6].num), (yyvsp[-2].node)); 
          free((yyvsp[-8].str)); 
      }
#line 1765 "parser.tab.c"
    break;

  case 55: /* decl: CHAR ID '[' NUM ']' '=' '{' init_list '}' ';'  */
#line 261 "parser.y"
                                                      { 
          if (isInCurrentScope((yyvsp[-8].str))) {
              reportSpecificError(ERROR_DUPLICATE_VAR, (yyvsp[-8].str));
          }
          (yyval.node) = createArrayInitDecl("char", (yyvsp[-8].str), (yyvsp[-6].num), (yyvsp[-2].node)); 
          free((yyvsp[-8].str)); 
      }
#line 1777 "parser.tab.c"
    break;

  case 56: /* assign: ID '=' expr ';'  */
#line 272 "parser.y"
                                { 
          Symbol* sym = lookupSymbol((yyvsp[-3].str));
          if (!sym) {
              reportSpecificError(ERROR_UNDECLARED_VAR, (yyvsp[-3].str));
          } else {
              char* exprType = getExpressionType((yyvsp[-1].node));
              checkAssignmentType(sym->type, exprType);
          }
          (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node)); 
          free((yyvsp[-3].str)); 
      }
#line 1793 "parser.tab.c"
    break;

  case 57: /* assign: ID '[' expr ']' '=' expr ';'  */
#line 283 "parser.y"
                                    { 
          Symbol* sym = lookupSymbol((yyvsp[-6].str));
          if (!sym) {
              reportSpecificError(ERROR_UNDECLARED_VAR, (yyvsp[-6].str));
          } else if (!sym->isArray) {
              reportSpecificError(ERROR_UNDECLARED_VAR, (yyvsp[-6].str));
          } else {
              char* indexType = getExpressionType((yyvsp[-4].node));
              checkArrayIndexType(indexType);
              char* exprType = getExpressionType((yyvsp[-1].node));
              checkAssignmentType(sym->type, exprType);
          }
          (yyval.node) = createArrayAssign((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node)); 
          free((yyvsp[-6].str)); 
      }
#line 1813 "parser.tab.c"
    break;

  case 58: /* init_list: expr  */
#line 302 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1819 "parser.tab.c"
    break;

  case 59: /* init_list: init_list ',' expr  */
#line 303 "parser.y"
                                { (yyval.node) = createInitList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1825 "parser.tab.c"
    break;

  case 60: /* if_stmt: IF '(' expr ')' block  */
#line 308 "parser.y"
                                { (yyval.node) = createIf((yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1831 "parser.tab.c"
    break;

  case 61: /* if_stmt: IF '(' expr ')' block ELSE block  */
#line 310 "parser.y"
                                { (yyval.node) = createIf((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1837 "parser.tab.c"
    break;

  case 62: /* while_stmt: WHILE '(' expr ')' block  */
#line 315 "parser.y"
                                { (yyval.node) = createWhile((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1843 "parser.tab.c"
    break;

  case 63: /* retry_stmt: RETRY '(' NUM ')' block  */
#line 320 "parser.y"
                                                        { (yyval.node) = createRetry((yyvsp[-2].num), 0, (yyvsp[0].node), NULL); }
#line 1849 "parser.tab.c"
    break;

  case 64: /* retry_stmt: RETRY '(' NUM ',' BACKOFF '=' NUM ')' block  */
#line 321 "parser.y"
                                                        { (yyval.node) = createRetry((yyvsp[-6].num), (yyvsp[-2].num), (yyvsp[0].node), NULL); }
#line 1855 "parser.tab.c"
    break;

  case 65: /* retry_stmt: RETRY '(' NUM ')' block ONFAIL block  */
#line 322 "parser.y"
                                                        { (yyval.node) = createRetry((yyvsp[-4].num), 0, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1861 "parser.tab.c"
    break;

  case 66: /* retry_stmt: RETRY '(' NUM ',' BACKOFF '=' NUM ')' block ONFAIL block  */
#line 323 "parser.y"
                                                                { (yyval.node) = createRetry((yyvsp[-8].num), (yyvsp[-4].num), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1867 "parser.tab.c"
    break;

  case 67: /* print_stmt: PRINT '(' expr ')' ';'  */
#line 328 "parser.y"
                                { (yyval.node) = createPrint((yyvsp[-2].node)); }
#line 1873 "parser.tab.c"
    break;

  case 68: /* expr: NUM  */
#line 333 "parser.y"
                                { (yyval.node) = createNum((yyvsp[0].num)); }
#line 1879 "parser.tab.c"
    break;

  case 69: /* expr: FLOAT_LITERAL  */
#line 334 "parser.y"
                                { (yyval.node) = createFloat((yyvsp[0].floats)); }
#line 1885 "parser.tab.c"
    break;

  case 70: /* expr: BOOL_LITERAL  */
#line 335 "parser.y"
                                { (yyval.node) = createBool((yyvsp[0].boolean)); }
#line 1891 "parser.tab.c"
    break;

  case 71: /* expr: CHAR_LITERAL  */
#line 336 "parser.y"
                                { (yyval.node) = createChar((yyvsp[0].character)); }
#line 1897 "parser.tab.c"
    break;

  case 72: /* expr: STRING_LITERAL  */
#line 337 "parser.y"
                                { (yyval.node) = createString((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1903 "parser.tab.c"
    break;

  case 73: /* expr: ID  */
#line 338 "parser.y"
                                { (yyval.node) = createVar((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1909 "parser.tab.c"
    break;

  case 74: /* expr: ID '[' expr ']'  */
#line 339 "parser.y"
                                { (yyval.node) = createArrayAccess((yyvsp[-3].str), (yyvsp[-1].node)); free((yyvsp[-3].str)); }
#line 1915 "parser.tab.c"
    break;

  case 75: /* expr: '(' expr ')'  */
#line 340 "parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1921 "parser.tab.c"
    break;

  case 76: /* expr: '(' type ')' expr  */
#line 341 "parser.y"
                                   { (yyval.node) = createCast((yyvsp[-2].str), (yyvsp[0].node)); }
#line 1927 "parser.tab.c"
    break;

  case 77: /* expr: expr '+' expr  */
#line 344 "parser.y"
                                { (yyval.node) = createBinOp(BINOP_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1933 "parser.tab.c"
    break;

  case 78: /* expr: expr '-' expr  */
#line 345 "parser.y"
                                { (yyval.node) = createBinOp(BINOP_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1939 "parser.tab.c"
    break;

  case 79: /* expr: expr '*' expr  */
#line 346 "parser.y"
                                { (yyval.node) = createBinOp(BINOP_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1945 "parser.tab.c"
    break;

  case 80: /* expr: expr '/' expr  */
#line 347 "parser.y"
                                { (yyval.node) = createBinOp(BINOP_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1951 "parser.tab.c"
    break;

  case 81: /* expr: expr '%' expr  */
#line 348 "parser.y"
                                { (yyval.node) = createBinOp(BINOP_MOD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1957 "parser.tab.c"
    break;

  case 82: /* expr: expr EXPONENT expr  */
#line 349 "parser.y"
                                { (yyval.node) = createBinOp(BINOP_EXP, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1963 "parser.tab.c"
    break;

  case 83: /* expr: expr AND expr  */
#line 352 "parser.y"
                                { (yyval.node) = createBinOp(BINOP_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1969 "parser.tab.c"
    break;

  case 84: /* expr: expr OR expr  */
#line 353 "parser.y"
                                { (yyval.node) = createBinOp(BINOP_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1975 "parser.tab.c"
    break;

  case 85: /* expr: expr LT expr  */
#line 356 "parser.y"
                                { (yyval.node) = createRelop(RELOP_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1981 "parser.tab.c"
    break;

  case 86: /* expr: expr GT expr  */
#line 357 "parser.y"
                                { (yyval.node) = createRelop(RELOP_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1987 "parser.tab.c"
    break;

  case 87: /* expr: expr LE expr  */
#line 358 "parser.y"
                                { (yyval.node) = createRelop(RELOP_LE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1993 "parser.tab.c"
    break;

  case 88: /* expr: expr GE expr  */
#line 359 "parser.y"
                                { (yyval.node) = createRelop(RELOP_GE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1999 "parser.tab.c"
    break;

  case 89: /* expr: expr EQ expr  */
#line 360 "parser.y"
                                { (yyval.node) = createRelop(RELOP_EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2005 "parser.tab.c"
    break;

  case 90: /* expr: expr NE expr  */
#line 361 "parser.y"
                                { (yyval.node) = createRelop(RELOP_NE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2011 "parser.tab.c"
    break;

  case 91: /* expr: '-' expr  */
#line 364 "parser.y"
                                { (yyval.node) = createUnaryOp(UNOP_NEG, (yyvsp[0].node)); }
#line 2017 "parser.tab.c"
    break;

  case 92: /* expr: NOT expr  */
#line 365 "parser.y"
                                { (yyval.node) = createUnaryOp(UNOP_NOT, (yyvsp[0].node)); }
#line 2023 "parser.tab.c"
    break;

  case 93: /* expr: ID '(' arg_list ')'  */
#line 368 "parser.y"
                                { 
          checkFunctionCall((yyvsp[-3].str), (yyvsp[-1].node));
          (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node)); 
      }
#line 2032 "parser.tab.c"
    break;

  case 94: /* expr: ID '(' ')'  */
#line 372 "parser.y"
                                { 
          checkFunctionCall((yyvsp[-2].str), NULL);
          (yyval.node) = createFuncCall((yyvsp[-2].str), NULL); 
      }
#line 2041 "parser.tab.c"
    break;

  case 95: /* arg_list: expr  */
#line 379 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2047 "parser.tab.c"
    break;

  case 96: /* arg_list: arg_list ',' expr  */
#line 380 "parser.y"
                                { (yyval.node) = createArgList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2053 "parser.tab.c"
    break;


#line 2057 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 383 "parser.y"


void yyerror(const char* s) {
    semantic_errors++;
    
    /* Specific error detection based on context */
    if (yytext) {
        if (strcmp(yytext, "}") == 0) {
            reportSpecificError(ERROR_MISMATCHED_BRACE, "Unexpected closing brace - missing opening brace or extra closing brace");
        } else if (strcmp(yytext, "{") == 0) {
            reportSpecificError(ERROR_MISSING_SEMICOLON, "");
            printf("   Location: Before '{' - missing semicolon at end of previous statement\n");
        } else if (strstr(yytext, "\n") || strlen(yytext) == 0) {
            reportSpecificError(ERROR_MISSING_SEMICOLON, "");
            printf("   Location: Line %d - statement not properly terminated\n", yylineno);
        } else {
            /* Generic syntax error for other cases */
            printf("✗ Syntax Error at line %d: %s (near \"%s\")\n",
                   yylineno, s, yytext);
            printf("   Check syntax rules for the C-Minus language\n");
        }
    } else {
        printf("✗ Syntax Error at line %d: %s\n", yylineno, s);
    }
}
