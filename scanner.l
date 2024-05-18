%{
    /* Definition section */
    #include "include/common.h"
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "parser.tab.h"  
%}

%option noyywrap

%%

"if"                { return IF; }     
"else"              { return ELSE; }
"for"               { return FOR; }
"while"             { return WHILE; }
"do"                { return DO; }
"switch"            { return SWITCH; }
"case"              { return CASE; }
"break"             { return BREAK; }
"return"            { return RETURN; }
"void"              { return VOID; }
"enum"              { return ENUM; }

"int"               { return INT_TYPE; }
"char"              { return CHAR_TYPE; }
"bool"              { return BOOL_TYPE; }
"float"             { return FLOAT_TYPE; }
"string"            { return STRING_TYPE; }
"const"             { return CONST; }


[\(\)\{\}:;,]   { return *yytext; } 


"=="                { return EQ; }
"!="                { return NE; }
">="                { return GE; }
"<="                { return LE; }
"++"                { return INC; }
"--"                { return DEC; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return MULT; }
"/"                 { return DIV; }
"%"                 { return MOD; }
"="                 { return ASSIGN; }
">"                 { return GT; }
"<"                 { return LT; }
"!"                 { return NOT; }


"&&"                { return AND; }
"||"                { return OR; }


0|-?[1-9][0-9]*                    { yylval.integer_val = atoi(yytext); return INTEGER; }
-?(0|[1-9][0-9]*)\.[0-9]*[1-9]     { yylval.float_val = strtof(yytext, NULL); return FLOAT; }

"true"                             { yylval.integer_val = 1; return BOOL_TRUE; }
"false"                            { yylval.integer_val = 0; return BOOL_FALSE; }

\'.\'                              { yylval.char_val = *(yytext+1); return CHAR; }
\".*\"                             { yylval.string_val = strtok(yytext, "\""); return STRING; }
[_a-zA-Z][_a-zA-Z0-9]*             { yylval.string_val = strdup(yytext); return VARIABLE; }

[ \t\n\r]+                         { /* Ignore whitespace */ }              

.                                  { fprintf(stderr, "Unrecognized character: %s\n", yytext); }

%%