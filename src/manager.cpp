#include "manager.hpp"

Manager::Manager()
{
    m_pParser.reset(new Parser());
    m_pFileHandler.reset(new FileHandler());
}

Manager::~Manager()
{
    
}

void Manager::updateParsingContent(std::string filePath)
{
    std::string fileContent = m_pFileHandler -> readFile(filePath);
    m_pParser -> updateFileContent(fileContent);
}
