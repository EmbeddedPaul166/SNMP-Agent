#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <memory>
#include <string>
#include "parser.hpp"
#include "filehandler.hpp"

class Manager
{
    public:
        Manager();
        ~Manager();
        
        void parse(std::string filePath);
        void startParsing();
    private:
        std::unique_ptr<Parser> m_pParser;
        std::unique_ptr<FileHandler> m_pFileHandler;
    
    protected:
    
};

#endif /*MANAGER_HPP*/
