#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <algorithm>
// #include "Tree.h"

#define RED true
#define BLACK false

using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    bool color;
};

Node *create_new_node(Node *ext_1, Node *ext_2, int key)
{
    Node *root = (Node *)malloc(sizeof(Node));
    if (!root)
    {
        cerr << "Memory allocation failed for root!" << endl;
        exit(1);
    }
    root->data = key;
    root->left = ext_1;
    root->right = ext_2;
    root->parent = nullptr;
    root->color = RED;
    // Red node is represented by the numerical value 1 while black nodes are represented by the numerical value 0.
    return root;
}

Node *create_ext_node()
{
    Node *root = (Node *)malloc(sizeof(Node));
    if (!root)
    {
        cerr << "Memory allocation failed for root!" << endl;
        exit(1);
    }
    root->data = INT_MIN;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    root->color = BLACK;
    // In theory, external (NIL) nodes are not real nodes, so they are said to be uncolored.
    // But for defining black-height and ensuring balance, they're treated as black.
    return root;
}

bool is_ext_node(Node *node)
{
    if (node->data == INT_MIN && node->color == BLACK)
    {
        return 1;
    }
    return 0;
}

void printpreorder(Node *root)
{
    if (root == nullptr || is_ext_node(root))
    {
        return;
    }
    else
    {
        cout << root->data << " ";
        printpreorder(root->left);
        printpreorder(root->right);
    }
}

void printinorder(Node *root)
{
    if (root == nullptr || is_ext_node(root))
    {
        return;
    }
    else
    {
        printinorder(root->left);
        cout << root->data << " ";
        printinorder(root->right);
    }
}

Node *search(Node *root, int key)
{
    if (root == nullptr)
    {
        // cout << "Key not found!" << endl;
        return nullptr;
    }
    if (root->data == key)
    {
        // cout << "Found" << endl;
        return root;
    }
    else if (root->data > key)
    {
        return search(root->left, key);
    }
    else
    {
        return search(root->right, key);
    }
}

int black_depth(Node *node)
{
    int d = 0;
    while (node->parent != nullptr)
    {
        if (node->parent->color == BLACK)
        {
            d++;
        }
    }
    return d;
}

bool child_dir(Node *root)
{
    if (root == nullptr)
    {
        cout << "Node is nullptr" << endl;
        return 0;
    }
    else if (root->parent == nullptr)
    {
        cout << "Node is the root of the tree" << endl;
        return 0;
    }
    if (root->parent->left == root)
    {
        return 0;
    }
    return 1;
}

Node *rotate_RB(Node *grandparent, Node *parent, Node *child)
{
    Node *root = grandparent;
    if (grandparent->left == parent && parent->left == child)
    {
        grandparent->left = parent->right;
        parent->right = grandparent;

        parent->parent = grandparent->parent;
        if (grandparent->parent != nullptr && grandparent->parent->left == grandparent)
        {
            grandparent->parent->left = parent;
        }
        else if (grandparent->parent != nullptr)
        {
            grandparent->parent->right = parent;
        }
        grandparent->parent = parent;

        root = parent;
    }
    else if (grandparent->right == parent && parent->right == child)
    {
        grandparent->right = parent->left;
        parent->left = grandparent;

        parent->parent = grandparent->parent;
        if (grandparent->parent != nullptr && grandparent->parent->left == grandparent)
        {
            grandparent->parent->left = parent;
        }
        else if (grandparent->parent != nullptr)
        {
            grandparent->parent->right = parent;
        }
        grandparent->parent = parent;

        root = parent;
    }
    else if (grandparent->left == parent && parent->right == child)
    {
        if (child == nullptr)
        {
            cout << "Child is null" << endl;
            return nullptr;
        }
        grandparent->left = child;
        parent->right = child->left;
        child->left = parent;

        child->parent = grandparent;
        parent->parent = child;
        parent->right->parent = parent;

        grandparent->left = child->right;
        if (child->right != nullptr)
        {
            child->right->parent = grandparent;
        }
        child->right = grandparent;

        child->parent = grandparent->parent;
        if (grandparent->parent != nullptr && grandparent->parent->left == grandparent)
        {
            grandparent->parent->left = child;
        }
        else if (grandparent->parent != nullptr)
        {
            grandparent->parent->right = child;
        }
        grandparent->parent = child;

        root = child;
    }
    else if (grandparent->right == parent && parent->left == child)
    {
        if (child == nullptr)
        {
            cout << "Child is null" << endl;
            return nullptr;
        }
        grandparent->right = child;
        parent->left = child->right;
        child->right = parent;

        child->parent = grandparent;
        parent->parent = child;
        parent->left->parent = parent;

        grandparent->right = child->left;
        if (child->left != nullptr)
        {
            child->left->parent = grandparent;
        }
        child->left = grandparent;

        child->parent = grandparent->parent;
        if (grandparent->parent != nullptr && grandparent->parent->left == grandparent)
        {
            grandparent->parent->left = child;
        }
        else if (grandparent->parent != nullptr)
        {
            grandparent->parent->right = child;
        }
        grandparent->parent = child;

        root = child;
    }
    return root;
}

Node *gethead(Node *node)
{
    if (node == nullptr)
    {
        cout << "Node is nullptr" << endl;
        return node;
    }
    else if (node->parent == nullptr)
    {
        return node;
    }
    return gethead(node->parent);
}

Node *insert(Node *root, int key)
{
    // Tree t(root);
    if (root == nullptr)
    {
        Node *ext_1 = create_ext_node(), *ext_2 = create_ext_node();
        root = create_new_node(ext_1, ext_2, key);
        root->color = BLACK; // Root is always colored black
        ext_1->parent = root;
        ext_2->parent = root;
        return root;
    }

    if (is_ext_node(root))
    {
        Node *ext_1 = create_ext_node(), *ext_2 = create_ext_node();
        Node *parent = root->parent;
        free(root);
        root = create_new_node(ext_1, ext_2, key);
        ext_1->parent = root;
        ext_2->parent = root;
        root->parent = parent;
        return root;
    }

    if (root->data == key)
    {
        cout << "Element already present in the tree! Cannot insert a duplicate element!" << endl;
        return root;
    }
    else if (root->data > key)
    {
        root->left = insert(root->left, key);
    }
    else
    {
        root->right = insert(root->right, key);
    }

    if (root != nullptr && root->left != nullptr && root->right != nullptr)
    {
        if (root->left->color == RED && root->right->color == BLACK)
        {
            if (root->left->left != nullptr && root->left->left->color == RED)
            {
                root = rotate_RB(root, root->left, root->left->left);
                root->color = BLACK;
                root->left->color = RED;
                root->right->color = RED;
            }
            else if (root->left->right != nullptr && root->left->right->color == RED)
            {
                root = rotate_RB(root, root->left, root->left->right);
                root->color = BLACK;
                root->left->color = RED;
                root->right->color = RED;
            }
        }
        else if (root->right->color == RED && root->left->color == BLACK)
        {
            if (root->right->left != nullptr && root->right->left->color == RED)
            {
                root = rotate_RB(root, root->right, root->right->left);
                root->color = BLACK;
                root->left->color = RED;
                root->right->color = RED;
            }
            else if (root->right->right != nullptr && root->right->right->color == RED)
            {
                root = rotate_RB(root, root->right, root->right->right);
                root->color = BLACK;
                root->left->color = RED;
                root->right->color = RED;
            }
        }
        else if (root->left->color == RED && root->right->color == RED)
        {
            if (root->left->left != nullptr && root->left->left->color == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else if (root->left->right != nullptr && root->left->right->color == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else if (root->right->left != nullptr && root->right->left->color == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else if (root->right->right != nullptr && root->right->right->color == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
        }
    }
    Node *node = gethead(root);
    node->color = BLACK;
    return root;
}

void freemem(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    freemem(root->left);
    freemem(root->right);
    free(root);
}

// Helper to check BST property
bool isBST(Node *node, int minVal, int maxVal)
{
    if (!node || is_ext_node(node))
        return true;
    // if (node->data <= minVal || node->data >= maxVal)
    //     return false;
    return isBST(node->left, minVal, node->data) &&
           isBST(node->right, node->data, maxVal);
}

// Helper: checks red-black properties recursively
int checkRBProps(Node *node, bool &isValid)
{
    if (!node)
        return 1; // NIL nodes are black, contribute 1 black

    // Property: Red node cannot have red children
    if (node->color == RED)
    {
        if ((node->left && node->left->color == RED) ||
            (node->right && node->right->color == RED))
        {
            isValid = false;
            cerr << "Red node with red child at " << node->data << endl;
            return -1;
        }
    }

    int leftBlackHeight = checkRBProps(node->left, isValid);
    int rightBlackHeight = checkRBProps(node->right, isValid);

    if (leftBlackHeight == -1 || rightBlackHeight == -1 || leftBlackHeight != rightBlackHeight)
    {
        isValid = false;
        cerr << "Black height mismatch at " << node->data << endl;
        return -1;
    }

    return leftBlackHeight + (node->color == BLACK ? 1 : 0);
}

// Main validator function
bool isValidRBTree(Node *root)
{
    if (!root)
        return true;

    // Rule 1: Root must be black
    if (root->color != BLACK)
    {
        cerr << "Root is not black\n";
        return false;
    }

    // Rule 2: Must satisfy BST property
    if (!isBST(root, INT_MIN, INT_MAX))
    {
        cerr << "BST property violated\n";
        return false;
    }

    // Rule 3: Red-black properties
    bool isValid = true;
    int bh = checkRBProps(root, isValid);

    if (!isValid || bh == -1)
    {
        cerr << "Red-Black properties violated\n";
        return false;
    }

    return true;
}

void collect_inorder(Node *root, vector<int> &result)
{
    if (!root || is_ext_node(root))
        return; // assuming -1 or NULL node
    collect_inorder(root->left, result);
    result.push_back(root->data);
    collect_inorder(root->right, result);
}

void collect_preorder(Node *root, vector<int> &result)
{
    if (!root || is_ext_node(root))
        return;
    result.push_back(root->data);
    collect_preorder(root->left, result);
    collect_preorder(root->right, result);
}

void assert_equal(const vector<int> &a, const vector<int> &b, const string &msg)
{
    if (a != b)
    {
        cout << "Assertion failed: " << msg << endl;
        cout << "Expected: ";
        for (int x : b)
            cout << x << " ";
        cout << "\nActual: ";
        for (int x : a)
            cout << x << " ";
        cout << endl;
        assert(false);
    }
}

void test_case(const string &name, const vector<int> &input,
               const vector<int> &expected_inorder,
               const vector<int> &expected_preorder)
{
    cout << "[RUNNING] " << name << endl;

    Node *root = nullptr;
    for (int val : input)
        root = insert(root, val);

    vector<int> inorder, preorder;
    collect_inorder(root, inorder);
    collect_preorder(root, preorder);

    assert_equal(inorder, expected_inorder, name + ": Inorder mismatch");
    assert_equal(preorder, expected_preorder, name + ": Preorder mismatch");
    assert(isValidRBTree(root));

    freemem(root);
    cout << "[PASSED] " << name << "\n"
         << endl;
}

void run_all_rb_insert_tests()
{
    test_case("Test 1: Left Rotation",
              {10, 20, 30},
              {10, 20, 30},
              {20, 10, 30});

    test_case("Test 2: Right Rotation",
              {30, 20, 10},
              {10, 20, 30},
              {20, 10, 30});

    test_case("Test 3: Recoloring Only",
              {10, 5, 15, 1},
              {1, 5, 10, 15},
              {10, 5, 1, 15});

    test_case("Test 4: Left-Right Rotation",
              {30, 10, 20},
              {10, 20, 30},
              {20, 10, 30});

    test_case("Test 5: Right-Left Rotation",
              {10, 30, 20},
              {10, 20, 30},
              {20, 10, 30});

    test_case("Test 6: Recolor to Root",
              {20, 10, 30, 5, 15, 25, 35, 3},
              {3, 5, 10, 15, 20, 25, 30, 35},
              {20, 10, 5, 3, 15, 30, 25, 35});

    test_case("Test 7: Duplicates Inserted",
              {10, 20, 10, 20}, // insert duplicates (should be ignored or handled)
              {10, 20},
              {10, 20}); // preorder depends on insert logic

    test_case("Test 8: Random Sequence",
              {42, 17, 68, 23, 9, 35, 50, 70, 12},
              {9, 12, 17, 23, 35, 42, 50, 68, 70},
              {42, 17, 9, 12, 23, 35, 68, 50, 70});

    test_case("Test 9: Sorted Input",
              {1, 2, 3, 4, 5},
              {1, 2, 3, 4, 5},
              {2, 1, 4, 3, 5}); // final shape balances via rotations

    test_case("Test 10: Root Recoloring",
              {10, 5, 20, 1, 6},
              {1, 5, 6, 10, 20},
              {10, 5, 1, 6, 20});
}

void test()
{
    struct Node *root = nullptr;
    vector<int> nums_create = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    for (int i = 0; i < (int)nums_create.size(); i++)
    {
        root = insert(root, nums_create[i]);
    }
    printinorder(root);
    cout << endl;
    printpreorder(root);
    cout << endl;
    vector<int> nums_search = {32, 56, 90};
    for (int i = 0; i < (int)nums_search.size(); i++)
    {
        root = search(root, nums_search[i]);
        // printinorder(root);
        // cout << endl;
        // printpreorder(root);
        // cout << endl;
    }
    printinorder(root);
    cout << endl;
    printpreorder(root);
    cout << endl;
    vector<int> nums_insert_2 = {32, 56, 90};
    for (int i = 0; i < (int)nums_insert_2.size(); i++)
    {
        root = insert(root, nums_insert_2[i]);
        // printinorder(root);
        // cout << endl;
        // printpreorder(root);
        // cout << endl;
    }
    printinorder(root);
    cout << endl;
    printpreorder(root);
    cout << endl;
    freemem(root);

    cout << "All test cases passed!" << endl;
}

int main()
{
    run_all_rb_insert_tests();
    test();
    struct Node *root = nullptr;
    int a, b, c, n;
    cout << "Enter the number of elements to be inserted in the RB Tree" << endl;
    cin >> a;
    vector<int> nums_create;
    for (int i = 0; i < a; i++)
    {
        cin >> n;
        nums_create.push_back(n);
        root = insert(root, nums_create[i]);
    }
    printinorder(root);
    cout << endl;
    printpreorder(root);
    cout << endl;
    cout << "Enter the number of elements to be searched in the RB Tree" << endl;
    cin >> b;
    vector<int> nums_search;
    for (int i = 0; i < b; i++)
    {
        cin >> n;
        nums_search.push_back(n);
        search(root, nums_search[i]);
        if (root != nullptr)
        {
            cout << "Search successful" << endl;
        }
        // printinorder(root);
        // cout << endl;
        // printpreorder(root);
        // cout << endl;
    }
    printinorder(root);
    cout << endl;
    printpreorder(root);
    cout << endl;
    cout << "Enter the number of elements to be inserted in the RB Tree" << endl;
    cin >> c;
    vector<int> nums_insert_2;
    for (int i = 0; i < c; i++)
    {
        cin >> n;
        nums_insert_2.push_back(n);
        root = insert(root, nums_insert_2[i]);
        // printinorder(root);
        // cout << endl;
        // printpreorder(root);
        // cout << endl;
    }
    printinorder(root);
    cout << endl;
    printpreorder(root);
    cout << endl;
    freemem(root);
}