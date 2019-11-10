#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <string>

struct Node
{ 
    int m_objectIdentifier;
    std::string m_name;
    std::string m_data;
    Node * m_pParentElement;
    std::vector<Node *> m_childElementPointerVector;
};

class Tree
{
    public:
        Tree();
        ~Tree();
        
        void addNode(int objectIdentifier, std::string dataType,
                     std::string name, std::string data,
                     Node * previousElement);
        
        
    private:
        Node * m_rootOfTheTree;
        
        void initializeRootOfTheTree();
        
    protected:
        
};

#endif /*TREE_HPP*/
