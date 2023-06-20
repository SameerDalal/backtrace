#ifndef CONTEXTNODE_H
#define CONTEXTNODE_H

#include <string>

class ContextNode {
private:
    std::string funcName;
    std::string memAddress;

public:
    ContextNode(std::string funcName, std::string memAddress);

    std::string functionName();
    std::string memoryAddress();
};

#endif  // CONTEXTNODE_H
