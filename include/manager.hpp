#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <memory>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include "parser.hpp"
#include "filehandler.hpp"

class Manager
{
    public:
        Manager();
        ~Manager();
        
        void parse(std::string filePath);
        void startParsing();
        void getNodeByOID(std::string & input);
    private:
        std::vector<unsigned int> getOIDVector(std::string & input);
        std::unique_ptr<Parser> m_pParser;
        std::unique_ptr<FileHandler> m_pFileHandler;
        
    
    protected:
    
};

#endif /*MANAGER_HPP*/
