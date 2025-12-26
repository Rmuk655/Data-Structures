## Coding Assignment 2 – CS2233

# Name: Krishnan
# Roll No: CS24BTECH11036

# Folder structure:
CS24BTECH11036/
│-- A2P1.c
|-- A2P1.exe
│-- A2P2.c
|-- A2P2.exe
│-- A2P3.c
|-- A2P3.exe
│-- A2P4.c
|-- A2P4.exe
│-- A2P5.c
|-- A2P5.exe
│-- A2P6.c
|-- A2P6.exe
│-- README.md

## General Instructions
- Each problem is solved in a separate C file:
  - `A2P1.c` → Non-recursive Traversals
  - `A2P2.c` → Tree from Inorder & Preorder
  - `A2P3.c` → Most Frequent Pair Distance
  - `A2P4.c` → Longest Equal-Value Path
  - `A2P5.c` → K-th Node on Path in BST
  - `A2P6.c` → Range Sum of BST
- All programs are written in C++.
- To compile:  
  bash
  gcc filename.c -o filename

- To run:  
  bash
  ./filename

- Inputs exactly match the formats described in the assignment PDF.
- Outputs are printed exactly in the specified formats.

------------------------------------------------------------------------

Notes

-   Array representation follows:
    -   Root at index 1.
    -   Left child at 2i, right child at 2i+1.
    -   NULL used for empty children.
-   Input must strictly match examples.
-   Programs assume valid inputs unless otherwise stated.

------------------------------------------------------------------------

Problem 1: Non-recursive Traversals

File: A2P1.cpp

**Compile:**
bash
gcc A2P1.cpp -o A2P1.exe

**Run:**
bash
./A2P1.exe

**Input Format:**
- Integer k signifying the number of test cases.
- A sequence of integers separated by spaces.
- Example:
  2
  1 2 3 4 5 6 7
  1 2 3 4 5 -1 6

**Output Format:**
- The inorder, preorder, postorder traversals of the given tree as space-separated values. (3 lines per test case).
- Example:
  4 2 5 1 6 3 7 **inorder traversal of 1st tree**
  1 2 4 5 3 6 7 **preorder traversal of 1st tree**
  4 5 2 6 7 3 1 **postorder traversal of 1st tree**
  4 2 5 1 3 6   **inorder traversal of 2nd tree**
  1 2 4 5 3 6   **preorder traversal of 2nd tree**
  4 5 2 6 3 1   **postorder traversal of 2nd tree**

------------------------------------------------------------------------

Problem 2: Tree from Inorder & Preorder

File: A2P2.cpp

**Compile:**
bash
gcc A2P2.cpp -o A2P2.exe

**Run:**
bash
./A2P2.exe

**Input Format:**
- Integer k signifying the number of test cases.
- 2k lines containing a sequence of integers, each representing the inorder and preorder traversals of the given tree in 2 lines for each of the k test cases.
- Example:
  3
  4 2 5 1 6 3 7 **inorder traversal of 1st tree**
  1 2 4 5 3 6 7 **preorder traversal of 1st tree**
  4 2 5 1 3 6   **inorder traversal of 2nd tree**
  1 2 4 5 3 6   **preorder traversal of 2nd tree**
  4 2 6 1 3 5   **inorder traversal of 3rd tree**
  1 2 4 5 3 6   **preorder traversal of 3rd tree**

**Output Format:**
- The array representation of the tree constructed from the given inorder and preorder traversals as space-separated values      (1 lines per test case) or ERROR if the given inorder and preorder traversal do not correspond to the same tree.
- Example:
  1 2 3 4 5 6 7
  1 2 3 4 5 NULL 6
  ERROR

------------------------------------------------------------------------

Problem 3: Most Frequent Pair Distance

File: A2P3.cpp

**Compile:**
bash
gcc A2P3.cpp -o A2P3.exe

**Run:**
bash
./A2P3.exe

**Input Format:**
- Integer n signifying the number of test cases.
- The first line consists of a sequence of space separated integers, representing the preorder traversals of the given tree.
- The second line consists of a sequence of space separated integers, representing the inorder traversals of the given tree.
- Example:
  5
  1 2 4 5 3
  4 2 5 1 3

**Output Format:**
- A single integer which represents the most frequent distance in the tree. If there is a tie, the output is the smallest distance.
- Example:
  1

------------------------------------------------------------------------

Problem 4: Longest Equal-Value Path

File: A2P4.cpp

**Compile:**
bash
gcc A2P4.cpp -o A2P4.exe

**Run:**
bash
./A2P4.exe

**Input Format:**
- Integer n signifying the number of nodes.
- Next line contains a sequence of n integers, each representing the value of the nodes which are 1-indexed.
- The next n - 1 lines each contain 2 integers representing an undirected edge between the two nodes u and v, where u and v represent the 1 based index of the nodes of the graph.
- Example:
  6
  5 5 5 5 1 5
  1 2
  1 3
  2 4
  3 5
  3 6

**Output Format:**
- A single integer representing the length of the longest equal value path in the tree.
- Example:
  5

------------------------------------------------------------------------

Problem 5: K-th Node on Path in BST

File: A2P5.cpp

**Compile:**
bash
gcc A2P5.cpp -o A2P5.exe

**Run:**
bash
./A2P5.exe

**Input Format:**
- Integer n signifying the number of nodes in the Binary Search Tree.
- The next line contains a sequence of n integers, the node values of the n nodes of the tree.
- The next line contains an integer q representing the number of queries.
- The next q lines contain three integers u(index of node 1), v(index of node 2), k(max path length).
- Example:
  7
  4 2 6 1 3 5 7
  2
  1 7 3
  3 5 2

**Output Format:**
- q lines, one for each query where it prints the kth node on the path from node u to v, -1 if such a node doesn't exist.
- Example:
  4
  2

------------------------------------------------------------------------

Problem 6: Range Sum of BST

File: A2P6.cpp

**Compile:**
bash
gcc A2P6.cpp -o A2P6.exe

**Run:**
bash
./A2P6.exe

**Input Format:**
- The first line contains the array representation of the Binary Search Tree.
- The next line contains 2 integers - low and high respectively.
- Example:
  10 5 15 3 7 -1 18
  7 15

**Output Format:**
- A single integer representing the sum of the values of all nodes of the tree whose values lie in the given range [low, high].
- Example:
  32

------------------------------------------------------------------------