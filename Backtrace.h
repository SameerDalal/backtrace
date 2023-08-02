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
    
    void write_to_dot();

public:

    Backtrace();
    ~Backtrace();

    void start_trace(std::string funcName, ...);

    void end_trace(std::string funcName);

    
};

#include "Backtrace.tpp" 