#include <cstdlib>
#include "parser.hpp"

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
    std::string nodeLine;
    std::string nodeName;
    unsigned int OID;
    std::vector<std::string> parentVector;
    std::vector<unsigned int> vectorOID;
    std::regex patternOIDLine(".*?OBJECT IDENTIFIER.*?}");
    std::smatch match;
    
    while (std::regex_search(fileContent, match, patternOIDLine))
    {
        nodeLine = match.str(0);
        nodeName = parseLineForNodeNameInImport(nodeLine, nodeName);
        OID = parseLineForOIDInImport(nodeLine, OID);
        parseLineForParentNamesInImport(nodeLine, parentVector, vectorOID); 
        
        if (parentVector.size() != 1)
        {
            addParentNodes(parentVector, vectorOID);
            m_pNode = addNodeFromImport(nodeName, OID, parentVector); 
        }
        else
        {
            m_pNode = addNodeFromImport(nodeName, OID, parentVector);
        }
        fileContent = std::regex_replace(fileContent, patternOIDLine, "", std::regex_constants::format_first_only);
        parentVector.clear();
        vectorOID.clear();
    }   
}

void Parser::parseMIBFile(std::string fileContent)
{
    
}


std::string Parser::parseLineForNodeNameInImport(std::string & nodeLine, std::string & nodeName)
{
    std::regex patternNodeName("(\\w*)\\s*OBJECT IDENTIFIER");
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

unsigned int Parser::parseLineForOIDInImport(std::string & nodeLine, unsigned int & OID)
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

void Parser::parseLineForParentNamesInImport(std::string & nodeLine, std::vector<std::string> & parentVector, std::vector<unsigned int> & vectorOID)
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
            vectorOID.push_back(0);
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
            m_pNode = m_pTree -> addNode(vectorOID[i], parentVector[i], nullptr, "", Visibility::NONE, EncodingType::NONE, AccessType::NONE, StatusType::NONE, m_pNode);
        }    
    }
}

Node * Parser::addNodeFromImport(std::string & nodeName, unsigned int & OID, std::vector<std::string> & parentVector)
{
    for (std::list<Node>::iterator it = m_pTree -> m_nodeList.begin(); it != m_pTree -> m_nodeList.end(); it++)
    {
        if ((*it).m_name == parentVector.front())
        {
            m_pNode = &(*it);
            break;
        }
    }
    return m_pTree -> addNode(OID, nodeName, nullptr, "", Visibility::NONE, EncodingType::NONE, AccessType::NONE, StatusType::NONE, m_pNode);
}
