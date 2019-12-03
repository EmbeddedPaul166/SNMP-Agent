#include <cstdlib>
#include "parser.hpp"
//TODO: replace regex_replace with sregex_iterator
//TODO: add main node data-type parsing and parse special sequence data type nodes
Parser::Parser()
{
    m_pNode = nullptr;
    m_pTree = std::make_unique<Tree>();
}

Parser::~Parser()
{
    
}

std::string Parser::isImportPresent(std::string fileContent)
{ 
    std::smatch match;
    std::regex pattern("IMPORTS\\s*((.*\\n)*?)\\s*OBJECT-TYPE");
    if (std::regex_search(fileContent, match, pattern))
    {
        std::string import = match.str(0);
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

void Parser::parseMIBImportFile(std::string fileContent)
{
    parseDiminishedNodes(fileContent);
    
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
    std::regex patternOID("(\\d)\\s\\}");
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

    for (std::vector<std::string>::size_type i = parentVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
    {
        if (parentVector[i] == "iso")
        {
            m_pNode = m_pTree -> m_rootOfTheTree;
        }
        else
        {
            m_pNode = m_pTree -> addNode(vectorOID[i], parentVector[i], nullptr, "", AccessType::NONE, StatusType::NONE, m_pNode);
        }    
    }
}

Node * Parser::addNodeOneOrMore(std::string & nodeName, unsigned int & OID, std::vector<std::string> & parentVector)
{
    for (std::list<Node>::iterator it = m_pTree -> m_nodeList.begin(); it != m_pTree -> m_nodeList.end(); it++)
    {
        if ((*it).m_name == parentVector.front())
        {
            m_pNode = &(*it);
            break;
        }
    }
    return m_pTree -> addNode(OID, nodeName, nullptr, "", AccessType::NONE, StatusType::NONE, m_pNode);
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
    Node * pParent= nullptr;
    
    for (std::sregex_iterator it = begin; it != end; it++)
    {
        match = *it;
        nodeString = match.str(0);
        parseNodeParameters(nodeString, nodeName, OID, accessType, statusType, description, &pParent);
        m_pNode = addNode(nodeName, OID, accessType, statusType, description, &pParent);
    }
     
}

void Parser::parseNodeParameters(std::string & nodeString, std::string & nodeName, unsigned int & OID, AccessType & accessType, StatusType & statusType, std::string & description, Node ** pParent)
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


Node * Parser::addNode(std::string & nodeName, unsigned int & OID, AccessType & accessType, StatusType & statusType, std::string & description, Node ** pParent)
{
    return m_pTree -> addNode(OID, nodeName, nullptr, description, accessType, statusType, *pParent);
}

void Parser::parseMIBFile(std::string fileContent)
{
    parseDiminishedNodes(fileContent);
    parseNodes(fileContent);
}

