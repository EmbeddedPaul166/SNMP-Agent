#include <iostream>
#include <string>
#include <cstdlib>
#include "manager.hpp"

int main() 
{
    char * pPath =  getenv("PROJECT_PATH");
    if (pPath == nullptr)
    {
        std::cout << "Error: Source set-env file first" << std::endl;
        return 0;
    }
    std::string filePath(pPath);
    filePath += "/mibs/RFC1213-MIB.txt";
    Manager manager;
    manager.parse(filePath);
    while (1)
    {
        
    }
    return 0;
}
