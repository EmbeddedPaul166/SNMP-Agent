#include "tree.hpp"

Tree::Tree()
{
    initializeRootOfTheTree(); 
}

Tree::~Tree()
{
    
}

void Tree::addNode(int objectIdentifier, std::string dataType,
                   std::string name, std::string data,
                   Node * parentElement)
{ 
    std::vector <Node *> emptyChildVector;
    Node newNode = {objectIdentifier,
                    name,
                    data,
                    parentElement,
                    emptyChildVector};
    
    parentElement -> m_childElementPointerVector.push_back(&newNode);
}

void Tree::initializeRootOfTheTree()
{
    addNode(1, "", "ISO", "", nullptr);

    std::vector <Node *> emptyChildVector;
    Node newNode = {1,
                    "",
                    "ISO",
                    nullptr,
                    emptyChildVector};
    m_rootOfTheTree = &newNode;
}
