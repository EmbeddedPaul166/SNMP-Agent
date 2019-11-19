#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <string>

//First we parse imports, and every import with object identifier is blacklisted

enum class Visibility
{
    UNIVERSAL,
    APPLICATION,
    CONTEXT_SPECIFIC,
    PRIVATE,
    NONE
};

enum class EncodingType
{
    IMPLICIT,
    EXPLICIT,
    NONE
};

enum class AccessType
{
    READ_ONLY,
    WRITE_ONLY,
    READ_WRITE,
    NOT_ACCESSIBLE,
    NONE
};

enum class StatusType
{
    MANDATORY,
    OPTIONAL,
    OBSOLETE,
    NONE
};

struct Node
{ 
    unsigned int m_objectIdentifier;
    std::string m_name;
    std::string * m_data_type;
    std::string m_description;
    Visibility m_visibility;
    EncodingType m_encodingType;
    AccessType m_accessType;
    StatusType m_statusType;
    Node * m_pParentElement;
    std::list<Node *> m_childElementPointerList;
};

class Tree
{
    public:
        Tree();
        ~Tree();
        
        Node * addNode(unsigned int objectIdentifier, std::string name, std::string * dataType,
                     std::string description, Visibility visibility, EncodingType encodingType,
                     AccessType accessType, StatusType statusType, Node * parentElement);
        Node * findNodeByObjectIdentifier(std::vector<unsigned int> vectorOfOID); 
        Node * findNodeByName(std::vector<unsigned int> vectorOfOID, std::string name);
        
        Node m_rootOfTheTree;
        std::vector<Node> m_nodeVector;
        
    private:
        std::vector<std::string> m_listOfDataTypes;
        
        Node * recursiveSearch(std::vector<unsigned int> vectorOfOID, unsigned int vectorPosition, Node * node);
        void initializeRootOfTheTree();
        void initializeListOfDataTypes();
    protected:
        
};

#endif /*TREE_HPP*/
