#include "TestLinkedList.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "../Rational/Rational.h"

void TestLinkedList::test_push_back_and_length()
{
    LinkedList<float> list;
    assert(list.length() == 0);
    list.push_back(10.0);
    // list.print(); // Should print 10.0
    assert(list.length() == 1);
    list.push_back(20.0);
    // list.print(); // Should print 10.0 20.0
    assert(list.length() == 2);
}

void TestLinkedList::test_push_front_and_pop_front()
{
    LinkedList<float> list;
    list.push_front(5.0);
    // list.print(); // Should print 5.0
    assert(list.length() == 1);
    list.push_front(3.0);
    // list.print(); // Should print 3.0 5.0
    assert(list.length() == 2);
    list.pop_front();
    // list.print(); // Should print 5.0
    assert(list.length() == 1);
    list.pop_front();
    // list.print(); // Should print nothing or a message
    assert(list.length() == 0);
    // Boundary: pop from empty list
    list.pop_front(); // Should not crash
    // list.print();     // Should print nothing or a message
    assert(list.length() == 0);
}

void TestLinkedList::test_isEmpty()
{
    LinkedList<float> list;
    assert(list.isEmpty());
    list.push_back(1.0);
    // list.print(); // Should print 1.0
    assert(!list.isEmpty());
    list.pop_front();
    // list.print(); // Should print nothing or a message
    assert(list.isEmpty());
}

void TestLinkedList::test_print_empty()
{
    LinkedList<float> list;
    // list.print(); // Should print nothing or a message
}

void TestLinkedList::test_print_nonempty()
{
    LinkedList<float> list;
    list.push_back(1.0);
    // list.print(); // Should print 1.0
    list.push_front(0.0);
    // list.print(); // Should print 0.0 1.0
}

void TestLinkedList::test_mixed_operations()
{
    LinkedList<float> list;
    list.push_back(1.0);
    // list.print(); // Should print 1.0
    list.push_front(0.0);
    // list.print(); // Should print 0.0 1.0
    list.push_back(2.0);
    // list.print(); // Should print 0.0 1.0 2.0
    assert(list.length() == 3);
    list.pop_front();
    // list.print(); // Should print 1.0 2.0
    assert(list.length() == 2);
    list.pop_front();
    // list.print(); // Should print 2.0
    list.pop_front();
    // list.print(); // Should print nothing or a message
    assert(list.isEmpty());
}

void TestLinkedList::test_search_found()
{
    LinkedList<float> list;
    list.push_back(1.0);
    list.push_back(2.0);
    list.push_back(3.0);
    // list.print();             // Should print 1.0 2.0 3.0
    assert(list.search(2.0)); // Should find 2.0 (middle)
    assert(list.search(1.0)); // Should find 1.0 (head)
    assert(list.search(3.0)); // Should find 3.0 (tail)
}

void TestLinkedList::test_search_not_found()
{
    LinkedList<float> list;
    list.push_back(1.0);
    list.push_back(2.0);
    assert(!list.search(3.0));  // 3.0 not in list
    assert(!list.search(-1.0)); // -1.0 not in list
}

void TestLinkedList::test_search_empty()
{
    LinkedList<float> list;
    assert(!list.search(1.0)); // Empty list, should not find anything
}

void TestLinkedList::test_delete_middle()
{
    LinkedList<float> list;
    list.push_back(1.0);
    list.push_back(2.0);
    list.push_back(3.0);
    // list.print();          // Should print 1.0 2.0 3.0
    assert(list.del(2.0)); // Delete middle element
    // list.print();          // Should print 1.0 3.0
    assert(!list.search(2.0));
    // list.print(); // Should print 1.0 3.0
    assert(list.length() == 2);
    // list.print(); // Should print 1.0 3.0
}

void TestLinkedList::test_delete_head()
{
    LinkedList<float> list;
    list.push_back(1.0);
    list.push_back(2.0);
    // list.print();          // Should print 1.0 2.0
    assert(list.del(1.0)); // Delete head
    // list.print();          // Should print 2.0
    assert(!list.search(1.0));
    // list.print(); // Should print 2.0
    assert(list.length() == 1);
    // list.print(); // Should print 2.0
}

void TestLinkedList::test_delete_tail()
{
    LinkedList<float> list;
    list.push_back(1.0);
    list.push_back(2.0);
    // list.print();          // Should print 1.0 2.0
    assert(list.del(2.0)); // Delete tail
    // list.print();          // Should print 1.0
    assert(!list.search(2.0));
    // list.print(); // Should print 1.0
    assert(list.length() == 1);
    // list.print(); // Should print 1.0
}

void TestLinkedList::test_delete_only_element()
{
    LinkedList<float> list;
    list.push_back(1.0);
    // list.print();          // Should print 1.0
    assert(list.del(1.0)); // Delete only element
    // list.print();          // Should print nothing or a message
    assert(list.isEmpty());
    // list.print(); // Should print nothing or a message
}

void TestLinkedList::test_delete_not_found()
{
    LinkedList<float> list;
    list.push_back(1.0);
    list.push_back(2.0);
    // list.print();
    assert(!list.del(3.0)); // 3.0 not in list
    // list.print();           // Should print 1.0 2.0
    assert(list.length() == 2);
    // list.print(); // Should print 1.0 2.0
}

void TestLinkedList::test_delete_empty()
{
    LinkedList<float> list;
    assert(!list.del(1.0)); // Delete from empty list
    // list.print();           // Should print nothing or a message
    assert(list.isEmpty());
    // list.print(); // Should print nothing or a message
}

void TestLinkedList::test_LinkedList_sorting()
{
    // Case 1: Unreduced Rational numbers
    LinkedList<Rational> list1;
    Rational r11(2, 1);
    Rational r12(1, 1);
    Rational r13(15, 3);
    Rational r14(24, 8);
    list1.push_back(r11);
    list1.push_back(r12);
    list1.push_back(r13);
    list1.push_back(r14);
    list1.insertionSort();
    // list1.print(); // Should print 1 2 3 5
    LinkedList<Rational> list_expected;
    list_expected.push_back(r12);
    list_expected.push_back(r11);
    list_expected.push_back(r14);
    list_expected.push_back(r13);
    assert(list1 == list_expected); // Check if the sorted list matches expected
    // Case 2: Duplicate Rational numbers
    LinkedList<Rational> list2;
    Rational r21(1, 2);
    Rational r22(2, 4);
    Rational r23(3, 6);
    list2.push_back(r21);
    list2.push_back(r22);
    list2.push_back(r23);
    list2.insertionSort();
    LinkedList<Rational> list_expected2;
    list_expected2.push_back(r21);
    list_expected2.push_back(r22);
    list_expected2.push_back(r23);
    assert(list2 == list_expected2);
    // list2.print(); // Should print 1/2 2/4 3/6
    //  Case 3: Already sorted list of Rational numbers
    LinkedList<Rational> list3;
    Rational r31(1, 5);
    Rational r32(2, 5);
    Rational r33(3, 5);
    Rational r34(4, 5);
    list3.push_back(r31);
    list3.push_back(r32);
    list3.push_back(r33);
    list3.push_back(r34);
    list3.insertionSort();
    LinkedList<Rational> list_expected3;
    list_expected3.push_back(r31);
    list_expected3.push_back(r32);
    list_expected3.push_back(r33);
    list_expected3.push_back(r34);
    assert(list3 == list_expected3);
    // list3.print(); // Should print 1/5 2/5 3/5 4/5
    //  Case 4: Reverse sorted list of Rational numbers
    LinkedList<Rational> list4;
    Rational r41(4, 5);
    Rational r42(3, 5);
    Rational r43(2, 5);
    Rational r44(1, 5);
    list4.push_back(r41);
    list4.push_back(r42);
    list4.push_back(r43);
    list4.push_back(r44);
    list4.insertionSort();
    LinkedList<Rational> list_expected4;
    list_expected4.push_back(r44);
    list_expected4.push_back(r43);
    list_expected4.push_back(r42);
    list_expected4.push_back(r41);
    assert(list4 == list_expected4);
    // list4.print(); // Should print 1/5 2/5 3/5 4/5
    //  Case 5: Mixed positive and negative Rational numbers
    LinkedList<Rational> list5;
    Rational r51(-1, 3);
    Rational r52(2, 3);
    Rational r53(-2, 5);
    Rational r54(1, 2);
    list5.push_back(r51);
    list5.push_back(r52);
    list5.push_back(r53);
    list5.push_back(r54);
    list5.insertionSort();
    LinkedList<Rational> list_expected5;
    list_expected5.push_back(r53);
    list_expected5.push_back(r51);
    list_expected5.push_back(r54);
    list_expected5.push_back(r52);
    assert(list5 == list_expected5);
    // list5.print(); // Should print -2/5 -1/3 1/2 2/3
    //  Case 6: Generate Random 100 Rational numbers, insert them into a linked list and insert sort them.
    //  Use assert to check if the list is sorted correctly.
    LinkedList<Rational> list6;
    std::vector<Rational> vector_expected_6;
    for (int i = 0; i < 10000; ++i)
    {
        int numerator = rand() % 10000;       // Random numerator between 0 and 99
        int denominator = rand() % 10000 + 1; // Random denominator between 1 and 100
        Rational r(numerator, denominator);
        list6.push_back(r);
        vector_expected_6.push_back(r);
    }
    // auto start_linked = std::chrono::high_resolution_clock::now();
    list6.insertionSort();
    // auto end_linked = std::chrono::high_resolution_clock::now();
    //  auto duration_linked = std::chrono::duration_cast<std::chrono::microseconds>(end_linked - start_linked).count();
    //   std::cout << "LinkedList sort time: " << duration_linked << " microseconds" << std::endl;

    // auto start_vector = std::chrono::high_resolution_clock::now();
    std::sort(vector_expected_6.begin(), vector_expected_6.end());
    // auto end_vector = std::chrono::high_resolution_clock::now();
    //  auto duration_vector = std::chrono::duration_cast<std::chrono::microseconds>(end_vector - start_vector).count();
    //   std::cout << "Vector sort time: " << duration_vector << " microseconds" << std::endl;
    Node<Rational> *node = list6.getHead(); // You should have a method like getHead()
    for (int i = 0; i < 10000; i++)
    {
        assert(node != nullptr); // Just in case
        assert(node->data == vector_expected_6[i]);
        node = node->next;
    }
    // Case 7: Rational numbers with large gcd of numerator and denominator
    LinkedList<Rational> list7;
    Rational r71(100, 200);
    Rational r72(300, 600);
    Rational r73(150, 300);
    list7.push_back(r71);
    list7.push_back(r72);
    list7.push_back(r73);
    list7.insertionSort();
    LinkedList<Rational> list_expected7;
    list_expected7.push_back(r73);
    list_expected7.push_back(r71);
    list_expected7.push_back(r72);
    assert(list7 == list_expected7);
    // list7.print(); // Should print 150/300 100/200 300/600
    //  Case 8: Mix of reduced and unreduced Rational numbers
    LinkedList<Rational> list8;
    Rational r81(1, 2);
    Rational r82(2, 4);
    Rational r83(4, 8);
    Rational r84(3, 6);
    Rational r85(5, 10);
    list8.push_back(r81);
    list8.push_back(r82);
    list8.push_back(r83);
    list8.push_back(r84);
    list8.push_back(r85);
    list8.insertionSort();
    LinkedList<Rational> list_expected8;
    list_expected8.push_back(r81);
    list_expected8.push_back(r82);
    list_expected8.push_back(r84);
    list_expected8.push_back(r83);
    list_expected8.push_back(r85);
    assert(list8 == list_expected8);
    // list8.print(); // Should print 1/2 2/4 3/6 4/8 5/10
    //  Case 9: Rational numbers including zero numerator
    LinkedList<Rational> list9;
    Rational r91(0, 1);
    Rational r92(1, 2);
    Rational r93(-1, 2);
    Rational r94(0, 5);
    list9.push_back(r91);
    list9.push_back(r92);
    list9.push_back(r93);
    list9.push_back(r94);
    list9.insertionSort();
    LinkedList<Rational> list_expected9;
    list_expected9.push_back(r93);
    list_expected9.push_back(r91);
    list_expected9.push_back(r94);
    list_expected9.push_back(r92);
    assert(list9 == list_expected9);
    // list9.print(); // Should print -1/2 0/1 0/5 1/2
    //  Case 10: Edge case: Single Rational number
    LinkedList<Rational> list10;
    Rational r101(3, 7);
    list10.push_back(r101);
    list10.insertionSort();
    LinkedList<Rational> list_expected10;
    list_expected10.push_back(r101);
    assert(list10 == list_expected10);
    // list10.print(); // Should print 3/7
    //  Case 11: Worst case scenario for insertion sort
    //  where the list is sorted in reverse order
    LinkedList<Rational> list11;
    Rational r111(1, 1);
    Rational r112(3, 4);
    Rational r113(1, 2);
    Rational r114(1, 3);
    Rational r115(1, 4);
    list11.push_back(r111);
    list11.push_back(r112);
    list11.push_back(r113);
    list11.push_back(r114);
    list11.push_back(r115);
    list11.insertionSort();
    LinkedList<Rational> list_expected11;
    list_expected11.push_back(r115);
    list_expected11.push_back(r114);
    list_expected11.push_back(r113);
    list_expected11.push_back(r112);
    list_expected11.push_back(r111);
    assert(list11 == list_expected11);
    // list11.print(); // Should print 1/4 1/3 1/2 3/4 1/1
    //  Case 12: Best case scenario for insertion sort
    //  where the list is already sorted
    LinkedList<Rational> list12;
    Rational r121(1, 5);
    Rational r122(1, 4);
    Rational r123(1, 3);
    Rational r124(1, 2);
    Rational r125(1, 1);
    list12.push_back(r121);
    list12.push_back(r122);
    list12.push_back(r123);
    list12.push_back(r124);
    list12.push_back(r125);
    list12.insertionSort();
    LinkedList<Rational> list_expected12;
    list_expected12.push_back(r121);
    list_expected12.push_back(r122);
    list_expected12.push_back(r123);
    list_expected12.push_back(r124);
    list_expected12.push_back(r125);
    assert(list12 == list_expected12);
    // list12.print(); // Should print 1/5 1/4 1/3 1/2 1/1
    //  Case 13: Average case scenario for insertion sort
    //  where the list is a mix of random Rational numbers
    LinkedList<Rational> list13;
    Rational r131(1, 2);
    Rational r132(2, 3);
    Rational r133(1, 4);
    Rational r134(3, 5);
    Rational r135(1, 3);
    list13.push_back(r131);
    list13.push_back(r132);
    list13.push_back(r133);
    list13.push_back(r134);
    list13.push_back(r135);
    list13.insertionSort();
    LinkedList<Rational> list_expected13;
    list_expected13.push_back(r133);
    list_expected13.push_back(r135);
    list_expected13.push_back(r131);
    list_expected13.push_back(r134);
    list_expected13.push_back(r132);
    assert(list13 == list_expected13);
    // list13.print(); // Should print 1/4 1/3 1/2 3/5 2/3
    //  Case 14: Equal Elements: Duplicate Rational numbers that are equal
    LinkedList<Rational> list14;
    Rational r141(1, 2);
    Rational r142(2, 4);
    Rational r143(3, 6);
    Rational r144(4, 8);
    Rational r145(1, 2);
    list14.push_back(r141);
    list14.push_back(r142);
    list14.push_back(r143);
    list14.push_back(r144);
    list14.push_back(r145);
    list14.insertionSort();
    LinkedList<Rational> list_expected14;
    list_expected14.push_back(r141);
    list_expected14.push_back(r142);
    list_expected14.push_back(r143);
    list_expected14.push_back(r144);
    list_expected14.push_back(r145);
    assert(list14 == list_expected14);
    // list14.print(); // Should print 1/2 2/4 3/6 4/8 1/2
    //  Case 15: Rational numbers with large GCD's of numerator and denominator, not reduced
    LinkedList<Rational> list15;
    Rational r151(50, 100);
    Rational r152(10, 20);
    Rational r153(75, 150);
    Rational r154(5, 10);
    list15.push_back(r151);
    list15.push_back(r152);
    list15.push_back(r153);
    list15.push_back(r154);
    list15.insertionSort();
    LinkedList<Rational> list_expected15;
    list_expected15.push_back(r154);
    list_expected15.push_back(r152);
    list_expected15.push_back(r151);
    list_expected15.push_back(r153);
    assert(list15 == list_expected15);
    // list15.print(); // Should print 5/10 10/20 50/100 75/150
}
void TestLinkedList::runTests()
{
    test_push_back_and_length();
    test_push_front_and_pop_front();
    test_isEmpty();
    test_print_empty();
    test_print_nonempty();
    test_mixed_operations();
    // std::cout << "All LinkedList tests passed!" << std::endl;
    test_search_found();
    test_search_not_found();
    test_search_empty();
    test_delete_middle();
    test_delete_head();
    test_delete_tail();
    test_delete_only_element();
    test_delete_not_found();
    test_delete_empty();
    test_LinkedList_sorting();
    std::cout << "All LinkedList tests passed!" << std::endl;
}