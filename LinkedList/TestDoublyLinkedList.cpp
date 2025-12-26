#include "TestDoublyLinkedList.h"
#include <iostream>
#include <cassert>

void TestDoublyLinkedList::testPushBack()
{
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    DoublyLinkedList<int> list_expected;
    list_expected.push_back(10);
    list_expected.push_back(20);
    list_expected.push_back(30);
    assert(list.length() == 3);
    assert(!list.isEmpty());
    assert(list == list_expected);
    // std::cout << "testPushBack passed." << std::endl;
}

void TestDoublyLinkedList::testPushFront()
{
    DoublyLinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    DoublyLinkedList<int> list_expected;
    list_expected.push_back(30);
    list_expected.push_back(20);
    list_expected.push_back(10);
    assert(list.length() == 3);
    assert(!list.isEmpty());
    assert(list == list_expected);

    // std::cout << "testPushFront passed." << std::endl;
}

void TestDoublyLinkedList::testPopFront()
{
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    DoublyLinkedList<int> list_expected;
    list_expected.push_back(20);
    list_expected.push_back(30);

    list.pop_front();
    assert(list.length() == 2);
    assert(list == list_expected);
    assert(list.isEmpty() == false);

    DoublyLinkedList<int> list_expected_2;
    list_expected_2.push_back(30);

    list.pop_front();
    assert(list.length() == 1);
    assert(list == list_expected_2);
    assert(list.isEmpty() == false);

    list.pop_front();
    assert(list.length() == 0);
    assert(list.isEmpty() == true);

    // std::cout << "testPopFront passed." << std::endl;
}

void TestDoublyLinkedList::testPopBack()
{
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    DoublyLinkedList<int> list_expected;
    list_expected.push_back(10);
    list_expected.push_back(20);

    list.pop_back();
    assert(list.length() == 2);
    assert(list == list_expected);
    assert(list.isEmpty() == false);

    DoublyLinkedList<int> list_expected_2;
    list_expected_2.push_back(10);

    list.pop_back();
    assert(list.length() == 1);
    assert(list == list_expected_2);
    assert(list.isEmpty() == false);

    list.pop_back();
    assert(list.length() == 0);
    assert(list.isEmpty() == true);

    // std::cout << "testPopBack passed." << std::endl;
}

void TestDoublyLinkedList::testIsEmpty()
{
    DoublyLinkedList<int> list;

    assert(list.isEmpty() == true);

    list.push_back(10);
    assert(list.isEmpty() == false);

    // std::cout << "testIsEmpty passed." << std::endl;
}

void TestDoublyLinkedList::testLength()
{
    DoublyLinkedList<int> list;

    assert(list.length() == 0);

    list.push_back(10);
    list.push_back(20);
    assert(list.length() == 2);

    list.pop_front();
    assert(list.length() == 1);

    list.pop_back();
    assert(list.length() == 0);

    // std::cout << "testLength passed." << std::endl;
}

void TestDoublyLinkedList::testPrintForward()
{
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    std::cout << "Forward print: ";
    list.printForward(); // This will print 10, 20, 30

    // Assuming printForward outputs to console, we can't assert on console output.
    // This is a placeholder to indicate the test.
    // std::cout << "testPrintForward passed." << std::endl;
}

void TestDoublyLinkedList::testPrintBackward()
{
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    std::cout << "Backward print: "; // This will print 30, 20, 10
    list.printBackward();

    // Assuming printBackward outputs to console, we can't assert on console output.
    // This is a placeholder to indicate the test.
    // std::cout << "testPrintBackward passed." << std::endl;
}

void TestDoublyLinkedList::testGetHeadValue()
{
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    assert(list.getHeadValue() == 10);

    list.pop_front();
    assert(list.getHeadValue() == 20);

    list.pop_front();
    assert(list.getHeadValue() == 30);

    list.pop_front();
    assert(list.isEmpty() == true);

    // After popping all elements, getHeadValue should return a default value (0 for int)
    assert(list.getHeadValue() == 0);

    // std::cout << "testGetHeadValue passed." << std::endl;
}

void TestDoublyLinkedList::testSwapWithNext()
{
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // Swap the first two nodes
    list.testSwapWithNext(list.getHead()); // Assuming testSwapWithNext is a public method for testing

    DoublyLinkedList<int> expectedList;
    expectedList.push_back(20);
    expectedList.push_back(10);
    expectedList.push_back(30);

    assert(list == expectedList);
    assert(list.length() == 3);
    assert(!list.isEmpty());

    list.testSwapWithNext(list.getHead());

    DoublyLinkedList<int> expectedList2;
    expectedList2.push_back(10);
    expectedList2.push_back(20);
    expectedList2.push_back(30);

    assert(list == expectedList2);
    assert(list.length() == 3);
    assert(!list.isEmpty());

    // std::cout << "testSwapWithNext passed." << std::endl;
}

void TestDoublyLinkedList::testReverse()
{
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    DoublyLinkedList<int> expectedReversedList;
    expectedReversedList.push_back(30);
    expectedReversedList.push_back(20);
    expectedReversedList.push_back(10);

    list.reverse(list);
    assert(list.length() == 3);
    assert(!list.isEmpty());
    assert(list == expectedReversedList);

    DoublyLinkedList<int> list1;
    for (int i = 1; i <= 100; i++)
    {
        list1.push_back(i * 10);
    }
    list1.reverse(list1);

    DoublyLinkedList<int> expectedReversedlist2;
    for (int i = 100; i >= 1; i--)
    {
        expectedReversedlist2.push_back(i * 10);
    }
    assert(list1.length() == 100);
    assert(!list1.isEmpty());
    assert(list1 == expectedReversedlist2);
    // std::cout << "Reversed print: ";
    // reversedList.printForward();

    // Assuming reverse outputs to console, we can't assert on console output.
    // This is a placeholder to indicate the test.
    // std::cout << "testReverse passed." << std::endl;
}

void TestDoublyLinkedList::testInsertionSort()
{
    DoublyLinkedList<int> list;
    list.push_back(30);
    list.push_back(10);
    list.push_back(20);

    DoublyLinkedList<int> expectedSortedList;
    expectedSortedList.push_back(10);
    expectedSortedList.push_back(20);
    expectedSortedList.push_back(30);

    list.insertion_sort();
    assert(list.length() == 3);
    assert(!list.isEmpty());
    assert(list == expectedSortedList);

    DoublyLinkedList<int> list1;
    for (int i = 10000; i >= 1; i--)
    {
        list1.push_back(i);
    }
    list1.insertion_sort();

    DoublyLinkedList<int> expectedReversedlist2;
    for (int i = 1; i <= 10000; i++)
    {
        expectedReversedlist2.push_back(i);
    }
    assert(list1.length() == 10000);
    assert(!list1.isEmpty());
    assert(list1 == expectedReversedlist2);
    // std::cout << "Sorted print: ";
    // sortedList.printForward();

    // Assuming insertion_sort outputs to console, we can't assert on console output.
    // This is a placeholder to indicate the test.
    std::cout << "testInsertionSort passed." << std::endl;
}

void TestDoublyLinkedList::runTests()
{
    testPushBack();
    testPushFront();
    testPopFront();
    testPopBack();
    testIsEmpty();
    testLength();
    testPrintForward();
    testPrintBackward();
    testGetHeadValue();
    testSwapWithNext();
    testReverse();
    testInsertionSort();
    std::cout << "All DoublyLinkedList tests passed!" << std::endl;
}