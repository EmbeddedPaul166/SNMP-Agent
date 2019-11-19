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
                   std::string description, Visibility visibility, EncodingType encodingType,
                   AccessType accessType, StatusType statusType, Node * parentElement)
{ 
    std::list <Node *> emptyChildList;
    emptyChildList.clear();
    Node newNode = {objectIdentifier,
                    name,
                    dataType,
                    description,
                    visibility,
                    encodingType,
                    accessType,
                    statusType,
                    parentElement,
                    emptyChildList};
    
    m_nodeVector.push_back(newNode);
    
    //std::list<Node *> & childList = parentElement -> m_childElementPointerList;
    if (parentElement -> m_childElementPointerList.empty())
    {
        parentElement -> m_childElementPointerList.push_back(&m_nodeVector.back()); 
    }
    else
    {
        for (std::list<Node *>::iterator it = parentElement -> m_childElementPointerList.begin(); it != parentElement -> m_childElementPointerList.end(); it++)
        {
            int childObjectIdentifier = (*it) -> m_objectIdentifier;
            int newChildObjectIdentifier = m_nodeVector.back().m_objectIdentifier;
            if (newChildObjectIdentifier < childObjectIdentifier)
            {
                parentElement -> m_childElementPointerList.insert(it, &m_nodeVector.back());
                break;
            }
            else if (parentElement -> m_childElementPointerList.end() == it)
            {
                parentElement -> m_childElementPointerList.push_back(&m_nodeVector.back());
                break;
            }
        }
    }
    Node * pNewNode = &m_nodeVector.back();
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
    Node newNode = {1,
                    "iso",
                    nullptr,
                    "",
                    Visibility::UNIVERSAL,
                    EncodingType::NONE,
                    AccessType::NOT_ACCESSIBLE,
                    StatusType::MANDATORY,
                    nullptr,
                    emptyChildList};
    m_rootOfTheTree = newNode;
    m_nodeVector.push_back(newNode);
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
        Node * pNode = recursiveSearch(vectorOfOID, 0, &m_rootOfTheTree);
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
        Node * pNode = recursiveSearch(vectorOfOID, 0, &m_rootOfTheTree);
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



