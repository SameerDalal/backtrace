#include "Backtrace.h"
#include "ContextNode.h"
#include <string>
#include <iostream>
#include <fstream>

ContextNode* initNode;

std::vector<std::string> argArr;

std::ofstream dotFileWrite("tree.dot");

Backtrace::Backtrace() {

    initNode = new ContextNode(nullptr, nullptr, "NULL", {});
    dotFileWrite << "digraph ContextTree {" << std::endl;

}

Backtrace::~Backtrace() {
    dotFileWrite << "}" << std::endl;
    dotFileWrite.close();
}

// parsing arguments from individual elements to arguments in one string. 
// Example:
// {"int", "test", 5, bool "test2", false} to {"int test = 5", "bool test2 = false"}
std::vector<std::string> Backtrace::parse_arg_arr() {
    std::vector<std::string> parsedArr;
    
    for(int i = 0; i < argArr.size()-2; i+=3) {
        parsedArr.push_back(argArr[i] + " " + argArr[i+1] + " = " + argArr[i+2]);
    }
    return parsedArr;
}


template <typename T>
void Backtrace::print_argument(const T& arg) {
    argArr.push_back(arg);
}

template <typename T, typename... Args>
void Backtrace::print_argument(const T& arg, const Args&... args) {
    argArr.push_back(arg);
    print_argument(args...);
}

template <typename... Args>
void Backtrace::start_trace(void* frame_addr, void* return_addr, const std::string& funcName, const Args&... args) {

    print_argument(args...);

    ContextNode* node = new ContextNode(frame_addr, return_addr, funcName, parse_arg_arr());
    
    initNode->setChild(node);
    
    node->setParentNode(initNode);
    
    initNode = node;
}

// function overload if there are no arguments
void Backtrace::start_trace(void* frame_addr, void* return_addr, const std::string& funcName) {
    
    ContextNode* node = new ContextNode(frame_addr, return_addr, funcName, {});
    
    initNode->setChild(node);
    
    node->setParentNode(initNode);
    
    initNode = node;
}

// could be used to pass return values into function
void Backtrace::end_trace(std::string funcName) {
    write_to_dot();
    initNode = initNode->getParentNode();
}


void Backtrace::write_to_dot() {

    if (initNode->getFunctionName() == "NULL" || initNode == nullptr) {
        std::cout << "The tree is empty." << std::endl;
        return;
    }

    dotFileWrite << "node" << initNode->getFunctionName() << 
      " [label=\"" << initNode->getFunctionName() <<
      "\\n Frame Address: 0x" << std::hex << initNode->getFrameAddress() << 
      "\\n Return Address: 0x" << std::hex << initNode->getReturnAddress() 
    << "\"];" << std::endl;

    if(initNode->getArguments().size() > 0) {
        for(auto params : initNode->getArguments()) {
            dotFileWrite << "node" << initNode->getParentNode()->getFunctionName() << " -> node" << initNode->getFunctionName() << " [label=\" "; 
            dotFileWrite << params << ", ";
            dotFileWrite << "\"];" << std::endl;
        }
    } else {
      // for functions that dont have parameters
        dotFileWrite << "node" << initNode->getParentNode()->getFunctionName() << " -> node" << initNode->getFunctionName() << std::endl;
    }
}


