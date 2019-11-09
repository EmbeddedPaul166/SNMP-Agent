#include "manager.hpp"

Manager::Manager()
{
    parser = new Parser();
    fileHandler = new FileHandler();
}

Manager::~Manager()
{
    delete parser;
    delete fileHandler;
}
