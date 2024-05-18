// helpers.h
#ifndef HELPERS_H
#define HELPERS_H
#include "parser.h"
    #include "common.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include<string.h>
    #include <stdarg.h>
    #include "symbolTable.h"
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
    SymbolTable* st = SymbolTable::getInstance();
    Node *currentScope = new Node();
    Node *rootScope = currentScope;
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

#endif // HELPERS_H