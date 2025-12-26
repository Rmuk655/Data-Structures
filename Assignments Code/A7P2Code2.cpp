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
    int data[3]; // Only data[3] is valid, data[4] will be accessed while splitting.
    struct node *children[5];
    struct node *parent;
};

node *create_new_node(int key)
{
    node *root = (node *)malloc(sizeof(node));
    if (!root)
    {
        cerr << "Memory allocation failed for root!" << endl;
        exit(1);
    }
    root->data[0] = key;
    for (int i = 1; i < 3; i++)
    {
        root->data[i] = INT_MAX;
    }
    for (int i = 0; i < 4; i++)
    {
        root->children[i] = nullptr;
    }
    root->parent = nullptr;
    return root;
}

bool not_full_node(node *node)
{
    for (int i = 0; i < 3; i++)
    {
        if (node->data[i] == INT_MAX)
        {
            return 1;
        }
    }
    return 0;
}

int insert_in_children(node *root, int key)
{
    if (key < root->data[0])
    {
        return 0;
    }
    else if (key > root->data[0] && key < root->data[1])
    {
        return 1;
    }
    else if (key > root->data[1] && key < root->data[2])
    {
        return 2;
    }
    return 3;
}

void insert_in_a_node(node *root, int key)
{
    if (root->data[0] > key)
    {
        root->data[2] = root->data[1];
        root->data[1] = root->data[0];
        root->data[0] = key;
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        if (root->data[i] < key && root->data[i + 1] > key)
        {
            for (int j = i + 1; j < 2; j++)
            {
                root->data[j + 1] = root->data[j];
            }
            root->data[i + 1] = key;
            return;
        }
    }
}

void fix_overflow(node *root, int key)
{
    if (root->parent == nullptr)
    {
        node *child_1 = create_new_node(key);
        node *child_2 = create_new_node(root->data[1]);
        child_1->parent = root;
        child_2->parent = root;
        child_1->children[0] = root->children[0];
        child_1->children[1] = root->children[1];
        child_2->children[0] = root->children[2];
        child_1->children[1] = root->children[3];
        root->children[0] = child_1;
        root->children[1] = child_2;
        child_2->data[1] = root->data[2];
        root->data[1] = INT_MAX;
        root->data[2] = INT_MAX;
        return;
    }
    int i, c = 0;
    vector<int> vec;
    for (i = 0; i < 3; i++)
    {
        if (c == 0 && root->data[i] > key)
        {
            vec.push_back(key);
            c = 1;
        }
        vec.push_back(root->data[i]);
    }
    node *sibling = create_new_node(vec[2]);
    insert_in_a_node(sibling, vec[3]);
    sibling->parent = root->parent;
    root->data[1] = INT_MAX;
    root->data[2] = INT_MAX;
    if (not_full_node(root->parent))
    {
        insert_in_a_node(root->parent, vec[1]);
    }
    else
    {
        fix_overflow(root->parent, vec[1]);
    }
    root->parent->children[2] = sibling;
    int pos;
    for (int i = 0; i < 4; i++)
    {
        if (root->parent->children[i] == root)
        {
            pos = i;
        }
    }
    if (pos < 3)
    {
        root->parent->children[pos + 1] = sibling;
    }
    else
    {
        fix_overflow(root->parent, key);
    }
}

bool children(node *node)
{
    for (int i = 0; i < 4; i++)
    {
        if (node->children[i] != nullptr)
        {
            return 1;
        }
    }
    return 0;
}

node *search(node *root, int key)
{
    if (root == nullptr)
    {
        // cout << "Key not found!" << endl;
        return nullptr;
    }
    else if (!children(root))
    {
        for (int i = 0; i < 3; i++)
        {
            if (root->data[i] == key)
            {
                cout << "Found" << endl;
                return root;
            }
        }
        return nullptr;
    }
    if (key < root->data[0])
    {
        return search(root->children[0], key);
    }
    for (int i = 0; i < 2; i++)
    {
        if (root->data[i] == key)
        {
            cout << "Found" << endl;
            return root;
        }
        else if (key > root->data[i] && key < root->data[i + 1])
        {
            return search(root->children[i], key);
        }
    }
    if (key > root->data[2])
    {
        return search(root->children[3], key);
    }
    return nullptr;
}

node *insert(node *root, int key)
{
    if (root == nullptr)
    {
        root = create_new_node(key);
        return root;
    }
    else if (search(root, key) != nullptr)
    {
        cout << "Cannot insert duplicate value" << endl;
        return root;
    }
    else if (!children(root))
    {
        if (not_full_node(root))
        {
            insert_in_a_node(root, key);
        }
        else
        {
            fix_overflow(root, key);
        }
        return root;
    }
    int pos = insert_in_children(root, key);
    insert(root->children[pos], key);
    return root;
}