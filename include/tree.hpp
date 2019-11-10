#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include <list>
#include <string>

struct Node
{ 
    int m_objectIdentifier;
    std::string m_name;
    std::string m_data;
    Node * m_pParentElement;
    std::list<Node *> m_childElementPointerList;
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
        Node * findNodeByObjectIdentifier(std::string objectIdentifier); 
        Node * findNodeByName(std::string objectIdentifierParentNode); 
    protected:
        
};

#endif /*TREE_HPP*/
