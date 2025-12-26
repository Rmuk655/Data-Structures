#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include "Tree.h"

using namespace std;

node *del(node *root, int key)
{
    Tree t(root);

    if (t.search(root, key) == nullptr)
    {
        cout << "Key not found!" << endl;
        return root;
    }
    if (root == nullptr)
    {
        cout << "Error! Key not found!" << endl;
        return nullptr;
    }
    if (root->data > key)
    {
        root->left = del(root->left, key);
    }
    else if (root->data < key)
    {
        root->right = del(root->right, key);
    }
    else if (root->data == key)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            free(root);
            root = nullptr;
            return nullptr;
        }
        else if (root->left == nullptr && root->right != nullptr)
        {
            node *child = root->right;
            child->parent = root->parent;
            free(root);
            return child;
        }
        else if (root->right == nullptr && root->left != nullptr)
        {
            node *child = root->left;
            child->parent = root->parent;
            free(root);
            return child;
        }
        else
        {
            node *x = root->right;
            while (x->left != nullptr)
            {
                x = x->left;
            }
            int n = x->data;
            del(root, x->data);
            root->data = n;
        }
    }

    int balance = t.getbalance(root);
    if (abs(balance) <= 1)
    {
        return root;
    }
    if (root != nullptr && t.child(root) != nullptr)
    {
        root = t.rotate(root, balance);
    }
    // return root;

    int balanceleft = t.getbalance(root->left), balanceright = t.getbalance(root->right);
    while (root != nullptr && t.child(root) != nullptr && ((abs(balanceleft) > 1) || (abs(balanceright)) > 1))
    {
        cout << "While loop entered" << endl;
        if (abs(balanceleft) > 1 && abs(balanceright) <= 1)
        {
            root->left = t.rotate(root->left, balanceleft);
        }
        else if (abs(balanceright) > 1 && abs(balanceleft) <= 1)
        {
            root->right = t.rotate(root->right, balanceright);
        }
        else if (abs(balanceleft) > 1 && (abs(balanceright) > 1))
        {
            root->left = t.rotate(root->left, balanceleft);
            root->right = t.rotate(root->right, balanceright);
        }
        balanceleft = t.getbalance(root->left);
        balanceright = t.getbalance(root->right);
        cout << "While loop done one time" << endl;
    }
    cout << "While loop exited" << endl;
    return root;
}

void testdel()
{
    node *head = nullptr;
    Tree t(head);

    // Test 1: Simple delete of leaf node (no rotation)
    head = nullptr;
    vector<int> nums_create = {30, 20, 40, 10};
    for (int val : nums_create)
        head = t.insert(head, val);

    head = del(head, 40);
    assert(t.search(head, 40) == nullptr);
    t.freemem(head);

    // Test 2: Delete causing Left-Left (LL) rotation
    head = nullptr;
    nums_create = {30, 20, 10};
    for (int val : nums_create)
        head = t.insert(head, val);

    head = del(head, 10); // Deletes leaf, triggers rebalance
    assert(t.search(head, 10) == nullptr);
    assert(abs(t.getbalance(head)) <= 1);
    t.freemem(head);

    // Test 3: Delete causing Left-Right (LR) rotation
    head = nullptr;
    nums_create = {30, 20, 40, 25};
    for (int val : nums_create)
        head = t.insert(head, val);

    head = del(head, 40);
    assert(t.search(head, 40) == nullptr);
    assert(abs(t.getbalance(head)) <= 1);
    t.freemem(head);

    // Test 4: Delete causing Right-Left (RL) rotation
    head = nullptr;
    nums_create = {10, 5, 20, 6};
    for (int val : nums_create)
        head = t.insert(head, val);

    head = del(head, 20);
    assert(t.search(head, 20) == nullptr);
    assert(abs(t.getbalance(head)) <= 1);
    t.freemem(head);

    // Test 5: Larger tree with multiple deletes
    head = nullptr;
    nums_create = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    for (int val : nums_create)
        head = t.insert(head, val);

    vector<int> nums_delete = {78, 88, 9, 112, 45};
    for (int val : nums_delete)
    {
        head = del(head, val);
        assert(t.search(head, val) == nullptr);
        assert(abs(t.getbalance(head)) <= 1);
    }
    t.freemem(head);

    // Test 6: Deleting root repeatedly
    head = nullptr;
    nums_create = {50, 30, 70, 60, 80};
    for (int val : nums_create)
        head = t.insert(head, val);

    while (head != nullptr)
    {
        int root_val = head->data;
        head = del(head, root_val);
        assert(t.search(head, root_val) == nullptr);
        if (head != nullptr)
            assert(abs(t.getbalance(head)) <= 1);
    }

    cout << "All deletion test cases passed successfully!" << endl;
}

int main()
{
    testdel();
    struct node *root = nullptr;
    Tree t(root);
    vector<int> nums_create = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    for (int i = 0; i < (int)nums_create.size(); i++)
    {
        root = t.insert(root, nums_create[i]);
    }
    t.printinorder(root);
    cout << endl;
    t.printpreorder(root);
    cout << endl;
    vector<int> nums_delete = {78, 88, 9, 71, 67};
    for (int i = 0; i < (int)nums_delete.size(); i++)
    {
        root = del(root, nums_delete[i]);
        t.printinorder(root);
        cout << endl;
        t.printpreorder(root);
        cout << endl;
    }
    t.freemem(root);
}