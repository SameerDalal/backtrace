#pragma once

#include "ContextNode.h"
#include <string>
#include <vector>
#include <fstream>
#include <stdarg.h>

class Backtrace {

private:

    ContextNode* initNode;

    std::vector<std::string> argArr;

    std::vector<std::string> parse_arg_arr();
   

public:

    Backtrace();
    ~Backtrace();

    void* object;

    void start_trace(void* frame_addr, void* return_addr, const std::string funcName, ...);

    // function overload if there are no arguments
    void start_trace(void* frame_addr, void* return_addr, const char* funcName);

    void end_trace(std::string funcName);

    void write_to_dot();
};

#include "Backtrace.tpp" 