#include "tree.hpp"

Tree::Tree()
{
    initializeListOfDataTypes();
    initializeRootOfTheTree();
}

Tree::~Tree()
{
    
}

Node * Tree::addNode(unsigned int objectIdentifier, std::string name, std::string * dataType,
                   std::string description, AccessType accessType, StatusType statusType,
                   Node * pParentElement)
{ 
    std::list <Node *> emptyChildList;
    emptyChildList.clear();
    Node newNode(objectIdentifier, name, dataType, description, accessType, statusType, pParentElement, emptyChildList);
    
    m_nodeList.push_back(newNode);
    
    if (pParentElement -> m_childElementPointerList.empty())
    {
        pParentElement -> m_childElementPointerList.push_back(&m_nodeList.back()); 
    }
    else
    {
        for (std::list<Node *>::iterator it = pParentElement -> m_childElementPointerList.begin(); it != pParentElement -> m_childElementPointerList.end(); it++)
        {
            int childObjectIdentifier = (*it) -> m_objectIdentifier;
            int newChildObjectIdentifier = m_nodeList.back().m_objectIdentifier;
            if (newChildObjectIdentifier < childObjectIdentifier)
            {
                pParentElement -> m_childElementPointerList.insert(it, &m_nodeList.back());
                break;
            }
            else if (pParentElement -> m_childElementPointerList.back() == (*it))
            {
                pParentElement -> m_childElementPointerList.push_back(&m_nodeList.back());
                break;
            }
        }
    }
    Node * pNewNode = &m_nodeList.back();
    return pNewNode;
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
    std::list <Node *> emptyChildList;
    Node newNode(1, "iso", nullptr, "", AccessType::NOT_ACCESSIBLE, StatusType::MANDATORY, nullptr, emptyChildList);
    m_nodeList.push_back(newNode);
    m_rootOfTheTree = &m_nodeList.back();
}

//Call this function with as such 'recursiveSearch(vector, 0, m_rootOfTheTree)' !!!
//This function should be called inside try catch block and if it returns nullptr it should throw exception!!!
Node * Tree::recursiveSearch(std::vector<unsigned int> vectorOfOID, unsigned int vectorPosition, Node * node)
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

Node * Tree::findNodeByObjectIdentifier(std::vector<unsigned int> vectorOfOID)
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

Node * Tree::findNodeByName(std::vector<unsigned int> vectorOfOID, std::string name)
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


