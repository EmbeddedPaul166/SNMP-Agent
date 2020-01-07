#include "coder.hpp"


Coder::Coder()
{
    
}

Coder::~Coder()
{
    
}

unsigned int Coder::encode(Node & node)
{
    unsigned int encoding = 0;
    DataType & dataType = node.m_dataType;
    if (dataType.m_baseType == BaseDataType::INTEGER)
    {
        encoding = encodeInteger(node);
    }
    else if (dataType.m_baseType == BaseDataType::OCTET_STRING)
    {
        encoding = encodeOctetString(node);
    }
    else if (dataType.m_baseType == BaseDataType::OBJECT_IDENTIFIER)
    {
        encoding = encodeObjectIdentifier(node);
    }
    else if (dataType.m_baseType == BaseDataType::NULL_D)
    {
        encoding = encodeNULL(node);
    }
    else if (dataType.m_baseType == BaseDataType::SEQUENCE_OF)
    {
        encoding = encodeSequence(node);
    }
    else if (dataType.m_baseType == BaseDataType::CHOICE)
    {
        encoding = encodeChoice(node);   
    }
    else
    {
        encoding = 0;
    }
    
    return encoding;
}


unsigned int Coder::encodeInteger(Node & node)
{
    return 0;
}
unsigned int Coder::encodeOctetString(Node & node)
{
    return 0;
}
unsigned int Coder::encodeObjectIdentifier(Node & node)
{
    return 0;
}
unsigned int Coder::encodeNULL(Node & node)
{
    return 0;
}
unsigned int Coder::encodeSequence(Node & node)
{
    return 0;
}
unsigned int Coder::encodeChoice(Node & node)
{
    return 0;
}


unsigned int Coder::encodeID(DataVisibility visibility, EncodingComplexity complexity)
{
    unsigned int encoding = 0;
    return encoding;
}


unsigned int Coder::encodeLength(unsigned int length)
{
    unsigned int encoding = 0;
    return encoding;
}
