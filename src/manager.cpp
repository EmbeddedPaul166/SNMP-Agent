#include "manager.hpp"

Manager::Manager()
{
    m_pParser = std::make_unique<Parser>();
    m_pFileHandler = std::make_unique<FileHandler>();
    m_pCoder = std::make_unique<Coder>();
    m_pValidator = std::make_unique<Validator>();
    m_pTree = std::make_unique<Tree>();
}

Manager::~Manager()
{
    
}


bool Manager::validate(DataType & dataType, DataType & nodeType, std::vector<std::string> & nodeNameVector)
{
    if (dataType.m_baseType == BaseDataType::SEQUENCE_OF)
    {
        nodeNameVector = nodeType.m_nodeNameList; 
        if (nodeNameVector.size() == 1)
        {
            for (std::vector<std::string>::size_type i = m_pParser -> m_customDataTypeVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
            {
                if (m_pParser -> m_customDataTypeNameVector[i] == nodeNameVector[0])
                {
                    DataType type = m_pParser -> m_customDataTypeVector[i];
                    nodeNameVector = type.m_nodeNameList;
                }
            }
        }
    }
    return m_pValidator -> validate(dataType, nodeType); 
}

bool Manager::validate(DataType & dataType, DataType & nodeType)
{
    return m_pValidator -> validate(dataType, nodeType);
}

bool Manager::validate(DataType & dataType, DataType & nodeType, int & data)
{
    return m_pValidator -> validate(dataType, nodeType, data);
}

bool Manager::validate(DataType & dataType, DataType & nodeType, std::string & data)
{
    return m_pValidator -> validate(dataType, nodeType, data);
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
    std::string baseType;
    std::string complexity;
    std::string encodingType;
    std::string visibility;
    int lengthLimit;
    int rangeLimitLower;
    int rangeLimitUpper;
    std::string description;
    std::string accessType;
    std::string statusType;
    m_pParser -> getNodeByOID(vectorOfOID,
                              isNodeFound,
                              OID,
                              name,
                              baseType,
                              complexity,
                              encodingType,
                              visibility,
                              lengthLimit,
                              rangeLimitLower,
                              rangeLimitUpper,
                              description,
                              accessType,
                              statusType);
    if (isNodeFound)
    {
        std::cout << "OID: " << OID << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Base type: " << baseType << std::endl;
        std::cout << "Encoding complexity: " << complexity << std::endl;
        std::cout << "Encoding type: " << encodingType << std::endl;
        std::cout << "Visibility: " << visibility << std::endl;
        std::cout << "Length limit: " << lengthLimit << std::endl;
        std::cout << "Range limit: " << rangeLimitUpper << std::endl;
        std::cout << "Description: " << description << std::endl;
        std::cout << "Access type: " << accessType << std::endl;
        std::cout << "Status type: " << statusType << std::endl; 
    }
    else
    {
        std::cout << "Node not found! Try different OID string." << std::endl;
    }
}

Node * Manager::getNodeByName(std::string & input)
{
    return m_pParser -> getNodeByName(input);
}

std::vector<std::byte> Manager::getEncodedInteger(DataType & dataType, int & data)
{
    std::vector<std::byte> encodedBytesVector = m_pCoder -> encodeInteger(dataType, data);
    return encodedBytesVector;
}

std::vector<std::byte> Manager::getEncodedOctetString(DataType & dataType, std::string & data)
{
    std::vector<std::byte> encodedBytesVector = m_pCoder -> encodeOctetString(dataType, data);
    return encodedBytesVector;
}

std::vector<std::byte> Manager::getEncodedObjectIdentifier(DataType & dataType, std::vector<unsigned int> & data)
{
    std::vector<std::byte> encodedBytesVector = m_pCoder -> encodeObjectIdentifier(dataType, data);
    return encodedBytesVector;
}

std::vector<std::byte> Manager::getEncodedBoolean(DataType & dataType, bool & data)
{
    std::vector<std::byte> encodedBytesVector = m_pCoder -> encodeBoolean(dataType, data);
    return encodedBytesVector;
}

std::vector<std::byte> Manager::getEncodedNULL(DataType & dataType)
{
    std::vector<std::byte> encodedBytesVector = m_pCoder -> encodeNULL(dataType);
    return encodedBytesVector;
}

//Call startASequence, then addStuffTo it including startASequence, you will need beginVector and endVector
//For every startASequence you need to call endASequence

void Manager::startASequence(DataType & dataType, std::vector<std::byte> & dataVector)
{
   m_pCoder -> startASequence(dataType, dataVector); 
}

void Manager::addInteger(DataType & dataType, int & data, int & lengthInBytes, std::vector<std::byte> & dataVector)
{
    m_pCoder -> addInteger(dataType, data, lengthInBytes, dataVector);
}

void Manager::addOctetString(DataType & dataType, std::string & data, int & lengthInBytes, std::vector<std::byte> & dataVector)
{
    m_pCoder -> addOctetString(dataType, data, lengthInBytes, dataVector);
}

void Manager::addObjectIdentifier(DataType & dataType, std::vector<unsigned int> & data, int & lengthInBytes, std::vector<std::byte> & dataVector)
{
    m_pCoder -> addObjectIdentifier(dataType, data, lengthInBytes, dataVector);
}

void Manager::addBoolean(DataType & dataType, bool & data, int & lengthInBytes, std::vector<std::byte> & dataVector)
{
    m_pCoder -> addBoolean(dataType, data, lengthInBytes, dataVector);
}

void Manager::addNULL(DataType & dataType, int & lengthInBytes, std::vector<std::byte> & dataVector)
{
    m_pCoder -> addNULL(dataType, lengthInBytes, dataVector);
}

void Manager::endASequence(int & lengthInBytes, std::vector<std::byte> & dataVector)
{
    m_pCoder -> endASequence(lengthInBytes, dataVector);
}

std::vector<std::byte> Manager::getEncodedSequence(std::vector<std::byte> & beginVector, std::vector<std::byte> & endVector)
{
    m_pCoder -> encodeSequence(beginVector, endVector);
    return beginVector;
}

void Manager::endSubSequence(int & lengthInBytesUpper, int & lengthInBytesLower, std::vector<std::byte> & beginVector)
{
    m_pCoder -> endSubSequence(lengthInBytesUpper, lengthInBytesLower, beginVector);
}

std::vector<std::byte> Manager::getEncodedSubSequence(std::vector<std::byte> & beginVector, std::vector<std::byte> & endVector, std::vector<std::byte> & endVectorUpper)
{
    m_pCoder -> encodeSubSequence(beginVector, endVector, endVectorUpper);
    return endVectorUpper;
}



