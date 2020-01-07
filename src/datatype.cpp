#include "datatype.hpp"


DataType::DataType(BaseDataType baseType, EncodingComplexity complexity, EncodingType encodingType, DataVisibility visibility, unsigned int lengthLimit, unsigned int rangeLimit)
{
    m_baseType = baseType;
    m_complexity = complexity;
    m_encodingType = encodingType;
    m_visibility = visibility;
    m_lengthLimit = lengthLimit;
    m_rangeLimit = rangeLimit;
}

DataType::DataType()
{
    m_baseType = BaseDataType::NULL_D;
    m_complexity = EncodingComplexity::PRIMITIVE;
    m_encodingType = EncodingType::UNIVERSAL;
    m_visibility = DataVisibility::UNIVERSAL;
    m_lengthLimit = 0;     
    m_rangeLimit = 0;
}

DataType::~DataType()
{
    
}

