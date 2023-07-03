#include <iostream>
#include "ContextNode.h"
#include <string>
#include <vector>

//private instance variables
//each node will store the symbols function name and memory address

std::string funcName;
std::string memAddress;
ContextNode* parent;
ContextNode* child;
std::vector<ContextNode*> children;


ContextNode::ContextNode(std::string funcName, std::string memAddress, ContextNode* parent, ContextNode* child) 
    : funcName(funcName), memAddress(memAddress), parent(parent), child(child) {


   

}

void addChildren() {
    children.insert(children.end(), child);
    // for some reason libunwind library does not display proper caller and callee functions when this is used instead:
    // children.push_back(child);
}


// getters

std::string ContextNode::functionName() {
    return funcName;
};

std::string ContextNode::memoryAddress() {
    return memAddress;
};

ContextNode* ContextNode::parentNodePointer() {
    return parent;
}

std::vector<ContextNode*> ContextNode::childrenNodesPointer() {
    return children;
}



// This class represents each node that will be part of the tree
// Another class should be built that takes a vector of the ContextNode and forms a tree.


