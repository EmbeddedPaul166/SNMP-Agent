#include "node.hpp"

Node::Node(unsigned int objectIdentifier, std::string name, std::string dataType, NewDataType newDataType,
           BaseDataType baseType, EncodingComplexity complexity, DataVisibility visibility,
           unsigned int lengthLimit,std::string description, AccessType accessType, StatusType statusType,
           Node * pParentElement, std::list<Node *> childElementPointerList)
{
    m_objectIdentifier = objectIdentifier;
    m_name = name;
    m_dataType = dataType;
    m_newDataType = newDataType;
    m_baseType = baseType;
    m_complexity = complexity;
    m_visibility = visibility;
    m_lengthLimit = lengthLimit;
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
