#include <iostream>
#include "ContextNode.h"
#include <string>
#include <vector>


ContextNode* parent;
std::vector<ContextNode*> children;

void* frame_addr;
void* return_addr;
std::string funcName;
std::vector<std::string> arguments;


ContextNode::ContextNode(void* frame_addr, void* return_addr, std::string funcName, std::vector<std::string> arguments) { 
    
    this->frame_addr = frame_addr;
    this->return_addr = return_addr;
    this->funcName = funcName;
    this->arguments = arguments;
 
}

ContextNode::~ContextNode() {
    delete this;
}

void ContextNode::setChild(ContextNode* child) {
    children.push_back(child);
}

void ContextNode::setParentNode(ContextNode* node){
    parent = node;
}

// getters

std::string ContextNode::getFunctionName() {
    return funcName;
};

ContextNode* ContextNode::getParentNode() {
    return parent;
}

std::vector<std::string> ContextNode::getArguments() {
    return arguments;
}

std::vector<ContextNode*> ContextNode::getChildren() {
    return children;
}

void* ContextNode::getFrameAddress() {
    return frame_addr;
}

void* ContextNode::getReturnAddress() {
    return return_addr;
}


