## Red-Black Tree Implementation in C++

### Name of the student: Krishnan
### Roll No: CS24BTECH11036

---

## 1. Problem Statement Description

The problem statement asks us to implement a **Red-Black Tree** in C++ with the following functionalities:

1. **Insert a node**
2. **Delete a node**
3. **Search for a node**
4. Printing the respective **Inorder** and **Preorder** traversals of the tree

The tree uses **external nodes** to simplify balancing and maintains the red-black properties during insertion and deletion.

---

## 2. File Structure
Krishnan_Ramanarayanan_CS24BTECH11036/
|--`Krishnan_Ramanarayanan_CS24BTECH11036.cpp` – Main C++ source code implementing Red-Black Tree operations.
|--`README.txt` – Instructions to compile and run the program.

---

## 3. Compilation Instructions

1. Open a terminal (Linux/macOS) or Command Prompt (Windows).
2. Navigate to the folder `Krishnan_Ramanarayanan_CS24BTECH11036`.
3. Compile the program using g++:

In bash, copy paste the command:
g++ -std=c++17 -o Krishnan_Ramanarayanan_CS24BTECH11036 Krishnan_Ramanarayanan_CS24BTECH11036.cpp

## 4. Run the executable:

bash
./Krishnan_Ramanarayanan_CS24BTECH11036

On Windows, the command is:

bash
./Krishnan_Ramanarayanan_CS24BTECH11036.exe

---

## 4. Input Format

1. First line contains the integer n, which represents the number of elements to insert in the tree.
2. Second line contains n integers separated by spaces – the n elements to be inserted into the tree.

**Example Input:**
17
9 8 5 4 99 78 31 34 89 90 21 23 45 77 88 112 32

After this initial input, the program displays a menu to perform further operations by taking in user inputs.
Menu:
Enter your choice:
1 - Search for an element
2 - Insert an element
3 - Delete an element
0 - Exit

---

## 5. Output Format

1. First, the program prints **Inorder traversal** of the tree.
2. Next line: **Preorder traversal** of the tree.
3. Menu options for further operations:

Enter your choice:
1 - Search for an element
2 - Insert an element
3 - Delete an element
0 - Exit

- **Search:** Enter an integer to search in the tree. The program will display whether the element is present or not.
- **Insert:** Enter an integer to insert. After insertion, the program prints the **Inorder** and **Preorder** traversals.
- **Delete:** Enter an integer to delete. If the element exists, it is removed; otherwise, an error message is displayed.
- **Exit:** Enter 0 to terminate the program.

---

## 6. Example Session

**Input:**

```
17
9 8 5 4 99 78 31 34 89 90 21 23 45 77 88 112 32
```

**Output:**

```
Inorder Traversal: 4 5 8 9 21 23 31 32 34 45 77 78 88 89 90 99 112
Preorder Traversal: 31 9 5 4 8 21 23 78 45 32 77 88 99 89 90 112
Enter your choice:
1 - Search for an element
2 - Insert an element
3 - Delete an element
0 - Exit
```

User can then interactively choose options 1, 2, 3, or 0.

---

## 7. Notes

- **Duplicate elements** are ignored during insertion.
- All nodes store **parent pointers** for easier rotations and fixing.

---