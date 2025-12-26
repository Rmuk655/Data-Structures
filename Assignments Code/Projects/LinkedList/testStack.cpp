#include <cassert>
#include <iostream>
#include "Stack.h"
#include "testStack.h"

using namespace std;
void TestStack::testPush()
{
    Stack<float> s;
    s.push(10);
    assert(s.top() == 10);
    s.push(20);
    assert(s.top() == 20);
    s.push(-5);
    assert(s.top() == -5);
    // cout << s; // Output:  -5 20 10
    // cout << "testPush passed\n";
}

void TestStack::testPop()
{
    Stack<float> s;
    s.push(1);
    s.push(2);
    s.push(3);
    assert(s.top() == 3);
    s.pop();
    assert(s.top() == 2);
    s.pop();
    assert(s.top() == 1);
    s.pop();
    assert(s.isEmpty());
    // cout << s; // Output: (empty stack, so no output)
    // cout << "testPop passed\n";
}

void TestStack::testCopyConstructor()
{
    Stack<float> s1;
    for (int i = 0; i < 5; ++i)
        s1.push(i);
    Stack<float> s2(s1);
    assert(s2.size() == s1.size());
    // cout << s1; // Output: 4 3 2 1 0
    // cout << s2; // Output: 4 3 2 1 0
    while (!s1.isEmpty())
    {
        assert(s1.top() == s2.top());
        // cout << s1; // Output: 4 3 2 1 0
        // cout << s2; // Output: 4 3 2 1 0
        s1.pop();
        s2.pop();
        // cout << s1; // Output: 3 2 1 0
        // cout << s2; // Output: 3 2 1 0
    }
    // cout << s1; // Output:  (empty stack, so no output)
    // cout << s2; // Output:  (empty stack, so no output)
    // cout << "testCopyConstructor passed\n";
}

void TestStack::testAssignment()
{
    Stack<float> s1;
    for (int i = 0; i < 3; ++i)
        s1.push(i);
    Stack<float> s2;
    s2 = s1;
    assert(s2.size() == s1.size());
    // cout << s1; // Output: 2 1 0
    // cout << s2; // Output: 2 1 0
    while (!s1.isEmpty())
    {
        assert(s1.top() == s2.top());
        s1.pop();
        s2.pop();
    }
    // cout << s1; // Output:  (empty stack, so no output)
    // cout << s2; // Output:  (empty stack, so no output)
    // cout << "testAssignment passed\n";
}

void TestStack::testTop()
{
    Stack<float> s;
    s.push(42);
    assert(s.top() == 42);
    s.push(100);
    assert(s.top() == 100);
    s.pop();
    assert(s.top() == 42);
    // cout << s; // Output: 42
    // cout << "testTop passed\n";
}

void TestStack::testEmpty()
{
    Stack<float> s;
    assert(s.isEmpty());
    s.push(1);
    assert(!s.isEmpty());
    s.pop();
    assert(s.isEmpty());
    // cout << s; // Output: (empty stack, so no output)
    // cout << "testEmpty passed\n";
}

void TestStack::testSize()
{
    Stack<float> s;
    assert(s.size() == 0);
    for (int i = 0; i < 10; ++i)
    {
        s.push(i);
        assert(s.size() == i + 1);
    }
    // cout << s; // Output: 9 8 7 6 5 4 3 2 1 0
    for (int i = 10; i > 0; --i)
    {
        s.pop();
        assert(s.size() == i - 1);
    }
    // cout << s; // No output since stack is empty
    assert(s.isEmpty());
    // cout << "testSize passed\n";
}

// Boundary test: pop/top on empty stack
void TestStack::testEmptyPopTop()
{
    Stack<float> s;
    s.pop();
    // cout << s; // Output: (empty stack, so no output)
    s.top();
    // cout << s; // Output: (empty stack, so no output)
    // cout << "testEmptyPopTop passed\n";
}
void TestStack::additionalTests()
{
    // 1. Push 5.5, 3.3, 2.2 (using double values)
    Stack<float> s;
    s.push(5.5);
    s.push(3.3);
    s.push(2.2);
    // cout << s << endl; // Expected: 2.2 3.3 5.5

    // 2. Pop top (2.2)
    s.pop();
    // cout << s << endl; // Expected: 3.3 5.5

    // 3. Check top()
    // cout << s.top() << endl;

    // 4. Pop all, check empty
    s.pop();
    s.pop();
    assert(s.isEmpty());

    // 5. Copy constructor: Stack s2(s1);
    Stack<float> s1;
    s1.push(1.1);
    s1.push(2.2);
    Stack<float> s2(s1);
    assert(s2.size() == s1.size());
    assert(s2.top() == s1.top());

    // 6. Assignment: s2 = s1
    Stack<float> s3;
    s3 = s1;
    assert(s3.size() == s1.size());
    assert(s3.top() == s1.top());

    // 7. Push after copy, original unchanged
    s3.push(9.9);
    // cout << s3.top() << endl;
    // cout << s1.top() << endl;

    // 8. Check size after multiple pushes
    Stack<float> s4;
    s4.push(7.7);
    s4.push(8.8);
    s4.push(9.9);
    assert(s4.size() == 3);

    // 9. Pop from empty
    Stack<float> s5;
    bool popResult = s5.pop(); // Assuming pop returns false if empty
    assert(popResult == false);

    // 10. Print empty stack
    // cout << s5; // Expected: no output or "empty"

    // cout << "additionalTests passed\n";
}
void TestStack::runAllTests()
{
    testPush();
    testPop();
    testCopyConstructor();
    testAssignment();
    testTop();
    testEmpty();
    testSize();
    testEmptyPopTop();
    additionalTests();
    cout << "All Stack tests passed!\n";
}