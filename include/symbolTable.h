#include<iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include "parser.h"
using namespace std;

struct Node
{
    Node *parent;
    unordered_map<string, vector<string>> node_data;
    vector<Node*> children;
};

class SymbolTable {
private:
  

    // Private constructor so that no objects can be created.
    SymbolTable() {}

    // Static instance of the class
    static SymbolTable* instance;

public:
    unordered_map<string, Node*> enumerationTypeMap;
    unordered_map<string, vector<DataTypeEnum>> functionTypeMap;
    unordered_map<string, bool> variables;
    // Static method to control the access to the singleton instance.
    static SymbolTable* getInstance();


    bool insertNode(Node*node,string identifier, string kind, int type );


    bool insertEnumVar(Node* node,string identifier, string kind, string type);
    

    string checkType(Node* node, string name);


    string getKind(Node* node, string name);
    

    bool validateEnum (Node *curr_node,std::pair<std::string,std::string>vars);
    
    
    void generateSymbolTable(Node*curr_node);



    Node *createNewScope(Node* currentScope);
    Node* switchBack(Node* currentScope);
    bool checkForUnusedVariables();
};


