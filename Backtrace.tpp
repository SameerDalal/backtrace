#include "Backtrace.h"
#include "ContextNode.h"
#include <string>
#include <iostream>
#include <fstream>
#include <libunwind.h>
#include <cxxabi.h>

ContextNode* initNode;

std::vector<std::string> argArr;

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
std::vector<std::string> Backtrace::parse_arg_arr() {
    if(argArr.size() < 1) {
        return {};
    }

    std::vector<std::string> parsedArr;
    for(int i = 0; i < argArr.size()-2; i+=3) {
        parsedArr.push_back(argArr[i] + " " + argArr[i+1] + " = " + argArr[i+2]);
    }
    return parsedArr;
}


void Backtrace::start_trace(std::string funcName, ...) {
    
    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    unw_word_t offset, pc;
    unw_get_reg(&cursor, UNW_REG_IP, &pc);

    unw_step(&cursor);
    
    unw_proc_info_t proc_info;
    unw_get_proc_info(&cursor, &proc_info);


    va_list argp;
    va_start(argp, funcName);

    const char* value;
    while ((value = va_arg(argp, const char*)) != nullptr) {
        argArr.push_back(value);
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
                                        parse_arg_arr());
    
    initNode->setChild(node);
    
    node->setParentNode(initNode);
    
    initNode = node;

    argArr.clear();
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
      "\\n Return Address: 0x" << std::hex << initNode->getReturnAddress() <<
      "\\n StartIP: 0x" << std::hex << initNode->getStartIP() <<
      "\\n EndIP: 0x" << std::hex << initNode->getEndIP() << 
      "\\n LSDA: 0x" << std::hex << initNode->getLsda() << 
      "\\n Handler: 0x" << std::hex << initNode->getHandler() <<
      "\\n Global Pointer: 0x" << std::hex << initNode->getGlobalPointer() <<
      "\\n Flags:" << initNode->getFlags() <<
      "\"];" << std::endl;

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

