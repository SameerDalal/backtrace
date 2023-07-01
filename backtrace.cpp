#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <execinfo.h> //this library helps obtain the backtrace but does not give information about function calls
#include <libunwind.h> //this library gives information about function calls
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "ContextNode.h"
#include "ContextTree.h"
#include <vector>
#include <algorithm>

void printStackTrace(int depth);
void symbolsParser(std::string symbols);
void createObjects(std::string functionName, std::string memoryAddress);
void buildTree();

void free();

// test functions
void test_1(int test);
void test_2();
void test_3();
void test_4_contextTree();

char **stack_symbols;

// vector of pointers
std::vector<ContextNode*> pointerArray;

class ContextNode;

class ContextTree;

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


    //initialize libunwind context and cursor

    unw_context_t context;
    unw_cursor_t cursor;

    
    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    unw_word_t instruction_pointer;
    unw_word_t program_counter;

    while (unw_step(&cursor) != 0) {
        
        char proc_name[64];

        // get the function at the current frame
        unw_get_proc_name(&cursor, proc_name, sizeof(proc_name), &instruction_pointer);
        std::cout << "Caller: " << proc_name << std::endl;

        // go to next frame. Add if statement to catch errors
        unw_step(&cursor);

        // get the function at the updated frame 
        unw_get_proc_name(&cursor, proc_name, sizeof(proc_name), &instruction_pointer);
        std::cout << "Callee: " << proc_name << std::endl;
    }
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
    ContextNode* node = new ContextNode(functionName, memoryAddress);
    pointerArray.push_back(node);
}


int main() {
    test_1(2);

    printStackTrace(prev_stack_depth-1,1);

    //clear mem
    free(stack_symbols);

    for (auto node : pointerArray) {
        delete node;
    }

    pointerArray.clear();
    
    return 0;
}

void test_1(int test) {
    std::cout << test << "\n";
    test_2();
}

void test_2() {
    std::cout << "works" << std::endl << std::endl;

    // prints initial backtrace trace since this is the first trace we are printing
    printStackTrace();

    test_3();
}

void test_3() {
    std::cout << "test2" << std::endl;
    std::cout << prev_stack_depth << std::endl;
    test_4_contextTree();
    
}

void test_4_contextTree() {
    // prints the additional traces (not repeating the original traces printed)
    printStackTrace(prev_stack_depth-1,1);

    //testing contextTree
    ContextNode c("234", "234");
    ContextTree d(c);
    d.buildTree();
    
    std::cout << std::endl;

    for (auto element : pointerArray) {
        std::cout << element->functionName() << " " << element->memoryAddress() << " " << element << std::endl;
    } 
}
