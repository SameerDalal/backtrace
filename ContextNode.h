#ifndef CONTEXTNODE_H
#define CONTEXTNODE_H

#include <string>
#include <vector>

class ContextNode {
    
private:

    ContextNode* parent;
    std::vector<ContextNode*> children;

    void* frame_addr;
    void* return_addr;
    std::string funcName;
    std::vector<std::string> arguments;
    

public:
    ContextNode(void* frame_addr, void* return_addr, std::string funcName, std::vector<std::string> arguments);
    ~ContextNode();

    void setChild(ContextNode* node);
    void removeChild();

    void setParentNode(ContextNode* node);

    std::string getFunctionName();
    ContextNode* getParentNode();

    std::vector<std::string> getArguments();

    std::vector<ContextNode*> getChildren();

    void* getFrameAddress();
    void* getReturnAddress();
    
};

#endif  // CONTEXTNODE_H
