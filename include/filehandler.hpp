#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>

class FileHandler
{
    public:
        FileHandler();
        ~FileHandler();
        
        std::string readFile(std::string filePath);
    private:
        std::string m_fileContent;
    protected:
 
};

#endif /*FILEHANDLER_HPP*/
