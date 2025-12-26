## Coding Assignment 3 – CS2233

# Name: Krishnan
# Roll No: CS24BTECH11036

# Folder structure:
CS24BTECH11036/
│-- A3P1.c
│-- A3P2.c
│-- A3P3.c
│-- A3P4.c
│-- A3P5.c
|-- Theory_answers.pdf
│-- README.md

## General Instructions
- Each problem is solved in a separate C file:
  - `A3P1.c` → AVL-Tree Construction (Query based)
  - `A3P2.c` → (2-4)-Tree Construction (Query based)
  - `A3P3.c` → B-Tree Construction (Query based)
  - `A3P4.c` → No of rotations (single and double) in an AVL Tree (Standalone Batch I/O)
  - `A3P5.c` → RB–ENUMERATE(x, a, b) (Standalone Batch I/O)

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

## Global Input/Output Format

The **global input and output format** applies to **Problems 1–3** (AVL Tree, (2-4) Tree, and B-Tree).  
All three problems follow a **query-based system** where the program runs continuously,  
reading queries until **EOF** (end of file).

---

### Input Format
n
a1 a2 a3 ... an
<query 1>
<query 2>
...

- **First line:**  
  `n` — number of elements to insert initially into the tree.

- **Second line:**  
  `n` space-separated integers representing the tree elements (inserted **in order**).  
  Duplicate elements must be **ignored**.

- **Subsequent lines:** Each line represents a query of one of the following types:

| Query Type | Format | Description                                                            |
|------------|--------|------------------------------------------------------------------------|
|     1      | `1 x`  | Search for key `x` in the tree.                                        |
|     2      | `2 x`  | Insert key `x` into the tree.                                          |
|     3      | `3 x`  | Delete key `x` from the tree.                                          |
|     4      | `4`    | Print the tree in **level-order**, one line per level. |

The program should continuously accept queries until **EOF**.

---

### Output Format

Each query type produces the following standardized output messages:

| Query Type  | Expected Output                                                                                                  |
|-------------|------------------------------------------------------------------------------------------------------------------|
|    `1 x`    | `<x> present`  or  `<x> not present`                                                                             |
|    `2 x`    | `<x> inserted`  or  `<x> already present. So no need to insert.`                                                 |
|    `3 x`    | `<x> deleted`  or  `<x> not present. So it can not be deleted`                                                   |
|     `4`     | Prints the **level-order traversal** of the tree:<br>Each level on a new line, nodes separated by single spaces. |

---

### Example

#### Input
17
9 8 5 4 99 78 31 34 89 90 21 23 45 77 88 112 32
1 56
2 21
2 56
2 90
3 51
1 32
3 32
4

#### Output
56 not present
21 already present. So no need to insert.
56 inserted
90 already present. So no need to insert.
51 not present. So it can not be deleted
32 present
32 deleted
<Level order traversal is printed in the following format>
<level 0 nodes>
<level 1 nodes>
<level 2 nodes>
....

------------------------------------------------------------------------

# Problem 1: AVL-Tree Construction (Query based)

### Description
Construct an **AVL tree** that supports the following operations using the global query system:
- Search  
- Insert  
- Delete  
- Level-order traversal  

- Note that duplicates must **not** be inserted.

---

File: A3P1.cpp

**Compile:**
bash
gcc A3P1.cpp -o A3P1.exe

**Run:**
bash
./A3P1.exe

### Input Format
n
a1 a2 a3 ... an
<query 1>
<query 2>
...

- First line: `n` — number of initial elements.  
- Second line: `n` space-separated integers inserted into the AVL tree **in order**.  
- Subsequent lines: Queries until EOF.

Each query follows one of these formats:
| Query Type | Format | Description               |
|------------|--------|---------------------------|
|      1     |  `1 x` | Search key `x`            |
|      2     |  `2 x` | Insert key `x`            |
|      3     |  `3 x` | Delete key `x`            |
|      4     |   `4`  | Print tree level-by-level |

---

### Output Format
| Query Type | Output                                                                       |
|------------|------------------------------------------------------------------------------|
|      1     | `<x> present` or `<x> not present`                                           |
|      2     | `<x> inserted` or `<x> already present. So no need to insert.`               |
|      3     | `<x> deleted` or `<x> not present. So it can not be deleted`                 |
|      4     | Print tree **level-by-level**, one level per line, nodes separated by spaces |

---

### Notes
- The tree must maintain **AVL balance** after each insertion/deletion.
- The code should continue reading and processing queries **until EOF**.

------------------------------------------------------------------------

# Problem 2: (2-4) Tree Construction (Query-Based)

### Description
Construct a **(2–4) Tree** supporting the same query types and I/O behavior as the AVL tree.  
Each node may contain 1–3 keys and up to 4 children.

---

File: A2P2.cpp

**Compile:**
bash
gcc A2P2.cpp -o A2P2.exe

**Run:**
bash
./A2P2.exe

### Input Format
Same as the **global query-based format**:
n
a1 a2 a3 ... an
<query 1>
<query 2>
...

- First line: `n` — number of initial elements.  
- Second line: `n` space-separated integers inserted into the AVL tree **in order**.  
- Subsequent lines: Queries until EOF.

Each query follows one of these formats:
| Query Type | Format | Description               |
|------------|--------|---------------------------|
|      1     |  `1 x` | Search key `x`            |
|      2     |  `2 x` | Insert key `x`            |
|      3     |  `3 x` | Delete key `x`            |
|      4     |   `4`  | Print tree level-by-level |

---

### Output Format
| Query Type | Output                                                                       |
|------------|------------------------------------------------------------------------------|
|      1     | `<x> present` or `<x> not present`                                           |
|      2     | `<x> inserted` or `<x> already present. So no need to insert.`               |
|      3     | `<x> deleted` or `<x> not present. So it can not be deleted`                 |
|      4     | Print tree **level-by-level**, one level per line, nodes separated by spaces |

------------------------------------------------------------------------

# Problem 3: B-Tree Construction (Query-Based)

### Description
Construct a **B-Tree** of order `t ≥ 2` supporting search, insert, delete, and level-order traversal  
using the **global query-based format**.

Each node stores:
- Up to `MAX = 2t − 1` keys  
- At least `MIN = t − 1` keys (except root)  

---

File: A2P3.cpp

**Compile:**
bash
gcc A2P3.cpp -o A2P3.exe

**Run:**
bash
./A2P3.exe

### Input Format
Same as the **global query-based format**:
n
a1 a2 a3 ... an
<query 1>
<query 2>
...

- First line: `n` — number of initial elements.  
- Second line: `n` space-separated integers inserted into the AVL tree **in order**.  
- Subsequent lines: Queries until EOF.

Each query follows one of these formats:
| Query Type | Format | Description               |
|------------|--------|---------------------------|
|      1     |  `1 x` | Search key `x`            |
|      2     |  `2 x` | Insert key `x`            |
|      3     |  `3 x` | Delete key `x`            |
|      4     |   `4`  | Print tree level-by-level |

---

### Output Format
| Query Type | Output                                                                       |
|------------|------------------------------------------------------------------------------|
|      1     | `<x> present` or `<x> not present`                                           |
|      2     | `<x> inserted` or `<x> already present. So no need to insert.`               |
|      3     | `<x> deleted` or `<x> not present. So it can not be deleted`                 |
|      4     | Print tree **level-by-level**, one level per line, nodes separated by spaces |

------------------------------------------------------------------------

# Problem 4: No of rotations (single and double) in an AVL Tree (Standalone Batch I/O)

### Description
Implement AVL tree operations using **batch input** (no query loop).  
Count the number of **single** and **double rotations** performed during all insertions and deletions.

---

File: A2P4.cpp

**Compile:**
bash
gcc A2P4.cpp -o A2P4.exe

**Run:**
bash
./A2P4.exe

### Input Format
N
op1 x1
op2 x2
...
opN xN

- `N` — number of operations  
- Each operation `opi` is:
  - `I x` → Insert key `x`
  - `D x` → Delete key `x`

---

### Output Format
After performing all operations, print the following **once**:

Inorder: <ascending order of keys>
Single rotations: <count>
Double rotations: <count>

---

### Example
#### Input
7
I 10
I 20
I 30
I 25
I 28
D 10
D 25

#### Output
Inorder: 20 28 30
Single rotations: 2
Double rotations: 1

------------------------------------------------------------------------

# Problem 5: RB–ENUMERATE(x, a, b)

### Description
Implement an algorithm `RB-ENUMERATE(x, a, b)` that outputs all keys `k`  
such that `a ≤ k ≤ b` in a **Red–Black Tree** rooted at node `x`.
- The algorithm must run in **Θ(m + log n)** time,  
  where `m` is the number of keys output, and `n` is the number of nodes.
- You must also **write a short proof** of correctness and efficiency.

---

File: A2P5.cpp

**Compile:**
bash
gcc A2P5.cpp -o A2P5.exe

**Run:**
bash
./A2P5.exe

### Input Format and Output Format
(Not governed by the global I/O format.)
Since only the function implementation is asked, no I/O format is specified for this question.
However for verification, I have included search, insert functions and one can run it the following way (after uncommenting the search, insert functions code):

Input: 
The first line consists of an integer n, denoting the number of elements to be inserted into the RB-Tree.
The next line consists of n space separated integers to be inserted into the RB-Tree.
The next line consists of two integers a, b denoting the lower and upper bounds (the same a, b used when calling the RB_Enumerate(x, a, b) function).

Output:
One line of m space separated integers consisting of the list of all integers between a and b evaluated by the RB_Enumerate(x, a, b) function.

---

### 🧠 Notes
- I have attached it's verification and **time complexity proof** of the implemented algorithm in the pdf file Theory_answers.pdf.

------------------------------------------------------------------------