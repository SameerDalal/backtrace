#include <iostream>
#include "ContextNode.h"
#include <string>
#include <vector>

//private instance variables
//each node will store the symbols function name and memory address


std::string funcName;

std::string memAddress;

std::vector<ContextNode> children;





ContextNode::ContextNode(std::string funcName, std::string memAddress, std::vector<ContextNode> children) 
    : funcName(funcName), memAddress(memAddress), children(children) {

}

// getters

std::string ContextNode::functionName() {
    return funcName;
};

std::string ContextNode::memoryAddress() {
    return memAddress;
};



// This class represents each node that will be part of the tree
// Another class should be built that takes a vector of the ContextNode and forms a tree.
