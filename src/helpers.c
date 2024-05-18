#include "../include/helpers.h"

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



void read_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }

    // Read input from file and process it as needed

    fclose(fp);
}