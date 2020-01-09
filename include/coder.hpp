#ifndef CODER_HPP
#define CODER_HPP

#include <string>
#include <vector>
#include "datatype.hpp"
#include "node.hpp"

class Coder
{
    public:
        Coder();
        ~Coder();
        
        std::vector<int8_t> encodeInteger(DataType & dataType, int & data);
        std::vector<int8_t> encodeOctetString(DataType & dataType, std::string & data);
        std::vector<int8_t> encodeObjectIdentifier(DataType & dataType, std::vector<unsigned int> & data);
        std::vector<int8_t> encodeNULL(DataType & dataType);
        std::vector<int8_t> encodeSequence(std::vector<DataType> & dataTypeVector);
        
    private:
        int8_t encodeID(DataType & dataType);
        std::vector<int8_t> encodeLength(int & length);
        std::vector<int8_t> splitIntoBytes(int & number, int & numberOfBytes);
        std::vector<int8_t> splitIntoBytes(int & number);
        
    protected:
 
};

#endif /*CODER_HPP*/

