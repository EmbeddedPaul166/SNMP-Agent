#include <cstdlib>
#include "parser.hpp"

//TODO: Complete custom data type parsing
//TODO: Add node data type parsing

Parser::Parser()
{
    m_pNode = nullptr;
    m_pTree = std::make_unique<Tree>();
}

Parser::~Parser()
{
    
}


void Parser::getNodeByOID(std::vector<unsigned int> vectorOfOID,
                          bool & isNodeFound,
                          unsigned int & OID,
                          std::string & name,
                          std::string & baseType,
                          std::string & complexity,
                          std::string & encodingType,
                          std::string & visibility,
                          unsigned int & lengthLimit,
                          std::string & description,
                          std::string & accessType,
                          std::string & statusType)
{
    m_pNode = m_pTree -> findNodeByObjectIdentifier(vectorOfOID);
    
    if (m_pNode == nullptr)
    {
        isNodeFound = false;
    }
    else
    {
        isNodeFound = true;
        OID = m_pNode -> m_objectIdentifier;
        name = m_pNode -> m_name;
        
        DataType & dataType = m_pNode -> m_dataType;
        if (dataType.m_baseType == BaseDataType::INTEGER)
        {
            baseType = "Integer";
        }
        else if (dataType.m_baseType == BaseDataType::OCTET_STRING)
        {
            baseType = "Octet string";
        }
        else if (dataType.m_baseType == BaseDataType::OBJECT_IDENTIFIER)
        {
            baseType = "Object identifier";
        }
        else if (dataType.m_baseType == BaseDataType::NULL_D)
        {
            baseType = "Null";
        }
        else if (dataType.m_baseType == BaseDataType::SEQUENCE)
        {
            baseType = "Sequence";
        }
        else if (dataType.m_baseType == BaseDataType::CHOICE)
        {
            baseType = "Choice";
        }
        else
        {
            baseType = "Error";
        }

        
        if (dataType.m_complexity == EncodingComplexity::PRIMITIVE)
        {
            complexity = "Primitive";
        }
        else if (dataType.m_complexity == EncodingComplexity::CONSTRUCTED)
        {
            complexity = "Constructed";
        }
        else
        {
            complexity = "Error";
        }
        
        if (dataType.m_encodingType == EncodingType::UNIVERSAL)
        {
            encodingType = "Universal";
        }
        else if (dataType.m_encodingType == EncodingType::IMPLICIT)
        {
            encodingType = "Implicit";
        }
        else if (dataType.m_encodingType == EncodingType::EXPLICIT)
        {
            encodingType = "Explicit";
        }
        else
        {
            encodingType = "Error";
        }
        
        if (dataType.m_visibility == DataVisibility::UNIVERSAL)
        {
            visibility = "Universal";
        }
        else if (dataType.m_visibility == DataVisibility::APPLICATION)
        {
            visibility = "Application";
        }
        else if (dataType.m_visibility == DataVisibility::CONTEXT_SPECIFIC)
        {
            visibility = "Context specific";
        }
        else if (dataType.m_visibility == DataVisibility::PRIVATE)
        {
            visibility = "Private";
        }
        else
        {
            visibility = "Error";
        }
        
        lengthLimit = dataType.m_lengthLimit;
        
        description = m_pNode -> m_description;
        if (description == "")
        {
            description = "None";
        }
        
        if (m_pNode -> m_accessType == AccessType::READ_ONLY)
        {
            accessType = "Read only";
        }
        else if (m_pNode -> m_accessType == AccessType::WRITE_ONLY)
        {
            accessType = "Write Only";
        }
        else if (m_pNode -> m_accessType == AccessType::READ_WRITE)
        {
            accessType = "Read write";
        }
        else if (m_pNode -> m_accessType == AccessType::NOT_ACCESSIBLE)
        {
            accessType = "Not accessible";
        }
        else
        {
            accessType = "Error";
        }
        
        if (m_pNode -> m_statusType == StatusType::MANDATORY)
        {
            statusType = "Mandatory";  
        }
        else if (m_pNode -> m_statusType == StatusType::OPTIONAL)
        {
            statusType = "Optional";
        }
        else if (m_pNode -> m_statusType == StatusType::OBSOLETE)
        {
            statusType = "Obsolete";  
        }
        else
        {
            statusType = "Error";
        }
    }
}

std::string Parser::isImportPresent(std::string fileContent)
{ 
    std::smatch match;
    std::regex pattern("IMPORTS\\s*((.*\\n)*?)\\s*OBJECT-TYPE");
    if (std::regex_search(fileContent, match, pattern))
    {
        std::string import = match.str(0); 
        
        pattern.assign("IMPORTS\\s*((.*\\n)*?)\\s*FROM");
        if (std::regex_search(import, match, pattern))
        {
            std::string importedDataTypes = match.str(1);
            pattern.assign("\\w+");
            std::sregex_iterator begin(importedDataTypes.cbegin(), importedDataTypes.cend(), pattern);
            std::sregex_iterator end;
            std::string customDataType;
            for (std::sregex_iterator it = begin; it != end; it++)
            {
                match = *it;
                m_customDataTypeNameVector.push_back(match.str(0));
            }
        }
        
        pattern.assign("FROM (.*)");
        if (std::regex_search(import, match, pattern))
        {
            std::string importPath(getenv("PROJECT_PATH"));
            importPath  = importPath + "/mibs/" + match.str(1) + ".txt";
            return importPath;
        }
    }
    return "";
}

void Parser::parseCustomDataTypesInImport(std::string fileContent)
{ 
    std::smatch match;
    
    for (std::vector<std::string>::size_type i = m_customDataTypeNameVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
    {
        std::string patternOneString = m_customDataTypeNameVector[i] + " ::=\\n\\s*[^:upper:c].*?\\n\\s*.*";
        std::string patternTwoString = m_customDataTypeNameVector[i] + " ::=\\n\\s*CHOICE((.*\\n)*?)\\s*\\}"; 
        std::regex patternOne(patternOneString);
        std::regex patternTwo(patternTwoString);
        std::regex patternThree("CHOICE");
        if (std::regex_search(fileContent, match, patternOne))
        {
            std::string matchString = match.str(0);
            if (!std::regex_search(matchString, match, patternThree))
            {
                m_customDataTypeStringVector.push_back(matchString);
            }
        }
        if (std::regex_search(fileContent, match, patternTwo))
        {
            m_customDataTypeStringVector.push_back(match.str(0)); 
        }
    } 
}

void Parser::parseMIBImportFile(std::string fileContent)
{
    parseDiminishedNodes(fileContent); 
    parseCustomDataTypesInImport(fileContent);
}

void Parser::parseDiminishedNodes(std::string fileContent)
{
    std::string nodeLine;
    std::string nodeName;
    unsigned int OID;
    std::vector<std::string> parentVector;
    std::vector<unsigned int> vectorOID;
    std::regex patternOIDLine("\\n[^-].*?OBJECT IDENTIFIER ::=.*?}");
    std::smatch match;
    std::sregex_iterator begin(fileContent.cbegin(), fileContent.cend(), patternOIDLine);
    std::sregex_iterator end;
    
    for (std::sregex_iterator it = begin; it != end; it++)
    {
        match = *it;
        nodeLine = match.str(0);
        nodeName = parseLineForNodeNameDiminished(nodeLine, nodeName);
        OID = parseLineForOIDDiminished(nodeLine, OID);
        parseLineForParentNamesDiminished(nodeLine, parentVector, vectorOID); 
        if (parentVector.size() != 1)
        {
            addParentNodes(parentVector, vectorOID);
            m_pNode = addNodeOneOrMore(nodeName, OID, parentVector); 
        }
        else
        {
            m_pNode = addNodeOneOrMore(nodeName, OID, parentVector);
        }
        parentVector.clear();
        vectorOID.clear();
    }   
}

std::string Parser::parseLineForNodeNameDiminished(std::string & nodeLine, std::string & nodeName)
{
    std::regex patternNodeName("(\\S*)\\s*OBJECT IDENTIFIER");
    std::regex patternCutNodeName("");
    std::smatch match;
    if (std::regex_search(nodeLine, match, patternNodeName))
    {
        nodeName = match.str(1);
        patternCutNodeName.assign(nodeName);
        nodeLine = std::regex_replace(nodeLine, patternCutNodeName, "", std::regex_constants::format_first_only);
        return nodeName;
    }
    return "";
}

unsigned int Parser::parseLineForOIDDiminished(std::string & nodeLine, unsigned int & OID)
{
    std::regex patternOID("(\\d+)\\s\\}");
    std::smatch match;
    if (std::regex_search(nodeLine, match, patternOID))
    {
        OID = std::stoi(match.str(1));
        return OID;
    }
    return 0;
}

void Parser::parseLineForParentNamesDiminished(std::string & nodeLine, std::vector<std::string> & parentVector, std::vector<unsigned int> & vectorOID)
{
    std::regex patternParentNames("\\s+?([^ \\{]\\S*)\\s+?\\d\\s*\\}");
    std::regex patternParentOID("\\((.)\\)");
    std::regex patternCutBraceLeft("\\(");
    std::regex patternCutBraceRight("\\)");
    std::smatch match;
    std::string matchString;
    std::string cutString;
    
    while (std::regex_search(nodeLine, match, patternParentNames))
    {
        matchString = match.str(1);
        cutString = matchString;
        if (std::regex_search(matchString, match, patternParentOID))
        {
            vectorOID.push_back(std::stoi(match.str(1)));
            matchString = std::regex_replace(matchString, patternParentOID, "", std::regex_constants::format_first_only);
            parentVector.push_back(matchString);
        }
        else
        {
            vectorOID.push_back(1);
            parentVector.push_back(matchString);
        }
        cutString = std::regex_replace(cutString, patternCutBraceLeft, "\\(", std::regex_constants::format_first_only);
        cutString = std::regex_replace(cutString, patternCutBraceRight, "\\)", std::regex_constants::format_first_only);
        std::regex patternCut(cutString);
        nodeLine = std::regex_replace(nodeLine, patternCut, "", std::regex_constants::format_first_only);
    } 
}

void Parser::addParentNodes(std::vector<std::string> & parentVector, std::vector<unsigned int> & vectorOID)
{ 
    std::regex patternParentOID("\\(.\\)");
    std::smatch match;
    DataType dataType;
    for (std::vector<std::string>::size_type i = parentVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
    {
        if (parentVector[i] == "iso")
        {
            m_pNode = m_pTree -> m_rootOfTheTree;
        }
        else
        {
            m_pNode = m_pTree -> addNode(vectorOID[i], parentVector[i], dataType, "", AccessType::NOT_ACCESSIBLE, StatusType::MANDATORY, m_pNode);
        }    
    }
}

Node * Parser::addNodeOneOrMore(std::string & nodeName, unsigned int & OID, std::vector<std::string> & parentVector)
{
    
    DataType dataType;
    for (std::list<Node>::iterator it = m_pTree -> m_nodeList.begin(); it != m_pTree -> m_nodeList.end(); it++)
    {
        if ((*it).m_name == parentVector.front())
        {
            m_pNode = &(*it);
            break;
        }
    }
    return m_pTree -> addNode(OID, nodeName, dataType, "", AccessType::NOT_ACCESSIBLE, StatusType::MANDATORY, m_pNode);
}

void Parser::parseNodes(std::string fileContent)
{
    std::regex patternNode("\\n[^-]\\w+?\\sOBJECT-TYPE\\s*((.*\\n)*?)\\s*::= .*\\n");
    std::smatch match;
    std::string nodeString;
    std::sregex_iterator begin(fileContent.cbegin(), fileContent.cend(), patternNode);
    std::sregex_iterator end;
    
    std::string nodeName;
    unsigned int OID;
    AccessType accessType;
    StatusType statusType;
    std::string description;
    DataType dataType;
    Node * pParent = nullptr;
    
    for (std::sregex_iterator it = begin; it != end; it++)
    {
        match = *it;
        nodeString = match.str(0);
        parseNodeParameters(nodeString, nodeName, OID, dataType, description, accessType, statusType, &pParent);
        m_pNode = addNode(nodeName, OID, dataType, description, accessType, statusType, &pParent);
    }
     
}

void Parser::parseNodeParameters(std::string & nodeString, std::string & nodeName, unsigned int & OID, DataType & dataType, std::string & description, AccessType & accessType, StatusType & statusType, Node ** pParent)
{
    std::regex pattern("(\\w+) OBJECT-TYPE");
    std::smatch match;
    
    if (std::regex_search(nodeString, match, pattern))
    {
        nodeName = match.str(1);
    }
    
    pattern.assign("(\\d+) \\}");
    if (std::regex_search(nodeString, match, pattern))
    {
        OID = std::stoi(match.str(1));
    }
    
    pattern.assign("SYNTAX  ((.*\\n)*?)    ACCESS");
    if (std::regex_search(nodeString, match, pattern))
    {
        std::string matchString = match.str(1);
        dataType = parseDataType(matchString);
    }
    
    pattern.assign("ACCESS  (.+)");
    if (std::regex_search(nodeString, match, pattern))
    {
        std::string accessString = match.str(1);
        if (accessString == "read-only")
        {
            accessType = AccessType::READ_ONLY;
        }
        else if (accessString == "write-only")
        {
            accessType = AccessType::WRITE_ONLY;
        }
        else if (accessString == "read-write")
        {
            accessType = AccessType::READ_WRITE;    
        }
        else if (accessString == "not-accessible")
        {
            accessType = AccessType::NOT_ACCESSIBLE;
        }
    }
    
    pattern.assign("STATUS  (.+)");
    if (std::regex_search(nodeString, match, pattern))
    {
        
        std::string statusString = match.str(1);
        if (statusString == "mandatory")
        {
            statusType = StatusType::MANDATORY;
        }
        else if (statusString == "optional")
        {
            statusType = StatusType::OPTIONAL;
        }
        else if (statusString == "obsolete")
        {
            statusType = StatusType::OBSOLETE;    
        }
    }
    
    pattern.assign("\"(.+?((.*\\n)+).+?)\"\\n");
    if (std::regex_search(nodeString, match, pattern))
    {
        description = match.str(1);
    }
    
    pattern.assign("\\{ (.+) \\d \\}");
    if (std::regex_search(nodeString, match, pattern))
    {
        std::string parentName = match.str(1);
        for (std::list<Node>::iterator it = m_pTree -> m_nodeList.begin(); it != m_pTree -> m_nodeList.end(); it++)
        {
            if ((*it).m_name == parentName)
            {
                *pParent = &(*it);
                break;
            }
        }
    }
}


Node * Parser::addNode(std::string & nodeName, unsigned int & OID, DataType & dataType, std::string & description, AccessType & accessType, StatusType & statusType, Node ** pParent)
{
    return m_pTree -> addNode(OID, nodeName, dataType, description, accessType, statusType, *pParent);
}


DataType Parser::parseDataType(std::string & dataTypeString)
{
    DataType dataType;
    return dataType;
}

void Parser::parseCustomDataTypesInMain(std::string fileContent)
{
    std::smatch match;
    
    std::string patternOneString ="\\w* ::=\\n\\s*.*[^\\{]\\n";
    std::string patternTwoString = "\\w* ::=\\n\\s*SEQUENCE((.*\\n)*?)\\s*\\}";
    std::string patternThreeString = "\\w* ::=\\n\\s*CHOICE((.*\\n)*?)\\s*\\}";
    
    std::regex patternOne(patternOneString);
    std::regex patternTwo(patternTwoString);
    std::regex patternThree(patternThreeString);
    
    std::sregex_iterator beginOne(fileContent.cbegin(), fileContent.cend(), patternOne);
    
    std::sregex_iterator beginTwo(fileContent.cbegin(), fileContent.cend(), patternTwo);
    
    std::sregex_iterator beginThree(fileContent.cbegin(), fileContent.cend(), patternThree);
    
    std::sregex_iterator end;
    
    for (std::sregex_iterator it = beginOne; it != end; it++)
    {
        match = *it;
        m_customDataTypeStringVector.push_back(match.str(0));
    }
    
    for (std::sregex_iterator it = beginTwo; it != end; it++)
    {
        match = *it;
        m_customDataTypeStringVector.push_back(match.str(0));
    }
    
    for (std::sregex_iterator it = beginThree; it != end; it++)
    {
        match = *it;
        m_customDataTypeStringVector.push_back(match.str(0));
    }
}

void Parser::parseCustomDataTypeInformation()
{ 
    std::smatch match; 
    std::regex patternName("(\\w*) ::=");
    std::regex patternSequence("SEQUENCE");
    std::regex patternChoice("CHOICE");
    std::regex patternInteger("::=\\n\\s*INTEGER");
    std::regex patternOctetString("::=\\n\\s*OCTET STRING");
    std::regex patternObjectIdentifier("::=\\n\\s*OBJECT IDENTIFIER");
    std::regex patternNULL("::=\\n\\s*NULL");
    
    std::regex patternImplicit("IMPLICIT");
    std::regex patternExplicit("EXPLICIT");
    
    std::regex patternUniversal("UNIVERSAL");
    std::regex patternApplication("APPLICATION");
    std::regex patternContextSpecific("CONTEXT-SPECIFIC");
    std::regex patternPrivate("PRIVATE");
    
    std::regex patternSingleElementSequence("\\s*(\\w*?[^{},=])\\n\\s*.*?[^{}]\\n");
    std::regex patternSingleElementChoice("(\\w+)\\n");
    
    DataType dataType;
    
    m_customDataTypeNameVector.clear();
    
    for (std::vector<std::string>::size_type i = m_customDataTypeStringVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
    {
        std::string & dataString = m_customDataTypeStringVector[i];
        
        if (std::regex_search(dataString, match, patternName))
        {
           m_customDataTypeNameVector.push_back(match.str(1));
        }
        
        if (std::regex_search(dataString, match, patternSequence))
        {
            
            dataType.m_baseType = BaseDataType::SEQUENCE;
            dataType.m_complexity = EncodingComplexity::CONSTRUCTED;
            std::sregex_iterator beginS(dataString.cbegin(), dataString.cend(), patternSingleElementSequence); 
            std::sregex_iterator endS;
            for (std::sregex_iterator it = beginS; it != endS; it++)
            {
                match = *it;
                dataType.nodeNameList.push_back(match.str(1));
            }
        }
        else if (std::regex_search(dataString, match, patternChoice))
        {
            dataType.m_baseType = BaseDataType::CHOICE;
            dataType.m_complexity = EncodingComplexity::CONSTRUCTED;
            std::sregex_iterator beginC(dataString.cbegin(), dataString.cend(), patternSingleElementChoice); 
            std::sregex_iterator endC;
            for (std::sregex_iterator it = beginC; it != endC; it++)
            {
                match = *it;
                dataType.nodeNameList.push_back(match.str(1));
            }
        
        }
        else if (std::regex_search(dataString, match, patternInteger))
        {
            dataType.m_baseType = BaseDataType::INTEGER;
            dataType.m_complexity = EncodingComplexity::PRIMITIVE;
        }
        else if (std::regex_search(dataString, match, patternOctetString))
        {
            dataType.m_baseType = BaseDataType::OCTET_STRING;
            dataType.m_complexity = EncodingComplexity::PRIMITIVE;
        }
        else if (std::regex_search(dataString, match, patternObjectIdentifier))
        {
            dataType.m_baseType = BaseDataType::OBJECT_IDENTIFIER;
            dataType.m_complexity = EncodingComplexity::PRIMITIVE;
        }
        else
        {
            dataType.m_baseType = BaseDataType::NULL_D;
            dataType.m_complexity = EncodingComplexity::PRIMITIVE;
        }
        
        if (std::regex_search(dataString, match, patternImplicit))
        {
            dataType.m_encodingType = EncodingType::IMPLICIT;
        }
        else if (std::regex_search(dataString, match, patternExplicit))
        {
            dataType.m_encodingType = EncodingType::EXPLICIT;
        }
        else
        {
            dataType.m_encodingType = EncodingType::UNIVERSAL;
        }
        
        if (std::regex_search(dataString, match, patternUniversal))
        {
            dataType.m_visibility = DataVisibility::UNIVERSAL;
        }
        else if (std::regex_search(dataString, match, patternApplication))
        {
            dataType.m_visibility = DataVisibility::APPLICATION;
        }
        else if (std::regex_search(dataString, match, patternPrivate))
        {
            dataType.m_visibility = DataVisibility::PRIVATE;
        }
        else
        {
            dataType.m_visibility = DataVisibility::CONTEXT_SPECIFIC;
        }
        
        m_customDataTypeVector.push_back(dataType);
    }
}

void Parser::parseMIBFile(std::string fileContent)
{
    parseCustomDataTypesInMain(fileContent);
    parseCustomDataTypeInformation();
    parseDiminishedNodes(fileContent);
    parseNodes(fileContent);
}

