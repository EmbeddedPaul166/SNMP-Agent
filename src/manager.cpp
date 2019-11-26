#include "manager.hpp"

Manager::Manager()
{
    m_pParser = std::make_unique<Parser>();
    m_pFileHandler = std::make_unique<FileHandler>();
}

Manager::~Manager()
{
    
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
