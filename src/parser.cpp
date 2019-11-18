#include <cstdlib>
#include "parser.hpp"

Parser::Parser()
{
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
    std::regex patternParentOID("\\(\\d\\)");
    std::string nodeLine;
    std::string nodeName;
    unsigned int OID;
    std::vector<std::string> parentVector;
    Node * previousNode;
    //Parse for node string line
    while (std::regex_search(fileContent, match, patternOIDLine))
    {
        nodeLine = match.str(0);
        //Parse for node name
        if (std::regex_search(nodeLine, match, patternNodeName))
        {
            nodeName = match.str(1);
            patternCutNodeName.assign(nodeName);
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
            parentVector.push_back(match.str(1));
            parentVector.back() = std::regex_replace(parentVector.back(), patternCutBraceLeft, "\\(", std::regex_constants::format_first_only);
            parentVector.back() = std::regex_replace(parentVector.back(), patternCutBraceRight, "\\)", std::regex_constants::format_first_only);
            std::regex patternCut(parentVector.back());
            nodeLine = std::regex_replace(nodeLine, patternCut, "", std::regex_constants::format_first_only);
        } 
        fileContent = std::regex_replace(fileContent, patternOIDLine, "", std::regex_constants::format_first_only);
        //Parse parentVector for parents' OID (number in brackets) 
        std::vector<unsigned int> vectorOID;
        for (std::vector<std::string>::iterator it = parentVector.end(); it != parentVector.begin(); it--)
        {
            if (regex_search(*it, match, patternParentOID))
            {
                vectorOID.push_back(std::stoi(match.str(0)));
                *it = std::regex_replace(*it, patternParentOID, "");
            }
            else
            {
                vectorOID.push_back(0);
            }
        }
         
        //Optionally add parent nodes
        if (parentVector.size() != 1)
        {
            for (std::vector<std::string>::iterator it = parentVector.end(); it != parentVector.begin(); it--)
            {
                if (*it == "ISO")
                {
                    previousNode = m_pTree -> m_rootOfTheTree;
                    vectorOID.erase(vectorOID.begin());
                }
                else
                {
                    //Add parent nodes
                    previousNode = m_pTree -> addNode(vectorOID.front(), *it, nullptr, "", Visibility::NONE, EncodingType::NONE, AccessType::NONE, StatusType::NONE, previousNode);
                    vectorOID.erase(vectorOID.begin());
                    
                }    
            }
            //Add node
            previousNode = m_pTree -> addNode(OID, nodeName, nullptr, "", Visibility::NONE, EncodingType::NONE, AccessType::NONE, StatusType::NONE, previousNode);
        }
        else
        { 
            //Add node
            previousNode = m_pTree -> addNode(OID, nodeName, nullptr, "", Visibility::NONE, EncodingType::NONE, AccessType::NONE, StatusType::NONE, previousNode);
        }
        
    }   
}

void Parser::parseMIBFile(std::string fileContent)
{
    
}


