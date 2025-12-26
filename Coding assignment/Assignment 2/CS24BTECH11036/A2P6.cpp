#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Time complexity = O(n)
// Space complexity = O(n)

// Definition of each node of the tree.
struct node
{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
};

// Time complexity = O(1)
// Space complexity = O(1)
// Extra space complexity = O(1)
// Function to create a new node in the tree by setting up the pointers appropriately.
struct node *create_node(int key)
{
    node *root = new node;
    root->data = key;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    return root;
}

// Time complexity = O(n)
// Space complexity = O(h) = O(n) (worst case), h is the height of the tree.
// Function to construct the tree given it's array representation.
struct node *tree_construct(int *arr, int n, int ind)
{
    // The function is recursive, we keep creating nodes for the root and it's children and attach them to the root's left, right and so on recursively.
    // If we reach an index in the array out of bounds, it means the node doesn't exist in the tree. Hence, we return nullptr.
    if (ind >= n)
    {
        return nullptr;
    }
    // If the array contains INT_MIN, meaning the element it corresponds to is null/-1 (we create the array this way, check main function), then we return nullptr.
    if (arr[ind] == INT_MIN)
    {
        return nullptr;
    }
    // We create root node and recursively create it's respective left and right subtrees.
    struct node *root = create_node(arr[ind]);
    root->left = tree_construct(arr, n, 2 * ind + 1);
    // Setting the parent pointer for the left child of root.
    if (root->left != nullptr)
    {
        root->left->parent = root;
    }
    root->right = tree_construct(arr, n, 2 * ind + 2);
    // Setting the parent pointer for the right child of root.
    if (root->right != nullptr)
    {
        root->right->parent = root;
    }
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
        if (temp->data == key)
        {
            break;
        }
        // If we do not find the node, we check key < temp->data, implying that key might be present in the left subtree of the node temp.
        // So, we set temp as temp->left to search for the node with data = key in the left subtree of the node temp.
        else if (temp->data > key)
        {
            temp = temp->left;
        }
        // If we do not find the node, we check key > temp->data, implying that key might be present in the right subtree of the node temp.
        // So, we set temp as temp->right to search for the node with data = key in the right subtree of the node temp.
        else if (temp->data < key)
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

// Time complexity = O(n)
// Space complexity = O(h) = O(n) (worst case), h is the height of the tree.
// Sum function used to find the sum of values of all nodes where the value of the node lies in the range [low, high].
int summ(struct node *root, int low, int high)
{
    // Initialize sum to 0, handle edge case of root = nullptr where the tree doesn't exist and sum remains 0.
    int sum = 0;
    if (root == nullptr)
    {
        return 0;
    }
    // If the value of the root is in the range [low, high], we add it to the value of sum.
    if (root->data >= low && root->data <= high)
    {
        sum = sum + root->data;
    }
    // We recurse and add sum for the left and right subtrees of the root of the tree and return the final sum.
    sum = sum + summ(root->left, low, high);
    sum = sum + summ(root->right, low, high);
    return sum;
}

// Main function which takes in inputs from the user and calls the respective functions to print the respective outputs.
int main()
{
    // We initialize root node* of the tree to nullptr.
    struct node *root = nullptr;
    // We store the array representation initially in a string named input.
    string input;
    getline(cin, input);

    // Arr stores the array representation of the tree, index represents the index of the elements in the array.
    int arr[100], ind = 0;
    // We use stringstream to parse the given string input by breaking it into k substrings and parsing them separately.
    istringstream iss(input);
    string tok;

    // We parse through the string till we reach it's end.
    while (iss >> tok)
    {
        // NULL/-1 tells us that the given node does not exist (it is a nullptr). We set the corresponding array representation as INT_MIN.
        if (tok == "NULL" || tok == "null" || tok == "-1")
        {
            arr[ind] = INT_MIN;
            ind++;
        }
        // We parse the string as an integer and add to the array at the corresponding index, maintained by ind.
        else
        {
            arr[ind] = stoi(tok);
            ind++;
        }
    }
    // We construct the tree and return it's root, a struct node*.
    root = tree_construct(arr, ind, 0);
    // We call the respective, non-recursive implementations of inorder, preorder, postorder.
    int low, high;
    cin >> low >> high;
    // We print the sum of node values in the range low to high.
    cout << summ(root, low, high) << endl;
}