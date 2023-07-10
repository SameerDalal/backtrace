#include <iostream>
#include <string>
#include "Backtrace.h"

void test_1(int test);
void test_2();
void test_3();
void test_4_contextTree();

class Backtrace;

int main() {
        

    Backtrace* bt = Backtrace::getInstance();
    bt->printTrace();
    bt->startTrace("main", nullptr);


    test_1(2);

    bt->endTrace("main");

    return 0;
}

void test_1(int test) {
    Backtrace* bt = Backtrace::getInstance();
    bt->startTrace("test_1", nullptr);

    std::cout << test << std::endl;
    test_2();

    bt->endTrace("main");
}

void test_2() {
    Backtrace* bt = Backtrace::getInstance();
    bt->startTrace("test_2", nullptr);

    std::cout << "works" << std::endl << std::endl;
    bt->printTrace();

    test_3();

    std::cout << bt->object << std::endl;
    
    std::cout << std::endl;

    bt->endTrace("test_2");
}

void test_3() {
    Backtrace* bt = Backtrace::getInstance();
    bt->startTrace("test_3", nullptr);

    test_4_contextTree();

    bt->endTrace("test_2");
}

void test_4_contextTree() {

}
