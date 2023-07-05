#ifndef CONTEXTNODE_H
#define CONTEXTNODE_H

#include <string>
#include <vector>

class ContextNode {
    
private:
    std::string funcName;
    std::string memAddress;
    ContextNode* parent;
    std::vector<ContextNode*> children;

public:
    ContextNode(std::string funcName = "", std::string memAddress = "");
    //~ContextNode();

    void setChildren(ContextNode* child = nullptr);
    void setParent(ContextNode* parent = nullptr);
    
    std::string functionName();
    std::string memoryAddress();
    ContextNode* parentNodePointer();
    std::vector<ContextNode*> childrenNodesPointer();
    
};

#endif  // CONTEXTNODE_H
