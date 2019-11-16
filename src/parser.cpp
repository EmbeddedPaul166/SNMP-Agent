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
    std::regex pattern("\\n.*?OBJECT IDENTIFIER.*?}");
    std::string nodeLines;
    //This will probably be the best way to parse everything for now
    while (std::regex_search(fileContent, match, pattern))
    {
        nodeLines = match.str(0);
        //parse arguments and add nodes here
        std::regex_replace(fileContent, pattern, "");
    }
    
    
}

void Parser::parseMIBFile(std::string fileContent)
{
    
}


