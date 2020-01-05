#include "manager.hpp"

Manager::Manager()
{
    m_pParser = std::make_unique<Parser>();
    m_pFileHandler = std::make_unique<FileHandler>();
}

Manager::~Manager()
{
    
}

void Manager::parse(std::string filePath)
{
    std::string fileContent = m_pFileHandler -> readFile(filePath);
    std::string importPath = m_pParser -> isImportPresent(fileContent);
    if (importPath != "")
    {
        std::string importContent = m_pFileHandler -> readFile(importPath);
        m_pParser -> parseMIBImportFile(importContent);
    }
    m_pParser -> parseMIBFile(fileContent);
}


std::vector<unsigned int> Manager::getOIDVector(std::string & input)
{
    unsigned int n = 0;
    std::vector<unsigned int> numbersVector;
    std::vector<unsigned int> digitsVector;
    while(input.size() != n)
    {
        if (std::isdigit(input[n]))
        {
            digitsVector.push_back(input[n] - '0');
        }
        else if (input[n] == '.')
        {
            if (digitsVector.size() == 1)
            {
                numbersVector.push_back(digitsVector.back());
                digitsVector.clear();
            }
            else
            {
                unsigned int multiplier = static_cast<unsigned int>(std::pow(10, digitsVector.size() - 1));
                unsigned int number = 0;
                for (std::vector<std::string>::size_type i = 0; i != digitsVector.size(); i++)
                {
                    number += digitsVector[i]*multiplier;
                    multiplier /= 10;
                }
                numbersVector.push_back(number);
                digitsVector.clear(); 
            }
        }
        n++;
    }
    return numbersVector;
}

void Manager::getNodeByOID(std::string & input)
{
    std::vector<unsigned int> vectorOfOID = getOIDVector(input);
    bool isNodeFound;
    unsigned int OID;
    std::string name;
    std::string dataType;
    std::string description;
    std::string accessType;
    std::string statusType;
    m_pParser -> getNodeByOID(vectorOfOID,
                              isNodeFound,
                              OID,
                              name,
                              dataType,
                              description,
                              accessType,
                              statusType);
    if (isNodeFound)
    {
        std::cout << "OID: " << OID << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Data type: " << dataType << std::endl;
        std::cout << "Description: " << description << std::endl;
        std::cout << "Access type: " << accessType << std::endl;
        std::cout << "Status type: " << statusType << std::endl; 
    }
    else
    {
        std::cout << "Node not found! Try different OID string." << std::endl;
    }
}

