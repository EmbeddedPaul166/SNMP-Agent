#include "validator.hpp"

Validator::Validator()
{
    
}

Validator::~Validator()
{
    
}

//Used for NULL, Boolean and sequence_of
bool Validator::validate(DataType & dataType, DataType & nodeType)
{
    if (dataType.m_baseType == nodeType.m_baseType)
    {
        if (dataType.m_baseType == BaseDataType::SEQUENCE_OF)
        {
            //sequence elements check
            return true;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

//Used for integer
bool Validator::validate(DataType & dataType, DataType & nodeType, int & data)
{
    if (dataType.m_baseType == nodeType.m_baseType)
    {
        if (nodeType.m_rangeLimitLower != 0 || nodeType.m_rangeLimitUpper != 0)
        {
            if (data > nodeType.m_rangeLimitLower && data < nodeType.m_rangeLimitUpper)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

//Used for octet string
bool Validator::validate(DataType & dataType, DataType & nodeType, std::string & data)
{
    if (dataType.m_baseType == nodeType.m_baseType)
    {
        if (nodeType.m_lengthLimit != 0)
        {
            if (static_cast<int>(data.size()) < nodeType.m_lengthLimit)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

