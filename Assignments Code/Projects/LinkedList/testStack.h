#ifndef TESTSTACK_H
#define TESTSTACK_H
#include <iostream>
#include "LinkedList.h"
#include "Stack.h"
using namespace std;
class TestStack
{
public:
    void runAllTests();
    void testPush();
    void testPop();
    void testCopyConstructor();
    void testAssignment();
    void testTop();
    void testEmpty();
    void testSize();
    void testEmptyPopTop();
    void additionalTests();
};
#endif