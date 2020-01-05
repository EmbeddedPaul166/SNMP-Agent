#include "node.hpp"

Node::Node(unsigned int objectIdentifier, std::string name, std::string dataType,
           std::string description, AccessType accessType, StatusType statusType, Node * pParentElement,
           std::list<Node *> childElementPointerList)
{
    m_objectIdentifier = objectIdentifier;
    m_name = name;
    m_dataType = dataType;
    m_description = description;
    m_accessType = accessType;
    m_statusType = statusType;
    m_pParentElement = pParentElement;
    m_childElementPointerList = childElementPointerList;
}

Node::Node()
{
    
}

Node::~Node()
{
    
}
