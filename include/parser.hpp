#ifndef PARSER_HPP
#define PARSER_HPP

#include <regex>
#include <memory>
#include <string>
#include <vector>
#include "tree.hpp"

class Parser
{
    public:
        Parser();
        ~Parser(); 
        
        std::string isImportPresent(std::string fileContent);
        void parseMIBImportFile(std::string fileContent);
        void parseMIBFile(std::string fileContent);
        
    private:
        std::vector<std::string> m_importList;
        std::unique_ptr<Tree> m_pTree; 
        Node * m_pNode;
    protected:
      
};

#endif /*PARSER_HPP*/
