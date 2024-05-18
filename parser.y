%{
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
%}

%code requires{
    #include "include/parser.h"
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