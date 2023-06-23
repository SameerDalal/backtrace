#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <execinfo.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "contextnode.h"
#include <vector>
#include <algorithm>

void printStackTrace(int depth);
void symbolsParser(std::string symbols);
void createObjects(std::string functionName, std::string memoryAddress);
void buildTree();
void free();

// test functions
void foo(int test);
void bar();
void otherTest();
void otherOtherTest();

char **stack_symbols;

// vector of pointers
std::vector<ContextNode*> pointerArray;

class ContextNode;

int prev_stack_depth;

void printStackTrace(int start = 0, int end = 0) {

    const int max_depth = 128;
    void *stack_trace[max_depth];
    int stack_depth = backtrace(stack_trace, max_depth);

    stack_symbols = backtrace_symbols(stack_trace, stack_depth);
    
    std::reverse(stack_symbols, stack_symbols + stack_depth);

    for(int i = start; i < stack_depth - end; i++)
    {
        symbolsParser(stack_symbols[i]);
        std::cout << stack_symbols[i] << std::endl;
    }
    
    // assigns prev_stack_depth to the number of traces already in the tree
    prev_stack_depth = stack_depth;

}

/*
    array of pointers that would store each context node
    or each context node can also take into the constructor a child node - pointers would be needed so that you can print out each node of the tree
    each context node (considered to be a parent) can also have a child node
    then build the tree recursively by parsing through the array
*/

void symbolsParser(std::string symbols)
{
    //get symbol name
    size_t startIndex = symbols.find('(') + 1;
    size_t endIndex = symbols.find('+');

    std::string funcName = symbols.substr(startIndex, endIndex - startIndex);

    //get mem address
    startIndex = symbols.find('[', endIndex) + 1;
    endIndex = symbols.find(']', startIndex);

    std::string memAddress = symbols.substr(startIndex, endIndex - startIndex);
    //std::cout << node.functionName() + " " + node.memoryAddress() << std::endl << std::endl;
    createObjects(funcName, memAddress);
}

void createObjects(std::string functionName, std::string memoryAddress) {
    // specifically stack allocation (not using heap allocation).
    ContextNode node(functionName, memoryAddress);

    pointerArray.push_back(&node);
}

void buildTree() {
    // create another class to build tree
}


int main() {
    foo(2);

    free(stack_symbols);

    return 0;
}

void foo(int test) {
    std::cout << test << "\n";
    bar();
}

void bar() {
    std::cout << "works" << std::endl << std::endl;

    // prints initial backtrace trace since this is the first trace we are printing
    printStackTrace();

    otherTest();
}

void otherTest() {
    std::cout << "test2" << std::endl;
    std::cout << prev_stack_depth << std::endl;
    otherOtherTest();
    
}

void otherOtherTest() {
    // prints the additional traces (not repeating the original traces printed)
    printStackTrace(prev_stack_depth-1,1);
}












