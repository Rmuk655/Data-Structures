#include <iostream>
#include <string>

using namespace std;

// Time complexity = O(n^2)
// Space complexity = O(1)

// Definition of each node of the tree.
struct node
{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
};

// Time Complexity of insert function = O(n)
// Space Complexity of insert function = O(1)
// Insert function to construct the tree with root root by adding new nodes with value key.
struct node *insert(struct node *root, int key)
{
    // Handling an edge case when root is nullptr, we have to create the root of the tree itself.
    if (root == nullptr)
    {
        node *root = new struct node();
        root->data = key;
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;
        return root;
    }
    // We now set temp as root and traverse through the tree to insert the new node at the appropriate place.
    node *temp = root;
    while (temp != nullptr)
    {
        // If key < temp->data, then we go to the left subtree of temp (if not null) and insert the new node at the appropriate place in the left subtree.
        if (key < temp->data)
        {
            if (temp->left == nullptr)
            {
                break;
            }
            temp = temp->left;
        }
        // If key > temp->data, then we go to the right subtree of temp (if not null) and insert the new node at the appropriate place in the right subtree.
        else if (key > temp->data)
        {
            if (temp->right == nullptr)
            {
                break;
            }
            temp = temp->right;
        }
        // Handling edge case where duplicate values are inserted into the tree.
        else
        {
            cout << "Duplicate values cannot be inserted into the tree!" << endl;
            return root;
        }
    }
    // We create the new node as temp2 and set its pointers appropriately.
    node *temp2 = new struct node();
    temp2->data = key;
    temp2->left = nullptr;
    temp2->right = nullptr;
    // Since we break if temp->left or temp->right is null and we still need to insert the node, we check for two cases:
    // Case 1: If key < temp->data, we insert the new node temp2 as the left child of temp.
    if (key < temp->data)
    {
        temp->left = temp2;
    }
    // Case 2: If key > temp->data, we insert the new node temp2 as the right child of temp.
    else
    {
        temp->right = temp2;
    }
    // We set the parent pointer of the child temp2 too.
    temp2->parent = temp;
    return root;
}

// Time Complexity of search function = O(h) = O(n) (worst case), h is the height of the Binary Search Tree.
// Space Complexity of search function = O(1)
// Search function used to search for a given node in a BST.
struct node *search(struct node *root, int key)
{
    // If the root is nullptr, return nullptr as the tree doesn't exist and hence the key cannot be find.
    if (root == nullptr)
    {
        return nullptr;
    }
    // Else, set a temp pointer to the root of the tree and visit each node of the tree till temp is nullptr which means the tree ends there.
    struct node *temp = root;
    while (temp != nullptr)
    {
        // If we find the node with matching value, we break out of the loop and return temp as the node with the given value key.
        if (key == temp->data)
        {
            break;
        }
        // If we do not find the node, we check key < temp->data, implying that key might be present in the left subtree of the node temp.
        // So, we set temp as temp->left to search for the node with data = key in the left subtree of the node temp.
        else if (key < temp->data)
        {
            temp = temp->left;
        }
        // If we do not find the node, we check key > temp->data, implying that key might be present in the right subtree of the node temp.
        // So, we set temp as temp->right to search for the node with data = key in the right subtree of the node temp.
        else if (key > temp->data)
        {
            temp = temp->right;
        }
    }
    // If temp is nullptr or temp->data of the current value of node* temp doesn't match the value key even after searching throughout tree
    //  then it implies that we have not found the node with the given value key. Hence, we return nullptr.
    if (temp == nullptr || temp->data != key)
    {
        return nullptr;
    }
    // We return the node with value key.
    return temp;
}

// Time complexity = O(n^2)
// Space complexity = O(1)
// Function kth_node helps us find the kth node in the path from the node with value u to the node with value v.
int kth_node(struct node *root, int u, int v, int k)
{
    // We first find the node with value u and store it in the node* temp. node_k stores the kth node in the path from u to v.
    struct node *temp = search(root, u), *node_k = nullptr;
    // Find the least common ancestor of u, v by recursively setting temp to temp->parent until the node with value v is found in any of the subtrees of temp.
    while (!search(temp, v) && k > 0)
    {
        k--;
        temp = temp->parent;
    }
    // We now proceed towards the node with value v and loop till we either find the kth node (till k = 0) or temp = nullptr which means the node doesn't exist.
    while (temp != nullptr && k > 0)
    {
        // We have found the node, break the loop.
        if (v == temp->data)
        {
            break;
        }
        // If v < temp->data, we search in the left subtree of temp.
        else if (v < temp->data)
        {
            temp = temp->left;
        }
        // If v > temp->data, we search in the right subtree of temp.
        else if (v > temp->data)
        {
            temp = temp->right;
        }
        k--;
    }
    // If k != 0, there are not enough number of nodes in the path from the node with value u to the node with value v.
    // Hence, no such node exists and we return -1.
    if (k != 0)
    {
        return -1;
    }
    // Else we return the kth node's data.
    return temp->data;
}

// Main function which takes in inputs from the user and calls the respective functions to print the respective outputs.
int main()
{
    // We initialize root node* of the tree to nullptr.
    struct node *root = nullptr;
    // We take the number of nodes in the binary search tree as input.
    int n;
    cin >> n;
    // The first n inputs are inserted into the binary search tree with root root.
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        root = insert(root, x);
    }
    // We take the number of queries as input q.
    int q;
    cin >> q;
    // We loop through each query.
    while (q > 0)
    {
        // We take the numbers u, v, k as input.
        int u, v, k;
        cin >> u >> v >> k;
        // We output the data of the kth_node of this path by calling the kth_node function to which we pass root, u, v, k - 1.
        // The reason we pass k-1 is that we have to consider the node u as the first node and not the next node in this unique path as the first node.
        cout << kth_node(root, u, v, k - 1) << endl;
        q--;
    }
}