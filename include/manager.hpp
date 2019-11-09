#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "parser.hpp"
#include "filehandler.hpp"

class Manager
{
    public:
        Manager();
        ~Manager();
    private:
        Parser * parser;
        FileHandler * fileHandler;
    
    protected:
    
};

#endif /*MANAGER_HPP*/
