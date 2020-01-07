#ifndef CODER_HPP
#define CODER_HPP

#include <string>
#include "datatype.hpp"
#include "node.hpp"

enum class TagTable
{
    INTEGER = 0x02,
    OCTET_STRING = 0x04,
    OBJECT_IDENTIFIER = 0x06,
    NULL_D = 0x05,
    SEQUENCE_OF = 0x10,
    CHOICE = 0x12
};

class Coder
{
    public:
        Coder();
        ~Coder();
        
        unsigned int encode(Node & node); 
        
    private:
        unsigned int encodeInteger(Node & node);
        unsigned int encodeOctetString(Node & node);
        unsigned int encodeObjectIdentifier(Node & node);
        unsigned int encodeNULL(Node & node);
        unsigned int encodeSequence(Node & node);
        unsigned int encodeChoice(Node & node);
        
        unsigned int encodeID(DataVisibility visibility, EncodingComplexity complexity);
        unsigned int encodeLength(unsigned int length);
    protected:
 
};

#endif /*CODER_HPP*/

