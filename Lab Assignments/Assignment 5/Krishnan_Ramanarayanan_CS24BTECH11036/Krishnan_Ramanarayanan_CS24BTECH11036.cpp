#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

// Time Complexity of insert function = O(n)
// Space Complexity of insert function = O(1)
struct node *insert(struct node *root, int key)
{
    if (root == nullptr)
    {
        node *root = new struct node();
        root->data = key;
        root->left = nullptr;
        root->right = nullptr;
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
    node *temp2 = new struct node();
    temp2->data = key;
    temp2->left = nullptr;
    temp2->right = nullptr;
    if (key < temp->data)
    {
        temp->left = temp2;
    }
    else
    {
        temp->right = temp2;
    }
    return root;
}

// Time Complexity of search function = O(n)
// Space Complexity of search function = O(1)
struct node *search(struct node *root, int key)
{
    if (root == nullptr)
    {
        return nullptr;
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

struct node *parent(struct node *root, struct node *node)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (!search(root, node->data))
    {
        cout << "Cannot find node. Hence, cannot find it's parent" << endl;
        return nullptr;
    }
    else if (root == node)
    {
        return nullptr;
    }
    struct node *parent = root;
    while (parent != nullptr && !(parent->left == node || parent->right == node))
    {
        if (node->data < parent->data)
        {
            parent = parent->left;
        }
        else
        {
            parent = parent->right;
        }
    }
    return parent;
}

// Time Complexity of successor function = O(h^2), h = height of tree.
// Space Complexity of successor function = O(1)
struct node *successor(struct node *root, int key)
{
    struct node *node = search(root, key);
    if (node->right != nullptr)
    {
        struct node *temp = node->right;
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }
    struct node *succ = parent(root, node);
    while (succ != nullptr && succ->right == node)
    {
        node = succ;
        succ = parent(root, succ);
    }
    return succ;
}

// Time Complexity of delete function = O(n^2)
// Space Complexity of delete function = O(n)
struct node *del(struct node *root, int key)
{
    struct node *node = search(root, key);
    if (node->left == nullptr && node->right == nullptr)
    {
        struct node *par = parent(root, node);
        if (par == nullptr)
        {
            delete root;
            return nullptr;
        }
        if (par->left == node)
        {
            par->left = nullptr;
        }
        else
        {
            par->right = nullptr;
        }
        delete node;
        return root;
    }
    else if (node->left != nullptr && node->right == nullptr)
    {
        struct node *par = parent(root, node);
        if (par == nullptr)
        {
            root = node->left;
            delete node;
            return root;
        }
        if (par->left == node)
        {
            par->left = node->left;
        }
        else
        {
            par->right = node->left;
        }
        return root;
    }
    else if (node->left == nullptr && node->right != nullptr)
    {
        struct node *par = parent(root, node);
        if (par == nullptr)
        {
            root = node->right;
            delete node;
            return root;
        }
        if (par->left == node)
        {
            par->left = node->right;
        }
        else
        {
            par->right = node->right;
        }
        return root;
    }
    struct node *temp = node->right;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }
    node->data = temp->data;
    node->right = del(node->right, node->data);
    return root;
}

int height(struct node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        return 1;
    }
    return 1 + max(height(root->left), height(root->right));
}

void print_level(struct node *root, int level)
{
    if (root == nullptr)
    {
        return;
    }
    else if (level == 1)
    {
        cout << root->data << " ";
    }
    print_level(root->left, level - 1);
    print_level(root->right, level - 1);
}

void print_level_order(struct node *root)
{
    if (root == nullptr)
    {
        return;
    }
    int h = height(root);
    for (int i = 1; i <= h; i++)
    {
        print_level(root, i);
    }
}

// Test function incorporates the test cases given in the question itself to verify the functionality of the above code.
// Uncomment the code to run the tests and see the printed detailed outputs on the screen.
void test()
{
    struct node *root = nullptr;
    vector<int> vec = {12, 31, 34, 56, 78, 89, 91, 32, 56, 81, 100, 2, 55, 21, 99, 121, 67};
    for (int i = 0; i < vec.size(); i++)
    {
        if (!search(root, vec[i]))
        {
            root = insert(root, vec[i]);
        }
    }
    vector<int> sea = {32, 56, 90}, ins = {32, 56, 21, 90}, succ = {32, 56, 21, 90}, dele = {332, 51, 71, 67};
    for (int i = 0; i < sea.size(); i++)
    {
        if (!search(root, sea[i]))
        {
            cout << sea[i] << " is not present in the tree!" << endl;
        }
        else
        {
            cout << sea[i] << " found!" << endl;
        }
    }
    for (int i = 0; i < ins.size(); i++)
    {
        if (!search(root, ins[i]))
        {
            root = insert(root, ins[i]);
            cout << "Inserted element " << ins[i] << " into the tree!" << endl;
        }
        else
        {
            cout << "Cannot insert duplicate element " << ins[i] << " into the tree!" << endl;
        }
    }
    cout << "Level order of the tree after insertions: " << endl;
    print_level_order(root);
    cout << endl;
    for (int i = 0; i < succ.size(); i++)
    {
        if (search(root, succ[i]))
        {
            cout << successor(root, succ[i])->data << " is the successor of " << succ[i] << endl;
        }
        else
        {
            cout << succ[i] << " is not present in the tree. Hence, it's successor cannot be found!" << endl;
        }
    }
    for (int i = 0; i < dele.size(); i++)
    {
        if (!search(root, dele[i]))
        {
            cout << dele[i] << " is not present in the tree! Cannot delete element!" << endl;
        }
        else
        {
            root = del(root, dele[i]);
            cout << "Deleted element " << dele[i] << " from the tree!" << endl;
        }
    }
    cout << "Level order of the tree after deletions: " << endl;
    print_level_order(root);
    cout << endl;
}

// Main function is for running the code with user input.
int main()
{
    // Uncomment to run the test code.
    // test();
    struct node *root = nullptr;
    int n;
    cin >> n;
    vector<int> vec;
    while (n > 0)
    {
        int x;
        cin >> x;
        vec.push_back(x);
        n--;
    }
    for (int i = 0; i < vec.size(); i++)
    {
        if (!search(root, vec[i]))
        {
            root = insert(root, vec[i]);
        }
    }
    print_level_order(root);
    cout << endl;
    cout << "Enter your choice: " << endl;
    cout << "1 - Search for an element" << endl;
    cout << "2 - Insert an element" << endl;
    cout << "3 - Find the successor of an element" << endl;
    cout << "4 - Delete an element" << endl;
    cout << "0 - Exit" << endl;
    int op;
    cin >> op;
    while (op != 0)
    {
        if (op == 1)
        {
            int x;
            cin >> x;
            if (!search(root, x))
            {
                cout << "Element is not present in the tree!" << endl;
            }
            else
            {
                cout << "Element found!" << endl;
            }
        }
        else if (op == 2)
        {
            int x;
            cin >> x;
            if (!search(root, x))
            {
                root = insert(root, x);
            }
            print_level_order(root);
            cout << endl;
        }
        else if (op == 3)
        {
            int x;
            cin >> x;
            if (!search(root, x))
            {
                cout << "Element is not present in the tree. Cannot find it's successor!" << endl;
            }
            else
            {
                cout << successor(root, x)->data << endl;
            }
        }
        else if (op == 4)
        {
            int x;
            cin >> x;
            if (search(root, x))
            {
                root = del(root, x);
                print_level_order(root);
                cout << endl;
            }
            else
            {
                cout << "Cannot delete element as it doesn't exist in the tree!" << endl;
            }
        }
        cin >> op;
    }
}