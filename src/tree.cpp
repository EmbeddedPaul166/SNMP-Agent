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

//Call this function with as such 'findNodeByObjectIdentifier(vector, 0, m_rootOfTheTree)' !!!
//This function should be called inside try catch block and if it returns nullptr it should throw exception!!!
Node * Tree::findNodeByObjectIdentifier(std::vector<int> vectorOfOID, int vectorPosition, Node * node)
{
    std::list<Node *> childList = node -> m_childElementPointerList;
    std::list<Node *>::iterator childListIterator = childList.begin();
    for (auto const & pNode : childList)
    {   
        if (pNode -> m_objectIdentifier ==  vectorOfOID.at(vectorPosition) && vectorOfOID.size() - 1 == vectorPosition)
        {
            return pNode;        
        }
        else if (pNode -> m_objectIdentifier ==  vectorOfOID.at(vectorPosition))
        {
            vectorPosition++;
            findNodeByObjectIdentifier(vectorOfOID, vectorPosition, pNode);
        }
        std::advance(childListIterator, 1);
    } 
    return nullptr;
}

Node * Tree::findNodeByName(std::string objectIdentifierParentNode, std::string name)
{
      
    return nullptr;
}



