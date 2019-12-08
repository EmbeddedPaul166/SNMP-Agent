#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "node.hpp"
#include "datatype.hpp"

class Tree
{
    public:
        Tree();
        ~Tree();
        
        Node * addNode(unsigned int objectIdentifier, std::string name, std::string * dataType,
                       std::string description, AccessType accessType, StatusType statusType,
                       Node * pParentElement);
        Node * findNodeByObjectIdentifier(std::vector<unsigned int> vectorOfOID); 
        Node * findNodeByName(std::vector<unsigned int> vectorOfOID, std::string name);
        
        Node * m_rootOfTheTree;
        std::list<Node> m_nodeList;
        std::vector<std::string> m_dataTypeVector;
        
    private:
        Node * recursiveSearch(std::vector<unsigned int> vectorOfOID, unsigned int vectorPosition, Node * node);
        void initializeRootOfTheTree();
        std::string * checkDataType(std::string dataType);
        
    protected:
        
};

#endif /*TREE_HPP*/
