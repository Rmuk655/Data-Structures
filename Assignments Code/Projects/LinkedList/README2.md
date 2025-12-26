# Additional README
# Assignment 4: Generic Queue using DoublyLinkedList (with Template Support)
You will practice generic programming, constructor and destructor chaining, and object-oriented design across multiple files. Also, you will include a test suite and main.cpp with sample usage.

# Objective
Extend your DoublyLinkedList class to use C++ templates and implement a Queue data structure that works for any type — including built-in types (int, float, etc.) and custom user-defined types like Rational.

# 🧪 Queue Test Cases

This section describes the test cases for our Queue implementation. The tests validate enqueueing, dequeueing, front checking, copying, assignment, size checking, and working with a custom type (`Rational`). Each test case lists the action performed and the expected output.

| **Test Case** | **Action**                                             | **Expected Output**         |
|---------------|--------------------------------------------------------|-----------------------------|
| **1**       | Enqueue `1.1`, `2.2`, `3.3`                             | Queue: `1.1 2.2 3.3`         |
| **2**       | Dequeue (removes `1.1`)                                  | Queue: `2.2 3.3`             |
| **3**       | Check `front()`                                         | `2.2`                      |
| **4**       | Pop all, then check `isEmpty()`                         | `true`                     |
| **5**       | Copy constructor: `Queue<float> q2(q1)`                 | Identical contents         |
| **6**       | Assignment: `q2 = q1`                                   | Identical contents         |
| **7**       | Check size                                             | `3`                        |
| **8**       | Enqueue custom type: `Rational(1, 2)`, `Rational(3, 4)` | Queue: `1/2 3/4`           |
| **9**       | Compare two queues using `operator==` (if defined)      | Matches                    |
| **10**      | Print queue using overloaded `operator<<`              | Formatted output           |


# 🛠️ Build Instructions

1. Update the `Makefile` with these rules:
   - `make`

2. Compile and run using:
   ```bash
   make
   ./main

make clean  
.\Stack_app.exe

