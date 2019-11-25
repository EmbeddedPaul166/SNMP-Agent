#include <cstdlib>
#include "parser.hpp"

Parser::Parser()
{
    m_pNode = nullptr;
    m_pTree.reset(new Tree());
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
    std::smatch match;
    std::regex patternOIDLine(".*?OBJECT IDENTIFIER.*?}");
    std::regex patternNodeName("(\\w*)\\s*OBJECT IDENTIFIER");
    std::regex patternCutNodeName("");
    std::regex patternOID("(\\d)\\s\\}");
    std::regex patternParentNames("\\s+?([^ \\{]\\S*)\\s+?\\d\\s*\\}");
    std::regex patternCutBraceLeft("\\(");
    std::regex patternCutBraceRight("\\)");
    std::regex patternParentOID("\\(.\\)");
    std::string nodeLine;
    std::vector<unsigned int> vectorOID;
    unsigned int OID;
    std::vector<std::string> parentVector;
    //Parse for node string line
    while (std::regex_search(fileContent, match, patternOIDLine))
    {
        nodeLine = match.str(0);
        //Parse for node name
        if (std::regex_search(nodeLine, match, patternNodeName))
        {
            m_nodeName = match.str(1);
            patternCutNodeName.assign(m_nodeName);
            nodeLine = std::regex_replace(nodeLine, patternCutNodeName, "", std::regex_constants::format_first_only);
        }
        
        //Parse for node OID
        if (std::regex_search(nodeLine, match, patternOID))
        {
            OID = std::stoi(match.str(1));
        }
        
        //Parse for parent names
        while (std::regex_search(nodeLine, match, patternParentNames))
        {
            std::string matchString = match.str(1);
            parentVector.push_back(matchString);
            matchString = std::regex_replace(matchString, patternCutBraceLeft, "\\(", std::regex_constants::format_first_only);
            matchString = std::regex_replace(matchString, patternCutBraceRight, "\\)", std::regex_constants::format_first_only);
            std::regex patternCut(matchString);
            nodeLine = std::regex_replace(nodeLine, patternCut, "", std::regex_constants::format_first_only);
        } 
        fileContent = std::regex_replace(fileContent, patternOIDLine, "", std::regex_constants::format_first_only);
        //Parse parentVector for parents' OID (number in brackets)
        if (parentVector.size() != 1)
        {
            for (std::vector<std::string>::size_type i = parentVector.size() - 1; i != (std::vector<std::string>::size_type) - 1 ; i--)
            {
                if (regex_search(parentVector[i], match, patternParentOID))
                {
                    std::string numberInBraces = match.str(0);
                    numberInBraces.erase(0, 1);
                    numberInBraces.erase(numberInBraces.size() - 1);
                    vectorOID.push_back(std::stoi(numberInBraces));
                    parentVector[i] = std::regex_replace(parentVector[i], patternParentOID, "");
                }
                else
                {
                    vectorOID.push_back(0);
                }
            }
            
            for (std::vector<std::string>::size_type i = parentVector.size() - 1; i != (std::vector<std::string>::size_type) - 1; i--)
            {
                if (parentVector[i] == "iso")
                {
                    m_pNode = &(m_pTree -> m_rootOfTheTree);
                    vectorOID.erase(vectorOID.begin());
                }
                else
                {
                    //Add parent nodes
                    m_pNode = m_pTree -> addNode(vectorOID.front(), parentVector[i], nullptr, "", Visibility::NONE, EncodingType::NONE, AccessType::NONE, StatusType::NONE, m_pNode);
                    vectorOID.erase(vectorOID.begin());
                    
                }    
            }
            //Add node
            m_pNode = m_pTree -> addNode(OID, m_nodeName, nullptr, "", Visibility::NONE, EncodingType::NONE, AccessType::NONE, StatusType::NONE, m_pNode);
        }
        else
        {
            for (std::list<Node>::iterator it = m_pTree -> m_nodeList.begin(); it != m_pTree -> m_nodeList.end(); it++)
            {
                if ((*it).m_name == parentVector.front())
                {
                    m_pNode = &(*it);
                    break;
                }
            }
            m_pNode = m_pTree -> addNode(OID, m_nodeName, nullptr, "", Visibility::NONE, EncodingType::NONE, AccessType::NONE, StatusType::NONE, m_pNode);
        }
        parentVector.clear();    
    }   
}

void Parser::parseMIBFile(std::string fileContent)
{
    
}


