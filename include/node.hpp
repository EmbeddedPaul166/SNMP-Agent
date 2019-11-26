#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <list>

enum class Visibility
{
    UNIVERSAL,
    APPLICATION,
    CONTEXT_SPECIFIC,
    PRIVATE,
    NONE
};

enum class EncodingType
{
    IMPLICIT,
    EXPLICIT,
    NONE
};

enum class AccessType
{
    READ_ONLY,
    WRITE_ONLY,
    READ_WRITE,
    NOT_ACCESSIBLE,
    NONE
};

enum class StatusType
{
    MANDATORY,
    OPTIONAL,
    OBSOLETE,
    NONE
};

class Node
{
    public:
        Node(unsigned int objectIdentifier, std::string name, std::string * dataType,
             std::string description, Visibility visibility, EncodingType encodingType,
             AccessType accessType, StatusType statusType, Node * parentElement,
             std::list<Node *> childElementPointerList);
        Node();
        ~Node(); 
        
        unsigned int m_objectIdentifier;
        std::string m_name;
        std::string * m_dataType;
        std::string m_description;
        Visibility m_visibility;
        EncodingType m_encodingType;
        AccessType m_accessType;
        StatusType m_statusType;
        Node * m_pParentElement;
        std::list<Node *> m_childElementPointerList;
    private:
        
    protected:
        
};

#endif /*NODE_HPP*/
