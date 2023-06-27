#ifndef CONTEXTNODE_H
#define CONTEXTNODE_H

#include <string>
#include <vector>

class ContextNode {
private:
    std::string funcName;
    std::string memAddress;
    
    std::vector<ContextNode> children;


public:
    ContextNode(std::string funcName = "", std::string memAddress = "", std::vector<ContextNode> children = {});

    std::string functionName();
    std::string memoryAddress();
};

#endif  // CONTEXTNODE_H
