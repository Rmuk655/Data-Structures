# Data Structures (CS2233)

Implementations of fundamental data structures and algorithms in C++, from the Data Structures course at IIT Hyderabad. The core structures are written by hand: balanced trees, hashing, heaps, graph algorithms and a 2-SAT solver.

## What is implemented

| Area | Implementations | Where |
|---|---|---|
| **Linked lists, stacks, queues** | Odd-even list, XOR doubly linked list, infix to postfix, stack sorting by recursion, stack with middle operations | Coding Assignment 1, Labs 1-2 |
| **Binary trees and BSTs** | Non-recursive traversals, tree from inorder + preorder, longest equal-value path, k-th node on a BST path, BST range sum | Coding Assignment 2, Labs 3-5 |
| **Balanced trees** | AVL tree, (2,4)-tree, B-tree, red-black tree with external nodes, AVL rotation counting, red-black range enumeration | Coding Assignment 3, Lab 6 |
| **Hashing** | Static dictionary with perfect hashing, Bloom filter on a transaction dataset | Coding Assignment 1 (P4), Lab 8 |
| **Heaps** | Heap sort with `Delete_Min` and `Heapify` | Lab 7 |
| **Graphs** | BFS, Prim, Kruskal, Dijkstra, non-recursive DFS | Coding Assignment 4 |
| **Satisfiability** | 2-SAT through strongly connected components | Lab 9 |

## Repository layout

| Folder | Contents |
|---|---|
| `Coding assignment/Assignment 1-4/` | Graded coding assignments with per-assignment READMEs, problem statements (PDF) and theory answers |
| `Lab Assignments/Assignment 1-9/` | Weekly lab programs with problem statements |
| `LinkedList/` | Singly/doubly linked lists, stack and queue as C++ templates, with tests and a Makefile |
| `Rational/` | Rational-number class with operator overloading, tests and a Makefile |
| `Notes program practice/` | Searching and sorting algorithms written alongside lectures |
| `Strings/`, `hello-gcc/` | Small C practice programs |
| `Assignments/`, `Assignments Code solutions/`, `Coding Assignments My Code/` | Additional practice and reference material collected during the course |

## Build and run

Every program is a single file.

```bash
g++ -std=c++17 -O2 "Lab Assignments/Assignment 6/Krishnan_Ramanarayanan_CS24BTECH11036/Krishnan_Ramanarayanan_CS24BTECH11036.cpp" -o rbtree
./rbtree
```

`LinkedList/` and `Rational/` use a Makefile:

```bash
cd LinkedList && make
```

## Testing

The tree implementations (red-black, AVL, (2,4)-tree and B-tree) were checked by randomized differential testing against `std::set`: random insert/delete sequences, with the structural invariants (ordering, balance, uniform leaf depth, parent pointers) verified after every operation, under AddressSanitizer and LeakSanitizer.

## About

Roll number CS24BTECH11036. The programs follow the assignment specifications; `Coding assignment/*/README.md` files give per-problem descriptions and compile instructions.
