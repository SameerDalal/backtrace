#include <iostream>
#include <string>
#include "Backtrace.h"
#include <sstream>

void test_1(int test);
void test_2();
void test_3();
void test_4_contextTree();


Backtrace* bt = new Backtrace();


int main() {

    bt->start_func_call("main", nullptr);


    
    for(int i = 0; i < 5; i++) {
        bt->start_trace_call("test_1", "arg1", nullptr);
        test_1(i);
        bt->end_trace_call();
    }
   


    bt->start_trace_call("test_1", "i", nullptr);
    test_1(34);
    bt->end_trace_call();


    bt->end_func_call("main");

    //calling destructor
    bt->~Backtrace();


    return 0;
}

void test_1(int param1) {
    
    //can use (void*) but preferably convert all parameters to std::string
    bt->start_func_call("test_1", "int", "param1", std::to_string(param1).c_str(), nullptr);

    bt->start_trace_call("test_2", nullptr);

    test_2();

    bt->end_trace_call();


    bt->start_trace_call("test_3", nullptr);
    test_3();

    bt->end_trace_call();

    bt->end_func_call("test_1");
}

void test_2() {

    bt->start_func_call("test_2", nullptr);

    bt->start_trace_call("test_3", nullptr);
    test_3();

    bt->end_trace_call();

    bt->end_func_call("test_2");
}

void test_3() {

    bt->start_func_call("test_3", nullptr);

    bt->start_trace_call("test_4", nullptr);

    test_4_contextTree();

    bt->end_trace_call();

    bt->end_func_call("test_3");
}

void test_4_contextTree() {

}
