#include "TestLinkedList.h"
#include "testStack.h"
#include "TestQueue.h"
#include "TestDoublyLinkedList.h"
#include <cassert>
#include <iostream>
int main()
{
    TestLinkedList tl;
    tl.runTests();
    TestStack ts;
    ts.runAllTests();
    TestDoublyLinkedList td;
    td.runTests();
    TestQueue tq;
    tq.runAllTests();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}