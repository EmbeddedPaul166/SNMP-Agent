#include "coder.hpp"


Coder::Coder()
{
    
}

Coder::~Coder()
{
    
}

std::vector<int8_t> Coder::encodeInteger(DataType & dataType, int & data)
{
    std::vector<int8_t> dataVector;
    return dataVector;
}

std::vector<int8_t> Coder::encodeOctetString(DataType & dataType, std::string & data)
{
    std::vector<int8_t> dataVector;
    return dataVector;
}

std::vector<int8_t> Coder::encodeObjectIdentifier(DataType & dataType, std::vector<unsigned int> & data)
{
    std::vector<int8_t> dataVector;
    return dataVector;
}

std::vector<int8_t> Coder::encodeNULL(DataType & dataType)
{
    std::vector<int8_t> dataVector;
    return dataVector;
}

std::vector<int8_t> Coder::encodeSequence(std::vector<DataType> & dataTypeVector)
{
    std::vector<int8_t> dataVector;
    return dataVector;
}

int8_t Coder::encodeID(DataType & dataType)
{
    int8_t encoding = 0;
    
    uint8_t visibilityApplicationMask = 0x40;
    uint8_t visibilityContextSpecificMask = 0x80;
    uint8_t visibilityPrivateMask = 0xC0;
    
    uint8_t complexityConstructedMask = 0x20;
    
    uint8_t tagIntegerMask = 0x02;
    uint8_t tagOctetStringMask = 0x04;
    uint8_t tagObjectIdentifierMask = 0x06;
    uint8_t tagNullMask = 0x10;
    uint8_t tagSequenceOfMask = 0x05;
    
    if (dataType.m_visibility == DataVisibility::APPLICATION)
    {
        encoding |= visibilityApplicationMask;    
    }
    else if (dataType.m_visibility == DataVisibility::CONTEXT_SPECIFIC)
    {
        encoding |= visibilityContextSpecificMask;
    }
    else if (dataType.m_visibility == DataVisibility::PRIVATE)
    {
        encoding |= visibilityPrivateMask;
    }
    
    if (dataType.m_complexity == EncodingComplexity::CONSTRUCTED)
    {
        encoding |= complexityConstructedMask;      
    }
    
    if (dataType.m_baseType == BaseDataType::INTEGER)
    {
        encoding |= tagIntegerMask;
    }
    else if (dataType.m_baseType == BaseDataType::OCTET_STRING)
    {
        encoding |= tagOctetStringMask;
    }
    else if (dataType.m_baseType == BaseDataType::OBJECT_IDENTIFIER)
    {
        encoding |= tagObjectIdentifierMask;
    }
    else if (dataType.m_baseType == BaseDataType::NULL_D)
    {
        encoding |= tagNullMask;
    }
    else if (dataType.m_baseType == BaseDataType::SEQUENCE_OF)
    {
        encoding |= tagSequenceOfMask;
    }
    
    return encoding;
}

std::vector<int8_t> Coder::splitIntoBytes(int & number, int & numberOfBytes)
{
    std::vector<int8_t> vectorOfBytes;
    if (number != 0)
    {
        for (int i = 0; i < numberOfBytes; i++)
        {
            vectorOfBytes.push_back(number >> (i * 8));
            bool completeByteFlag = vectorOfBytes[i] & (1 << 7);
            if (completeByteFlag && i == numberOfBytes - 1)
            {
                vectorOfBytes.push_back(0);
            }
        }
    }
    else if (number == 0)
    {
        vectorOfBytes.push_back(0);
        numberOfBytes = 1;
    }
    else
    {
        for (int i = 0; i < numberOfBytes; i++)
        {
            vectorOfBytes.push_back(number >> (i * 8));
        }
    }
    
    return vectorOfBytes;
}

std::vector<int8_t> Coder::splitIntoBytes(int & number)
{
    int numberOfBytes = 0;
    std::vector<int8_t> vectorOfBytes;
    if (number != 0)
    {
        while (number > 0)
        {
            number >>= 8;
            numberOfBytes++;
        }  
        
        for (int i = 0; i < numberOfBytes; i++)
        {
            vectorOfBytes.push_back(number >> (i * 8));
            bool completeByteFlag = vectorOfBytes[i] & (1 << 7);
            if (completeByteFlag && i == numberOfBytes - 1)
            {
                vectorOfBytes.push_back(0);
            }
        }
    }
    else if (number == 0)
    {
        vectorOfBytes.push_back(0);
        numberOfBytes = 1;
    }
    else
    {
        while (number > 0)
        {
            number >>= 8;
            numberOfBytes++;
        }  
        
        std::vector<int8_t> vectorOfBytes(numberOfBytes);
        for (int i = 0; i < numberOfBytes; i++)
        {
            vectorOfBytes.push_back(number >> (i * 8));
        }
    }
    
    return vectorOfBytes;
}

std::vector<int8_t> Coder::encodeLength(int & lengthInBytes)
{
    std::vector<int8_t> vectorOfBytes;
    
    int numberOfSeptets = 0;
    if (lengthInBytes != 0)
    {
        while (lengthInBytes > 0)
        {
            lengthInBytes >>= 7;
            numberOfSeptets++;
        }  
        
        for (int i = 0; i < numberOfSeptets; i++)
        {
            if (i == numberOfSeptets - 1)
            {
                uint8_t num = lengthInBytes >> (i * 7);
                num |= (1 << 8);
                vectorOfBytes.push_back(num);
                
            }
            else
            {
                uint8_t num = lengthInBytes >> (i * 7);
                num &= ~(1 << 8);
                vectorOfBytes.push_back(num);
            }
        }
    }
    else if (lengthInBytes == 0)
    {
        vectorOfBytes.push_back(0);
    }
    
    return vectorOfBytes;
}
