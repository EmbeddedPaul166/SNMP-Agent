#include <regex>
#include "parser.hpp"

Parser::Parser()
{
    
}

Parser::~Parser()
{
    
}

void Parser::updateFileContent(std::string fileContent)
{
    m_fileContent = fileContent;
}
