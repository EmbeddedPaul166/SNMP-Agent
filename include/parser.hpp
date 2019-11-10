#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "tree.hpp"

class Parser
{
    public:
        Parser();
        ~Parser(); 
        
        void updateFileContent(std::string fileContent);
        
    private:
        std::string m_fileContent;       
    protected:
      
};

#endif /*PARSER_HPP*/
