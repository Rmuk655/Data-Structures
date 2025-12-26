#include <iostream>
#include <cassert>
#include "Queue.h"
#include "TestQueue.h"
#include "../Rational/Rational.h"

void TestQueue::testEnqueue()
{
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    Queue<int> expectedQueue;
    expectedQueue.enqueue(10);
    expectedQueue.enqueue(20);
    expectedQueue.enqueue(30);

    assert(queue.size() == 3);
    assert(!queue.isEmpty());
    assert(queue == expectedQueue);

    assert(queue.front() == 10);

    expectedQueue.enqueue(40);
    queue.enqueue(40);
    assert(queue.size() == 4);
    assert(queue.front() == 10);
    assert(queue == expectedQueue);

    // std::cout << "testEnqueue passed." << std::endl;
}
void TestQueue::testDequeue()
{
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    Queue<int> expectedQueue;
    expectedQueue.enqueue(20);
    expectedQueue.enqueue(30);

    queue.dequeue();
    assert(queue.size() == 2);
    assert(queue == expectedQueue);
    assert(!queue.isEmpty());

    expectedQueue.dequeue();
    expectedQueue.dequeue();
    assert(expectedQueue.isEmpty());

    // std::cout << "testDequeue passed." << std::endl;
}

void TestQueue::testCopyConstructor()
{
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    Queue<int> copiedQueue(queue);
    assert(copiedQueue.size() == 3);
    assert(!copiedQueue.isEmpty());
    assert(copiedQueue.front() == 10);
    assert(queue == copiedQueue);

    // std::cout << "testCopyConstructor passed." << std::endl;
}

void TestQueue::testAssignment()
{
    Queue<int> queue1;
    queue1.enqueue(10);
    queue1.enqueue(20);
    queue1.enqueue(30);

    Queue<int> queue2;
    queue2 = queue1;

    assert(queue2.size() == 3);
    assert(!queue2.isEmpty());
    assert(queue2.front() == 10);
    assert(queue1 == queue2);

    // std::cout << "testAssignment passed." << std::endl;
}

void TestQueue::testFront()
{
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    assert(queue.front() == 10);
    queue.dequeue();
    assert(queue.front() == 20);
    queue.dequeue();
    assert(queue.front() == 30);

    // std::cout << "testFront passed." << std::endl;
}

void TestQueue::testEmpty()
{
    Queue<int> queue;
    assert(queue.isEmpty() == true);

    queue.enqueue(10);
    assert(queue.isEmpty() == false);

    queue.dequeue();
    assert(queue.isEmpty() == true);

    // std::cout << "testEmpty passed." << std::endl;
}

void TestQueue::testSize()
{
    Queue<int> queue;
    assert(queue.size() == 0);

    queue.enqueue(10);
    assert(queue.size() == 1);

    queue.enqueue(20);
    assert(queue.size() == 2);

    queue.dequeue();
    assert(queue.size() == 1);

    queue.dequeue();
    assert(queue.size() == 0);

    // std::cout << "testSize passed." << std::endl;
}

void TestQueue::testCustomType()
{
    Queue<Rational> queue;
    queue.enqueue(Rational(10, 1));
    queue.enqueue(Rational(20, 1));
    queue.enqueue(Rational(30, 1));

    assert(queue.size() == 3);
    assert(queue.front() == Rational(10, 1));

    queue.dequeue();
    assert(queue.front() == Rational(20, 1));

    queue.dequeue();
    assert(queue.front() == Rational(30, 1));

    // std::cout << "testCustomType passed." << std::endl;
}

void TestQueue::testqueue()
{
    // std::cout << "Test Case 1: Enqueue 1.1, 2.2, 3.3\n";

    Queue<float> q1;
    q1.enqueue(1.1f);
    q1.enqueue(2.2f);
    q1.enqueue(3.3f);

    assert(q1.size() == 3);
    assert(!q1.isEmpty());
    assert(q1.front() == 1.1f);

    Queue<float> expectedQueue;
    expectedQueue.enqueue(1.1f);
    expectedQueue.enqueue(2.2f);
    expectedQueue.enqueue(3.3f);

    assert(q1 == expectedQueue);
    // std::cout << "Queue: " << q1 << "\n"; // Expect: 1.1 2.2 3.3

    // std::cout << "Test Case 2: Dequeue (removes 1.1)\n";
    q1.dequeue();

    assert(q1.size() == 2);
    assert(q1.front() == 2.2f);

    Queue<float> expectedQueue2;
    ;
    expectedQueue2.enqueue(2.2f);
    expectedQueue2.enqueue(3.3f);

    assert(q1 == expectedQueue2);

    // std::cout << "Queue: " << q1 << "\n"; // Expect: 2.2 3.3

    // std::cout << "Test Case 3: Check front()\n";
    assert(q1.front() == 2.2f);
    // std::cout << "Front: " << q1.front() << "\n"; // Expect: 2.2

    // std::cout << "Test Case 4: Pop all, check isEmpty()\n";
    q1.dequeue();
    q1.dequeue();
    assert(q1.isEmpty());
    // std::cout << "Is empty: " << std::boolalpha << q1.isEmpty() << "\n"; // true

    // std::cout << "Test Case 5: Copy constructor: Queue<float> q2(q1)\n";
    q1.enqueue(10.5f);
    q1.enqueue(20.5f);
    q1.enqueue(30.5f);
    Queue<float> q2(q1);
    assert(q1 == q2);
    // std::cout << "q1: " << q1 << "\nq2: " << q2 << "\n";

    // std::cout << "Test Case 6: Assignment: q2 = q1\n";
    Queue<float> q3;
    q3 = q1;
    assert(q1 == q3);
    // std::cout << "q3: " << q3 << "\n";

    // std::cout << "Test Case 7: Check size\n";
    assert(q1.size() == 3);
    // std::cout << "Size: " << q1.size() << "\n";

    // std::cout << "Test Case 8: Custom type Rational(1,2), Rational(3,4)\n";
    Queue<Rational> rq;
    rq.enqueue(Rational(1, 2));
    rq.enqueue(Rational(3, 4));

    assert(rq.size() == 2);
    assert(rq.front() == Rational(1, 2));
    rq.dequeue();
    assert(rq.front() == Rational(3, 4));
    assert(!rq.isEmpty());
    // std::cout << "Queue: " << rq << "\n"; // Expect: 1/2 3/4

    // std::cout << "Test Case 9: Compare two queues\n";
    Queue<Rational> rq2(rq);
    assert(rq == rq2);
    // std::cout << "Queues match: " << std::boolalpha << (rq == rq2) << "\n";

    // std::cout << "Test Case 10: Print queue with <<\n";
    // std::cout << "Formatted output: " << rq << "\n";
}

void TestQueue::runAllTests()
{
    testEnqueue();
    testDequeue();
    testCopyConstructor();
    testAssignment();
    testFront();
    testEmpty();
    testSize();
    testCustomType();
    testqueue();

    std::cout << "All Queue tests passed!" << std::endl;
}