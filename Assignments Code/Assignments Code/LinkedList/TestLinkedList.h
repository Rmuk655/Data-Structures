#ifndef TESTLINKEDLIST_H
#define TESTLINKEDLIST_H
#include "LinkedList.h"
#include <iostream>
class TestLinkedList
{
public:
    void test_push_back_and_length();
    void test_push_front_and_pop_front();
    void test_isEmpty();
    void test_print_empty();
    void test_print_nonempty();
    void test_mixed_operations();
    void test_search_found();
    void test_search_not_found();
    void test_search_empty();
    void test_delete_middle();
    void test_delete_head();
    void test_delete_tail();
    void test_delete_only_element();
    void test_delete_not_found();
    void test_delete_empty();
    void test_LinkedList_sorting();
    void runTests();
};
#endif