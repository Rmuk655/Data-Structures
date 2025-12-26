# Coding Assignment 1 – CS2233

## Folder Structure
```
CS24BTECH11036/
│-- A1P1.c
|-- A1P1.exe
│-- A1P2.c
|-- A1P2.exe
│-- A1P3.c
|-- A1P3.exe
│-- A1P4.c
|-- A1P4.exe
│-- A1P5.c
|-- A1P5.exe
│-- A1P6.c
|-- A1P6.exe
│-- README.md

## General Instructions
- Each problem is solved in a separate C file:
  - `A1P1.c` → Odd–Even Linked List
  - `A1P2.c` → XOR Doubly Linked List
  - `A1P3.c` → Infix to Postfix Conversion
  - `A1P4.c` → Static Dictionary with Perfect Hashing
  - `A1P5.c` → Sort Stack using Recursion
  - `A1P6.c` → Stack with Middle Operations
- All programs are written in C++.
- To compile:  
  bash
  gcc filename.c -o filename

- To run:  
  bash
  ./filename

- Inputs exactly match the formats described in the assignment PDF.
- Outputs are printed exactly in the specified formats.


## Problem 1 – Odd–Even Linked List
**Compile:**
bash
gcc A1P1.c -o A1P1.exe

**Run:**
bash
./A1P1.exe

**Input Format:**
- A sequence of integers separated by commas and spaces, ending with `-1`.
- Example:
  2, 1, 3, 5, 6, 4, 7, -1

**Output Format:**
- Reordered list (odd indices first, then even indices) as comma and space-separated values.
- Example:
  2, 3, 6, 7, 1, 5, 4

## Problem 2 – XOR Doubly Linked List
**Compile:**
bash
gcc A1P2.c -o A1P2.exe

**Run:**
bash
./A1P2.exe

**Input Format:**
- First line: integer `k` (number of operations).
- Next `k` lines: operation details. Valid formats are:
  - `1 x` → Search x
  - `2 x` → Insert x
  - `3 x` → Delete x
  - `4`   → Reverse

**Output Format:**
- One line per operation result.

## Problem 3 – Infix to Postfix Conversion
**Compile:**
bash
gcc A1P3.c -o A1P3.exe

**Run:**
bash
./A1P3.exe

**Input Format:**
- Integer k, the number of test k cases
- For the next k lines, input valid infix expressions in each line.

**Output Format:**
- Equivalent postfix expressions for each test case.

## Problem 4 – Static Dictionary with Perfect Hashing
**Compile:**
bash
gcc A1P4.c -o A1P4.exe

**Run:**
bash
./A1P4.exe

**Input Format:**
- Integer `n` (NHS_No to be searched).

**Output Format:**
- Prints search results.

## Problem 5 – Sort Stack using Recursion
**Compile:**
bash
gcc A1P5.c -o A1P5.exe

**Run:**
bash
./A1P5.exe

**Input Format:**
- First line: integer `n` (number of elements in the stack).
- Next line: `n` integers (stack elements).

**Output Format:**
- Stack elements printed in sorted order (descending).

## Problem 6 – Stack with Middle Operations
**Compile:**
bash
gcc A1P6.c -o A1P6.exe

**Run:**
bash
./A1P6.exe

**Input Format:**
- First line: integer `Q` (number of operations).
- Next `Q` lines: operation details.
  - `1 x` → Push x
  - `2`   → Pop
  - `3`   → Find Middle
  - `4`   → Delete Middle

**Output Format:**
- One line per operation result

## Notes
- Handle underflow/overflow cases as described.
- Test cases are provided in each file as comments.
- Memory should be freed wherever applicable.