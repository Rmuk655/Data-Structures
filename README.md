# Data Structures

Implementations of fundamental data structures and algorithms in C++, written by hand: balanced trees, hashing, heaps, graph algorithms and a 2-SAT solver.

## What is implemented

| Area | Implementations | Where |
|---|---|---|
| **Linked lists, stacks, queues** | Odd-even list, XOR doubly linked list, infix to postfix, stack sorting by recursion, stack with middle operations | `Coding assignment/Assignment 1`, `Lab Assignments/Assignment 1-2`, `LinkedList/` |
| **Binary trees and BSTs** | Non-recursive traversals, tree from inorder + preorder, longest equal-value path, k-th node on a BST path, BST range sum | `Coding assignment/Assignment 2`, `Lab Assignments/Assignment 3-5` |
| **Balanced trees** | AVL tree, (2,4)-tree, B-tree, red-black tree with external nodes, AVL rotation counting, red-black range enumeration | `Coding assignment/Assignment 3`, `Lab Assignments/Assignment 6` |
| **Hashing** | Static dictionary with perfect hashing, Bloom filter on a transaction dataset | `Coding assignment/Assignment 1`, `Lab Assignments/Assignment 8` |
| **Heaps** | Heap sort with `Delete_Min` and `Heapify` | `Lab Assignments/Assignment 7` |
| **Graphs** | BFS, Prim, Kruskal, Dijkstra, non-recursive DFS | `Coding assignment/Assignment 4` |
| **Satisfiability** | 2-SAT through strongly connected components | `Lab Assignments/Assignment 9` |

## Repository layout

| Folder | Contents |
|---|---|
| `Coding assignment/` | Larger problem sets 1-4, each with a README describing the problems and how to run them |
| `Lab Assignments/` | Shorter programs 1-9, one data structure or algorithm each |
| `problem-solutions/` | Additional solutions to the problem sets |
| `problem-statements/` | The problem statements (PDF) for the lab programs |
| `LinkedList/` | Singly/doubly linked lists, stack and queue as C++ templates, with tests and a Makefile |
| `Rational/` | Rational-number class with operator overloading, tests and a Makefile |
| `Notes program practice/` | Searching and sorting algorithms |
| `Strings/`, `hello-gcc/` | Small C practice programs |
| `Assignments Code solutions/` | Additional implementations (AVL, red-black, 2-4 trees, hashing, 2-CNF SAT) built with a Makefile |

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
