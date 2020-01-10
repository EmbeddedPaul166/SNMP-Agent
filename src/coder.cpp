#include "coder.hpp"


Coder::Coder()
{
    
}

Coder::~Coder()
{
    
}

std::vector<std::byte> Coder::encodeInteger(DataType & dataType, int & data)
{
    std::vector<std::byte> dataVector;
    dataVector.push_back(encodeID(dataType));
    int length = 0;
    std::vector<std::byte> dataInBytes = splitIntoBytes(data, length);
    std::vector<std::byte> lengthInBytes = encodeLength(length);
    dataVector.insert(dataVector.end(), lengthInBytes.begin(), lengthInBytes.end());
    dataVector.insert(dataVector.end(), dataInBytes.begin(), dataInBytes.end());
    return dataVector;
}

std::vector<std::byte> Coder::encodeOctetString(DataType & dataType, std::string & data)
{
    std::vector<std::byte> dataVector;
    dataVector.push_back(encodeID(dataType));
    int length = data.size();
    std::vector<std::byte> lengthInBytes = encodeLength(length);
    std::vector<std::byte> dataInBytes = splitIntoBytes(data);
    dataVector.insert(dataVector.end(), lengthInBytes.begin(), lengthInBytes.end());
    dataVector.insert(dataVector.end(), dataInBytes.begin(), dataInBytes.end());
    return dataVector;
}

std::vector<std::byte> Coder::encodeObjectIdentifier(DataType & dataType, std::vector<unsigned int> & data)
{
    std::vector<std::byte> dataVector;
    dataVector.push_back(encodeID(dataType));
    int length = data.size() - 1;
    std::vector<std::byte> lengthInBytes = encodeLength(length);
    dataVector.insert(dataVector.end(), lengthInBytes.begin(), lengthInBytes.end());
    if (data.size() > 2)
    {
        uint8_t firstElement = 40*data[0] + data[1];
        firstElement |= (1 << 7);
        dataVector.push_back(static_cast<std::byte>(firstElement));
        for (std::vector<unsigned int>::size_type i = 2; i < data.size(); i++)
        {
            if (i == data.size() - 1)
            {
                uint8_t element = data[i];
                element &= ~(1 << 7);
                dataVector.push_back(static_cast<std::byte>(element));
            }
            else
            {
                uint8_t element = data[i];
                element |= (1 << 7);
                dataVector.push_back(static_cast<std::byte>(element));
            }
        }
    }
    else if (data.size() == 2)
    {
        uint8_t firstElement = 40*data[0] + data[1];
        firstElement &= ~(1 << 7);
        dataVector.push_back(static_cast<std::byte>(firstElement));
    }
    else
    {
        dataVector.push_back(static_cast<std::byte>(0));
    }
    return dataVector;
}

std::vector<std::byte> Coder::encodeBoolean(DataType & dataType, bool & data)
{
    std::vector<std::byte> dataVector;
    dataVector.push_back(encodeID(dataType));
    dataVector.push_back(static_cast<std::byte>(1));
    if (data)
    {
        dataVector.push_back(static_cast<std::byte>(0xFF)); 
    }
    else
    {
        dataVector.push_back(static_cast<std::byte>(0x00)); 
    }
    return dataVector;
    
}

std::vector<std::byte> Coder::encodeNULL(DataType & dataType)
{
    std::vector<std::byte> dataVector;
    dataVector.push_back(encodeID(dataType));
    dataVector.push_back(static_cast<std::byte>(0));
    return dataVector;
}

//TODO: Encode sequences, but first check if primitive types are working correctly
std::vector<std::byte> Coder::encodeSequence(std::vector<DataType> & dataTypeVector)
{
    std::vector<std::byte> dataVector;
    return dataVector;
}

std::byte Coder::encodeID(DataType & dataType)
{
    std::byte encoding = static_cast<std::byte>(0);
    
    std::byte visibilityApplicationMask = static_cast<std::byte>(0x40);
    std::byte visibilityContextSpecificMask = static_cast<std::byte>(0x80);
    std::byte visibilityPrivateMask = static_cast<std::byte>(0xC0);
    
    std::byte complexityConstructedMask = static_cast<std::byte>(0x20);
    
    std::byte tagIntegerMask = static_cast<std::byte>(0x02);
    std::byte tagOctetStringMask = static_cast<std::byte>(0x04);
    std::byte tagObjectIdentifierMask = static_cast<std::byte>(0x06);
    std::byte tagBooleanMask = static_cast<std::byte>(0x01);
    std::byte tagNullMask = static_cast<std::byte>(0x05);
    std::byte tagSequenceOfMask = static_cast<std::byte>(0x10);
    
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
    else if (dataType.m_baseType == BaseDataType::BOOLEAN)
    {
        encoding |= tagBooleanMask;
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

std::vector<std::byte> Coder::splitIntoBytes(int & number, int & numberOfBytes)
{
    std::vector<std::byte> vectorOfBytes;
    if (number != 0)
    {
       numberOfBytes = getNumberOfBytes(number);
       for (int i = numberOfBytes - 1; i >= 0; i--) 
        {
           vectorOfBytes.push_back(static_cast<std::byte>(((number >> i * 8) & 0xFF))); 
        }
    }
    else
    {
        vectorOfBytes.push_back(static_cast<std::byte>(0));
    }
    
    return vectorOfBytes;
}

std::vector<std::byte> Coder::splitIntoBytes(int & number)
{
    std::vector<std::byte> vectorOfBytes;
    if (number != 0)
    {
        int numberOfBytes = getNumberOfBytes(number);
        for (int i = numberOfBytes - 1; i >= 0; i--)
        {
           vectorOfBytes.push_back(static_cast<std::byte>(((number >> i * 8) & 0xFF))); 
        }
    }
    else
    {
        vectorOfBytes.push_back(static_cast<std::byte>(0));
    }
    
    return vectorOfBytes;
}

std::vector<std::byte> Coder::splitIntoBytes(std::string & string)
{
    std::vector<std::byte> vectorOfBytes;
    for(std::string::size_type i = 0; i < string.size(); i++)
    {
        vectorOfBytes.push_back(static_cast<std::byte>(string[i]));
    }
    
    return vectorOfBytes;
}

std::vector<std::byte> Coder::encodeLength(int & lengthInBytes)
{
    std::vector<std::byte> vectorOfBytes;
    
    int numberOfSeptets = 0;
    if (lengthInBytes != 0)
    {
        int len = lengthInBytes;
        while (len != 0)
        {
            len >>= 7;
            numberOfSeptets++;
        }  
        
        for (int i = 0; i < numberOfSeptets; i++)
        {
            if (i == numberOfSeptets - 1)
            {
                int8_t num = lengthInBytes >> (i * 7);
                num &= ~(1 << 7);
                vectorOfBytes.push_back(static_cast<std::byte>(num));
                
            }
            else
            {
                int8_t num = lengthInBytes >> (i * 7);
                num |= (1 << 7);
                vectorOfBytes.push_back(static_cast<std::byte>(num));
            }
        }
    }
    else
    {
        vectorOfBytes.push_back(static_cast<std::byte>(0));
    }
    
    return vectorOfBytes;
}

int Coder::getNumberOfBytes(int number)
{
    return sizeof(int); 
}
