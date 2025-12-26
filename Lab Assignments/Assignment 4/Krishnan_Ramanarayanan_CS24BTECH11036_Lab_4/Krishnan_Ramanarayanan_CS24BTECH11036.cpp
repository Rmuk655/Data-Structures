#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

node *createNode(int key)
{
    node *root = new node;
    root->data = key;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}

struct node *insertLeft(struct node *root, int key)
{
    struct node *newnode = createNode(key);
    root->left = newnode;
    return root;
}

struct node *insertRight(struct node *root, int key)
{
    struct node *newnode = createNode(key);
    root->right = newnode;
    return root;
}

struct node *construct_tree(vector<int> preord, vector<int> inord)
{
    if (preord.empty())
    {
        return nullptr;
    }
    struct node *root = createNode(preord[0]);
    if (preord.size() == 1)
    {
        return root;
    }
    int left = 0, right = 0;
    for (int i = 0; i < inord.size(); i++)
    {
        if (inord[i] == preord[0])
        {
            left = i;
            break;
        }
    }
    right = inord.size() - 1 - left;
    vector<int> left_pre, left_in, right_pre, right_in;
    for (int i = 0; i < left; i++)
    {
        left_pre.push_back(preord[1 + i]);
        left_in.push_back(inord[i]);
    }
    for (int i = 0; i < right; i++)
    {
        right_pre.push_back(preord[1 + left + i]);
        right_in.push_back(inord[1 + left + i]);
    }
    struct node *l_child = construct_tree(left_pre, left_in);
    struct node *r_child = construct_tree(right_pre, right_in);
    if (left)
    {
        insertLeft(root, l_child->data);
        root->left = l_child;
    }
    if (right)
    {
        insertRight(root, r_child->data);
        root->right = r_child;
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

void postorder(struct node *root)
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
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int main()
{
    int k;
    cin >> k;
    while (k > 0)
    {
        struct node *root = nullptr;
        int n;
        cin >> n;
        vector<int> preord, inord;
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            preord.push_back(x);
        }
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            inord.push_back(x);
        }
        root = construct_tree(preord, inord);
        preorder(root);
        cout << endl;
        postorder(root);
        cout << endl;
        inorder(root);
        cout << endl;
        k--;
    }
}