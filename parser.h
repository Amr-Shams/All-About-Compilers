#pragma once
#include <stdbool.h>
#include<vector>
using namespace std;
typedef struct nodeTypeTag nodeTypeTag;


typedef enum {
    Constant_Node,
    Identifier_Node,
    Type_Node,
    Operator_Node,
    ArgumentNode
} nodeEnum;

typedef enum {
    BoolDataType,
    CharDataType,
    IntDataType,
    FloatDataType,
    StringDataType,
    VoidDataType,
    EnumDataType,
    ConstDataType,
    Error,
    Unknown
} DataTypeEnum;

const char* typeEnumToString(DataTypeEnum type);
const DataTypeEnum stringToTypeEnum(const string type);


typedef struct {
    char* name;
} IdentifierNodeType;


typedef struct {
    DataTypeEnum ConstDataType;
    void* value;
} ConstantNodeType;
typedef struct {
    int oper;
    int nops;
    struct nodeTypeTag *op[1];
} OperatorNodeType;


typedef struct {
    DataTypeEnum type;
} TypeNodeType;

typedef struct {
    vector<DataTypeEnum> arguments;
    vector<char*> argumentsNames;
    vector<nodeTypeTag*> argumentsNodes;
} ArgumentNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;
    union {
        ConstantNodeType constant;
        IdentifierNodeType identifier;
        TypeNodeType defineType;
        OperatorNodeType oper;
        ArgumentNodeType argumentType;
    };
} nodeType;
