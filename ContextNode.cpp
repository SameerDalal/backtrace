#include <iostream>
#include "ContextNode.h"
#include <string>
#include <vector>

//private instance variables
//each node will store the symbols function name and memory address

ContextNode* parent;
std::string funcName;
void* object;

ContextNode::ContextNode(ContextNode* parent, std::string funcName, void* object){ 
    this->parent = parent;
    this->funcName = funcName;
    this->object = object;
}
/*
ContextNode::~ContextNode() {
    delete nullNode;
}
*/



// getters

std::string ContextNode::functionName() {
    return funcName;
};

void* ContextNode::classReference() {
    return object;
};

ContextNode* ContextNode::parentNode() {
    return parent;
}



// This class represents each node that will be part of the tree
// Another class should be built that takes a vector of the ContextNode and forms a tree.


