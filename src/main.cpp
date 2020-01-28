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
    
    //Validate sequence
    std::string nodeName = "ifTable";
    Node * pNode = manager.getNodeByName(nodeName);
    std::vector<std::string> nodeNameVector;
    
    if (manager.validate(dataType, pNode -> m_dataType, nodeNameVector))
    {
        std::cout << "Ok sequence " <<  nodeName <<std::endl;
        
    }
    else
    {
        std::cout << "Not ok sequence " <<  nodeName <<std::endl;
    }
    
    manager.startASequence(dataType, beginVector);
    
    //Validate integer element
    dataType.m_baseType = BaseDataType::INTEGER;
    dataType.m_complexity = EncodingComplexity::PRIMITIVE;
    nodeName = "ifType"; 
    bool isFound = false;
    int x = 5;
    pNode = manager.getNodeByName(nodeName);
    
    for (std::vector<std::string>::size_type i = nodeNameVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
    {
        if (nodeNameVector[i] == pNode -> m_name)
        {
            isFound = true;
            break;
        }
    }
    
    if (isFound)
    {
        if (manager.validate(dataType, pNode -> m_dataType, x))
        {
            std::cout << "OK integer " <<  nodeName <<std::endl;
        }
        else
        {
            std::cout << "Not ok integer " <<  nodeName <<std::endl;
        }
    }
    else 
    {
        std::cout << "Not ok integer " <<  nodeName <<std::endl;
    }
    
    manager.addInteger(dataType, x, lengthInBytes, endVector);
    
    //Validate octet string element
    dataType.m_baseType = BaseDataType::OCTET_STRING;
    nodeName = "ifPhysAddress";  
    isFound = false;
    std::string y = "heh";
    pNode = manager.getNodeByName(nodeName);
    
    for (std::vector<std::string>::size_type i = nodeNameVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
    {
        if (nodeNameVector[i] == pNode -> m_name)
        {
            isFound = true;
            break;
        }
    }
    
    if (isFound)
    {
        if (manager.validate(dataType, pNode -> m_dataType, y))
        {
            std::cout << "OK octet string " <<  nodeName <<std::endl;
        }
        else
        {
            std::cout << "Not ok octet string " <<  nodeName <<std::endl;
        }
    }
    else 
    {
        std::cout << "Not ok octet string " <<  nodeName <<std::endl;
    }
    
    manager.addOctetString(dataType, y, lengthInBytes, endVector);
    
    //Validate oid element
    dataType.m_baseType = BaseDataType::OBJECT_IDENTIFIER;
    nodeName = "ifLastChange";  
    isFound = false;
    std::vector<unsigned int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(6); 
    pNode = manager.getNodeByName(nodeName);
    
    for (std::vector<std::string>::size_type i = nodeNameVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
    {
        if (nodeNameVector[i] == pNode -> m_name)
        {
            isFound = true;
            break;
        }
    }
    
    if (isFound)
    {
        if (manager.validate(dataType, pNode -> m_dataType))
        {
            std::cout << "OK oid " <<  nodeName <<std::endl;
        }
        else
        {
            std::cout << "Not ok oid " <<  nodeName <<std::endl;
        }
    }
    else 
    {
        std::cout << "Not ok oid " <<  nodeName <<std::endl;
    } 
    
    manager.addObjectIdentifier(dataType, vec, lengthInBytes, endVector);

    //Validate bool element
    dataType.m_baseType = BaseDataType::BOOLEAN;
    nodeName = "ifOutDiscards";  
    isFound = false;
    bool z = true;
    pNode = manager.getNodeByName(nodeName);
    
    for (std::vector<std::string>::size_type i = nodeNameVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
    {
        if (nodeNameVector[i] == pNode -> m_name)
        {
            isFound = true;
            break;
        }
    }
    
    if (isFound)
    {
        if (manager.validate(dataType, pNode -> m_dataType))
        {
            std::cout << "OK boolean " <<  nodeName <<std::endl;
        }
        else
        {
            std::cout << "Not ok boolean " <<  nodeName <<std::endl;
        }
    }
    else 
    {
        std::cout << "Not ok boolean " <<  nodeName <<std::endl;
    } 
    
    manager.addBoolean(dataType, z, lengthInBytes, endVector);
    
    //Validate NULL element 
    dataType.m_baseType = BaseDataType::NULL_D;
    nodeName = "ifOutDiscards";  
    isFound = false;
    pNode = manager.getNodeByName(nodeName);
    
    for (std::vector<std::string>::size_type i = nodeNameVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
    {
        if (nodeNameVector[i] == pNode -> m_name)
        {
            isFound = true;
            break;
        }
    }
    
    if (isFound)
    {
        if (manager.validate(dataType, pNode -> m_dataType))
        {
            std::cout << "OK null " <<  nodeName <<std::endl;
        }
        else
        {
            std::cout << "Not ok null " <<  nodeName <<std::endl;
        }
    }
    else 
    {
        std::cout << "Not ok null " <<  nodeName <<std::endl;
    } 
    
    manager.addNULL(dataType, lengthInBytes, endVector);
    
    manager.endASequence(lengthInBytes, beginVector);
    manager.getEncodedSequence(beginVector, endVector);
    
    
    //Print sequence elements
    for (std::vector<std::byte>::size_type i = 0; i < beginVector.size(); i++)
    {
        std::bitset<8> x(std::to_integer<uint8_t>(beginVector[i]));
        std::cout << x << std::endl;
    } 
    
    std::cout << std::endl;
    std::cout << std::endl;
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
    
    std::cout << std::endl;
    std::cout << std::endl;
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
    encodeASequence(manager);
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
