%{
    /*Definition section */
    #include "include/common.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include<string.h>
    #include <stdarg.h>
    #include "include/parser.h"
    #include "include/symbolTable.h"
    #include "include/helpers.h"
    extern FILE *yyin;
    extern int yylex(void);
    void yyerror(const char *str);
    void read_file(char *filename);
    void yywarning(const char* str);
%}

%code requires{
    #include "include/parser.h"
    #include "include/symbolTable.h"
    #include "include/helpers.h"
    
}


%union {
    int integer_val;
    char* string_val;
    float float_val;
    char char_val;
    bool bool_val;
    nodeType* node;
}

%token IF ELSE FOR WHILE DO SWITCH CASE BREAK RETURN ENUM VOID 
%token INT_TYPE CHAR_TYPE BOOL_TYPE FLOAT_TYPE STRING_TYPE CONST

%token <string_val> EQ NE GE LE INC DEC AND OR GT LT 
%token <string_val> PLUS MINUS MULT DIV MOD NOT ASSIGN
%token <integer_val> INTEGER 
%token <float_val> FLOAT 
%token <integer_val> BOOL_FALSE BOOL_TRUE 
%token <char_val> CHAR 
%token <string_val> STRING 
%token <string_val> VARIABLE

%type <node> statement recursive_statement conditional_statement
                if_conditional_statement switch_conditional_statement
                case_statement loop_statement for_loop_statement
                while_loop_statement do_while_loop_statement assignment
                expressions function_call functional_statement function_parameters parameter  
                equality_expression relational_expression additive_expression multiplicative_expression unary_expression primary_expression
                function_parameters_calls parameter_calls function return_types
                enum_statement enum_variables variable_Type variable_value     
%%

program: root {printf("end of program\n"); st->checkForUnusedVariables();};


/* $$: $1 $2 */
root:  root statement 
        {
        execute($2);
        } 
        | root functional_statement 
        {
        execute($2);
        } 
        | root enum_statement
        {
        execute($2);
        }
        |
        {/* empty */}
        ;

statement:  conditional_statement 
        { 
        $$=$1;
        } 
        |  
        loop_statement 
        { 
        $$=$1;
        } 
        |  
        assignment ';' 
        { 
        $$=$1;
        } 
        ;
            
recursive_statement: recursive_statement statement 
        {
        $$=createOperationNode(';',2,$1,$2);
        } 
        | 
        {
        $$=NULL;
        }
        ;
            
//---------conditional statement---------// 
conditional_statement:  switch_conditional_statement 
        {
        $$=$1;
        } 
        |
        if_conditional_statement 
        {
        $$=$1;
        } 
        ;

if_conditional_statement:  IF '(' expressions ')' '{'recursive_statement'}'  ELSE '{'recursive_statement'}' 
        {
        $$=createOperationNode(IF,3,$3,$6,$10);
        } 
        | IF '(' expressions ')' '{'recursive_statement'}' 
        {
        $$=createOperationNode(IF,2,$3,$6);
        }
        ; 

switch_conditional_statement:   SWITCH '('VARIABLE')' '{' case_statement '}' 
        {
        $$=createOperationNode(SWITCH,2,createIdentifierNode($3),$6);
        } 
        ;

case_statement: case_statement CASE variable_value ':' recursive_statement BREAK  
        {
        $$=createOperationNode(CASE,3,$1,$3,$5);
        } 
        |  
        {
        $$=NULL;
        } 
        ; 

//---------loop statement---------// 
loop_statement: for_loop_statement  
        {
        $$=$1;
        } 
        | 
        while_loop_statement 
        {
        $$=$1;
        } 
        | 
        do_while_loop_statement 
        {
        $$=$1;
        } 
        ;

for_loop_statement: FOR '(' assignment ';' expressions ';' assignment')' '{' recursive_statement '}' 
        {
        $$=createOperationNode(FOR,4,$3,$5,$7,$10);
        } 
        ;

while_loop_statement: WHILE '(' expressions ')' '{' recursive_statement '}'  
        {
        $$=createOperationNode(WHILE,2,$3,$6);
        } 
        ;


do_while_loop_statement: DO '{' recursive_statement '}' WHILE '(' expressions ')'  
        {
        $$=createOperationNode(DO,2,$3,$7);
        }
        ;

//-------------assignments-------------//
assignment: variable_Type VARIABLE ASSIGN expressions
        {
        $$=createOperationNode(ASSIGN,3,$1,createIdentifierNode($2),$4);
        } 
        | VARIABLE ASSIGN expressions  
        {
        $$=createOperationNode(ASSIGN,2,createIdentifierNode($1),$3);
        }  
        | ENUM VARIABLE VARIABLE ASSIGN VARIABLE 
        {
        $$=createOperationNode(ASSIGN,4,createType(EnumDataType),createIdentifierNode($2),createIdentifierNode($3),createIdentifierNode($5));
        } 
        | CONST variable_Type VARIABLE ASSIGN expressions
        {
        $$=createOperationNode(ASSIGN,4,createType(ConstDataType),$2,createIdentifierNode($3),$5);
        }
        | expressions  
        {
        $$ = $1;
        }
        ; 

//------------Expressions-------------//


expressions: expressions OR equality_expression 
        {
        $$=createOperationNode(OR,2,$1,$3);
        }
        | expressions AND equality_expression 
        {
        $$=createOperationNode(AND,2,$1,$3);
        }
        | equality_expression  
        {
        $$=$1;
        }
        ;



equality_expression:  equality_expression EQ relational_expression 
        {
        $$=createOperationNode(EQ,2,$1,$3);
        } 
        | equality_expression NE relational_expression  
        {
        $$=createOperationNode(NE,2,$1,$3);
        } 
        | equality_expression GE relational_expression  
        {
        $$=createOperationNode(GE,2,$1,$3);
        }
        | equality_expression LE relational_expression  
        {
        $$=createOperationNode(LE,2,$1,$3);
        }
        | relational_expression  
        {
        $$=$1;
        } 
        ;

relational_expression:  relational_expression GT additive_expression 
        {
        $$=createOperationNode(GT,2,$1,$3);
        } 
        | relational_expression LT additive_expression 
        {
        $$=createOperationNode(LT,2,$1,$3);
        } 
        | additive_expression 
        {
        $$=$1;
        }
        ;

additive_expression: additive_expression PLUS multiplicative_expression 
        {
        $$=createOperationNode(PLUS,2,$1,$3);
        } 
        | additive_expression MINUS multiplicative_expression 
        {
        $$=createOperationNode(MINUS,2,$1,$3);
        } 
        | multiplicative_expression 
        {
        $$=$1;
        } 
        ;

multiplicative_expression:  multiplicative_expression MULT unary_expression 
        {
        $$=createOperationNode(MULT,2,$1,$3);
        } 
        | multiplicative_expression DIV unary_expression 
        {
        $$=createOperationNode(DIV,2,$1,$3);
        } 
        | multiplicative_expression MOD unary_expression 
        {
        $$=createOperationNode(MOD,2,$1,$3);
        }
        | unary_expression 
        {
        $$=$1;
        }
        ; 

unary_expression:  MINUS unary_expression  
        {
        $$=createOperationNode(MINUS,1,$2);
        } 
        | NOT unary_expression 
        {
        $$=createOperationNode(NOT,1,$2);
        }
        | INC unary_expression 
        {
        $$=createOperationNode(INC,1,$2);
        }
        | DEC unary_expression 
        {
        $$=createOperationNode(DEC,1,$2);
        }
        | primary_expression  
        {
        $$=$1;
        } 
        ;

primary_expression: '(' expressions ')' 
        {
        $$=$2;
        } 
        | variable_value | function_call
        {
        $$ = $1;
        } 
        | VARIABLE 
        {
        $$ = createIdentifierNode($1);
        };


//------------functions---------------//
function_call:  VARIABLE '(' function_parameters_calls ')' 
        {
        $$=createOperationNode('f',2,createIdentifierNode($1),$3);
        }
        ;

functional_statement: function 
        {
        $$=$1;
        };

function_parameters: parameter 
        {
        $$=$1;
        } 
        | 
        {
        $$=NULL;
        }
        ; 

parameter:  parameter ',' variable_Type VARIABLE  
        {
        $$ = addToParameterList($1, $3, createIdentifierNode($4));
        } 
        | variable_Type VARIABLE 
        {
        $$ = createParameterList($1, createIdentifierNode($2));
        } 
        ;

function_parameters_calls:  parameter_calls 
        {
        $$=$1;
        } 
        | 
        {
        $$=NULL;
        }
        ; 

parameter_calls: parameter_calls ',' expressions 
        {
        $$=addToParameterCallList($1,$3);
        } 
        | expressions 
        {
        $$=createParameterCallList($1);
        } 
        ;

function: variable_Type VARIABLE '(' function_parameters ')' '{' recursive_statement RETURN return_types';' '}'  
        {
        $$=createOperationNode('d',5,$1,createIdentifierNode($2),$4,$7,$9);
        } 
        | VOID VARIABLE '(' function_parameters ')' '{' recursive_statement '}' 
        {
        $$=createOperationNode('d',4,createType(VoidDataType),createIdentifierNode($2),$4,$7);
        } 
        ;

return_types:   expressions  
        {
        $$=$1;
        }
        ;

enum_statement: ENUM VARIABLE '{'enum_variables'}' 
        {
        $$=createOperationNode(ENUM,2,createIdentifierNode($2),$4);
        }
        ; 

enum_variables:  enum_variables ',' VARIABLE ASSIGN expressions 
        {
        $$=createOperationNode(',',3,$1,createIdentifierNode($3),$5);
        } 
        | enum_variables ',' VARIABLE 
        {
        $$=createOperationNode(',',2,$1,createIdentifierNode($3));
        } 
        | VARIABLE ASSIGN expressions 
        {
        $$=createOperationNode(',',2,createIdentifierNode($1),$3);
        } 
        | VARIABLE 
        {
        $$=createOperationNode(',',1,createIdentifierNode($1));
        } 
        ;

//------------variables---------------//
variable_Type:  INT_TYPE  
        {
        $$ = createType(IntDataType);
        } 
        | CHAR_TYPE 
        {
        $$ = createType(CharDataType);
        } 
        | BOOL_TYPE 
        {
        $$ = createType(BoolDataType);
        } 
        | FLOAT_TYPE 
        {
        $$ = createType(FloatDataType);
        } 
        | STRING_TYPE 
        {
        $$ = createType(StringDataType);
        }
        ;  

variable_value: INTEGER  
        {
        $$ = constantValue(IntDataType, &$1);
        } 
        | FLOAT 
        {
        $$ = constantValue(FloatDataType, &$1);
        } 
        | BOOL_FALSE 
        {
        $$ = constantValue(BoolDataType, &$1);
        } 
        | BOOL_TRUE 
        {
        $$ = constantValue(BoolDataType, &$1);
        } 
        | CHAR 
        {
        $$ = constantValue(CharDataType, &$1);
        } 
        | STRING
        {
        $$ = constantValue(StringDataType, $1);
        } 
        ;
%%


int main(int argc, char **argv) {
  return mainFunction(argc, argv);
}