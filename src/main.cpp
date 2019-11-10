#include <string>
#include "manager.hpp"

int main() 
{
    std::string filePath = "/home/paul/Software/Workspace/University/Sieci_Komputerowe/SNMP-Agent/mibs/RFC1213-MIB.txt";
    Manager manager;
    manager.updateParsingContent(filePath);
    while (1)
    {
        
    }
    return 0;
}
