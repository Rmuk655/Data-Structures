#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Time complexity = O(n^2)
// Space complexity = O(n^2)

// Definition of each node of the tree.
struct node
{
    int data;
    struct node *left;
    struct node *right;
};

// Function to create a new node in the tree by setting up the pointers appropriately.
node *createNode(int key)
{
    struct node *root = new struct node;
    root->data = key;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}

// Time complexity = O(n^2)
// Space complexity = O(n^2)
// Construct_tree function constructs the tree with given preorder and inorder traversals and returns the root node of the tree.
struct node *construct_tree(vector<int> preord, vector<int> inord, int n)
{
    // If no element exists in pre/inorder then return nullptr as tree has 0 elements.
    if (n == 0)
    {
        return nullptr;
    }
    // If 1 element exists in pre/inorder then return root with value preord[0] as tree has only 1 element.
    struct node *root = createNode(preord[0]);
    if (n == 1)
    {
        return root;
    }
    // Otherwise we find the number of elements in the left subtree and right subtree as left and right respectively.
    int left = 0, right = 0;
    for (int i = 0; i < n; i++)
    {
        if (inord[i] == preord[0])
        {
            left = i;
            break;
        }
    }
    right = n - 1 - left;
    // We now create 4 vectors for the pre, in orders of the left and right subtrees respectively and construct the left and right subtrees of root recursively.
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
    // Once we fill the vectors with the respective values, we construct the left, right subtrees by calling the function construct_tree again recursively.
    struct node *l_child = construct_tree(left_pre, left_in, left);
    struct node *r_child = construct_tree(right_pre, right_in, right);
    // If there exists non zero number of elements in the left subtree we insert the l_child as root->left.
    if (left)
    {
        root->left = l_child;
    }
    // If there exists non zero number of elements in the right subtree we insert the r_child as root->right.
    if (right)
    {
        root->right = r_child;
    }
    return root;
}

// Time complexity = O(n)
// Space complexity = O(n)
// Helper function checkinorder checks if the inorder traversal of the constructed tree matches the given inorder traversal.
bool checkinorder(struct node *root, vector<int> inord, int n, int &i)
{
    // Handling the edge case where root is nullptr.
    if (root == nullptr)
    {
        return true;
    }
    // If the left subtree of the root of tree doesn't match the given inorder, then return false.
    if (!checkinorder(root->left, inord, n, i))
    {
        return false;
    }
    // If we reach out of bounds or any corresponding inorder value doesn't match, return false.
    if (i >= n || root->data != inord[i])
    {
        return false;
    }
    // Root is at the index left_child_index + 1. We will further add 1 to access the right_child_index in the right subtree recursion.
    i++;
    // We check the inorder of the right subtree of the tree.
    return checkinorder(root->right, inord, n, i);
}

// Time complexity = O(n)
// Space complexity = O(n)
// Helper function checkpreorder checks if the preorder traversal of the constructed tree matches the given preorder traversal.
bool checkpreorder(struct node *root, vector<int> preord, int n, int &i)
{
    // Handling the edge case where root is nullptr.
    if (root == nullptr)
    {
        return true;
    }
    // If we reach out of bounds or any corresponding preorder value doesn't match, return false.
    if (i >= n || root->data != preord[i])
    {
        return false;
    }
    // Left_child is at the index root_index + 1. We will further add 1 to access the right_child_index in the right subtree recursion.
    i++;
    // If the left subtree of the root of tree doesn't match the given preorder, then return false.
    if (!checkpreorder(root->left, preord, n, i))
    {
        return false;
    }
    // If the right subtree of the root of tree doesn't match the given inorder, then return false, else true.
    // We do it by directly returning the result of the preorder of the root->right.
    return checkpreorder(root->right, preord, n, i);
}

// Time complexity = O(n)
// Space complexity = O(n)
// Helper function to find the height of tree.
int height(struct node *root)
{
    // Handling the edge case when the root is nullptr, tree doesn't exist and hence the height of tree is 0.
    if (root == nullptr)
    {
        return 0;
    }
    // Handling the edge case when the root has no children. The height of tree is 1.
    else if (root->left == nullptr && root->right == nullptr)
    {
        return 1;
    }
    // We recurse to find the height of the tree as 1 (height due to the node) + maximum of heights of the respective left and right children of the node.
    return 1 + max(height(root->left), height(root->right));
}

// Time complexity = O(n)
// Space complexity = O(n)
// Helper function print level prints a given level 'level' of the tree with root 'root'.
void print_level(struct node *root, int level)
{
    // Handling the edge case when the level of tree to be printed is 1.
    if (level == 1)
    {
        // If the tree exists, print root->data.
        if (root != nullptr)
        {
            cout << root->data << " ";
        }
        // Else print NULL.
        else
        {
            cout << "NULL ";
        }
        return;
    }
    // If the level to be printed is some level > 1, then we have 2 cases:
    // Case 1: If the given root node exists, then print it's left and right subtrees in array representation recursively.
    if (root != nullptr)
    {
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
    }
    // Case 2: If the given root node doesn't exist, then print nullptr for each of it's children recursively.
    // If a given node is null, it's children are also null. To represent this we need to print it's null subtree recursively.
    else
    {
        print_level(nullptr, level - 1);
        print_level(nullptr, level - 1);
    }
}

// Time complexity = O(n^2)
// Space complexity = O(n)
// The main print function that prints the array representation of the tree given it's root 'root'.
void print_arr_rep(struct node *root)
{
    // Handling the edge case when the root is nullptr, tree doesn't exist and hence we print NULL.
    if (root == nullptr)
    {
        cout << "NULL" << endl;
        return;
    }
    // We find the height of the tree.
    int h = height(root);
    // We print the array representation level by level, from level 1 to level h = height of tree.
    for (int i = 1; i <= h; i++)
    {
        print_level(root, i);
    }
}

// Main function which takes in inputs from the user and calls the respective functions to print the respective outputs.
int main()
{
    // We take the number of test cases as input.
    int k;
    cin >> k;
    // We ignore the current line and move on to the next so that the getline doesn't read the previous line that contained k.
    cin.ignore();
    // Looping through each test case using a while loop.
    while (k > 0)
    {
        // We initialize root node* of the tree to nullptr and create the array representation of the tree as a string input.
        struct node *root = nullptr;
        // We take the inorder traversal as a string named input.
        string input;
        getline(cin, input);

        // inord stores the inorder traversal of the tree, preord stores the preorder traversal of the tree.
        vector<int> inord, preord;
        // We use stringstream to parse the given string input by breaking it into k substrings and parsing them separately.
        istringstream iss(input);
        string tok;

        // We parse through the string till we reach it's end.
        while (iss >> tok)
        {
            // We parse the string as an integer and add to the inord array at the corresponding index, maintained by ind.
            inord.push_back(stoi(tok));
        }

        // We take the preorder traversal as a string named input.
        getline(cin, input);
        // We use stringstream to parse the given string input by breaking it into k substrings and parsing them separately.
        istringstream iss_2(input);

        // We parse through the string till we reach it's end.
        while (iss_2 >> tok)
        {
            preord.push_back(stoi(tok));
        }
        // If the sizes of the inorder, preorder traversals dont match, we print ERROR.
        if (inord.size() != preord.size())
        {
            cout << "ERROR" << endl;
        }
        else
        {
            // We construct the tree using preorder and inorder traversals.
            root = construct_tree(preord, inord, preord.size());
            int x = 0, y = 0;
            // If the preorder and inorder traversals of the constructed tree match the preorder and inorder of input, we print the array representation of the tree.
            if (checkpreorder(root, preord, preord.size(), x) && checkinorder(root, inord, inord.size(), y) && x == preord.size() && y == inord.size())
            {
                print_arr_rep(root);
                cout << endl;
            }
            // If it doesn't match, we print error.
            else
            {
                cout << "ERROR" << endl;
            }
        }
        k--;
    }
}