#ifndef BACKTRACE_H
#define BACKTRACE_H

#include "ContextNode.h"
#include <string>

class Backtrace {
private:
    
    ContextNode* btNode;
    Backtrace();
public:
    
    void* object;

    void startTrace(std::string funcName, void* object);
    void endTrace(std::string funcName);

    static Backtrace* getInstance();

    void printTrace();
};

static Backtrace* btInstance;

#endif // BACKTRACE_H
