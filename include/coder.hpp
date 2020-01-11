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
        
        void startASequence(DataType & dataType, std::vector<std::byte> & dataVector);
        void addInteger(DataType & dataType, int & data, int & lengthInBytes, std::vector<std::byte> & dataVector);
        void addOctetString(DataType & dataType, std::string & data, int & lengthInBytes, std::vector<std::byte> & dataVector);
        void addObjectIdentifier(DataType & dataType, std::vector<unsigned int> & data, int & lengthInBytes, std::vector<std::byte> & dataVector);
        void addBoolean(DataType & dataType, bool & data, int & lengthInBytes, std::vector<std::byte> & dataVector);
        void addNULL(DataType & dataType, int & lengthInBytes, std::vector<std::byte> & dataVector);
        void endASequence(int & lengthInBytes, std::vector<std::byte> & dataVector);
        std::vector<std::byte> encodeSequence(std::vector<std::byte> & beginVector, std::vector<std::byte> & endVector);
        void endSubSequence(int & lengthInBytesUpper, int & lengthInBytesLower, std::vector<std::byte> & beginVector);
        std::vector<std::byte> encodeSubSequence(std::vector<std::byte> & beginVector, std::vector<std::byte> & endVector, std::vector<std::byte> & endVectorUpper);
        
    private:
        unsigned int m_startSequenceCount;
        unsigned int m_endSequenceCount;
        
        std::byte encodeID(DataType & dataType);
        std::vector<std::byte> encodeLength(int & length);
        std::vector<std::byte> splitIntoBytes(int & number, int & numberOfBytes);
        std::vector<std::byte> splitIntoBytes(int & number);
        std::vector<std::byte> splitIntoBytes(std::string & string);
        int getNumberOfBytes(int number);
        int getNumberOfBytes(std::string string);
        int getNumberOfBytes(std::vector<unsigned int> vector);
        
    protected:
 
};

#endif /*CODER_HPP*/

