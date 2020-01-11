#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <memory>
#include <cstdlib>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include "parser.hpp"
#include "filehandler.hpp"
#include "coder.hpp"

class Manager
{
    public:
        Manager();
        ~Manager();
        
        void parse(std::string filePath);
        void startParsing();
        void getNodeByOID(std::string & input);
        std::vector<std::byte> getEncodedInteger(DataType & dataType, int & data);
        std::vector<std::byte> getEncodedOctetString(DataType & dataType, std::string & data);
        std::vector<std::byte> getEncodedObjectIdentifier(DataType & dataType, std::vector<unsigned int> & data);
        std::vector<std::byte> getEncodedBoolean(DataType & dataType, bool & data);
        std::vector<std::byte> getEncodedNULL(DataType & dataType);
        void startASequence(DataType & dataType, std::vector<std::byte> & dataVector);
        void addInteger(DataType & dataType, int & data, int & lengthInBytes, std::vector<std::byte> & dataVector);
        void addOctetString(DataType & dataType, std::string & data, int & lengthInBytes, std::vector<std::byte> & dataVector);
        void addObjectIdentifier(DataType & dataType, std::vector<unsigned int> & data, int & lengthInBytes, std::vector<std::byte> & dataVector);
        void addBoolean(DataType & dataType, bool & data, int & lengthInBytes, std::vector<std::byte> & dataVector);
        void addNULL(DataType & dataType, std::vector<std::byte> & dataVector);
        void endASequence(int & lengthInBytes, std::vector<std::byte> & dataVector);
        std::vector<std::byte> getEncodedSequence(std::vector<std::byte> beginVector, std::vector<std::byte> endVector);
    private:
        std::vector<unsigned int> getOIDVector(std::string & input);
        std::unique_ptr<Parser> m_pParser;
        std::unique_ptr<FileHandler> m_pFileHandler;
        std::unique_ptr<Coder> m_pCoder;
        
    
    protected:
    
};

#endif /*MANAGER_HPP*/
