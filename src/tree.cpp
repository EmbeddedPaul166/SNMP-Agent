#include "tree.hpp"

Tree::Tree()
{
    
}

Tree::~Tree()
{
    
}

void Tree::addNode(int &objectIdentifier, std::string &dataType,
             std::string &name, std::string &data, Node &previousElement)
{ 
    Node newNode = {objectIdentifier,
                    dataType,
                    name,
                    data,
                    &previousElement};
    
    m_tree.push_back(newNode);
}
