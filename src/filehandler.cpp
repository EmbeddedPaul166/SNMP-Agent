#include <iostream>
#include <fstream>
#include <sstream>
#include "filehandler.hpp"


FileHandler::FileHandler()
{
    
}

FileHandler::~FileHandler()
{
    
}


std::string FileHandler::readFile(std::string filePath)
{
    std::ifstream file(filePath);
    if (file.is_open())
    {
        auto ss = std::ostringstream{};
        ss << file.rdbuf();
        m_fileContent = ss.str();
        return m_fileContent; 
    }
    else
    {
        return "";
    } 
}
