#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <algorithm>

using namespace std;

struct node
{
    int data;
    // int height;
    struct node *left;
    struct node *right;
    struct node *parent;
};

node *create_node(int key)
{
    // cout << "Pass 2.1.1.1" << endl;
    node *root = (node *)malloc(sizeof(node));
    if (!root)
    {
        cout << "Memory allocation failed for root!" << endl;
        exit(1);
    }
    // cout << "Pass 2.1.1.2" << endl;
    root->data = key;
    // head->height = 1;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    return root;
}

void printpreorder(node *head)
{
    if (head == nullptr)
    {
        return;
    }
    else
    {
        cout << head->data << " ";
        printpreorder(head->left);
        printpreorder(head->right);
    }
}

void printinorder(node *head)
{
    if (head == nullptr)
    {
        return;
    }
    else
    {
        printinorder(head->left);
        cout << head->data << " ";
        printinorder(head->right);
    }
}

int getheight(node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    else if (node->left == nullptr && node->right == nullptr)
    {
        return 1;
    }
    return 1 + max(getheight(node->left), getheight(node->right));
}

int getbalance(node *node)
{
    int a = getheight(node->left), b = getheight(node->right);
    return a - b;
}

node *rotate(node *root, int balance)
{
    node *grandparent = root, *parent, *child;
    if (root == nullptr)
    {
        return nullptr;
    }
    if (abs(balance) < 1)
    {
        return root;
    }
    else if (balance < -1)
    {
        parent = grandparent->right;
        if (parent == nullptr)
        {
            cout << "Parent is null! " << endl;
            return root;
        }
        if (getbalance(parent) <= 0)
        {
            child = parent->right;
        }
        else
        {
            child = parent->left;
        }
    }
    else
    {
        parent = grandparent->left;
        if (parent == nullptr)
        {
            cout << "Parent is null! " << endl;
            return root;
        }
        if (getbalance(parent) <= 0)
        {
            child = parent->right;
        }
        else
        {
            child = parent->left;
        }
    }
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

node *search(node *root, int key)
{
    if (root == nullptr)
    {
        cout << "Key not found!" << endl;
        return nullptr;
    }
    if (root->data == key)
    {
        cout << "Found" << endl;
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

node *child(node *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (root->left != nullptr)
    {
        return root->left;
    }
    return root->right;
}

node *insert(node *root, int key)
{
    if (root == nullptr)
    {
        // cout << "Pass 2.1.1" << endl;
        root = create_node(key);
        // cout << "Pass 2.1.2" << endl;
        return root;
    }
    if (root->data == key)
    {
        cout << "Element is already present in the given tree!" << endl;
        return root;
    }
    if (root->data > key)
    {
        // cout << "Pass 2.1" << endl;
        root->left = insert(root->left, key);
        // cout << "Pass 2.2" << endl;
        if (root->left == nullptr)
        {
            cout << "root->left is null" << endl;
        }
        else
        {
            root->left->parent = root;
        }
    }
    else
    {
        root->right = insert(root->right, key);
        if (root->right == nullptr)
        {
            cout << "root->right is null" << endl;
        }
        else
        {
            root->right->parent = root;
        }
    }
    int balance = getbalance(root);
    if (abs(balance) <= 1)
    {
        return root;
    }
    if (root != nullptr && child(root) != nullptr)
    {
        root = rotate(root, balance);
    }
    return root;
}

void freemem(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    freemem(root->left);
    freemem(root->right);
    free(root);
}

vector<int> inorder(node *root)
{
    vector<int> res;
    function<void(node *)> dfs = [&](node *n)
    {
        if (!n)
            return;
        dfs(n->left);
        res.push_back(n->data);
        dfs(n->right);
    };
    dfs(root);
    return res;
}

void tests()
{
    node *root = nullptr;

    // Helper to verify AVL balance
    function<bool(node *)> isAVL = [&](node *root) -> bool
    {
        if (!root)
            return true;
        int diff = getbalance(root);
        if (abs(diff) > 1)
            return false;
        return isAVL(root->left) && isAVL(root->right);
    };

    // Test 1: Single insert
    root = insert(nullptr, 10);
    assert(root && root->data == 10);
    assert(getheight(root) == 1);
    freemem(root);

    // Test 2: LL Rotation
    root = nullptr;
    root = insert(root, 30);
    // cout << "Pass 1" << endl;
    root = insert(root, 20);
    // cout << "Pass 2" << endl;
    root = insert(root, 10);
    assert(root->data == 20);
    assert(isAVL(root));
    freemem(root);

    // Test 3: RR Rotation
    root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    assert(root->data == 20);
    assert(isAVL(root));
    freemem(root);

    // Test 4: LR Rotation
    root = nullptr;
    root = insert(root, 30);
    root = insert(root, 10);
    root = insert(root, 20);
    assert(root->data == 20);
    assert(isAVL(root));
    freemem(root);

    // Test 5: RL Rotation
    root = nullptr;
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 20);
    assert(root->data == 20);
    assert(isAVL(root));
    freemem(root);

    // Test 6: Complex insertions
    vector<int> keys = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    root = nullptr;
    for (int k : keys)
        root = insert(root, k);
    assert(isAVL(root));

    vector<int> in = inorder(root);
    assert(is_sorted(in.begin(), in.end()));
    freemem(root);

    // Test 7: Duplicates (if your insert ignores them)
    root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 10); // If duplicates not allowed
    vector<int> v = inorder(root);
    assert(adjacent_find(v.begin(), v.end()) == v.end()); // no duplicates
    freemem(root);

    // Test 8: Mixed numbers
    vector<int> mixed = {0, -10, 10, -20, 20};
    root = nullptr;
    for (int val : mixed)
        root = insert(root, val);
    assert(isAVL(root));
    vector<int> in_mix = inorder(root);
    assert(is_sorted(in_mix.begin(), in_mix.end()));
    freemem(root);

    // Test 9: Stress test
    root = nullptr;
    for (int i = 1; i <= 1000; ++i)
        root = insert(root, i);
    assert(isAVL(root));
    assert(getheight(root) <= 10); // AVL ensures log(n) height
    // cout << "Height :" << getheight(root) << endl;
    freemem(root);

    cout << "All test cases passed!" << endl;
}

int main()
{
    tests();
    struct node *root = nullptr;
    int a, b, c;
    cin >> a;
    for (int i = 0; i < a; i++)
    {
        int n;
        cin >> n;
        root = insert(root, n);
        cout << "Preorder traversal of the tree is: " << endl;
        printpreorder(root);
        cout << endl;
        cout << "Inorder traversal of the tree is: " << endl;
        printinorder(root);
        cout << endl;
    }
    cin >> b;
    for (int i = 0; i < b; i++)
    {
        int n;
        cin >> n;
        search(root, n);
    }
    cin >> c;
    for (int i = 0; i < c; i++)
    {
        int n;
        cin >> n;
        root = insert(root, n);
        cout << "Preorder traversal of the tree is: " << endl;
        printpreorder(root);
        cout << endl;
        cout << "Inorder traversal of the tree is: " << endl;
        printinorder(root);
        cout << endl;
    }
    free(root);
}