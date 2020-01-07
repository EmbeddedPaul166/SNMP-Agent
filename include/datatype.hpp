#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <vector>
#include <list>
#include <string>

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

enum class EncodingComplexity
{
    PRIMITIVE,
    CONSTRUCTED
};

enum class EncodingType
{
    UNIVERSAL,
    IMPLICIT,
    EXPLICIT
};

enum class DataVisibility
{
    UNIVERSAL,
    APPLICATION,
    CONTEXT_SPECIFIC,
    PRIVATE
};

class DataType
{
    public:
        DataType(BaseDataType baseType, EncodingComplexity complexity, EncodingType encodingType, DataVisibility visibility, unsigned int lengthLimit, unsigned int rangeLimit);
        DataType();
        ~DataType();
        
        BaseDataType m_baseType;
        EncodingComplexity m_complexity;
        EncodingType m_encodingType;
        DataVisibility m_visibility;
        unsigned int m_lengthLimit;
        unsigned int m_rangeLimit;
        std::vector<std::string> m_nodeNameList;
        
    private:
    protected:
 
};

#endif /*DATATYPE_HPP*/
