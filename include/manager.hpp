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
        
        void updateParsingContent(std::string filePath);
    private:
        std::unique_ptr<Parser> m_pParser;
        std::unique_ptr<FileHandler> m_pFileHandler;
    
    protected:
    
};

#endif /*MANAGER_HPP*/
