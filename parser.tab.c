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
#line 1 "parser.y"

    /*Definition section */
    #include "include/common.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include<string.h>
    #include <stdarg.h>
    #include "include/parser.h"
    #include "include/symbolTable.h"
    extern FILE *yyin;
    extern int yylex(void);
    void yyerror(const char *str);
    void read_file(char *filename);
    void yywarning(const char* str);
    FILE* errorsFile;
    FILE* warningsFile;
    FILE* OutputQuadraplesFile;
    int Labels;
    int CaseLabels;
    int EndSwitchLabel;
    int EnumValue;
    int TempVariables;
    nodeType *createOperationNode(int oper, int nops, ...);
    nodeType *createIdentifierNode(char *name);
    nodeType *constantValue(DataTypeEnum type, void* value);
    nodeType *createType(DataTypeEnum type);
    DataTypeEnum coercion(DataTypeEnum type1, DataTypeEnum type2);
    DataTypeEnum execute(nodeType *p);
    DataTypeEnum getIdentifierType(char* identifierName);
    nodeType *createParameterList(nodeType * node, nodeType * identifier);
    nodeType *addToParameterList(nodeType * parameterList, nodeType* node, nodeType * parameter);
    nodeType *createParameterCallList(nodeType * node);
    nodeType *addToParameterCallList(nodeType * parameterList, nodeType* node);
    void freeNode(nodeType *p);
    SymbolTable* st = SymbolTable::getInstance();
    Node *currentScope = new Node();
    Node *rootScope = currentScope;

#line 110 "parser.tab.c"

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
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_DO = 7,                         /* DO  */
  YYSYMBOL_SWITCH = 8,                     /* SWITCH  */
  YYSYMBOL_CASE = 9,                       /* CASE  */
  YYSYMBOL_BREAK = 10,                     /* BREAK  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_ENUM = 12,                      /* ENUM  */
  YYSYMBOL_VOID = 13,                      /* VOID  */
  YYSYMBOL_INT_TYPE = 14,                  /* INT_TYPE  */
  YYSYMBOL_CHAR_TYPE = 15,                 /* CHAR_TYPE  */
  YYSYMBOL_BOOL_TYPE = 16,                 /* BOOL_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 17,                /* FLOAT_TYPE  */
  YYSYMBOL_STRING_TYPE = 18,               /* STRING_TYPE  */
  YYSYMBOL_CONST = 19,                     /* CONST  */
  YYSYMBOL_EQ = 20,                        /* EQ  */
  YYSYMBOL_NE = 21,                        /* NE  */
  YYSYMBOL_GE = 22,                        /* GE  */
  YYSYMBOL_LE = 23,                        /* LE  */
  YYSYMBOL_INC = 24,                       /* INC  */
  YYSYMBOL_DEC = 25,                       /* DEC  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_GT = 28,                        /* GT  */
  YYSYMBOL_LT = 29,                        /* LT  */
  YYSYMBOL_PLUS = 30,                      /* PLUS  */
  YYSYMBOL_MINUS = 31,                     /* MINUS  */
  YYSYMBOL_MULT = 32,                      /* MULT  */
  YYSYMBOL_DIV = 33,                       /* DIV  */
  YYSYMBOL_MOD = 34,                       /* MOD  */
  YYSYMBOL_NOT = 35,                       /* NOT  */
  YYSYMBOL_ASSIGN = 36,                    /* ASSIGN  */
  YYSYMBOL_INTEGER = 37,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 38,                     /* FLOAT  */
  YYSYMBOL_BOOL_FALSE = 39,                /* BOOL_FALSE  */
  YYSYMBOL_BOOL_TRUE = 40,                 /* BOOL_TRUE  */
  YYSYMBOL_CHAR = 41,                      /* CHAR  */
  YYSYMBOL_STRING = 42,                    /* STRING  */
  YYSYMBOL_VARIABLE = 43,                  /* VARIABLE  */
  YYSYMBOL_44_ = 44,                       /* ';'  */
  YYSYMBOL_45_ = 45,                       /* '('  */
  YYSYMBOL_46_ = 46,                       /* ')'  */
  YYSYMBOL_47_ = 47,                       /* '{'  */
  YYSYMBOL_48_ = 48,                       /* '}'  */
  YYSYMBOL_49_ = 49,                       /* ':'  */
  YYSYMBOL_50_ = 50,                       /* ','  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_root = 53,                      /* root  */
  YYSYMBOL_statement = 54,                 /* statement  */
  YYSYMBOL_recursive_statement = 55,       /* recursive_statement  */
  YYSYMBOL_conditional_statement = 56,     /* conditional_statement  */
  YYSYMBOL_if_conditional_statement = 57,  /* if_conditional_statement  */
  YYSYMBOL_switch_conditional_statement = 58, /* switch_conditional_statement  */
  YYSYMBOL_case_statement = 59,            /* case_statement  */
  YYSYMBOL_loop_statement = 60,            /* loop_statement  */
  YYSYMBOL_for_loop_statement = 61,        /* for_loop_statement  */
  YYSYMBOL_while_loop_statement = 62,      /* while_loop_statement  */
  YYSYMBOL_do_while_loop_statement = 63,   /* do_while_loop_statement  */
  YYSYMBOL_assignment = 64,                /* assignment  */
  YYSYMBOL_expressions = 65,               /* expressions  */
  YYSYMBOL_equality_expression = 66,       /* equality_expression  */
  YYSYMBOL_relational_expression = 67,     /* relational_expression  */
  YYSYMBOL_additive_expression = 68,       /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 69, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 70,          /* unary_expression  */
  YYSYMBOL_primary_expression = 71,        /* primary_expression  */
  YYSYMBOL_function_call = 72,             /* function_call  */
  YYSYMBOL_functional_statement = 73,      /* functional_statement  */
  YYSYMBOL_function_parameters = 74,       /* function_parameters  */
  YYSYMBOL_parameter = 75,                 /* parameter  */
  YYSYMBOL_function_parameters_calls = 76, /* function_parameters_calls  */
  YYSYMBOL_parameter_calls = 77,           /* parameter_calls  */
  YYSYMBOL_function = 78,                  /* function  */
  YYSYMBOL_return_types = 79,              /* return_types  */
  YYSYMBOL_enum_statement = 80,            /* enum_statement  */
  YYSYMBOL_enum_variables = 81,            /* enum_variables  */
  YYSYMBOL_variable_Type = 82,             /* variable_Type  */
  YYSYMBOL_variable_value = 83             /* variable_value  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   487

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      45,    46,     2,     2,    50,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    49,    44,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    48,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    76,    76,    80,    84,    88,    93,    96,   101,   106,
     112,   117,   123,   128,   134,   138,   144,   150,   155,   161,
     166,   171,   177,   183,   190,   197,   201,   205,   209,   213,
     222,   226,   230,   238,   242,   246,   250,   254,   260,   264,
     268,   274,   278,   282,   288,   292,   296,   300,   306,   310,
     314,   318,   322,   328,   332,   332,   336,   343,   349,   354,
     359,   364,   368,   374,   379,   384,   388,   394,   398,   404,
     410,   416,   420,   424,   428,   435,   439,   443,   447,   451,
     457,   461,   465,   469,   473,   477
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "DO", "SWITCH", "CASE", "BREAK", "RETURN", "ENUM", "VOID",
  "INT_TYPE", "CHAR_TYPE", "BOOL_TYPE", "FLOAT_TYPE", "STRING_TYPE",
  "CONST", "EQ", "NE", "GE", "LE", "INC", "DEC", "AND", "OR", "GT", "LT",
  "PLUS", "MINUS", "MULT", "DIV", "MOD", "NOT", "ASSIGN", "INTEGER",
  "FLOAT", "BOOL_FALSE", "BOOL_TRUE", "CHAR", "STRING", "VARIABLE", "';'",
  "'('", "')'", "'{'", "'}'", "':'", "','", "$accept", "program", "root",
  "statement", "recursive_statement", "conditional_statement",
  "if_conditional_statement", "switch_conditional_statement",
  "case_statement", "loop_statement", "for_loop_statement",
  "while_loop_statement", "do_while_loop_statement", "assignment",
  "expressions", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "primary_expression", "function_call", "functional_statement",
  "function_parameters", "parameter", "function_parameters_calls",
  "parameter_calls", "function", "return_types", "enum_statement",
  "enum_variables", "variable_Type", "variable_value", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-51)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -51,    16,   322,   -51,   -31,   -27,   -21,    -7,    -3,    15,
      27,   -51,   -51,   -51,   -51,   -51,   153,    36,    36,    36,
      36,   -51,   -51,   -51,   -51,   -51,   -51,     5,    36,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,    28,     8,   191,
      19,    78,    52,   -51,   -51,   -51,   -51,   -51,   -51,    39,
     -51,    36,   436,    36,   -51,    49,   -35,    71,    54,    79,
     -51,   -51,   -51,   -51,    36,    36,    17,   -51,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    44,    42,    89,    90,   107,    91,    14,   105,   116,
     111,   153,   125,     8,     8,   117,   112,   -51,   191,   191,
      19,    19,    19,    19,    78,    78,    52,    52,   -51,   -51,
     -51,    36,   153,   126,   121,    36,   138,   128,   171,   -51,
     140,   142,   158,   -37,   149,   146,   155,    36,   -51,    36,
       8,   169,   -51,   -17,   -51,   172,   -51,   -51,    36,   -51,
     175,   174,   153,   -51,     8,     8,   182,    88,   436,   141,
      36,    -2,     8,   183,   -51,   188,   -51,   234,   193,   -51,
      94,   445,   -51,    36,   185,   -51,   363,   195,   202,   -51,
     201,     8,   -51,    36,   -51,   -51,   -51,     8,   196,   229,
     273,   404,   203,   -51,   -51,   -51,   -51
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,    75,    76,    77,    78,    79,     0,     0,     0,     0,
       0,    80,    81,    82,    83,    84,    85,    56,     0,     3,
       7,    13,    12,     8,    19,    20,    21,     0,    29,    32,
      37,    40,    43,    47,    52,    55,     4,    58,     5,     0,
      54,     0,     0,     0,    11,     0,     0,     0,     0,    56,
      50,    51,    48,    49,     0,    64,     0,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    60,     0,    26,    66,     0,    63,    53,    31,    30,
      33,    34,    35,    36,    38,    39,    41,    42,    44,    45,
      46,     0,    60,     0,     0,     0,     0,     0,     0,    10,
       0,     0,    74,     0,     0,    59,     0,     0,    57,     0,
      25,     0,    11,     0,    11,     0,    18,    27,     0,    70,
       0,     0,     0,    62,    28,    65,     0,     0,     0,     0,
       0,     0,    73,    72,    11,     0,    11,    15,     0,    23,
       0,     0,    16,     0,     0,    61,     0,     0,     0,    24,
       0,    71,    68,     0,    11,    11,    11,    69,     0,     0,
       0,     0,     0,    14,    22,    17,    67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -51,   -51,   -51,   250,   168,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -50,   -28,    46,   135,    64,    66,   -14,
     -51,   -51,   -51,   143,   -51,   -51,   -51,   -51,   -51,   -51,
     -51,    -1,    95
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,   119,    87,    30,    31,    32,   151,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,   124,   125,    95,    96,    47,   178,    48,
     123,    85,    50
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      66,    49,    84,    60,    61,    62,    63,   161,    89,    68,
      69,   139,    90,   140,    51,    58,     3,     4,    52,     5,
       6,     7,     8,    82,    53,    86,    83,   148,    11,    12,
      13,    14,    15,    16,    68,    69,    93,    94,    17,    18,
      54,    64,    55,    68,    69,    19,   162,    74,    75,    20,
      65,    21,    22,    23,    24,    25,    26,    27,    56,    28,
      17,    18,   118,    97,   108,   109,   110,    19,    68,    69,
      57,    20,    67,    21,    22,    23,    24,    25,    26,    59,
     111,    28,    81,   130,    78,    79,    80,   133,   113,   112,
     126,     4,    88,     5,     6,     7,     8,    92,   158,   144,
      83,   145,    11,    12,    13,    14,    15,    16,    76,    77,
     152,   126,    17,    18,    98,    99,    91,    68,    69,    19,
      68,    69,   160,    20,    65,    21,    22,    23,    24,    25,
      26,    27,   114,    28,   115,   171,   157,   117,   104,   105,
     169,   155,   106,   107,     4,   177,     5,     6,     7,     8,
     116,   120,   121,    83,   122,    11,    12,    13,    14,    15,
      16,   127,   129,   128,    89,    17,    18,    11,    12,    13,
      14,    15,    19,   132,   111,   134,    20,   135,    21,    22,
      23,    24,    25,    26,    27,   137,    28,   136,     4,   159,
       5,     6,     7,     8,   138,   141,   142,    83,   143,    11,
      12,    13,    14,    15,    16,   100,   101,   102,   103,    17,
      18,    70,    71,    72,    73,   146,    19,   150,   153,   163,
      20,   154,    21,    22,    23,    24,    25,    26,    27,   156,
      28,   165,     4,   172,     5,     6,     7,     8,   167,   168,
     182,    83,   174,    11,    12,    13,    14,    15,    16,   175,
     176,   186,    29,    17,    18,   131,   170,     0,     0,     0,
      19,     0,     0,     0,    20,     0,    21,    22,    23,    24,
      25,    26,    27,     0,    28,     0,     4,   183,     5,     6,
       7,     8,     0,     0,     0,    83,     0,    11,    12,    13,
      14,    15,    16,     0,     0,     0,     0,    17,    18,     0,
     147,     0,   149,     0,    19,     0,     0,     0,    20,     0,
      21,    22,    23,    24,    25,    26,    27,     0,    28,     0,
       0,   184,   164,     0,   166,     4,     0,     5,     6,     7,
       8,     0,     0,     0,     9,    10,    11,    12,    13,    14,
      15,    16,   179,   180,   181,     0,    17,    18,     0,     0,
       0,     0,     0,    19,     0,     0,     0,    20,     0,    21,
      22,    23,    24,    25,    26,    27,     4,    28,     5,     6,
       7,     8,     0,     0,   173,    83,     0,    11,    12,    13,
      14,    15,    16,     0,     0,     0,     0,    17,    18,     0,
       0,     0,     0,     0,    19,     0,     0,     0,    20,     0,
      21,    22,    23,    24,    25,    26,    27,     4,    28,     5,
       6,     7,     8,     0,   185,     0,    83,     0,    11,    12,
      13,    14,    15,    16,     0,     0,     0,     0,    17,    18,
       0,     0,     0,     0,     0,    19,     0,     0,     0,    20,
       0,    21,    22,    23,    24,    25,    26,    27,    83,    28,
      11,    12,    13,    14,    15,    16,     0,     0,     0,     0,
      17,    18,     0,     0,     0,     0,     0,    19,     0,     0,
       0,    20,     0,    21,    22,    23,    24,    25,    26,    27,
       0,    28,    21,    22,    23,    24,    25,    26
};

static const yytype_int16 yycheck[] =
{
      28,     2,    52,    17,    18,    19,    20,     9,    43,    26,
      27,    48,    47,    50,    45,    16,     0,     3,    45,     5,
       6,     7,     8,    51,    45,    53,    12,    44,    14,    15,
      16,    17,    18,    19,    26,    27,    64,    65,    24,    25,
      47,    36,    45,    26,    27,    31,    48,    28,    29,    35,
      45,    37,    38,    39,    40,    41,    42,    43,    43,    45,
      24,    25,    48,    46,    78,    79,    80,    31,    26,    27,
      43,    35,    44,    37,    38,    39,    40,    41,    42,    43,
      36,    45,    43,   111,    32,    33,    34,   115,    46,    45,
      91,     3,    43,     5,     6,     7,     8,    43,   148,   127,
      12,   129,    14,    15,    16,    17,    18,    19,    30,    31,
     138,   112,    24,    25,    68,    69,    45,    26,    27,    31,
      26,    27,   150,    35,    45,    37,    38,    39,    40,    41,
      42,    43,    43,    45,    44,   163,    48,    46,    74,    75,
      46,   142,    76,    77,     3,   173,     5,     6,     7,     8,
      43,    46,    36,    12,    43,    14,    15,    16,    17,    18,
      19,    36,    50,    46,    43,    24,    25,    14,    15,    16,
      17,    18,    31,    47,    36,    47,    35,     6,    37,    38,
      39,    40,    41,    42,    43,    43,    45,    47,     3,    48,
       5,     6,     7,     8,    36,    46,    50,    12,    43,    14,
      15,    16,    17,    18,    19,    70,    71,    72,    73,    24,
      25,    20,    21,    22,    23,    46,    31,    45,    43,    36,
      35,    47,    37,    38,    39,    40,    41,    42,    43,    47,
      45,    43,     3,    48,     5,     6,     7,     8,     4,    46,
      44,    12,    47,    14,    15,    16,    17,    18,    19,    47,
      49,    48,     2,    24,    25,   112,   161,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    35,    -1,    37,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,     3,    48,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    -1,    14,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    24,    25,    -1,
     132,    -1,   134,    -1,    31,    -1,    -1,    -1,    35,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    45,    -1,
      -1,    48,   154,    -1,   156,     3,    -1,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,   174,   175,   176,    -1,    24,    25,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    -1,    37,
      38,    39,    40,    41,    42,    43,     3,    45,     5,     6,
       7,     8,    -1,    -1,    11,    12,    -1,    14,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    24,    25,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    -1,
      37,    38,    39,    40,    41,    42,    43,     3,    45,     5,
       6,     7,     8,    -1,    10,    -1,    12,    -1,    14,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    24,    25,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,
      -1,    37,    38,    39,    40,    41,    42,    43,    12,    45,
      14,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    35,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    45,    37,    38,    39,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,    53,     0,     3,     5,     6,     7,     8,    12,
      13,    14,    15,    16,    17,    18,    19,    24,    25,    31,
      35,    37,    38,    39,    40,    41,    42,    43,    45,    54,
      56,    57,    58,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    78,    80,    82,
      83,    45,    45,    45,    47,    45,    43,    43,    82,    43,
      70,    70,    70,    70,    36,    45,    65,    44,    26,    27,
      20,    21,    22,    23,    28,    29,    30,    31,    32,    33,
      34,    43,    65,    12,    64,    82,    65,    55,    43,    43,
      47,    45,    43,    65,    65,    76,    77,    46,    66,    66,
      67,    67,    67,    67,    68,    68,    69,    69,    70,    70,
      70,    36,    45,    46,    43,    44,    43,    46,    48,    54,
      46,    36,    43,    81,    74,    75,    82,    36,    46,    50,
      65,    74,    47,    65,    47,     6,    47,    43,    36,    48,
      50,    46,    50,    43,    65,    65,    46,    55,    44,    55,
      45,    59,    65,    43,    47,    82,    47,    48,    64,    48,
      65,     9,    48,    36,    55,    43,    55,     4,    46,    46,
      83,    65,    48,    11,    47,    47,    49,    65,    79,    55,
      55,    55,    44,    48,    48,    10,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    53,    53,    54,    54,    54,
      55,    55,    56,    56,    57,    57,    58,    59,    59,    60,
      60,    60,    61,    62,    63,    64,    64,    64,    64,    64,
      65,    65,    65,    66,    66,    66,    66,    66,    67,    67,
      67,    68,    68,    68,    69,    69,    69,    69,    70,    70,
      70,    70,    70,    71,    71,    71,    71,    72,    73,    74,
      74,    75,    75,    76,    76,    77,    77,    78,    78,    79,
      80,    81,    81,    81,    81,    82,    82,    82,    82,    82,
      83,    83,    83,    83,    83,    83
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     0,     1,     1,     2,
       2,     0,     1,     1,    11,     7,     7,     6,     0,     1,
       1,     1,    11,     7,     8,     4,     3,     5,     5,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     2,     2,
       2,     2,     1,     3,     1,     1,     1,     4,     1,     1,
       0,     4,     2,     1,     0,     3,     1,    11,     8,     1,
       5,     5,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
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
  case 2: /* program: root  */
#line 76 "parser.y"
              {printf("end of program\n"); st->checkForUnusedVariables();}
#line 1365 "parser.tab.c"
    break;

  case 3: /* root: root statement  */
#line 81 "parser.y"
        {
        execute((yyvsp[0].node));
        }
#line 1373 "parser.tab.c"
    break;

  case 4: /* root: root functional_statement  */
#line 85 "parser.y"
        {
        execute((yyvsp[0].node));
        }
#line 1381 "parser.tab.c"
    break;

  case 5: /* root: root enum_statement  */
#line 89 "parser.y"
        {
        execute((yyvsp[0].node));
        }
#line 1389 "parser.tab.c"
    break;

  case 6: /* root: %empty  */
#line 93 "parser.y"
        {/* empty */}
#line 1395 "parser.tab.c"
    break;

  case 7: /* statement: conditional_statement  */
#line 97 "parser.y"
        { 
        (yyval.node)=(yyvsp[0].node);
        }
#line 1403 "parser.tab.c"
    break;

  case 8: /* statement: loop_statement  */
#line 102 "parser.y"
        { 
        (yyval.node)=(yyvsp[0].node);
        }
#line 1411 "parser.tab.c"
    break;

  case 9: /* statement: assignment ';'  */
#line 107 "parser.y"
        { 
        (yyval.node)=(yyvsp[-1].node);
        }
#line 1419 "parser.tab.c"
    break;

  case 10: /* recursive_statement: recursive_statement statement  */
#line 113 "parser.y"
        {
        (yyval.node)=createOperationNode(';',2,(yyvsp[-1].node),(yyvsp[0].node));
        }
#line 1427 "parser.tab.c"
    break;

  case 11: /* recursive_statement: %empty  */
#line 117 "parser.y"
        {
        (yyval.node)=NULL;
        }
#line 1435 "parser.tab.c"
    break;

  case 12: /* conditional_statement: switch_conditional_statement  */
#line 124 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1443 "parser.tab.c"
    break;

  case 13: /* conditional_statement: if_conditional_statement  */
#line 129 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1451 "parser.tab.c"
    break;

  case 14: /* if_conditional_statement: IF '(' expressions ')' '{' recursive_statement '}' ELSE '{' recursive_statement '}'  */
#line 135 "parser.y"
        {
        (yyval.node)=createOperationNode(IF,3,(yyvsp[-8].node),(yyvsp[-5].node),(yyvsp[-1].node));
        }
#line 1459 "parser.tab.c"
    break;

  case 15: /* if_conditional_statement: IF '(' expressions ')' '{' recursive_statement '}'  */
#line 139 "parser.y"
        {
        (yyval.node)=createOperationNode(IF,2,(yyvsp[-4].node),(yyvsp[-1].node));
        }
#line 1467 "parser.tab.c"
    break;

  case 16: /* switch_conditional_statement: SWITCH '(' VARIABLE ')' '{' case_statement '}'  */
#line 145 "parser.y"
        {
        (yyval.node)=createOperationNode(SWITCH,2,createIdentifierNode((yyvsp[-4].string_val)),(yyvsp[-1].node));
        }
#line 1475 "parser.tab.c"
    break;

  case 17: /* case_statement: case_statement CASE variable_value ':' recursive_statement BREAK  */
#line 151 "parser.y"
        {
        (yyval.node)=createOperationNode(CASE,3,(yyvsp[-5].node),(yyvsp[-3].node),(yyvsp[-1].node));
        }
#line 1483 "parser.tab.c"
    break;

  case 18: /* case_statement: %empty  */
#line 155 "parser.y"
        {
        (yyval.node)=NULL;
        }
#line 1491 "parser.tab.c"
    break;

  case 19: /* loop_statement: for_loop_statement  */
#line 162 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1499 "parser.tab.c"
    break;

  case 20: /* loop_statement: while_loop_statement  */
#line 167 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1507 "parser.tab.c"
    break;

  case 21: /* loop_statement: do_while_loop_statement  */
#line 172 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1515 "parser.tab.c"
    break;

  case 22: /* for_loop_statement: FOR '(' assignment ';' expressions ';' assignment ')' '{' recursive_statement '}'  */
#line 178 "parser.y"
        {
        (yyval.node)=createOperationNode(FOR,4,(yyvsp[-8].node),(yyvsp[-6].node),(yyvsp[-4].node),(yyvsp[-1].node));
        }
#line 1523 "parser.tab.c"
    break;

  case 23: /* while_loop_statement: WHILE '(' expressions ')' '{' recursive_statement '}'  */
#line 184 "parser.y"
        {
        (yyval.node)=createOperationNode(WHILE,2,(yyvsp[-4].node),(yyvsp[-1].node));
        }
#line 1531 "parser.tab.c"
    break;

  case 24: /* do_while_loop_statement: DO '{' recursive_statement '}' WHILE '(' expressions ')'  */
#line 191 "parser.y"
        {
        (yyval.node)=createOperationNode(DO,2,(yyvsp[-5].node),(yyvsp[-1].node));
        }
#line 1539 "parser.tab.c"
    break;

  case 25: /* assignment: variable_Type VARIABLE ASSIGN expressions  */
#line 198 "parser.y"
        {
        (yyval.node)=createOperationNode(ASSIGN,3,(yyvsp[-3].node),createIdentifierNode((yyvsp[-2].string_val)),(yyvsp[0].node));
        }
#line 1547 "parser.tab.c"
    break;

  case 26: /* assignment: VARIABLE ASSIGN expressions  */
#line 202 "parser.y"
        {
        (yyval.node)=createOperationNode(ASSIGN,2,createIdentifierNode((yyvsp[-2].string_val)),(yyvsp[0].node));
        }
#line 1555 "parser.tab.c"
    break;

  case 27: /* assignment: ENUM VARIABLE VARIABLE ASSIGN VARIABLE  */
#line 206 "parser.y"
        {
        (yyval.node)=createOperationNode(ASSIGN,4,createType(EnumDataType),createIdentifierNode((yyvsp[-3].string_val)),createIdentifierNode((yyvsp[-2].string_val)),createIdentifierNode((yyvsp[0].string_val)));
        }
#line 1563 "parser.tab.c"
    break;

  case 28: /* assignment: CONST variable_Type VARIABLE ASSIGN expressions  */
#line 210 "parser.y"
        {
        (yyval.node)=createOperationNode(ASSIGN,4,createType(ConstDataType),(yyvsp[-3].node),createIdentifierNode((yyvsp[-2].string_val)),(yyvsp[0].node));
        }
#line 1571 "parser.tab.c"
    break;

  case 29: /* assignment: expressions  */
#line 214 "parser.y"
        {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1579 "parser.tab.c"
    break;

  case 30: /* expressions: expressions OR equality_expression  */
#line 223 "parser.y"
        {
        (yyval.node)=createOperationNode(OR,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1587 "parser.tab.c"
    break;

  case 31: /* expressions: expressions AND equality_expression  */
#line 227 "parser.y"
        {
        (yyval.node)=createOperationNode(AND,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1595 "parser.tab.c"
    break;

  case 32: /* expressions: equality_expression  */
#line 231 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1603 "parser.tab.c"
    break;

  case 33: /* equality_expression: equality_expression EQ relational_expression  */
#line 239 "parser.y"
        {
        (yyval.node)=createOperationNode(EQ,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1611 "parser.tab.c"
    break;

  case 34: /* equality_expression: equality_expression NE relational_expression  */
#line 243 "parser.y"
        {
        (yyval.node)=createOperationNode(NE,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1619 "parser.tab.c"
    break;

  case 35: /* equality_expression: equality_expression GE relational_expression  */
#line 247 "parser.y"
        {
        (yyval.node)=createOperationNode(GE,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1627 "parser.tab.c"
    break;

  case 36: /* equality_expression: equality_expression LE relational_expression  */
#line 251 "parser.y"
        {
        (yyval.node)=createOperationNode(LE,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1635 "parser.tab.c"
    break;

  case 37: /* equality_expression: relational_expression  */
#line 255 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1643 "parser.tab.c"
    break;

  case 38: /* relational_expression: relational_expression GT additive_expression  */
#line 261 "parser.y"
        {
        (yyval.node)=createOperationNode(GT,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1651 "parser.tab.c"
    break;

  case 39: /* relational_expression: relational_expression LT additive_expression  */
#line 265 "parser.y"
        {
        (yyval.node)=createOperationNode(LT,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1659 "parser.tab.c"
    break;

  case 40: /* relational_expression: additive_expression  */
#line 269 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1667 "parser.tab.c"
    break;

  case 41: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 275 "parser.y"
        {
        (yyval.node)=createOperationNode(PLUS,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1675 "parser.tab.c"
    break;

  case 42: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 279 "parser.y"
        {
        (yyval.node)=createOperationNode(MINUS,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1683 "parser.tab.c"
    break;

  case 43: /* additive_expression: multiplicative_expression  */
#line 283 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1691 "parser.tab.c"
    break;

  case 44: /* multiplicative_expression: multiplicative_expression MULT unary_expression  */
#line 289 "parser.y"
        {
        (yyval.node)=createOperationNode(MULT,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1699 "parser.tab.c"
    break;

  case 45: /* multiplicative_expression: multiplicative_expression DIV unary_expression  */
#line 293 "parser.y"
        {
        (yyval.node)=createOperationNode(DIV,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1707 "parser.tab.c"
    break;

  case 46: /* multiplicative_expression: multiplicative_expression MOD unary_expression  */
#line 297 "parser.y"
        {
        (yyval.node)=createOperationNode(MOD,2,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1715 "parser.tab.c"
    break;

  case 47: /* multiplicative_expression: unary_expression  */
#line 301 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1723 "parser.tab.c"
    break;

  case 48: /* unary_expression: MINUS unary_expression  */
#line 307 "parser.y"
        {
        (yyval.node)=createOperationNode(MINUS,1,(yyvsp[0].node));
        }
#line 1731 "parser.tab.c"
    break;

  case 49: /* unary_expression: NOT unary_expression  */
#line 311 "parser.y"
        {
        (yyval.node)=createOperationNode(NOT,1,(yyvsp[0].node));
        }
#line 1739 "parser.tab.c"
    break;

  case 50: /* unary_expression: INC unary_expression  */
#line 315 "parser.y"
        {
        (yyval.node)=createOperationNode(INC,1,(yyvsp[0].node));
        }
#line 1747 "parser.tab.c"
    break;

  case 51: /* unary_expression: DEC unary_expression  */
#line 319 "parser.y"
        {
        (yyval.node)=createOperationNode(DEC,1,(yyvsp[0].node));
        }
#line 1755 "parser.tab.c"
    break;

  case 52: /* unary_expression: primary_expression  */
#line 323 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1763 "parser.tab.c"
    break;

  case 53: /* primary_expression: '(' expressions ')'  */
#line 329 "parser.y"
        {
        (yyval.node)=(yyvsp[-1].node);
        }
#line 1771 "parser.tab.c"
    break;

  case 55: /* primary_expression: function_call  */
#line 333 "parser.y"
        {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1779 "parser.tab.c"
    break;

  case 56: /* primary_expression: VARIABLE  */
#line 337 "parser.y"
        {
        (yyval.node) = createIdentifierNode((yyvsp[0].string_val));
        }
#line 1787 "parser.tab.c"
    break;

  case 57: /* function_call: VARIABLE '(' function_parameters_calls ')'  */
#line 344 "parser.y"
        {
        (yyval.node)=createOperationNode('f',2,createIdentifierNode((yyvsp[-3].string_val)),(yyvsp[-1].node));
        }
#line 1795 "parser.tab.c"
    break;

  case 58: /* functional_statement: function  */
#line 350 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1803 "parser.tab.c"
    break;

  case 59: /* function_parameters: parameter  */
#line 355 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1811 "parser.tab.c"
    break;

  case 60: /* function_parameters: %empty  */
#line 359 "parser.y"
        {
        (yyval.node)=NULL;
        }
#line 1819 "parser.tab.c"
    break;

  case 61: /* parameter: parameter ',' variable_Type VARIABLE  */
#line 365 "parser.y"
        {
        (yyval.node) = addToParameterList((yyvsp[-3].node), (yyvsp[-1].node), createIdentifierNode((yyvsp[0].string_val)));
        }
#line 1827 "parser.tab.c"
    break;

  case 62: /* parameter: variable_Type VARIABLE  */
#line 369 "parser.y"
        {
        (yyval.node) = createParameterList((yyvsp[-1].node), createIdentifierNode((yyvsp[0].string_val)));
        }
#line 1835 "parser.tab.c"
    break;

  case 63: /* function_parameters_calls: parameter_calls  */
#line 375 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1843 "parser.tab.c"
    break;

  case 64: /* function_parameters_calls: %empty  */
#line 379 "parser.y"
        {
        (yyval.node)=NULL;
        }
#line 1851 "parser.tab.c"
    break;

  case 65: /* parameter_calls: parameter_calls ',' expressions  */
#line 385 "parser.y"
        {
        (yyval.node)=addToParameterCallList((yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1859 "parser.tab.c"
    break;

  case 66: /* parameter_calls: expressions  */
#line 389 "parser.y"
        {
        (yyval.node)=createParameterCallList((yyvsp[0].node));
        }
#line 1867 "parser.tab.c"
    break;

  case 67: /* function: variable_Type VARIABLE '(' function_parameters ')' '{' recursive_statement RETURN return_types ';' '}'  */
#line 395 "parser.y"
        {
        (yyval.node)=createOperationNode('d',5,(yyvsp[-10].node),createIdentifierNode((yyvsp[-9].string_val)),(yyvsp[-7].node),(yyvsp[-4].node),(yyvsp[-2].node));
        }
#line 1875 "parser.tab.c"
    break;

  case 68: /* function: VOID VARIABLE '(' function_parameters ')' '{' recursive_statement '}'  */
#line 399 "parser.y"
        {
        (yyval.node)=createOperationNode('d',4,createType(VoidDataType),createIdentifierNode((yyvsp[-6].string_val)),(yyvsp[-4].node),(yyvsp[-1].node));
        }
#line 1883 "parser.tab.c"
    break;

  case 69: /* return_types: expressions  */
#line 405 "parser.y"
        {
        (yyval.node)=(yyvsp[0].node);
        }
#line 1891 "parser.tab.c"
    break;

  case 70: /* enum_statement: ENUM VARIABLE '{' enum_variables '}'  */
#line 411 "parser.y"
        {
        (yyval.node)=createOperationNode(ENUM,2,createIdentifierNode((yyvsp[-3].string_val)),(yyvsp[-1].node));
        }
#line 1899 "parser.tab.c"
    break;

  case 71: /* enum_variables: enum_variables ',' VARIABLE ASSIGN expressions  */
#line 417 "parser.y"
        {
        (yyval.node)=createOperationNode(',',3,(yyvsp[-4].node),createIdentifierNode((yyvsp[-2].string_val)),(yyvsp[0].node));
        }
#line 1907 "parser.tab.c"
    break;

  case 72: /* enum_variables: enum_variables ',' VARIABLE  */
#line 421 "parser.y"
        {
        (yyval.node)=createOperationNode(',',2,(yyvsp[-2].node),createIdentifierNode((yyvsp[0].string_val)));
        }
#line 1915 "parser.tab.c"
    break;

  case 73: /* enum_variables: VARIABLE ASSIGN expressions  */
#line 425 "parser.y"
        {
        (yyval.node)=createOperationNode(',',2,createIdentifierNode((yyvsp[-2].string_val)),(yyvsp[0].node));
        }
#line 1923 "parser.tab.c"
    break;

  case 74: /* enum_variables: VARIABLE  */
#line 429 "parser.y"
        {
        (yyval.node)=createOperationNode(',',1,createIdentifierNode((yyvsp[0].string_val)));
        }
#line 1931 "parser.tab.c"
    break;

  case 75: /* variable_Type: INT_TYPE  */
#line 436 "parser.y"
        {
        (yyval.node) = createType(IntDataType);
        }
#line 1939 "parser.tab.c"
    break;

  case 76: /* variable_Type: CHAR_TYPE  */
#line 440 "parser.y"
        {
        (yyval.node) = createType(CharDataType);
        }
#line 1947 "parser.tab.c"
    break;

  case 77: /* variable_Type: BOOL_TYPE  */
#line 444 "parser.y"
        {
        (yyval.node) = createType(BoolDataType);
        }
#line 1955 "parser.tab.c"
    break;

  case 78: /* variable_Type: FLOAT_TYPE  */
#line 448 "parser.y"
        {
        (yyval.node) = createType(FloatDataType);
        }
#line 1963 "parser.tab.c"
    break;

  case 79: /* variable_Type: STRING_TYPE  */
#line 452 "parser.y"
        {
        (yyval.node) = createType(StringDataType);
        }
#line 1971 "parser.tab.c"
    break;

  case 80: /* variable_value: INTEGER  */
#line 458 "parser.y"
        {
        (yyval.node) = constantValue(IntDataType, &(yyvsp[0].integer_val));
        }
#line 1979 "parser.tab.c"
    break;

  case 81: /* variable_value: FLOAT  */
#line 462 "parser.y"
        {
        (yyval.node) = constantValue(FloatDataType, &(yyvsp[0].float_val));
        }
#line 1987 "parser.tab.c"
    break;

  case 82: /* variable_value: BOOL_FALSE  */
#line 466 "parser.y"
        {
        (yyval.node) = constantValue(BoolDataType, &(yyvsp[0].integer_val));
        }
#line 1995 "parser.tab.c"
    break;

  case 83: /* variable_value: BOOL_TRUE  */
#line 470 "parser.y"
        {
        (yyval.node) = constantValue(BoolDataType, &(yyvsp[0].integer_val));
        }
#line 2003 "parser.tab.c"
    break;

  case 84: /* variable_value: CHAR  */
#line 474 "parser.y"
        {
        (yyval.node) = constantValue(CharDataType, &(yyvsp[0].char_val));
        }
#line 2011 "parser.tab.c"
    break;

  case 85: /* variable_value: STRING  */
#line 478 "parser.y"
        {
        (yyval.node) = constantValue(StringDataType, (yyvsp[0].string_val));
        }
#line 2019 "parser.tab.c"
    break;


#line 2023 "parser.tab.c"

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

#line 482 "parser.y"



nodeType *constantValue(DataTypeEnum type, void* value) {
    nodeType *p;
    if ((p = (nodeType* )malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");
    p->constant.ConstDataType = type;

    switch (type) {
        case IntDataType:
            p->constant.value = memcpy(malloc(sizeof(int)), value, sizeof(int));
            break;
        case FloatDataType:
            p->constant.value = memcpy(malloc(sizeof(float)), value, sizeof(float));
            break;
        case BoolDataType:
            p->constant.value = memcpy(malloc(sizeof(bool)), value, sizeof(bool));
            break;
        case CharDataType:
            p->constant.value = memcpy(malloc(sizeof(char)), value, sizeof(char));
            break;
        case StringDataType:
            p->constant.value = strdup((char*)value);
            break;
        case VoidDataType:
        case EnumDataType:
        case ConstDataType:
        case Error:
            p->constant.value = NULL;
            break;
        case Unknown:
            yyerror("unknown type");
            break;
    }
    return p;
}

nodeType *createOperationNode(int oper, int nops, ...) {
    va_list ap;
    va_start(ap, nops);

    nodeType *p = (nodeType *)calloc(1, sizeof(nodeType) + (nops - 1) * sizeof(nodeType *));
    if (!p) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    p->type = Operator_Node;
    p->oper.oper = oper;
    p->oper.nops = nops;

    for (int i = 0; i < nops; i++) {
        p->oper.op[i] = va_arg(ap, nodeType*);
    }

    va_end(ap);
    return p;
}
nodeType *createType(DataTypeEnum type) {
    nodeType *p = (nodeType *)calloc(1, sizeof(nodeType));
    if (!p) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    p->type = Type_Node;
    p->defineType.type = type;
    return p;
}

nodeType *createIdentifierNode(char* i) {
    nodeType *p;
    if ((p = (nodeType *)malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");
    p->type = Identifier_Node;
    p->identifier.name = i;
    return p;
}
void handleOutOfMemory() {
    yyerror("out of memory");
    exit(1);
}

nodeType *createNode() {
    nodeType *p = (nodeType *)malloc(sizeof(nodeType));
    if (p == NULL)
        handleOutOfMemory();
    p->type = ArgumentNode;
    return p;
}

nodeType *createParameterList(nodeType * node, nodeType * identifier) {
    nodeType *p = createNode();
    p->argumentType.arguments.push_back(node->defineType.type);
    p->argumentType.argumentsNames.push_back(identifier->identifier.name);
    return p;
}

nodeType *addToParameterList(nodeType * parameterList, nodeType* node, nodeType * parameter){
    parameterList->argumentType.arguments.push_back(node->defineType.type);
    parameterList->argumentType.argumentsNames.push_back(parameter->identifier.name);
    return parameterList;
}

nodeType *createParameterCallList(nodeType * node) {
    nodeType *p = createNode();
    p->argumentType.argumentsNodes.push_back(node);
    return p;
}

nodeType *addToParameterCallList(nodeType * parameterList, nodeType* node){
    parameterList->argumentType.argumentsNodes.push_back(node);
    return parameterList;
}



void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == Operator_Node) {
        for (i = 0; i < p->oper.nops; i++)
            freeNode(p->oper.op[i]);
    }
    free(p);
}
DataTypeEnum handleIfStatement(nodeType *p) {
    bool hasElse = p->oper.nops == 3;
    int label = Labels++;
    execute(p->oper.op[0]);
    fprintf(OutputQuadraplesFile, "JZ L%d\n", label);
    currentScope = st->createNewScope(currentScope);
    execute(p->oper.op[1]);
    currentScope = st->switchBack(currentScope);
    int elseLabel;
    if (hasElse) {
        elseLabel = Labels++;
        fprintf(OutputQuadraplesFile, "JMP L%d\n", elseLabel);
    }
    fprintf(OutputQuadraplesFile, "L%d:\n", label);
    if (hasElse) {
        currentScope = st->createNewScope(currentScope);
        execute(p->oper.op[2]);
        fprintf(OutputQuadraplesFile, "L%d:\n", elseLabel);
        currentScope = st->switchBack(currentScope);
    }
    if (p->oper.op[0]->type == Constant_Node) {
        if (p->oper.op[0]->constant.ConstDataType == IntDataType || p->oper.op[0]->constant.ConstDataType == BoolDataType
        && !*(int*)p->oper.op[0]->constant.value) {
            yywarning("condition is always false");
        }
    }
    return VoidDataType;
}

/*int x = 5 */
void writeVar(void* value, DataTypeEnum type) {
    switch (type) {
        case IntDataType:
            fprintf(OutputQuadraplesFile, "PUSH %d\n", *(int*)value);
            EnumValue = *(int*)value;
            break;
        case FloatDataType:
            fprintf(OutputQuadraplesFile, "PUSH %f\n", *(float*)value);
            break;
        case BoolDataType:
            fprintf(OutputQuadraplesFile, "PUSH %s\n", *(bool*)value ? "true" : "false");
            break;
        case CharDataType:
            fprintf(OutputQuadraplesFile, "PUSH %c\n", *(char*)value);
            break;
        case StringDataType:
            fprintf(OutputQuadraplesFile, "PUSH %s\n", (char*)value);
            break;
        default:
            yyerror("unknown type");
            break;
    }
}
DataTypeEnum handleSwitchStatement(nodeType *p) {
    TempVariables ++;
    EndSwitchLabel++;
    DataTypeEnum varType = getIdentifierType(p->oper.op[0]->identifier.name);
    st->variables[p->oper.op[0]->identifier.name] = true;
    if(varType != CharDataType && varType != IntDataType){
        yyerror("This type of variable is not supported in switch statement");
        return Error;
    }
    fprintf(OutputQuadraplesFile, "PUSH %s\n", p->oper.op[0]->identifier.name);
    fprintf(OutputQuadraplesFile, "POP Temp%d\n", TempVariables);
    int CurrentEndSwitch = EndSwitchLabel;
    execute(p->oper.op[1]);
    fprintf(OutputQuadraplesFile, "E%d:\n",CurrentEndSwitch); 
    return VoidDataType;
}

DataTypeEnum handleCaseStatement(nodeType *p) {
    int CurrentTempVar = TempVariables;
    int CurrentEndSwitch = EndSwitchLabel;
    currentScope=st->createNewScope(currentScope);
    execute(p->oper.op[0]);
    int CurrentCaseLabel = CaseLabels;
    fprintf(OutputQuadraplesFile, "PUSH Temp%d\n", CurrentTempVar);
    DataTypeEnum caseConst = execute(p->oper.op[1]);
    if(caseConst != IntDataType && caseConst != CharDataType){
        yyerror("This type of case is not supported in switch statement");
        return Error;
    }
    fprintf(OutputQuadraplesFile, "COMP_E\n");
    fprintf(OutputQuadraplesFile, "JZ C%d\n", CaseLabels++);  
    execute(p->oper.op[2]);
    fprintf(OutputQuadraplesFile, "JMP E%d\n", CurrentEndSwitch);  
    currentScope = st->switchBack(currentScope);
    fprintf(OutputQuadraplesFile, "C%d:\n",CurrentCaseLabel); 
    return VoidDataType;
}

DataTypeEnum handleEnumCaseStatement(nodeType *p) {
     if(!st->insertNode(currentScope,p->oper.op[0]->identifier.name,"enum",EnumDataType)){
        yyerror("variable already exists in the current scope");
        return Error;
    }
    currentScope=st->createNewScope(currentScope);
    st->enumerationTypeMap[p->oper.op[0]->identifier.name] = currentScope;
    execute(p->oper.op[0]);
    execute(p->oper.op[1]);
    currentScope = st->switchBack(currentScope);
    return VoidDataType;
}

DataTypeEnum handleIdetifierNode(nodeType *p) {
    DataTypeEnum typeIdentifier = getIdentifierType(p->identifier.name);
            switch (typeIdentifier) {
                case IntDataType:
                case FloatDataType:
                case StringDataType:
                case BoolDataType:
                case CharDataType:
                case ConstDataType:
                    writeVar(p->identifier.name, StringDataType);
                    st->variables[p->identifier.name] = true;
                    return typeIdentifier;
                case VoidDataType:
                    return VoidDataType;
                case EnumDataType:
                    EnumValue = -1;
                    return EnumDataType;
                default:
                    for (auto it = st->enumerationTypeMap.begin(); it != st->enumerationTypeMap.end(); ++it) {
                        if(stringToTypeEnum(it->first) == typeIdentifier)
                        {
                            st->variables[p->identifier.name] = true;
                            return IntDataType;
                        }
                    }
                    yyerror("variable was not declared in this scope");
                    return Error;
    }
}
DataTypeEnum handleLogicalOperation(nodeType *p) {
    DataTypeEnum typeOP1 = execute(p->oper.op[0]);
    DataTypeEnum typeOP2 = execute(p->oper.op[1]);
    if((typeOP1 != BoolDataType && typeOP1 != IntDataType) || (typeOP2 != BoolDataType && typeOP2 != IntDataType)){
        yyerror("This type of operands are not supported in this operation");
        return Error;
    }
    if(p->oper.oper == AND){
        fprintf(OutputQuadraplesFile, "AND \n");
    }
    else if(p->oper.oper == OR){
        fprintf(OutputQuadraplesFile, "OR \n");
    }
    return BoolDataType;
}
DataTypeEnum handlEqualitEqualityOperation(nodeType *p) {
    DataTypeEnum typeOP1 = execute(p->oper.op[0]);
    DataTypeEnum typeOP2 = execute(p->oper.op[1]);
    DataTypeEnum finalType = coercion(typeOP1,typeOP2);
    if(finalType == Error)
    {
        yyerror("types are not compatible");
    }
    if(finalType != typeOP1 || finalType != typeOP2)
    {
        // write to the file the new type
        string type = typeEnumToString(finalType);
        fprintf(OutputQuadraplesFile, "CONV_%s\n", type.c_str());
    }
    if(p->oper.oper == EQ){
        fprintf(OutputQuadraplesFile, "COMP_E \n");
    }
    else if(p->oper.oper == NE){
        fprintf(OutputQuadraplesFile, "COMP_NE \n");
    }
    else if(p->oper.oper == GE){
        fprintf(OutputQuadraplesFile, "COMP_GE \n");
    }
    else if(p->oper.oper == LE){
        fprintf(OutputQuadraplesFile, "COMP_LE \n");
    }

    return BoolDataType;
}
DataTypeEnum handleRelationalOperation(nodeType *p) {
    DataTypeEnum typeOP1 = execute(p->oper.op[0]);
    DataTypeEnum typeOP2 = execute(p->oper.op[1]);
    DataTypeEnum finalType = coercion(typeOP1,typeOP2);
    if(finalType == Error)
    {
        yyerror("types are not compatible");
    }
    if(finalType != typeOP1 || finalType != typeOP2)
    {
        string type = typeEnumToString(finalType);
        fprintf(OutputQuadraplesFile, "CONV_%s\n", type.c_str());
    }
    if(p->oper.oper == LT){
        fprintf(OutputQuadraplesFile, "COMP_L \n");
    }
    else if(p->oper.oper == GT){
        fprintf(OutputQuadraplesFile, "COMP_G \n");
    }
    return BoolDataType;
}
DataTypeEnum handleArithmeticOperation(nodeType *p) {
    DataTypeEnum typeOP1 = execute(p->oper.op[0]);
    DataTypeEnum typeOP2 = execute(p->oper.op[1]);
    DataTypeEnum finalType = coercion(typeOP1,typeOP2);
    if(finalType == Error)
    {
        yyerror("types are not compatible");
    }
    if(finalType != typeOP1 || finalType != typeOP2)
    {
        string type = typeEnumToString(finalType);
        fprintf(OutputQuadraplesFile, "CONV_%s\n", type.c_str());
    }
    if(p->oper.oper == PLUS){
        fprintf(OutputQuadraplesFile, "PLUS \n");
    }
    else if(p->oper.oper == MINUS){
        fprintf(OutputQuadraplesFile, "MINUS \n");
    }
    else if(p->oper.oper == MULT){
        fprintf(OutputQuadraplesFile, "MULTIPLY \n");
    }
    else if(p->oper.oper == DIV){
        fprintf(OutputQuadraplesFile, "DIVIDE \n");
    }
    else if(p->oper.oper == MOD){
        fprintf(OutputQuadraplesFile, "MOD \n");
    }
    return finalType;
}

DataTypeEnum handleMultiplicativeOperation(nodeType *p) {
    DataTypeEnum typeOP1 = execute(p->oper.op[0]);
    DataTypeEnum typeOP2 = execute(p->oper.op[1]);
    DataTypeEnum finalType = coercion(typeOP1,typeOP2);
    if(finalType == Error)
    {
        yyerror("types are not compatible");
    }
    if(finalType != typeOP1 || finalType != typeOP2)
    {
        string type = typeEnumToString(finalType);
        fprintf(OutputQuadraplesFile, "CONV_%s\n", type.c_str());
    }
    if(p->oper.oper == MULT){
        fprintf(OutputQuadraplesFile, "MULTIPLY \n");
    }
    else if(p->oper.oper == DIV){
        fprintf(OutputQuadraplesFile, "DIVIDE \n");
    }
    else if(p->oper.oper == MOD){
        fprintf(OutputQuadraplesFile, "MOD \n");
    }
    return finalType;
}
DataTypeEnum handleAdditiveOperation(nodeType *p) {
    DataTypeEnum typeOP1 = execute(p->oper.op[0]);
    DataTypeEnum typeOP2 = execute(p->oper.op[1]);
    DataTypeEnum finalType = coercion(typeOP1,typeOP2);
    if(finalType == Error)
    {
        yyerror("types are not compatible");
    }
    if(finalType != typeOP1 || finalType != typeOP2)
    {
        string type = typeEnumToString(finalType);
        fprintf(OutputQuadraplesFile, "CONV_%s\n", type.c_str());
    }
    if(p->oper.oper == PLUS){
        fprintf(OutputQuadraplesFile, "PLUS \n");
    }
    else if(p->oper.oper == MINUS){
        fprintf(OutputQuadraplesFile, "MINUS \n");
    }
    return finalType;
}
DataTypeEnum handleUnaryOperation(nodeType *p) {
    DataTypeEnum typeOP = execute(p->oper.op[0]);
    if(p->oper.oper == INC){
        if(typeOP != IntDataType && typeOP != FloatDataType){
            yyerror("This operator doesn't support this type of operand");
        }
        fprintf(OutputQuadraplesFile, "INC \n");
    }
    else if(p->oper.oper == DEC){
        if(typeOP != IntDataType && typeOP != FloatDataType){
            yyerror("This operator doesn't support this type of operand");
        }
        fprintf(OutputQuadraplesFile, "DEC \n");
    }
    else if(p->oper.oper == NOT){
        if(typeOP != BoolDataType){
            yyerror("This operator doesn't support this type of operand");
        }
        fprintf(OutputQuadraplesFile, "NOT \n");
    }
    else if(p->oper.oper == MINUS){
        if(typeOP != IntDataType && typeOP != FloatDataType){
            yyerror("This operator doesn't support this type of operand");
        }
        fprintf(OutputQuadraplesFile, "MINUS \n");
    }
    return typeOP;
}
DataTypeEnum handleForLoop(nodeType *p) {
    int loopStartLabel = Labels;
    int LoopEndLabel = loopStartLabel + 1;

    currentScope = st->createNewScope(currentScope);
    printf("L%d:\n", loopStartLabel);
    // Initialization
    execute(p->oper.op[0]);
    fprintf(OutputQuadraplesFile, "L%d:\n", Labels++);
    // Condition check
    printf("Inside for loop\n");
    execute(p->oper.op[1]);
    fprintf(OutputQuadraplesFile, "JZ L%d\n", Labels++);
    // Loop body
    execute(p->oper.op[3]);

    // Increment
    execute(p->oper.op[2]);
    fprintf(OutputQuadraplesFile, "JMP L%d\n", loopStartLabel);

    // End of loop
    fprintf(OutputQuadraplesFile, "L%d:\n", LoopEndLabel);

    currentScope = st->switchBack(currentScope);
    return VoidDataType;
}
DataTypeEnum handleWhileLoop(nodeType *p) {
    int CurrentLabel = Labels;
    currentScope=st->createNewScope(currentScope);
    fprintf(OutputQuadraplesFile, "L%d:\n",Labels++); //label in
    execute(p->oper.op[0]); // Condition check
    int CurrentLabel2 = Labels;
    fprintf(OutputQuadraplesFile, "JZ L%d\n", Labels++); //jz label out
    execute(p->oper.op[1]); // Loop body
    fprintf(OutputQuadraplesFile, "JMP L%d\n", CurrentLabel);   //jmp label in
    fprintf(OutputQuadraplesFile, "L%d:\n",CurrentLabel2); //label out
    currentScope = st->switchBack(currentScope);
    return VoidDataType;
}

DataTypeEnum handleDo(nodeType *p) {
    int CurrentLabel = Labels;
    currentScope = st->createNewScope(currentScope);
    fprintf(OutputQuadraplesFile, "L%d:\n", Labels++); //label in
    execute(p->oper.op[0]); // Loop body
    int x = Labels;
    execute(p->oper.op[1]); // Condition check
    int y = Labels;
    fprintf(OutputQuadraplesFile, "JZ L%d\n", Labels); //jz label out
    fprintf(OutputQuadraplesFile, "JMP L%d\n", CurrentLabel);   //jmp label in
    fprintf(OutputQuadraplesFile, "L%d:\n",Labels++); //label out
    currentScope = st->switchBack(currentScope);
    return VoidDataType;
}

void handleParameters(nodeType *p, bool reverseOrder) {
    if(p != NULL){
        int start = reverseOrder ? p->argumentType.arguments.size() - 1 : 0;
        int end = reverseOrder ? -1 : p->argumentType.arguments.size();
        int step = reverseOrder ? -1 : 1;
        for(int i = start; i != end; i += step){
            if(!st->insertNode(currentScope,p->argumentType.argumentsNames[i],"parameter",p->argumentType.arguments[i]))
             yyerror("parameter already exists in the current scope");
            fprintf(OutputQuadraplesFile, "POP %s\n", p->argumentType.argumentsNames[i]);
        }
    }
}


DataTypeEnum handleFunction(nodeType *p) {
    int caseNumber = p->oper.nops;
    if(!st->insertNode(currentScope,p->oper.op[1]->identifier.name,"function",p->oper.op[0]->defineType.type)){
        yyerror("function already exists in the current scope");
        return Error;
    }
    Node * tempNode = new Node();
    tempNode= currentScope;
    currentScope=st->createNewScope(currentScope);
    fprintf(OutputQuadraplesFile, "%s: \n", p->oper.op[1]->identifier.name);
    st->functionTypeMap[p->oper.op[1]->identifier.name] = [&]() -> vector<DataTypeEnum> {
        if (p->oper.op[2]) {
            return p->oper.op[2]->argumentType.arguments;
        } else {
            return vector<DataTypeEnum>{};
        }
    }();
    DataTypeEnum functionType = execute(p->oper.op[0]);
    handleParameters(p->oper.op[2], caseNumber == 5);
    execute(p->oper.op[3]);
    if(caseNumber == 5){
        DataTypeEnum returnType = execute(p->oper.op[4]);
        DataTypeEnum finalType = coercion(functionType, returnType);
        if(finalType == Error){
            yyerror("return type doesn't match the function type");
            return Error;
        }
    }
    currentScope->parent=tempNode;
    currentScope = st->switchBack(currentScope);
    fprintf(OutputQuadraplesFile, "END_FUNC\n");
}
DataTypeEnum checkArguments(nodeType* p, const std::string& functionName) {
    if(p->oper.op[1] != NULL)
    {
        if(p->oper.op[1]->argumentType.argumentsNodes.size() != st->functionTypeMap[functionName].size()){
            yyerror("number of passed arguments doesnt match the number of parameters");
            return Error;
        }
        for(int i=0; i < st->functionTypeMap[functionName].size(); i++){
            DataTypeEnum parameterType = execute(p->oper.op[1]->argumentType.argumentsNodes[i]);
            if(parameterType != st->functionTypeMap[functionName][i]){
                yyerror("type of passed argument doesnt match the type of the parameter");
                return Error;
            }
        }
    }
    else {
        if(st->functionTypeMap[functionName].size() != 0){
            yyerror("number of passed arguments doesnt match the number of parameters");
            return Error;
        }
    }
    return VoidDataType;
}
DataTypeEnum handleFunctionCall(nodeType *p){
    std::string functionName = p->oper.op[0]->identifier.name;
    DataTypeEnum funcType = getIdentifierType( p->oper.op[0]->identifier.name);
    DataTypeEnum checkResult = checkArguments(p, functionName);
    if(checkResult == Error) return Error;
    fprintf(OutputQuadraplesFile, "CALL %s\n", functionName.c_str());
    return funcType;
}

DataTypeEnum handleEndofLine(nodeType *p) {
    execute(p->oper.op[0]);
    execute(p->oper.op[1]);
    return VoidDataType;
}

void insertEnumVariable(nodeType* p, int index) {
    bool isInserted = st->insertNode(currentScope,p->oper.op[index]->identifier.name,"enum constant",0);
    if(!isInserted){
        yyerror("enum variable already exists in the current scope");
    }
}

void writeToFile(nodeType* p, int index, bool incrementEnumValue) {
    if (incrementEnumValue) {
        fprintf(OutputQuadraplesFile, "PUSH %d\n", ++EnumValue);
    }
    fprintf(OutputQuadraplesFile, "POP %s\n", p->oper.op[index]->identifier.name);
}

DataTypeEnum handleEnumVars(nodeType* p) {
    switch(p->oper.nops){
        case 1: 
        {
            insertEnumVariable(p, 0);
            writeToFile(p, 0, true);
            break;
        }
        case 2:
        {
            if(p->oper.op[0]->type==Identifier_Node){
                DataTypeEnum enumvartype = execute(p->oper.op[1]);
                if(enumvartype != IntDataType){
                    yyerror("enum variable value must be an integer");
                    return Error;
                }
                insertEnumVariable(p, 0);
                writeToFile(p, 0, false);
            }
            else 
            {
                insertEnumVariable(p, 1);
                execute(p->oper.op[0]);
                writeToFile(p, 1, true);
            }
            break;
        }
        case 3:
        {
            execute(p->oper.op[0]); //enum variables
            DataTypeEnum enumvartype3 = execute(p->oper.op[2]);
            if(enumvartype3 != IntDataType){
                yyerror("enum variable value must be an integer");
                return Error;
            }
            insertEnumVariable(p, 1);
            execute(p->oper.op[2]);
            writeToFile(p, 1, false);
            break;
        }
    }
    return VoidDataType;
}

DataTypeEnum handleAssignCase2(nodeType* p) {
    string kind = st->getKind(currentScope, p->oper.op[0]->identifier.name);
    if(kind == "constant"){
        yyerror("assignment of read only variable");
        return Error;
    }
    if(kind == "enum variable")
    {
        if(p->oper.op[1]->type!=Identifier_Node){
            yyerror("Invalid enum operation");
            return Error;
        }
        string enumName = st->checkType(currentScope, p->oper.op[0]->identifier.name);
        if(!st->validateEnum(currentScope,std::make_pair(enumName,p->oper.op[1]->identifier.name)))
        {
            yyerror("Invalid enum operation");
            return Error;
        }
        return EnumDataType;
    }
    DataTypeEnum varType = getIdentifierType(p->oper.op[0]->identifier.name);
    DataTypeEnum exprType = execute(p->oper.op[1]);
    DataTypeEnum finalType = coercion(varType, exprType);
    if(finalType==Error){
        yyerror("Type mismatch in 2 operands");
        return Error;
    }
    if(finalType != varType)
    {
        std::string type = typeEnumToString(varType);
        fprintf(OutputQuadraplesFile, "CONV_%s\n", type.c_str());            
    }
    fprintf(OutputQuadraplesFile, "POP %s\n", p->oper.op[0]->identifier.name);
    return varType;
}

DataTypeEnum handleAssignCase3(nodeType* p) {
    DataTypeEnum varType = execute(p->oper.op[0]);
    DataTypeEnum exprType = execute(p->oper.op[2]);
    DataTypeEnum finalType = coercion(varType, exprType);
    if(finalType==Error)
    {
        yyerror("Type mismatch in 3 operands");
        return Error;
    }
    if(finalType != varType)
    {
        std::string type = typeEnumToString(varType);
        fprintf(OutputQuadraplesFile, "CONV_%s\n", type.c_str());                                 
    }
    bool isInserted = st->insertNode(currentScope,p->oper.op[1]->identifier.name,"variable",p->oper.op[0]->defineType.type);
    if(!isInserted){
        yyerror("variable already exists in the current scope");
    }
    fprintf(OutputQuadraplesFile, "POP %s\n", p->oper.op[1]->identifier.name);
}


DataTypeEnum handleAssignCase4ConstType(nodeType* p) {
    DataTypeEnum varType = execute(p->oper.op[1]);
    DataTypeEnum exprType = execute(p->oper.op[3]);
    DataTypeEnum finalType = coercion(varType, exprType);
    if(finalType==Error)
    {
        yyerror("Type mismatch in 4 operands");
        return Error;
    }
    if(finalType != varType)
    {
        std::string type = typeEnumToString(varType);
        fprintf(OutputQuadraplesFile, "CONV_%s\n", type.c_str());             
    }
    bool isInserted = st->insertNode(currentScope,p->oper.op[2]->identifier.name,"constant",p->oper.op[1]->defineType.type);
    if(!isInserted){
        yyerror("variable already exists in the current scope");
    }
    fprintf(OutputQuadraplesFile, "POP %s\n", p->oper.op[2]->identifier.name);
}

DataTypeEnum handleAssignCase4EnumType(nodeType* p) {
    DataTypeEnum varType = execute(p->oper.op[1]);
    if(varType==Error)
    {
        yyerror("Enum wasnt defined in the current scope");
        return Error;
    }

    if(!st->validateEnum(currentScope,std::make_pair(p->oper.op[1]->identifier.name,p->oper.op[3]->identifier.name)))
    {
        yyerror("invalid enum operation");
        return Error;
    }
    fprintf(OutputQuadraplesFile, "PUSH %s\n", p->oper.op[3]->identifier.name);
    if(!st->insertEnumVar(currentScope,p->oper.op[2]->identifier.name,"enum variable",p->oper.op[1]->identifier.name))
    {
        yyerror("variable already exists in the current scope");
        return Error;
    }
    fprintf(OutputQuadraplesFile, "POP %s\n", p->oper.op[2]->identifier.name);
}

DataTypeEnum handleAssignCase4(nodeType* p) {
    if(p->oper.op[0]->defineType.type==ConstDataType){
        handleAssignCase4ConstType(p);
    }
    else if(p->oper.op[0]->defineType.type==EnumDataType)
    {
        handleAssignCase4EnumType(p);
    }
}

DataTypeEnum handleAssign(nodeType* p) {
    switch(p->oper.nops){
        case 2:
            return handleAssignCase2(p);
            break;
        case 3:
            return handleAssignCase3(p);
            break;
        case 4:
            return handleAssignCase4(p);
            break;
    }
}
DataTypeEnum handelMinusOps(nodeType*p){
    switch (p->oper.nops){
        case 1:
            return handleUnaryOperation(p);
        case 2:
            return handleAdditiveOperation(p);
    }
}
typedef DataTypeEnum (*operationHandler)(nodeType*);

operationHandler operationHandlers[] = {
    // handle loops 
    [FOR] = handleForLoop,
    [WHILE] = handleWhileLoop,
    [DO] = handleDo,
    // handle conditional statements
    [IF] = handleIfStatement,
    [SWITCH] = handleSwitchStatement,
    [CASE] = handleCaseStatement,
    // handle enum cases
    [ENUM] = handleEnumCaseStatement,
    // hand logical operations
    [AND] = handleLogicalOperation,
    [OR] = handleLogicalOperation,
    // handl equality operations
    [EQ] = handlEqualitEqualityOperation,
    [NE] = handlEqualitEqualityOperation,
    [GE] = handlEqualitEqualityOperation,
    [LE] = handlEqualitEqualityOperation,
    // handle relational operations
    [LT] = handleRelationalOperation,
    [GT] = handleRelationalOperation,
    // handle arithmetic operations
    [MULT] = handleMultiplicativeOperation,
    [DIV] = handleMultiplicativeOperation,
    [MOD] = handleMultiplicativeOperation,
    [PLUS] = handleArithmeticOperation,
    [MINUS] = handelMinusOps,
    // handle unary operations
    [INC] = handleUnaryOperation,
    [DEC] = handleUnaryOperation,
    [NOT] = handleUnaryOperation,
    // handle assign operations
    [ASSIGN] = handleAssign,
    // handle end of line
    [';'] = handleEndofLine,
    // handle the enum variables
    [','] = handleEnumVars,
    // handel func declaration
    ['d'] = handleFunction,
    // handle function call
    ['f'] = handleFunctionCall
};
DataTypeEnum handlerConstValue(nodeType *p){
    writeVar(p->constant.value, p->constant.ConstDataType);
    return p->constant.ConstDataType;
}
DataTypeEnum handlerType_Node(nodeType *p){
    return p->defineType.type;
}
DataTypeEnum handlerOperation(nodeType* p) {
    return operationHandlers[p->oper.oper](p);
}


typedef DataTypeEnum (*executeHandler)(nodeType*);

executeHandler executeHandlers[] = {
    [Constant_Node] = handlerConstValue, // int x = 5
    [Identifier_Node] = handleIdetifierNode, // int x;
    [Type_Node] = handlerType_Node, // x + 5 (type_node)
    [Operator_Node] = handlerOperation 
};

DataTypeEnum execute(nodeType *p){

    if(p == NULL) return Error;
    return executeHandlers[p->type](p);
    return Error;
}

DataTypeEnum getIdentifierType(char* identifierName) 
{
    string typeIdentifier = st->checkType(currentScope, identifierName);

    // Create a vector of pairs to associate string types with DataTypeEnum values
    std::vector<std::pair<string, DataTypeEnum>> typeMap = {
        {"integer", IntDataType},
        {"float", FloatDataType},
        {"string", StringDataType},
        {"boolean", BoolDataType},
        {"void", VoidDataType},
        {"char", CharDataType},
        {"enum", EnumDataType},
        {"const", ConstDataType}
    };

    // Use std::find_if to find the type in the vector
    auto it = std::find_if(typeMap.begin(), typeMap.end(), 
                           [&typeIdentifier](const std::pair<string, DataTypeEnum>& pair) { return pair.first == typeIdentifier; });

    // If the type is found, return the corresponding DataTypeEnum value
    if (it != typeMap.end()) {
        return it->second;
    }

    // If the type is not found, report an error and return Error
    yyerror("variable was not declared in this scope");
    return Error;
}
DataTypeEnum coercion(DataTypeEnum typeOP1, DataTypeEnum typeOP2)
{
    // return the highest type by just comparing the enum values
    if(typeOP1 == Error || typeOP2 == Error)
    {
        return Error;
    }
    if(typeOP1 == typeOP2)
    {
        return typeOP1;
    }

    // If one of the types is a constant, return the other type
    if(typeOP1 == ConstDataType || typeOP2 == ConstDataType)
    {
        return ConstDataType;
    }
    // If one of the types is a string, enum, or void, return Error
    if(typeOP1 == StringDataType || typeOP1 == EnumDataType || typeOP1 == VoidDataType ||
       typeOP2 == StringDataType || typeOP2 == EnumDataType || typeOP2 == VoidDataType)
    {
        return Error;
    }

    return typeOP1 > typeOP2 ? typeOP1 : typeOP2;
}


void yyerror(const char *str)
{
    fprintf(stderr,"error: %s, Last token: %s \n",str, last_token);
    fprintf(errorsFile,"error: %s\n",str);
}

void yywarning(const char* str){
    warningsFile = fopen("warning.txt","w");
    fprintf(stderr,"%s\n",str);
    fprintf(warningsFile,"%s\n",str);
    fclose(warningsFile);
}

int yywrap()
{
    return 1;
} 

void read_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }

    // Read input from file and process it as needed

    fclose(fp);
}

int main(int argc, char **argv) {
    FILE *fp = stdin;
    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (!fp) {
            perror("Error opening file");
            return 1;
        }
    }

    errorsFile = fopen("errors.txt", "w");

    yyin = fp;
    //Quadraples data initialization:
    OutputQuadraplesFile = fopen("output.txt", "w");
    Labels = 0;
    CaseLabels = 0;
    EndSwitchLabel = 0;
    EnumValue = -1;
    TempVariables = 0;
    yyparse();

    fclose(fp);
    fclose(errorsFile);
    fclose(OutputQuadraplesFile);
    st->generateSymbolTable(currentScope);

    return 0;
}
