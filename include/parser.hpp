#ifndef PARSER_HPP
#define PARSER_HPP

#include <regex>
#include <sstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "tree.hpp"
#include "node.hpp"
#include "datatype.hpp"

class Parser
{
    public:
        Parser();
        ~Parser(); 
        
        std::string isImportPresent(std::string fileContent);
        void parseMIBImportFile(std::string fileContent);
        void parseMIBFile(std::string fileContent);
        void getNodeByOID(std::vector<unsigned int> vectorOfOID,
                          bool & isNodeFound,
                          unsigned int & OID,
                          std::string & name,
                          std::string & baseType,
                          std::string & complexity,
                          std::string & encodingType,
                          std::string & visibility,
                          int & lengthLimit,
                          int & rangeLimitLower,
                          int & rangeLimitUpper,
                          std::string & description,
                          std::string & accessType,
                          std::string & statusType);
        
    private: 
        void parseDiminishedNodes(std::string fileContent);
        void parseCustomDataTypesInImport(std::string fileContent);
        void parseCustomDataTypeInformation();
        void parseCustomDataTypesInMain(std::string fileContent);
        DataType parseDataType(std::string & dataTypeString);
        std::string parseLineForNodeNameDiminished(std::string & nodeLine, std::string & nodeName);
        unsigned int parseLineForOIDDiminished(std::string & nodeLine, unsigned int & OID);
        void parseLineForParentNamesDiminished(std::string & nodeLine, std::vector<std::string> & parentVector, std::vector<unsigned int> & vectorOID);
        void addParentNodes(std::vector<std::string> & parentVector, std::vector<unsigned int> & vectorOID);
        Node * addNodeOneOrMore(std::string & nodeName, unsigned int & OID, std::vector<std::string> & parentVector);
        Node * addNode(std::string & nodeName, unsigned int & OID, DataType & dataType, std::string & description, AccessType & accessType, StatusType & statusType, Node ** pParent);
        void parseNodes(std::string fileContent);
        void parseNodeParameters(std::string & nodeString, std::string & nodeName, unsigned int & OID, DataType & dataType, std::string & description, AccessType & accessType, StatusType & statusType, Node ** pParent);
        std::vector<std::string> m_importList;
        std::vector<std::string> m_customDataTypeStringVector;
        std::vector<std::string> m_customDataTypeNameVector;
        std::vector<DataType> m_customDataTypeVector;
        std::unique_ptr<Tree> m_pTree; 
        Node * m_pNode;
        
    protected:
      
};

#endif /*PARSER_HPP*/
