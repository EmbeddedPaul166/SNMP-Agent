#include <iostream>
#include <bitset>
#include <string>
#include <cstdlib>
#include "manager.hpp"
#include "datatype.hpp"

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
    
    std::vector<unsigned int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(6);
    vec.push_back(1);
    DataType dataType;
    dataType.m_baseType = BaseDataType::OBJECT_IDENTIFIER;
    dataType.m_complexity = EncodingComplexity::PRIMITIVE;
    dataType.m_visibility = DataVisibility::UNIVERSAL;
    std::vector<std::byte> encodedBytesVector = manager.getEncodedObjectIdentifier(dataType, vec);
    for (std::vector<std::byte>::size_type i = 0; i < encodedBytesVector.size(); i++)
    {
        std::bitset<8> x(std::to_integer<uint8_t>(encodedBytesVector[i]));
        std::cout << x << std::endl;
    }
    
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
