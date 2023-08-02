#include "Backtrace.h"
#include "ContextNode.h"
#include <string>
#include <iostream>
#include <fstream>
#include <libunwind.h>
#include <cxxabi.h>
#include <cstdarg>
#include <algorithm>


ContextNode* initNode;

std::vector<ContextNode*> nodes;


std::ofstream dotFileWrite("tree.dot");

unw_context_t context;
unw_cursor_t cursor;




Backtrace::Backtrace() {

    initNode = new ContextNode(nullptr, nullptr, "NULL", {}, {}, {}, {}, {}, {}, {});
    dotFileWrite << "digraph ContextTree {" << std::endl;

}

Backtrace::~Backtrace() {
    dotFileWrite << "}" << std::endl;
    dotFileWrite.close();

    //delete initNode
}


// parsing arguments from individual elements to arguments in one string. 
// Example:
// {"int", "test", 5, bool "test2", false} to {"int test = 5", "bool test2 = false"}
std::vector<std::string> Backtrace::parse_arg_arr(std::vector<std::string> array) {
    if(array.size() < 1) {
        return {};
    }

    std::vector<std::string> parsedArr;
    for(int i = 0; i < array.size()-2; i+=3) {
        parsedArr.push_back(array[i] + " " + array[i+1] + " = " + array[i+2]);
    }
    return parsedArr;
}


void Backtrace::start_trace_call(std::string funcName, ...) {

    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    unw_word_t offset, pc;
    unw_get_reg(&cursor, UNW_REG_IP, &pc);

    unw_step(&cursor);
    
    unw_proc_info_t proc_info;
    unw_get_proc_info(&cursor, &proc_info);

    char proc_name[128];

    unw_get_proc_name(&cursor, proc_name, sizeof(proc_name), &offset);

    for (const auto& node : nodes) {
        if (node->getStartIP() == proc_info.start_ip) {
            std::cout << "True" << std::endl;
            std::cout <<  node->getFunctionName() << std::endl;
            std::cout << node->getCallCount() << std::endl;
            node->setCallCount();
            std::cout << node->getCallCount() << std::endl << std::endl;
        }
    }
    
    va_list argp;
    va_start(argp, funcName);

    std::vector<std::string> argument_array;

    const char* value;
    while ((value = va_arg(argp, const char*)) != nullptr) {
        
        argument_array.push_back(value);
        
    }

    va_end(argp);


    initNode->setArguments(argument_array);

}

void Backtrace::end_trace_call() {

}


void Backtrace::start_func_call(std::string funcName, ...) {
    
    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    unw_word_t offset, pc;
    unw_get_reg(&cursor, UNW_REG_IP, &pc);

    unw_step(&cursor);
    
    unw_proc_info_t proc_info;
    unw_get_proc_info(&cursor, &proc_info);

    std::vector<std::string> parameter_array;

    va_list argp;
    va_start(argp, funcName);

    const char* value;
    while ((value = va_arg(argp, const char*)) != nullptr) {
        parameter_array.push_back(value);
    }

    va_end(argp);


    
    ContextNode* node = new ContextNode(
                                        __builtin_frame_address(1),
                                        __builtin_extract_return_addr(__builtin_return_address(1)), 
                                        funcName,
                                        proc_info.start_ip, 
                                        proc_info.end_ip, 
                                        proc_info.lsda, 
                                        proc_info.handler, 
                                        proc_info.gp, 
                                        proc_info.flags,
                                        parse_arg_arr(parameter_array));

    
    nodes.push_back(node);

    initNode->setChild(node);
    
    node->setParentNode(initNode);
    
    initNode = node;

}


// could be used to pass return values into function
void Backtrace::end_func_call(std::string funcName) {
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
      "\\n Return Address: 0x" << std::hex << initNode->getReturnAddress() <<
      "\\n StartIP: 0x" << std::hex << initNode->getStartIP() <<
      "\\n EndIP: 0x" << std::hex << initNode->getEndIP() << 
      "\\n LSDA: 0x" << std::hex << initNode->getLsda() << 
      "\\n Handler: 0x" << std::hex << initNode->getHandler() <<
      "\\n Global Pointer: 0x" << std::hex << initNode->getGlobalPointer() <<
      "\\n Flags:" << initNode->getFlags() <<
      "\"];" << std::endl;

    if(initNode->getParameters().size() > 0) {
        int counter = 0;
        for(auto params : initNode->getParameters()) {
            dotFileWrite << "node" << initNode->getParentNode()->getFunctionName() << " -> node" << initNode->getFunctionName() << " [label=\" "; 
            dotFileWrite << initNode->getParentNode()->getCallCount() << ":" << params << " --> " << initNode->getParentNode()->getArguments()[counter];
            dotFileWrite << "\"];" << std::endl;
            counter++;
        }
    } else {
      // for functions that dont have parameters
        dotFileWrite << "node" << initNode->getParentNode()->getFunctionName() << " -> node" << initNode->getFunctionName() << std::endl;
    }
}

