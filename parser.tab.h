/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 40 "parser.y"

    #include "include/parser.h"

#line 53 "parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    FOR = 260,                     /* FOR  */
    WHILE = 261,                   /* WHILE  */
    DO = 262,                      /* DO  */
    SWITCH = 263,                  /* SWITCH  */
    CASE = 264,                    /* CASE  */
    BREAK = 265,                   /* BREAK  */
    RETURN = 266,                  /* RETURN  */
    ENUM = 267,                    /* ENUM  */
    VOID = 268,                    /* VOID  */
    INT_TYPE = 269,                /* INT_TYPE  */
    CHAR_TYPE = 270,               /* CHAR_TYPE  */
    BOOL_TYPE = 271,               /* BOOL_TYPE  */
    FLOAT_TYPE = 272,              /* FLOAT_TYPE  */
    STRING_TYPE = 273,             /* STRING_TYPE  */
    CONST = 274,                   /* CONST  */
    EQ = 275,                      /* EQ  */
    NE = 276,                      /* NE  */
    GE = 277,                      /* GE  */
    LE = 278,                      /* LE  */
    INC = 279,                     /* INC  */
    DEC = 280,                     /* DEC  */
    AND = 281,                     /* AND  */
    OR = 282,                      /* OR  */
    GT = 283,                      /* GT  */
    LT = 284,                      /* LT  */
    PLUS = 285,                    /* PLUS  */
    MINUS = 286,                   /* MINUS  */
    MULT = 287,                    /* MULT  */
    DIV = 288,                     /* DIV  */
    MOD = 289,                     /* MOD  */
    NOT = 290,                     /* NOT  */
    ASSIGN = 291,                  /* ASSIGN  */
    INTEGER = 292,                 /* INTEGER  */
    FLOAT = 293,                   /* FLOAT  */
    BOOL_FALSE = 294,              /* BOOL_FALSE  */
    BOOL_TRUE = 295,               /* BOOL_TRUE  */
    CHAR = 296,                    /* CHAR  */
    STRING = 297,                  /* STRING  */
    VARIABLE = 298                 /* VARIABLE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 45 "parser.y"

    int integer_val;
    char* string_val;
    float float_val;
    char char_val;
    bool bool_val;
    nodeType* node;

#line 122 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
