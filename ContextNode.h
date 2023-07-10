#ifndef CONTEXTNODE_H
#define CONTEXTNODE_H

#include <string>
#include <vector>

class ContextNode {
    
private:

    ContextNode* parent;
    std::string funcName;
    void* object;
    

public:
    ContextNode(ContextNode* parent, std::string funcName, void* object);
    //~ContextNode();

    void setChild(ContextNode* node);
    void removeChild();
    
    std::string functionName();
    void* classReference();
    ContextNode* parentNode();
    
};

#endif  // CONTEXTNODE_H
