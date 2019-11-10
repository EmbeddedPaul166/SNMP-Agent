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
    std::list <Node *> emptyChildList;
    Node newNode = {objectIdentifier,
                    name,
                    data,
                    parentElement,
                    emptyChildList};
    
    if (parentElement -> m_childElementPointerList.empty())
    {
        parentElement -> m_childElementPointerList.push_back(&newNode); 
    }
    else
    {
        std::list<Node *>::iterator iterator = parentElement -> m_childElementPointerList.begin();
        for (auto const & j : parentElement -> m_childElementPointerList)
        {
            int childObjectIdentifier = j -> m_objectIdentifier;
            int newChildObjectIdentifier = newNode.m_objectIdentifier;
            if (newChildObjectIdentifier < childObjectIdentifier)
            {
                parentElement -> m_childElementPointerList.insert(iterator, &newNode);
                break;
            }
            else if (parentElement -> m_childElementPointerList.end() == iterator)
            {
                parentElement -> m_childElementPointerList.push_back(&newNode);
                break;
            }
            std::advance(iterator, 1);
        }
    }
}

void Tree::initializeRootOfTheTree()
{
    addNode(1, "", "ISO", "", nullptr);

    std::list <Node *> emptyChildList;
    Node newNode = {1,
                    "",
                    "ISO",
                    nullptr,
                    emptyChildList};
    m_rootOfTheTree = &newNode;
}

Node * Tree::findNodeByObjectIdentifier(std::string objectIdentifier)
{
    
    return nullptr;    
}

Node * Tree::findNodeByName(std::string objectIdentifierParentNode)
{
    
    return nullptr;
}



