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
    int data[3];
    struct node *children[4];
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

bool children(node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    for (int i = 0; i < 4; i++)
    {
        if (node->children[i] != nullptr)
        {
            return 1;
        }
    }
    return 0;
}

void printpreorder(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else if (!children(root))
    {
        for (int i = 0; i < 3; i++)
        {
            if (root->data[i] != INT_MAX)
            {
                cout << root->data[i] << " ";
            }
        }
        return;
    }
    cout << root->data[0] << " ";
    for (int i = 0; i < 4; i++)
    {
        printpreorder(root->children[i]);
        if (i < 2 && root->data[i + 1] != INT_MAX)
        {
            cout << root->data[i + 1] << " ";
        }
    }
}

void printinorder(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else if (!children(root))
    {
        for (int i = 0; i < 3; i++)
        {
            if (root->data[i] != INT_MAX)
            {
                cout << root->data[i] << " ";
            }
        }
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        if (root->children[i] != nullptr)
        {
            printinorder(root->children[i]);
            if (root->data[i] != INT_MAX)
            {
                cout << root->data[i] << " ";
            }
        }
    }
    printinorder(root->children[3]);
    return;
}

node *search(node *root, int key)
{
    if (root == nullptr)
    {
        cout << "Key not found!" << endl;
        return nullptr;
    }
    else if (!children(root))
    {
        for (int i = 0; i < 3; i++)
        {
            if (root->data[i] == key)
            {
                cout << "Found " << root->data[i] << endl;
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
            cout << "Found " << root->data[i] << endl;
            return root;
        }
        else if (key > root->data[i] && key < root->data[i + 1])
        {
            return search(root->children[i + 1], key);
        }
    }
    if (key > root->data[2])
    {
        return search(root->children[3], key);
    }
    else if (key == root->data[2])
    {
        return root;
    }
    return nullptr;
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

int elements_in_node(node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    for (int i = 0; i < 3; i++)
    {
        if (node->data[i] == INT_MAX)
        {
            return i;
        }
    }
    return 3;
}

void splitchild(node *x, int i)
{
    if (!not_full_node(x))
    {
        return;
    }
    node *y = x->children[i - 1];
    node *z = create_new_node(y->data[2]);
    int size_z = (3 + 1) / 2 - 1;
    if (children(y))
    {
        for (int j = 0; j <= size_z; j++)
        {
            z->children[j] = y->children[j + size_z + 1];
            y->children[j + size_z + 1] = nullptr;
        }
    }
    // node *temp1 = x->children[3];
    for (int j = elements_in_node(x); j >= i; j--)
    {
        x->children[j + 1] = x->children[j];
    }
    x->children[i] = z;
    // int temp = x->data[2];
    for (int j = (elements_in_node(x) - 1); j >= (i - 1); j--)
    {
        x->data[j + 1] = x->data[j];
    }
    // if (i == 1)
    // {
    //     x->data[i] = x->data[i - 1];
    // }
    x->data[i - 1] = y->data[1];
    y->data[1] = INT_MAX;
    y->data[2] = INT_MAX;
}

node *splitroot(node *&root)
{
    node *split = create_new_node(INT_MAX);
    split->children[0] = root;
    root = split;
    splitchild(split, 1);
    split->children[0]->data[1] = INT_MAX;
    split->children[0]->data[2] = INT_MAX;
    return split;
}

void insertnonfull(node *node, int key)
{
    int index = elements_in_node(node);
    if (!children(node))
    {
        while (index > 0 && key < node->data[index - 1])
        {
            node->data[index] = node->data[index - 1];
            index--;
        }
        node->data[index] = key;
    }
    else
    {
        while (index >= 1 && key < node->data[index - 1])
        {
            index--;
        }
        index++;
        if (elements_in_node(node->children[index - 1]) == 3)
        {
            splitchild(node, index);
            if (key > node->data[index - 1])
            {
                index++;
            }
        }
        insertnonfull(node->children[index - 1], key);
    }
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
    if (elements_in_node(root) == 3)
    {
        node *split = splitroot(root);
        insertnonfull(split, key);
    }
    else
    {
        insertnonfull(root, key);
    }
    return root;
}

void freemem(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        freemem(root->children[i]);
    }
    free(root);
}

vector<int> get_inorder(node *root)
{
    vector<int> res;
    if (!root)
        return res;
    int i = 0;
    while (i < 3 && root->data[i] != INT_MAX)
    {
        if (root->children[i])
        {
            vector<int> left = get_inorder(root->children[i]);
            res.insert(res.end(), left.begin(), left.end());
        }
        res.push_back(root->data[i]);
        i++;
    }
    if (root->children[i])
    {
        vector<int> right = get_inorder(root->children[i]);
        res.insert(res.end(), right.begin(), right.end());
    }
    return res;
}

vector<int> get_preorder(node *root)
{
    vector<int> res;
    if (!root)
        return res;
    int i = 0;
    while (i < 3 && root->data[i] != INT_MAX)
    {
        res.push_back(root->data[i]);
        i++;
    }
    for (int j = 0; j <= i; j++)
    {
        if (root->children[j])
        {
            vector<int> child = get_preorder(root->children[j]);
            res.insert(res.end(), child.begin(), child.end());
        }
    }
    return res;
}

void assert_equal(const vector<int> &v1, const vector<int> &v2, const string &msg)
{
    assert(v1 == v2 && msg.c_str());
}

void test()
{
    node *root = nullptr;

    // Test 1: Insert single element
    root = insert(root, 50);
    assert(search(root, 50) != nullptr);
    assert_equal(get_inorder(root), {50}, "Test 1 failed");
    cout << "Test 1 passed\n";

    // Test 2: Insert multiple elements (no split)
    root = insert(root, 20);
    root = insert(root, 70);
    assert_equal(get_inorder(root), {20, 50, 70}, "Test 2 failed");
    assert_equal(get_preorder(root), {20, 50, 70}, "Test 2 Preorder failed");
    cout << "Test 2 passed\n";

    // Test 3: Search for existing and non-existing keys
    assert(search(root, 20) != nullptr);
    assert(search(root, 99) == nullptr);
    cout << "Test 3 passed\n";

    // Test 4: Insert causing root split
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 90);
    assert_equal(get_inorder(root), {10, 20, 30, 50, 70, 90}, "Test 4 failed");
    cout << "Test 4 passed\n";

    // Test 5: Insert many elements and verify sorted order
    vector<int> keys = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
    for (int k : keys)
        root = insert(root, k);
    vector<int> expected(keys.begin(), keys.end());
    expected.insert(expected.end(), {10, 20, 30, 50, 70, 90});
    sort(expected.begin(), expected.end());
    assert_equal(get_inorder(root), expected, "Test 5 failed");
    cout << "Test 5 passed\n";

    // Test 6: Insert duplicate
    node *tmp = insert(root, 25); // should print duplicate warning and not insert
    assert_equal(get_inorder(root), expected, "Test 6 failed (duplicate insert)");
    cout << "Test 6 passed\n";

    // Test 7: Search for edge values
    assert(search(root, 5) != nullptr);
    assert(search(root, 95) != nullptr);
    assert(search(root, 999) == nullptr);
    cout << "Test 7 passed\n";

    // Test 8: Insert to cause multiple internal node splits
    vector<int> extra = {1, 2, 3, 4};
    for (int k : extra)
        root = insert(root, k);
    expected.insert(expected.end(), extra.begin(), extra.end());
    sort(expected.begin(), expected.end());
    assert_equal(get_inorder(root), expected, "Test 8 failed");
    cout << "Test 8 passed\n";

    cout << "All test cases passed!" << endl;
}

int main()
{
    test();
    struct node *root = nullptr;
    int a, b, c, n;
    cout << "Enter the number of elements to be inserted in the RB Tree" << endl;
    cin >> a;
    // vector<int> nums_create = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    vector<int> nums_create;
    for (int i = 0; i < a /*(int)nums_create.size()*/; i++)
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
    // vector<int> nums_search = {32, 56, 90};
    vector<int> nums_search;
    for (int i = 0; i < b /*(int)nums_search.size()*/; i++)
    {
        cin >> n;
        nums_search.push_back(n);
        node *result = search(root, nums_search[i]);
        if (result != nullptr)
        {
            cout << "Search for " << nums_search[i] << " successful" << endl;
        }
        else if (result == nullptr)
        {
            cout << "Search for " << nums_search[i] << " unsuccessful" << endl;
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
    vector<int> nums_insert_2 = {32, 56, 21, 90};
    for (int i = 0; i < c /*(int)nums_insert_2.size()*/; i++)
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