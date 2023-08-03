#ifndef CONTEXTNODE_H
#define CONTEXTNODE_H

#include <string>
#include <vector>
#include <libunwind.h>


class ContextNode {
    
private:

    ContextNode* parent;
    std::vector<ContextNode*> children;

    void* frame_addr;
    void* return_addr;
    std::string funcName;
    unw_word_t start_ip;
    unw_word_t end_ip;
    unw_word_t lsda;
    unw_word_t handler; 
    unw_word_t global_pointer;
    unw_word_t flags;
    std::vector<std::string> parameters;
    std::vector<std::string> arguments;

    int callCount;
    

public:
    ContextNode(        void* frame_addr, 
                        void* return_addr, 
                        std::string funcName,
                        unw_word_t start_ip,
                        unw_word_t end_ip,
                        unw_word_t lsda,
                        unw_word_t handler,
                        unw_word_t global_pointer,
                        unw_word_t flags,
                        std::vector<std::string> parameters);
    ~ContextNode();

    void setChild(ContextNode* node);
    void removeChild();

    void setParentNode(ContextNode* node);

    std::string getFunctionName();
    ContextNode* getParentNode();

    std::vector<std::string> getParameters();

    std::vector<std::string> getArguments();

    std::vector<ContextNode*> getChildren();

    void setArguments(std::vector<std::string> args);

    void* getFrameAddress();
    void* getReturnAddress();

    void addCallCount(int val);

    int getCallCount();

    unw_word_t getStartIP() const;
    unw_word_t getEndIP() const;
    unw_word_t getLsda() const;
    unw_word_t getHandler() const;
    unw_word_t getGlobalPointer() const;
    unw_word_t getFlags() const;
    
};

#endif
