#include "../include/symbolTable.h"
#include <functional>  

#include<string.h>
SymbolTable* SymbolTable::instance = nullptr;

/**
 * @brief Singleton pattern to get the instance of SymbolTable
 * @return Pointer to the instance of SymbolTable
 */
SymbolTable *SymbolTable::getInstance()
{
    if (!instance)
    {
        instance = new SymbolTable();
    }
    return instance;
}
/**
 * @brief Converts DataTypeEnum to string
 * @param type DataTypeEnum
 * @return const char* 
 */
const char* typeEnumToString(DataTypeEnum type){
    switch(type){
        case IntDataType:
            return "integer";
        case FloatDataType:
            return "float";
        case StringDataType:
            return "string";
        case BoolDataType:
            return "boolean";
        case VoidDataType:
            return "void";
        case CharDataType:
            return "char";
        case EnumDataType:
            return "enum";
        case ConstDataType:
            return "const";
        case Error:
            return "error";
        case Unknown:
            return "unknown";
    }
}
/**
 * @brief Converts string to DataTypeEnum
 * @param type string
 * @return DataTypeEnum
 */
const DataTypeEnum stringToTypeEnum(const string type){
    if(type == "integer"){
        return IntDataType;
    }
    else if(type == "float"){
        return FloatDataType;
    }
    else if(type == "string"){
        return StringDataType;
    }
    else if(type == "boolean"){
        return BoolDataType;
    }
    else if(type == "void"){
        return VoidDataType;
    }
    else if(type == "char"){
        return CharDataType;
    }
    else if(type == "enum"){
        return EnumDataType;
    }
    else if(type == "const"){
        return ConstDataType;
    }
    else if(type == "error"){
        return Error;
    }
    else{
        return Unknown;
    }
}
/**
 * @brief Inserts a node in the symbol table
 * @param name string
 * @param kind string
 * @param type int
 * @param curr_node Node*
 * @return bool
 */
bool SymbolTable::insertNode(Node* curr_node,string name, string kind, int type)
{
    bool exists = false;
    for (auto it = curr_node->node_data.begin(); it != curr_node->node_data.end(); ++it) {
        if( it->first == name)
        {
            exists = true;
        }
    }
    if(exists){
        return false;
    }

    vector<string> data(2);
    data[0] = kind;
    data[1] = typeEnumToString((DataTypeEnum)type);
    curr_node->node_data[name] = data;
    if(kind == "variable")
    {
        variables[name] = false;
    }
    
    return true;
}
/**
 * @brief Inserts an enum variable in the symbol table
 * @param name string
 * @param kind string
 * @param type string
 * @param curr_node Node*
 * @return bool
 */
bool SymbolTable::insertEnumVar(Node* curr_node,string name, string kind, string type)
{
    // Check if the name already exists in current scope
    auto it = std::find_if(curr_node->node_data.begin(), curr_node->node_data.end(), 
                           [&name](const pair<string, vector<string>>& pair){ return pair.first == name; });

    // If the name exists, return false
    if(it != curr_node->node_data.end()){
        return false;
    }

    curr_node->node_data[name] = {kind, type};
    variables[name] = false;
    return true;
}

/**
 * @brief Checks the type of a variable
 * @param node Node*
 * @param name string
 * @return string
 */


string SymbolTable::checkType(Node* node, string name)
{
    if(node == nullptr)
    {
        return "Error";
    }
    auto it = find_if(node->node_data.begin(), node->node_data.end(), 
                      [&name](const pair<string, vector<string>>& pair){ return pair.first == name; });
    if(it != node->node_data.end())
    {
        return it->second[1];
    }
    return checkType(node->parent, name);
}

/**
 * @brief Gets the kind of a variable
 * @param curr_node Node*
 * @param name string
 * @return string
 */
string SymbolTable::getKind(Node* curr_node, string name)
{
    if(curr_node == nullptr)
    {
        return "Error";
    }
    auto it = find_if(curr_node->node_data.begin(), curr_node->node_data.end(), 
                      [&name](const std::pair<std::string, std::vector<std::string>>& pair){ return pair.first == name; });
    if(it != curr_node->node_data.end())
    {
        return it->second[0];
    }
    return getKind(curr_node->parent, name);
}

/**
 * @brief Validates an enum variable
 * @param vars pair<string,string>
 * @param curr_node Node*
 * @return bool
 */
bool SymbolTable::validateEnum( Node* curr_node,std::pair<std::string,std::string>vars)
{
    string enumName(vars.first), name(vars.second);
    auto enumScope = enumerationTypeMap[enumName];
    auto it = find_if(enumScope->node_data.begin(), enumScope->node_data.end(), 
                      [&name](const std::pair<std::string, std::vector<std::string>>& pair){ return pair.first == name; });
    return it != enumScope->node_data.end();
}
/**
 * @brief Creates a new scope
 * @param currentScope Node*
 * @return Node*
 */
Node * SymbolTable::createNewScope(Node* currentScope){
    Node* newNode = new Node();
    newNode->parent = currentScope;
    currentScope->children.push_back(newNode);
    currentScope = newNode;
    return currentScope;
}
/**
 * @brief Switches back to the parent scope
 * @param currentScope Node*
 * @return Node*
 */

Node* SymbolTable::switchBack(Node* currentScope){
    return currentScope->parent;
}
/**
 * @brief Displays the data of a node
 * @param currentNode Node*
 */

void displayNodeData(Node *currentNode)
{
    if(currentNode == nullptr)
    {
        return;
    }
    for (const auto& nodeData : currentNode->node_data) {
        cout << nodeData.first << "\t\t" << nodeData.second[0] << "\t\t" << nodeData.second[1] << endl;
    }
    cout<<"========================================================================\n";
    for(const auto& child : currentNode->children){
        displayNodeData(child);
    }
}
/**
 * @brief Generates the symbol table
 * @param currentNode Node*
 */
void SymbolTable::generateSymbolTable(Node *currentNode)
{
    std::ofstream outputFile;
    outputFile.open("./symbolTable.txt", std::ios::out | std::ios::trunc);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open SymbolTable.txt\n";
        return;
    }

    // outputFile << "id\t\tkind\t\t\ttype\n";
    std::cout << "id\t\tkind\t\t\ttype\n";

    std::function<void(Node*)> displayNodeData = [&](Node *node) {
        if(node == nullptr)
        {
            return;
        }
        for (const auto& nodeData : node->node_data) {
            outputFile << "Variable: " << nodeData.first << "\n"
                       << "Kind: " << nodeData.second[0] << "\n"
                       << "Type: " << nodeData.second[1] << "\n";
            std::cout << "Variable: " << nodeData.first << "\n"
                      << "Kind: " << nodeData.second[0] << "\n"
                      << "Type: " << nodeData.second[1] << "\n";
            outputFile << "====================\n";
            std::cout << "====================\n";
        }
        for(const auto& child : node->children){
            displayNodeData(child);
        }
    };
    displayNodeData(currentNode);
    outputFile.close();
}


/**
 * @brief Checks for unused variables
 * @return bool
 */

bool SymbolTable::checkForUnusedVariables()
{
    std::ofstream myfile("warning.txt", std::ios_base::app);

    for (const auto& variable : variables) {
        if(!variable.second)
        {
            std::cout << "warning: unused variable " << variable.first << std::endl;
            myfile << "warning: unused variable " << variable.first << "\n";
        }
    }
    
    return true;
}
