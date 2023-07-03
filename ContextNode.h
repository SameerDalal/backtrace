#ifndef CONTEXTNODE_H
#define CONTEXTNODE_H

#include <string>
#include <vector>

class ContextNode {
private:
    std::string funcName;
    std::string memAddress;
    ContextNode* parent;
    ContextNode* child;
    std::vector<ContextNode*> children;


public:
    ContextNode(std::string funcName = "", std::string memAddress = "", ContextNode* parent = nullptr, ContextNode* children = nullptr);


    void addChildren();
    
    std::string functionName();
    std::string memoryAddress();
    ContextNode* parentNodePointer();
    std::vector<ContextNode*> childrenNodesPointer();
    
};

#endif  // CONTEXTNODE_H
