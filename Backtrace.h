#pragma once

#include "ContextNode.h"
#include <string>
#include <vector>
#include <fstream>
#include <stdarg.h>
#include <cstdarg>



class Backtrace {

private:

    ContextNode* initNode;

    std::vector<ContextNode*> nodes;

    std::vector<std::string> parse_arg_arr(std::vector<std::string> array);
    
    void write_to_dot();

public:

    Backtrace();
    ~Backtrace();

    void start_func_call(std::string funcName, ...);

    void start_trace_call(int ID, std::string funcName, ...);

    void end_trace_call();

    void end_func_call(std::string funcName);

    
};

#include "Backtrace.tpp" 