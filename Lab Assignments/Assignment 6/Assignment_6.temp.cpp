#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define RED true
#define BLACK false

struct node
{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
    bool color;
    // int black_depth;
};

struct node *createNode(int key)
{
    node *temp = new node;
    temp->data = key;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->parent = nullptr;
    temp->color = true;
    // temp->black_depth = 0;
    return temp;
}

struct node *search(struct node *root, int key)
{
    if (root == nullptr)
    {
        return root;
    }
    struct node *temp = root;
    while (temp != nullptr)
    {
        if (key == temp->data)
        {
            break;
        }
        else if (key < temp->data)
        {
            temp = temp->left;
        }
        else if (key > temp->data)
        {
            temp = temp->right;
        }
    }
    if (temp == nullptr || temp->data != key)
    {
        return nullptr;
    }
    return temp;
}

struct node *other_child(struct node *parent, struct node *child1)
{
    if (parent->left == child1)
    {
        return parent->right;
    }
    return parent->left;
}

void rotate(struct node *&root, struct node *grandparent, struct node *paren, struct node *child)
{
    if (grandparent->right == paren && paren->right == child)
    {
        grandparent->right = paren->left;
        if (paren->left)
        {
            paren->left->parent = grandparent;
        }
        paren->left = grandparent;
        if (!grandparent->parent)
        {
            root = paren;
        }
        else
        {
            paren->parent = grandparent->parent;
        }
        if (grandparent->parent)
        {
            if (grandparent->parent->right == grandparent)
            {
                grandparent->parent->right = paren;
            }
            else
            {
                grandparent->parent->left = paren;
            }
        }
        grandparent->parent = paren;

        grandparent->color = true;
        paren->color = false;
    }
    else if (grandparent->right == paren && paren->left == child)
    {
        grandparent->right = child;
        child->parent = grandparent;
        paren->left = child->right;
        if (child->right)
        {
            child->right->parent = paren;
        }
        child->right = paren;
        paren->parent = child;

        grandparent->right = child->left;
        if (child->left)
        {
            child->left->parent = grandparent;
        }
        child->left = grandparent;
        child->parent = grandparent->parent;
        if (grandparent->parent)
        {
            if (grandparent->parent->right == grandparent)
            {
                grandparent->parent->right = child;
            }
            else
            {
                grandparent->parent->left = child;
            }
        }
        grandparent->parent = child;

        child->color = BLACK;
        grandparent->color = RED;
    }
    else if (grandparent->left == paren && paren->right == child)
    {
        grandparent->left = child;
        child->parent = grandparent;
        paren->right = child->left;
        if (child->left)
        {
            child->left->parent = paren;
        }
        child->left = paren;
        paren->parent = child;

        grandparent->left = child->right;
        if (child->right)
        {
            child->right->parent = grandparent;
        }
        child->right = grandparent;
        child->parent = grandparent->parent;
        if (grandparent->parent)
        {
            if (grandparent->parent->left == grandparent)
            {
                grandparent->parent->left = child;
            }
            else
            {
                grandparent->parent->right = child;
            }
        }
        grandparent->parent = child;
        child->color = BLACK;
        grandparent->color = RED;
    }
    else if (grandparent->left == paren && paren->left == child)
    {
        grandparent->left = paren->right;
        paren->parent = grandparent->parent;
        if (!grandparent->parent)
        {
            root = paren;
        }
        if (paren->right)
        {
            paren->right->parent = grandparent;
        }
        paren->right = grandparent;
        if (grandparent->parent)
        {
            if (grandparent->parent->right == grandparent)
            {
                grandparent->parent->right = paren;
            }
            else
            {
                grandparent->parent->left = paren;
            }
        }
        grandparent->parent = paren;
        grandparent->color = true;
        paren->color = false;
    }
}

struct node *insert(struct node *root, int key)
{
    if (search(root, key))
    {
        cout << "Duplicate element inserted" << endl;
        return root;
    }
    else if (root == nullptr)
    {
        root = createNode(key);
        root->color = false;
        return root;
    }
    struct node *temp = root;
    while (temp != nullptr)
    {
        if (key < temp->data)
        {
            if (temp->left == nullptr)
            {
                break;
            }
            temp = temp->left;
        }
        else
        {
            if (temp->right == nullptr)
            {
                break;
            }
            temp = temp->right;
        }
    }
    node *temp2 = createNode(key);
    if (key < temp->data)
    {
        temp->left = temp2;
        temp2->parent = temp;
    }
    else
    {
        temp->right = temp2;
        temp2->parent = temp;
    }
    while (temp2->parent != nullptr && temp2->color == true && temp2->parent->color == true)
    {
        struct node *uncle = other_child(temp2->parent->parent, temp2->parent);
        if (uncle == nullptr || uncle->color == false)
        {
            rotate(root, temp2->parent->parent, temp2->parent, temp2);
            root->color = BLACK;
        }
        else if (uncle->color == true)
        {
            temp2->parent->parent->color = true;
            temp2->parent->color = false;
            uncle->color = false;
            temp2 = temp2->parent->parent;
        }
    }
    return root;
}

struct node *del(struct node *root, int key)
{
    if (!search(root, key))
    {
        cout << "The element " << key << " is not present in the red-black tree. Hence, we cannot delete it." << endl;
    }
    struct node *temp = search(root, key);
    if (temp->left == nullptr && temp->right == nullptr)
    {
        delete temp;
    }
    return root;
}

void preorder(struct node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << " ";
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << " ";
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void test()
{
    struct node *root = nullptr;
    vector<int> to_create = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    for (int i : to_create)
    {
        root = insert(root, i);
    }
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
    vector<int> to_search = {32, 56, 90}, to_insert = {132, 156, 11, 7}, to_delete = {332, 51, 71, 67};
    for (int i : to_search)
    {
        root = search(root, i);
    }
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
    for (int i : to_insert)
    {
        root = insert(root, i);
    }
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
    for (int i : to_delete)
    {
        del(root, i);
    }
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
}

int main()
{
    struct node *root = nullptr;
    test();
    int n;
    cin >> n;
    vector<int> vec;
    while (n > 0)
    {
        int x;
        cin >> x;
        vec.push_back(x);
        root = insert(root, x);
        n--;
    }
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
    cout << "Enter your choice: " << endl;
    cout << "1 - Search for an element" << endl;
    cout << "2 - Insert an element" << endl;
    cout << "3 - Delete an element" << endl;
    cout << "0 - Exit" << endl;
    int op;
    cin >> op;
    while (op)
    {
        if (op == 1)
        {
            int key;
            cin >> key;
            search(root, key);
        }
        else if (op == 2)
        {
            int key;
            cin >> key;
            insert(root, key);
            cout << "The inorder traversal of the tree is: ";
            inorder(root);
            cout << endl;
            cout << "The preorder traversal of the tree is: ";
            preorder(root);
            cout << endl;
        }
        else if (op == 3)
        {
            int key;
            cin >> key;
            if (search(root, key))
            {
                cout << del(root, key) << " is deleted from the Red-Black Tree" << endl;
            }
            else
            {
                cout << "The element " << key << " is not present in the red-black tree. Hence, we cannot delete it." << endl;
            }
        }
        cout << "Enter your choice: " << endl;
        cout << "1 - Search for an element" << endl;
        cout << "2 - Insert an element" << endl;
        cout << "3 - Delete an element" << endl;
        cout << "0 - Exit" << endl;
        int op;
        cin >> op;
    }
}