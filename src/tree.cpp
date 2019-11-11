#include "tree.hpp"

Tree::Tree()
{
    initializeListOfDataTypes();
    initializeRootOfTheTree();
}

Tree::~Tree()
{
    
}

void Tree::addNode(int objectIdentifier, std::string name, std::string data, std::string * dataType, Node * parentElement)
{ 
    std::list <Node *> emptyChildList;
    Node newNode = {objectIdentifier,
                    name,
                    data,
                    dataType,
                    parentElement,
                    emptyChildList};
    
    std::list<Node *> & childList = parentElement -> m_childElementPointerList;
    if (childList.empty())
    {
        childList.push_back(&newNode); 
    }
    else
    {
        for (std::list<Node *>::iterator it = childList.begin(); it != childList.end(); it++)
        {
            int childObjectIdentifier = (*it) -> m_objectIdentifier;
            int newChildObjectIdentifier = newNode.m_objectIdentifier;
            if (newChildObjectIdentifier < childObjectIdentifier)
            {
                childList.insert(it, &newNode);
                break;
            }
            else if (childList.end() == it)
            {
                childList.push_back(&newNode);
                break;
            }
        }
    }
}

void Tree::initializeListOfDataTypes()
{
    m_listOfDataTypes.push_back("INTEGER");
    m_listOfDataTypes.push_back("OCTET STRING");
    m_listOfDataTypes.push_back("OBJECT IDENTIFIER");
    m_listOfDataTypes.push_back("NULL");
}

void Tree::initializeRootOfTheTree()
{
    addNode(1, "", "ISO", nullptr, nullptr);

    std::list <Node *> emptyChildList;
    Node newNode = {1,
                    "",
                    "ISO",
                    nullptr,
                    nullptr,
                    emptyChildList};
    m_rootOfTheTree = &newNode;
}

//Call this function with as such 'recursiveSearch(vector, 0, m_rootOfTheTree)' !!!
//This function should be called inside try catch block and if it returns nullptr it should throw exception!!!
Node * Tree::recursiveSearch(std::vector<int> vectorOfOID, unsigned int vectorPosition, Node * node)
{
    std::list<Node *> & childList = node -> m_childElementPointerList;
    for (std::list<Node *>::iterator it = childList.begin(); it != childList.end(); it++)
    {   
        if ((*it) -> m_objectIdentifier ==  vectorOfOID.at(vectorPosition) && vectorOfOID.size() - 1 == vectorPosition)
        {
            return (*it);        
        }
        else if ((*it) -> m_objectIdentifier ==  vectorOfOID.at(vectorPosition))
        {
            vectorPosition++;
            recursiveSearch(vectorOfOID, vectorPosition, (*it));
        }
    } 
    return nullptr;
}

Node * Tree::findNodeByObjectIdentifier(std::vector<int> vectorOfOID)
{
    try
    {
        Node * pNode = recursiveSearch(vectorOfOID, 0, m_rootOfTheTree);
        if (pNode == nullptr)
        {
            throw "Node not found";
        }
        else
        {
            return pNode;    
        }
    }
    catch(std::string exception)
    {
        std::cout << exception << std::endl;
        return nullptr;
    }
}

Node * Tree::findNodeByName(std::vector<int> vectorOfOID, std::string name)
{
    try
    {
        Node * pNode = recursiveSearch(vectorOfOID, 0, m_rootOfTheTree);
        if (pNode == nullptr)
        {
            throw "Node not found";
        }
        else
        {
            Node * pNode =findNodeByObjectIdentifier(vectorOfOID);
            std::list<Node *> & childList = pNode -> m_childElementPointerList;     
            if (pNode != nullptr)
            {
                for (std::list<Node *>::iterator it = childList.begin(); it != childList.end(); it++)
                {
                    if ((*it) -> m_name == name)
                    {
                        return (*it);
                    }
                }
                throw "Node not found";
            }
            else 
            {
                throw "Node not found";    
            }
        }
    }
    catch(std::string exception)
    {
        std::cout << exception << std::endl;
        return nullptr;
    }    
}



