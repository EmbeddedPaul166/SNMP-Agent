#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <string>

struct Node
{ 
    int m_objectIdentifier;
    std::string m_name;
    std::string m_data;
    std::string * m_data_type;
    Node * m_pParentElement;
    std::list<Node *> m_childElementPointerList;
};

class Tree
{
    public:
        Tree();
        ~Tree();
        
        void addNode(int objectIdentifier, std::string name, std::string data, std::string * dataType, Node * previousElement);
        Node * findNodeByObjectIdentifier(std::vector<int> vectorOfOID); 
        Node * findNodeByName(std::vector<int> vectorOfOID, std::string name);
        
    private:
        Node * m_rootOfTheTree;
        std::vector<std::string> m_listOfDataTypes;
        
        Node * recursiveSearch(std::vector<int> vectorOfOID, unsigned int vectorPosition, Node * node); 
        void initializeRootOfTheTree();
        void initializeListOfDataTypes();
    protected:
        
};

#endif /*TREE_HPP*/
