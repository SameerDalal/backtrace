#pragma once

#include "ContextNode.h"
#include <string>
#include <vector>
#include <fstream>

class Backtrace {

private:

    ContextNode* initNode;

    std::vector<std::string> argArr;

    std::vector<std::string> parse_arg_arr();
   
    template <typename T>
    void print_argument(const T& arg);

    template <typename T, typename... Args>
    void print_argument(const T& arg, const Args&... args);

public:

    Backtrace();
    ~Backtrace();

    void* object;

    template <typename... Args>
    void start_trace(void* frame_addr, void* return_addr, const std::string& funcName, const Args&... args);

    // function overload if there are no arguments
    void start_trace(void* frame_addr, void* return_addr, const std::string& funcName);

    void end_trace(std::string funcName);

    void write_to_dot();
};

#include "Backtrace.tpp" 