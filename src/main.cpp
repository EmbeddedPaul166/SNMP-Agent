#include <string>
#include <cstdlib>
#include "manager.hpp"

int main() 
{
    
    std::string filePath(getenv("PROJECT_PATH"));
    filePath += "/mibs/RFC1213-MIB.txt";
    Manager manager;
    manager.parse(filePath);
    while (1)
    {
        
    }
    return 0;
}
