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
};

struct node *createNode(int key)
{
    node *temp = new node;
    temp->data = key;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->parent = nullptr;
    temp->color = true;
    return temp;
}

struct node *search(struct node *root, int key)
{
    if (root == nullptr)
    {
        return root;
    }
    struct node *temp = root;
    while (temp != nullptr && temp->data != INT_MIN)
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

void left_rotate(struct node *&root, struct node *paren)
{
    struct node *child = paren->right;
    paren->right = child->left;
    if (child->left != nullptr)
    {
        child->left->parent = paren;
    }
    child->parent = paren->parent;
    if (paren->parent == nullptr)
    {
        root = child;
    }
    else if (paren == paren->parent->left)
    {
        paren->parent->left = child;
    }
    else
    {
        paren->parent->right = child;
    }
    child->left = paren;
    paren->parent = child;
}

void right_rotate(struct node *&root, struct node *paren)
{
    struct node *child = paren->left;
    paren->left = child->right;
    if (child->right != nullptr)
    {
        child->right->parent = paren;
    }
    child->parent = paren->parent;
    if (paren->parent == nullptr)
    {
        root = child;
    }
    else if (paren == paren->parent->left)
    {
        paren->parent->left = child;
    }
    else
    {
        paren->parent->right = child;
    }
    child->right = paren;
    paren->parent = child;
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
    while (temp2->parent != nullptr && temp2->parent->color == true)
    {
        struct node *uncle = other_child(temp2->parent->parent, temp2->parent);
        if (uncle != nullptr && uncle->color == true)
        {
            temp2->parent->parent->color = true;
            temp2->parent->color = false;
            uncle->color = false;
            temp2 = temp2->parent->parent;
        }
        else
        {
            if (temp2->parent == temp2->parent->parent->left)
            {
                if (temp2 == temp2->parent->right)
                {
                    temp2 = temp2->parent;
                    left_rotate(root, temp2);
                }
                temp2->parent->color = BLACK;
                temp2->parent->parent->color = RED;
                right_rotate(root, temp2->parent->parent);
            }
            else
            {
                if (temp2 == temp2->parent->left)
                {
                    temp2 = temp2->parent;
                    right_rotate(root, temp2);
                }
                temp2->parent->color = BLACK;
                temp2->parent->parent->color = RED;
                left_rotate(root, temp2->parent->parent);
            }
        }
        root->color = BLACK;
    }
    return root;
}

void transplant(node *&root, node *node1, node *node2)
{
    if (node1->parent == nullptr)
    {
        root = node2;
    }
    else if (node1 == node1->parent->left)
    {
        node1->parent->left = node2;
    }
    else
    {
        node1->parent->right = node2;
    }
    if (node2 != nullptr)
    {
        node2->parent = node1->parent;
    }
}

int del(struct node *&root, int key)
{
    if (!search(root, key))
    {
        cout << key << " is not found in the tree. Hence, it cannot be deleted." << endl;
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        int del_node_data = root->data;
        delete root;
        return del_node_data;
    }
    // search_node represents the node to be deleted by using the search function.
    // del_node represents the actual node to be deleted.
    // repl_node represents the node with which we have to replace del_node with after deleting it.
    struct node *search_node = search(root, key), *del_node = search_node, *repl_node = nullptr;
    bool orig_col = del_node->color;
    if (!search_node->left)
    {
        repl_node = search_node->right;
        transplant(root, search_node, search_node->right);
    }
    else if (!search_node->right)
    {
        repl_node = search_node->left;
        transplant(root, search_node, search_node->left);
    }
    else
    {
        del_node = search_node->right;
        while (del_node->left)
        {
            del_node = del_node->left;
        }
        orig_col = del_node->color;
        repl_node = del_node->right;
        if (del_node != search_node->right)
        {
            transplant(root, del_node, del_node->right);
            del_node->right = search_node->right;
            if (del_node->right)
            {
                del_node->right->parent = del_node;
            }
        }
        else if (repl_node)
        {
            repl_node->parent = del_node;
        }
        transplant(root, search_node, del_node);
        del_node->left = search_node->left;
        if (del_node->left)
        {
            del_node->left->parent = del_node;
        }
        del_node->color = search_node->color;
    }

    if (orig_col == BLACK)
    {
        while (repl_node && repl_node != root && repl_node->color == BLACK)
        {
            struct node *sibling = other_child(repl_node->parent, repl_node);
            if (sibling && repl_node->parent && repl_node == repl_node->parent->left)
            {
                if (sibling->color == RED)
                {
                    sibling->color = BLACK;
                    repl_node->parent->color = RED;
                    left_rotate(root, repl_node->parent);
                    sibling = repl_node->parent->right;
                }
                else if (sibling->left && sibling->left->color == BLACK && sibling->right && sibling->right->color == BLACK)
                {
                    sibling->color = RED;
                    repl_node = repl_node->parent;
                }
                else
                {
                    if (sibling->right && sibling->right->color == BLACK)
                    {
                        if (sibling->left)
                        {
                            sibling->left->color = BLACK;
                        }
                        sibling->color = RED;
                        right_rotate(root, sibling);
                        if (repl_node->parent)
                        {
                            sibling = repl_node->parent->right;
                        }
                    }
                    if (repl_node->parent)
                    {
                        sibling->color = repl_node->parent->color;
                        repl_node->parent->color = BLACK;
                    }
                    if (sibling->right)
                    {
                        sibling->right->color = BLACK;
                    }
                    left_rotate(root, repl_node->parent);
                    repl_node = root;
                }
            }
            else if (sibling)
            {
                if (sibling->color == RED)
                {
                    sibling->color = BLACK;
                    if (repl_node->parent)
                    {
                        repl_node->parent->color = RED;
                    }
                    right_rotate(root, repl_node->parent);
                    if (repl_node->parent)
                    {
                        sibling = repl_node->parent->left;
                    }
                }
                else if (sibling->left && sibling->left->color == BLACK && sibling->right && sibling->right->color == BLACK)
                {
                    sibling->color = RED;
                    repl_node = repl_node->parent;
                }
                else
                {
                    if (sibling->left && sibling->left->color == BLACK)
                    {
                        if (sibling->right)
                        {
                            sibling->right->color = BLACK;
                        }
                        sibling->color = RED;
                        left_rotate(root, sibling);
                        if (repl_node->parent)
                        {
                            sibling = repl_node->parent->left;
                        }
                    }
                    if (repl_node->parent)
                    {
                        sibling->color = repl_node->parent->color;
                        repl_node->parent->color = BLACK;
                    }
                    if (sibling->left)
                    {
                        sibling->left->color = BLACK;
                    }
                    right_rotate(root, repl_node->parent);
                    repl_node = root;
                }
            }
        }
        if (repl_node != nullptr)
        {
            repl_node->color = BLACK;
        }
    }

    int del_node_data = search_node->data;
    delete search_node;
    return del_node_data;
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
    vector<int> to_search = {32, 56, 90}, to_insert = {132, 156, 11, 7}, to_delete_1 = {21, 78, 132, 156, 112, 31, 5, 90}, to_delete = {332, 51, 71, 67};
    for (int i : to_search)
    {
        if (search(root, i))
        {
            cout << i << " is present in the tree." << endl;
        }
        else
        {
            cout << i << " is not present in the tree." << endl;
        }
    }
    for (int i : to_insert)
    {
        root = insert(root, i);
    }
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
    for (int i : to_delete_1)
    {
        if (search(root, i))
        {
            del(root, i);
        }
        else
        {
            cout << "The element " << i << " is not present in the red-black tree. Hence, we cannot delete it." << endl;
        }
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