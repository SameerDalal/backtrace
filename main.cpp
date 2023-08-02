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

    bt->start_trace("main", nullptr);

    test_1(5);

    bt->end_trace("main");

    //calling destructor
    bt->~Backtrace();


    return 0;
}

void test_1(int test) {
    
    //can use (void*) but preferably convert all parameters to std::string
    bt->start_trace("test_1", "int", "test", std::to_string(test).c_str());
    
    test_2();

    test_3();

    bt->end_trace("test_1");
}

void test_2() {

    bt->start_trace("test_2", nullptr);

    test_3();

    bt->end_trace("test_2");
}

void test_3() {

    bt->start_trace("test_3", nullptr);

    test_4_contextTree();

    bt->end_trace("test_3");
}

void test_4_contextTree() {

}
