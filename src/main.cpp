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
        std::string input;
        std::cout << std::endl;
        std::cout << "Input OID string:" << std::endl;
        std::cin >> input;
        std::cout << std::endl;
        if (std::cin.fail())
        {
            std::cout << "Bad input!" << std::endl;
            continue;
        }
        else
        {
            manager.getNodeByOID(input);
        }
    }
    return 0;
}
