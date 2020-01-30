#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>
#include "datatype.hpp"

//TODO: implement validator functionality and function in main that codes for given OID node

class Validator
{
    public:
        Validator();
        ~Validator();
        
        //bool validate(DataType & dataType, DataType & nodeType, std::vector<std::string> & nodeNameVector);
        bool validate(DataType & dataType, DataType & nodeType);
        bool validate(DataType & dataType, DataType & nodeType, int & data);
        bool validate(DataType & dataType, DataType & nodeType, std::string & data);
        
    private:
        
    protected:
 
};

#endif /*VALIDATOR_HPP*/
