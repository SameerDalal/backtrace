#include "Backtrace.h"
#include "ContextNode.h"
#include <string>
#include <iostream>

ContextNode* btNode;

Backtrace::Backtrace() {
}

void Backtrace::startTrace(std::string funcName, void* object) {
    ContextNode* node = new ContextNode(btNode, funcName, object);
    btNode = node;
}
void Backtrace::endTrace(std::string funcName) {
    btNode = btNode->parentNode();
}

Backtrace* Backtrace::getInstance() {
    if(btInstance == nullptr) {
        btInstance = new Backtrace();
    }
    return btInstance;
}

void Backtrace::printTrace() {
    ContextNode* tempNode = btNode;
    while (tempNode != nullptr) {
        std::cout << tempNode->functionName() << std::endl;
        tempNode = tempNode->parentNode();
    }
    
}
