#include <iostream>
#include "ContextNode.h"
#include <string>
#include <vector>

//private instance variables
//each node will store the symbols function name and memory address
ContextNode* nullNode = new ContextNode("NULL", "NULL");

std::string funcName;
std::string memAddress;
ContextNode* parent;
std::vector<ContextNode*> children;


ContextNode::ContextNode(std::string funcName, std::string memAddress) 
    : funcName(funcName), memAddress(memAddress) {

}
/*
ContextNode::~ContextNode() {
    delete nullNode;
}
*/


// setters 
void ContextNode::setChildren(ContextNode* child) {
    if(child != nullptr) {
        children.insert(children.end(), child);
    }

}

void ContextNode::setParent(ContextNode* parent) {
    this->parent = parent;
}



// getters

std::string ContextNode::functionName() {
    return funcName;
};

std::string ContextNode::memoryAddress() {
    return memAddress;
};

ContextNode* ContextNode::parentNodePointer() {
    if(parent == nullptr) {
        return nullNode;
    } 
    return parent;
}

std::vector<ContextNode*> ContextNode::childrenNodesPointer() {
    if (children.size() == 0) {
        children.insert(children.end(), nullNode);
    }
    return children;
}



// This class represents each node that will be part of the tree
// Another class should be built that takes a vector of the ContextNode and forms a tree.


