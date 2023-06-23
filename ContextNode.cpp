#include <iostream>
#include "contextnode.h"

//private instance variables
//each node will store the symbols function name and memory address


    std::string funcName;
    
    std::string memAddress;



    ContextNode::ContextNode(std::string funcName, std::string memAddress) {
        this->funcName = funcName;
        this->memAddress = memAddress;
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
