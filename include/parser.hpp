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
        std::string parseLineForNodeNameInImport(std::string & nodeLine, std::string & nodeName);
        unsigned int parseLineForOIDInImport(std::string & nodeLine, unsigned int & OID);
        void parseLineForParentNamesInImport(std::string & nodeLine, std::vector<std::string> & parentVector, std::vector<unsigned int> & vectorOID);
        void addParentNodes(std::vector<std::string> & parentVector, std::vector<unsigned int> & vectorOID);
        Node * addNodeFromImport(std::string & nodeName, unsigned int & OID, std::vector<std::string> & parentVector);
        
        std::vector<std::string> m_importList;
        std::unique_ptr<Tree> m_pTree; 
        Node * m_pNode;
    protected:
      
};

#endif /*PARSER_HPP*/
