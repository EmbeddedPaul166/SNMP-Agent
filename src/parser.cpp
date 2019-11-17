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
    std::string nodeLine;
    std::string nodeName;
    std::vector<std::string> parentVector;
    //This will probably be the best way to parse everything for now
    while (std::regex_search(fileContent, match, patternOIDLine))
    {
        std::string nodeLine = match.str(0);
        //Here insert code to parse the rest
        std::regex patternNodeName("(\\w*)\\s*OBJECT IDENTIFIER");
        if (std::regex_search(nodeLine, match, patternNodeName))
        {
            nodeName = match.str(1);
            std::regex patternCutNodeName(nodeName);
            nodeLine = std::regex_replace(nodeLine, patternCutNodeName, "", std::regex_constants::format_first_only);
        }
        
        //std::regex patternParentNames("\\{\\s*(\\S*).*?\\}");
        std::regex patternParentNames("\\s+?([^ \\{]\\S*)\\s+?\\d\\s*\\}");
        while (std::regex_search(nodeLine, match, patternParentNames))
        {
            parentVector.push_back(match.str(1));
            
            std::regex patternCutBraces("\\(");
            parentVector.back() = std::regex_replace(parentVector.back(), patternCutBraces, "\\(", std::regex_constants::format_first_only);
            patternCutBraces.assign("\\)");
            parentVector.back() = std::regex_replace(parentVector.back(), patternCutBraces, "\\)", std::regex_constants::format_first_only);
            
            std::regex patternCut(parentVector.back());
            nodeLine = std::regex_replace(nodeLine, patternCut, "", std::regex_constants::format_first_only);
        } 
        fileContent = std::regex_replace(fileContent, patternOIDLine, "", std::regex_constants::format_first_only);
        
    }   
}

void Parser::parseMIBFile(std::string fileContent)
{
    
}


