#include <iostream>
#include <bitset>
#include <string>
#include <cstdlib>
#include "manager.hpp"
#include "datatype.hpp"

void encodeASequence(Manager & manager)
{
    std::vector<std::byte> beginVector;
    std::vector<std::byte> endVector;
    int lengthInBytes = 0;
    
    DataType dataType;
    dataType.m_baseType = BaseDataType::SEQUENCE_OF;
    dataType.m_complexity = EncodingComplexity::CONSTRUCTED;
    dataType.m_visibility = DataVisibility::UNIVERSAL;
    manager.startASequence(dataType, beginVector);
    
    int x = 5;
    dataType.m_baseType = BaseDataType::INTEGER;
    dataType.m_complexity = EncodingComplexity::PRIMITIVE;
    manager.addInteger(dataType, x, lengthInBytes, endVector);
    
    std::string y = "kupa";
    dataType.m_baseType = BaseDataType::OCTET_STRING;
    manager.addOctetString(dataType, y, lengthInBytes, endVector);
    
    std::vector<unsigned int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(6); 
    dataType.m_baseType = BaseDataType::OBJECT_IDENTIFIER;
    manager.addObjectIdentifier(dataType, vec, lengthInBytes, endVector);

    bool z = true;
    dataType.m_baseType = BaseDataType::BOOLEAN;
    manager.addBoolean(dataType, z, lengthInBytes, endVector);
    
    dataType.m_baseType = BaseDataType::NULL_D;
    manager.addNULL(dataType, lengthInBytes, endVector);
    
    manager.endASequence(lengthInBytes, beginVector);
    manager.getEncodedSequence(beginVector, endVector);
    
    for (std::vector<std::byte>::size_type i = 0; i < beginVector.size(); i++)
    {
        std::bitset<8> x(std::to_integer<uint8_t>(beginVector[i]));
        std::cout << x << std::endl;
    }
    
}

void encodeASequenceInsideASequence(Manager & manager)
{
    std::vector<std::byte> beginVector;
    std::vector<std::byte> endVector;
    int lengthInBytes = 0;
    
    DataType dataType;
    dataType.m_baseType = BaseDataType::SEQUENCE_OF;
    dataType.m_complexity = EncodingComplexity::CONSTRUCTED;
    dataType.m_visibility = DataVisibility::UNIVERSAL;
    manager.startASequence(dataType, beginVector);
    
    int x = 5;
    dataType.m_baseType = BaseDataType::INTEGER;
    dataType.m_complexity = EncodingComplexity::PRIMITIVE;
    manager.addInteger(dataType, x, lengthInBytes, endVector);
    
    std::string y = "kupa";
    dataType.m_baseType = BaseDataType::OCTET_STRING;
    manager.addOctetString(dataType, y, lengthInBytes, endVector);
    
    std::vector<std::byte> beginVector2;
    std::vector<std::byte> endVector2;
    int lengthInBytes2 = 0;
    
    dataType.m_baseType = BaseDataType::SEQUENCE_OF;
    dataType.m_complexity = EncodingComplexity::CONSTRUCTED;
    dataType.m_visibility = DataVisibility::UNIVERSAL;
    manager.startASequence(dataType, beginVector2);
    
    int l = 5;
    dataType.m_baseType = BaseDataType::INTEGER;
    dataType.m_complexity = EncodingComplexity::PRIMITIVE;
    manager.addInteger(dataType, l, lengthInBytes2, endVector2);
    
    int k = 10;
    dataType.m_baseType = BaseDataType::INTEGER;
    dataType.m_complexity = EncodingComplexity::PRIMITIVE;
    manager.addInteger(dataType, k, lengthInBytes2, endVector2);
    
    manager.endSubSequence(lengthInBytes, lengthInBytes2, beginVector2);
    manager.getEncodedSubSequence(beginVector2, endVector2, endVector);
    
    int j = 5;
    dataType.m_baseType = BaseDataType::INTEGER;
    dataType.m_complexity = EncodingComplexity::PRIMITIVE;
    manager.addInteger(dataType, j, lengthInBytes, endVector);

    manager.endASequence(lengthInBytes, beginVector);
    manager.getEncodedSequence(beginVector, endVector);
    
    for (std::vector<std::byte>::size_type i = 0; i < beginVector.size(); i++)
    {
        std::bitset<8> x(std::to_integer<uint8_t>(beginVector[i]));
        std::cout << x << std::endl;
    }
    
}

int main() 
{
    char * pPath =  getenv("PROJECT_PATH");
    if (pPath == nullptr)
    {
        std::cout << "Error: Source set-env file first" << std::endl;
        return 0;
    }
    std::string filePath(pPath);
    filePath += "/mibs/RFC1213-MIB.txt";
    Manager manager;
    manager.parse(filePath);
    encodeASequenceInsideASequence(manager);
    
    while (1)
    {
        std::string input;
        std::cout << std::endl;
        std::cout << "Input OID string:" << std::endl;
        std::cin >> input;
        std::cout << std::endl;
        if (std::cin.fail())
        {
            std::cout << "Bad input!" << std::endl;
            continue;
        }
        else
        {
            manager.getNodeByOID(input);
        }
    }
    return 0;
}
