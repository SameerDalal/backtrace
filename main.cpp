#include <iostream>
#include <string>
#include "Backtrace.h"
#include <sstream>

void test_1(int test1, int test2);
void test_2();
void test_3();
void test_4_contextTree();



int main() {
    bootstrap();
    for(int i = 0; i < 1000; i++) {
        trace_func_call("test_1", 2, "test1:i", "test2:i");
        test_1(i, i);
        trace_func_call_end();
    }

    trace_func_call("test_1", 2, "test1:34", "test2:25");
    test_1(34, 25);
    trace_func_call_end();
    
    trace_func_call("test_2", 0);
    test_2();
    trace_func_call_end();
    
    finalize();
    return 0;
}

void test_1(int test1, int test2) {
    trace_func_call("test_2", 0);
    test_2();
    trace_func_call_end();

    trace_func_call("test_3", 0);
    test_3();
    trace_func_call_end();
}


void test_2() {
    trace_func_call("test_3", 0);
    test_3();
    trace_func_call_end();
}

void test_3() {
    trace_func_call("test_4_contextTree", 0);
    test_4_contextTree();
    trace_func_call_end();
}

void test_4_contextTree() {

}
