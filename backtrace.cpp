#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <execinfo.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "contextnode.h"


void printStackTrace(int depth);
void symbolsParser(std::string symbols);
void foo(int test);
void free();
void bar();

char **stack_symbols;

class ContextNode;

void printStackTrace(int depth = 0) {
    const int max_depth = 128;
    void *stack_trace[max_depth];
    int stack_depth = backtrace(stack_trace, max_depth);

    std::cout << stack_depth << "\n" << std::endl;

    stack_symbols = backtrace_symbols(stack_trace, stack_depth);

    for(int i = depth; i < stack_depth; i++)
    {
        std::cout << stack_symbols[i] << std::endl;
        symbolsParser(stack_symbols[i]);
    }
}

// array of pointers that would store each context node
//each context node (considered to be a parent) can also have a child node
// the build the tree recusivley by parsing through the array


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
    // specifically stack allocation (not using heap allocation).
    ContextNode node(funcName, memAddress);

    // std::cout << node.functionName() + " " + node.memoryAddress() << std::endl;

    

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
    std::cout << "works" << std::endl;
    printStackTrace();
}



// #include <execinfo.h> header file is used to obtain the backtrace of a program
// to do this install `libunwind-dev` package

// sudo apt-get install libunwind-dev
// g++ -g program.cpp -o program.exe