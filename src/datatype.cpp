#include "datatype.hpp"


DataType::DataType(BaseDataType baseType, EncodingComplexity complexity, EncodingType encodingType, DataVisibility visibility, unsigned int lengthLimit, unsigned int rangeLimitLower, unsigned int rangeLimitUpper)
{
    m_baseType = baseType;
    m_complexity = complexity;
    m_encodingType = encodingType;
    m_visibility = visibility;
    m_lengthLimit = lengthLimit;
    m_rangeLimitLower = rangeLimitLower;
    m_rangeLimitUpper = rangeLimitUpper;
    m_tag = 0;
}

DataType::DataType()
{
    m_baseType = BaseDataType::NULL_D;
    m_complexity = EncodingComplexity::PRIMITIVE;
    m_encodingType = EncodingType::UNIVERSAL;
    m_visibility = DataVisibility::UNIVERSAL;
    m_lengthLimit = 0;     
    m_rangeLimitLower = 0;
    m_rangeLimitUpper = 0;
    m_tag = 0;
}

DataType::~DataType()
{
    
}

