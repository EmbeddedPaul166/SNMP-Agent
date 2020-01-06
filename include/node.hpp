#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <list>

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

enum class BaseDataType
{
    INTEGER,
    OCTET_STRING,
    OBJECT_IDENTIFIER,
    NULL_D,
    SEQUENCE,
    SEQUENCE_OF,
    CHOICE
};

enum class DataVisibility
{
    UNIVERSAL,
    APPLICATION,
    CONTEXT_SPECIFIC,
    PRIVATE
};

enum class EncodingComplexity
{
    PRIMITIVE,
    CONSTRUCTED
};

enum class NewDataType
{
    NO,
    UNIVERSAL,
    IMPLICIT,
    EXPLICIT
};

class Node
{
    public:
        Node(unsigned int objectIdentifier, std::string name, std::string dataType, NewDataType newDataType,
             BaseDataType baseType, EncodingComplexity complexity, DataVisibility visibility,
             unsigned int lengthLimit, std::string description, AccessType accessType, StatusType statusType,
             Node * pParentElement, std::list<Node *> childElementPointerList);
        Node();
        ~Node(); 
        
        unsigned int m_objectIdentifier;
        std::string m_name;
        std::string m_dataType;
        NewDataType m_newDataType;
        BaseDataType m_baseType;
        EncodingComplexity m_complexity;
        DataVisibility m_visibility;
        unsigned int m_lengthLimit;
        std::string m_description;
        AccessType m_accessType;
        StatusType m_statusType;
        Node * m_pParentElement;
        std::list<Node *> m_childElementPointerList;
    private:
        
    protected:
        
};

#endif /*NODE_HPP*/
