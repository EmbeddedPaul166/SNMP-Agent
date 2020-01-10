#ifndef CODER_HPP
#define CODER_HPP

#include <cstddef>
#include <cmath>
#include <string>
#include <vector>
#include "datatype.hpp"
#include "node.hpp"

class Coder
{
    public:
        Coder();
        ~Coder();
        
        std::vector<std::byte> encodeInteger(DataType & dataType, int & data);
        std::vector<std::byte> encodeOctetString(DataType & dataType, std::string & data);
        std::vector<std::byte> encodeObjectIdentifier(DataType & dataType, std::vector<unsigned int> & data);
        std::vector<std::byte> encodeBoolean(DataType & dataType, bool & data);
        std::vector<std::byte> encodeNULL(DataType & dataType);
        std::vector<std::byte> encodeSequence(std::vector<DataType> & dataTypeVector);
        
    private:
        std::byte encodeID(DataType & dataType);
        std::vector<std::byte> encodeLength(int & length);
        std::vector<std::byte> splitIntoBytes(int & number, int & numberOfBytes);
        std::vector<std::byte> splitIntoBytes(int & number);
        std::vector<std::byte> splitIntoBytes(std::string & string);
        int getNumberOfBytes(int number);
        
    protected:
 
};

#endif /*CODER_HPP*/

