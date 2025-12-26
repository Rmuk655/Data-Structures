# Assignment 2: Insertion Sort on a Templated Linked List of Rational Numbers in C++
This project reinforces object-oriented programming, generic programming using templates, operator overloading, and basic sorting algorithms in C++.
Structuring code across multiple files: Rational.h, Rational.cpp, testRational.h, testRational.cpp, main.cpp.
Including test cases and expected outputs.

# Objective
The objective of this project is to implement sorting of rational numbers represented as fractions using an insertion sort algorithm on a singly linked list.

## ✅ Test Case Descriptions

| **Test Case**                            | **Description**                               | **Example**                         |
|-----------------------------------------|-----------------------------------------------|-------------------------------------|
| Equal rational numbers (different forms)| Tests if equivalent fractions compare as equal| `Rational(1, 2) == Rational(2, 4)`  |
| Not equal rational numbers              | Ensures distinct values are not equal         | `Rational(3, 5) != Rational(2, 5)`  |
| Less than / Greater than                | Verifies `<` and `>` comparisons              | `Rational(1, 3) < Rational(2, 3)`   |
| Less than or equal / Greater than or equal | Checks `<=` and `>=` operators              | `Rational(3, 6) <= Rational(1, 2)`  |
| Negative number comparison              | Compares a negative to a positive value       | `Rational(-1, 2) < Rational(1, 2)`  |
| Zero comparisons                        | Tests if zero values are recognized as equal  | `Rational(0, 1) == Rational(0, 5)`  |

# 🛠️ Build Instructions

1. Update the `Makefile` with these rules:
   - `make`

2. Compile and run using:
   ```bash
   make
   ./main

make clean
.\rational_app.exe