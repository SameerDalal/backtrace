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
#include <list>

class ContextNode;

class ContextTree;

void printStackTrace(int depth);
void symbolsParser(std::string symbols);
void createObjects(std::string functionName, std::string memoryAddress);
void assignParentAndChild(bool second, int iterations);
void buildTree();

void free();

// test functions
void test_1(int test);
void test_2();
void test_3();
void test_4_contextTree();

char **stack_symbols;

std::vector<ContextNode*> pointerArray;

int prev_stack_depth;

//initialize libunwind context and cursor
unw_context_t context;
unw_cursor_t cursor;


struct linkedList {
    std::string callee;
    std::string caller;
};


void printStackTrace(int start = 0) {

    std::vector<linkedList> callerCalleeList;

    const int max_depth = 128;
    void *stack_trace[max_depth];
    int stack_depth = backtrace(stack_trace, max_depth);
    stack_symbols = backtrace_symbols(stack_trace, stack_depth);
    
    std::reverse(stack_symbols, stack_symbols + stack_depth);

    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    unw_word_t instruction_pointer;
    unw_word_t program_counter;

    for(int i = start; i < stack_depth; i++) {
        
        symbolsParser(stack_symbols[i]);
        std::cout << stack_symbols[i] << std::endl;
        
        char proc_name_callee[64];

        char proc_name_caller[64];

        // get the function at the current frame
        unw_get_proc_name(&cursor, proc_name_callee, sizeof(proc_name_callee), &instruction_pointer);
        //std::cout << "Callee: " << proc_name_callee << std::endl;

        // go to next frame. Add if statement to catch errors
        unw_step(&cursor);

        // get the function at the updated frame 
        unw_get_proc_name(&cursor, proc_name_caller, sizeof(proc_name_caller), &instruction_pointer);
        //std::cout << "Caller: " << proc_name_caller << std::endl;

        callerCalleeList.insert(callerCalleeList.begin(), {proc_name_callee, proc_name_caller});
    }
    
    // assigns prev_stack_depth to the number of traces already in the tree
    prev_stack_depth = stack_depth;

    std::cout << std::endl;

    for (auto list : callerCalleeList) {
        std::cout << "Caller: " << list.caller << std::endl;
        std::cout << "Callee: " << list.callee << std::endl; 
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

void assignParentAndChild(bool second, int iterations = 0) {
    // needs cleanup
    for(int i = iterations; i < pointerArray.size(); i++) {

        if(iterations > 0) {
            if(second) {
                std::cout << "Parent of " << pointerArray[i]->functionName() << " is set to " << pointerArray[i-2]->functionName() << std::endl;
                pointerArray[i]->setParent(pointerArray[i-2]);

                std::cout << "Child of " << pointerArray[i-2]->functionName() << " is set to " << pointerArray[i]->functionName() << std::endl;
                pointerArray[i-2]->setChildren(pointerArray[i]);
                second = false;
            } else {
                std::cout << "Parent of " << pointerArray[i]->functionName() << " is set to " << pointerArray[i-1]->functionName() << std::endl;
                pointerArray[i]->setParent(pointerArray[i-1]);
            }
        } else {
            std::cout << "Parent of " << pointerArray[i]->functionName() << " is null" << std::endl;
            pointerArray[i]->setParent();
        }
        if(i+1 < pointerArray.size()) {
            std::cout << "Child of " << pointerArray[i]->functionName() << " is set to " << pointerArray[i+1]->functionName() << std::endl;
            pointerArray[i]->setChildren(pointerArray[i+1]);
        } else {
            std::cout << "Child of " << pointerArray[i]->functionName() << " is null" << std::endl;
            pointerArray[i]->setChildren();
        }
        iterations++;
    }
}


int main() {

    test_1(2);

    //clear mem
    free(stack_symbols);

    for (auto node : pointerArray) {
        delete node;
    }

    pointerArray.clear();
    
    return 0;
}

void test_1(int test) {
    std::cout << test << std::endl;
    test_2();
}

void test_2() {
    std::cout << "works" << std::endl << std::endl;

    // prints initial backtrace trace since this is the first trace we are printing
    printStackTrace();
    std::cout << std::endl;
    assignParentAndChild(false);

    std::cout << std::endl;

    test_3();
}

void test_3() {
    std::cout << "test2" << std::endl << prev_stack_depth << std::endl << std::endl;
    test_4_contextTree();
    
}

void test_4_contextTree() {

    // prints the additional traces (not repeating the original traces printed)
    std::cout << "Additional Trace: " << std::endl;
    printStackTrace(prev_stack_depth-1);
    std::cout << std::endl;
    assignParentAndChild(true, prev_stack_depth-2);

    std::cout << std::endl;
    //testing contextTree
    ContextNode c("234", "234");
    ContextTree d(c);
    d.buildTree();
    
    std::cout << std::endl;
    
    for (auto symbol : pointerArray) {
        std::cout << "| Function Name: " << symbol->functionName()
                  << " | Memory Address: " << symbol->memoryAddress() 
                  << " | Pointer: " << symbol 
                  << " | Parent: " << symbol->parentNodePointer()->functionName()
                  << " | Children: "; 
        for (auto child : symbol->childrenNodesPointer()) {
            std::cout << child->functionName() << ", ";
        }
        std::cout << std::endl << std::endl;
    }
}
