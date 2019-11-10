#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <string>

struct Node
{ 
    int m_objectIdentifier;
    std::string m_dataType;
    std::string m_name;
    std::string m_data;
    Node * m_pPreviousElement; 
};

class Tree
{
    public:
        Tree();
        ~Tree();
        
        void addNode(int &objectIdentifier, std::string &dataType,
                     std::string &name, std::string &data,
                     Node &previousElement);
        
        
    private:
        std::vector<Node> m_tree;
        
    protected:
        
};

#endif /*TREE_HPP*/
