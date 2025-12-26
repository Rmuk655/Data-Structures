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

node *Tree::create_node(int key)
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

void Tree::freemem(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    freemem(root->left);
    freemem(root->right);
    free(root);
}

void Tree::printpreorder(node *root)
{
    if (root == nullptr)
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

void Tree::printinorder(node *root)
{
    if (root == nullptr)
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

int Tree::getheight(node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        return 1;
    }
    return 1 + max(getheight(root->left), getheight(root->right));
}

int Tree::getbalance(node *node)
{
    int a = getheight(node->left), b = getheight(node->right);
    return a - b;
}

node *Tree::rotate(node *root, int balance)
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
        if (Tree::getbalance(parent) <= 0)
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

node *Tree::search(node *root, int key)
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

node *Tree::child(node *root)
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

node *Tree::insert(node *root, int key)
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

void inorderHelper(node *root, vector<int> &result)
{
    if (root == nullptr)
        return;
    inorderHelper(root->left, result);
    result.push_back(root->data);
    inorderHelper(root->right, result);
}

vector<int> inorder(node *root)
{
    vector<int> result;
    inorderHelper(root, result);
    return result;
}