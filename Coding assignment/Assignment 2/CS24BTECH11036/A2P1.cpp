#include <iostream>
#include <sstream>
#include <string>

using namespace std;
#define SIZE_STACK 100

// Time complexity = O(n)
// Space complexity = O(n)

// Definition of each node of the tree.
struct node
{
    int data;
    struct node *left;
    struct node *right;
};

// Function to create a new node in the tree by setting up the pointers appropriately.
struct node *create_node(int key)
{
    node *root = new node;
    root->data = key;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}

// Time complexity = O(n)
// Space complexity = O(n)
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
    root->right = tree_construct(arr, n, 2 * ind + 2);
    return root;
}

// Using a struct Stack to store it's top element's index + 1.
struct Stack
{
    struct node *arr[1000];
    int top;
};

// Function to check if the Stack is empty or not by checking if it's top value is 0 which means the no of elements in the stack = 0.
bool isEmpty(Stack *stack)
{
    if (stack->top == 0)
    {
        return true;
    }
    return false;
}

// Function to check if the Stack is full or not by checking if it's top value is SIZE_STACK which means the no of elements in the stack
// = max no of possible elements in the stack = SIZE_STACK.
bool isFull(Stack *stack)
{
    if (stack->top == SIZE_STACK)
    {
        return true;
    }
    return false;
}

// Function to insert an element into the stack.
void Push(Stack *&stack, struct node *node)
{
    // Checking if the stack is full as we cannot any element into a full stack.
    if (isFull(stack))
    {
        cout << "Cannot insert an element into a full stack." << endl;
        return;
    }
    // If the stack is not full, we add the integer ele at the top's position and increase stack.top by 1 as we have added an element to the stack.
    *(stack->arr + stack->top) = node;
    stack->top++;
}

// Function to delete an element from the stack.
struct node *Pop(Stack *&stack)
{
    // Checking if the stack is empty as we cannot remove an element from an empty stack.
    if (isEmpty(stack))
    {
        return nullptr; // Returning nullptr means that we have got an underflow error.
    }
    // Normal case when the stack is not empty, we decrease stack.top by 1 as we are removing an element.
    struct node *x = *(stack->arr + stack->top - 1);
    stack->top--;
    return x;
}

// Time complexity = O(n)
// Space complexity = O(n)
// Non-recursive implementation of inorder traversal of a tree.
void inorder(struct node *root)
{
    // Handling the edge case when the root is nullptr, we print nothing.
    if (root == nullptr)
    {
        cout << endl;
        return;
    }
    // Handling the edge case when the root has no children, we print root->data only.
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << endl;
        return;
    }
    // We create a new empty stack to store the nodes of the tree whose data are to be printed in inorder.
    Stack *stac = new Stack();
    struct node *curr = root;
    // We now loop through the tree to print the inorder representation. We stop when the stack is empty and we have reached a leaf node.
    while (curr != nullptr || !isEmpty(stac))
    {
        // We first reach the left most node of the tree and push all elements from the root to it's left most node in the stack.
        if (curr != nullptr)
        {
            Push(stac, curr);
            curr = curr->left;
        }
        // Once we reach the left most node, we cannot go further, so we set the curr node to the top most element of the stack (the last left most element).
        // We print the data corresponding to that element and pop the stack while setting curr to curr->right to print the elements of the right subtree of curr.
        else
        {
            curr = Pop(stac);
            cout << curr->data << " ";
            curr = curr->right;
        }
    }
    cout << endl;
}

// Time complexity = O(n)
// Space complexity = O(n)
// Non-recursive implementation of preorder traversal of a tree.
void preorder(struct node *root)
{
    // Handling the edge case when the root is nullptr, we print nothing.
    if (root == nullptr)
    {
        cout << endl;
        return;
    }
    // Handling the edge case when the root has no children, we print root->data only.
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << endl;
        return;
    }
    // We create a new empty stack to store the nodes of the tree whose data are to be printed in preorder.
    Stack *stac = new Stack();
    // We push root to the stack to print it first.
    Push(stac, root);
    struct node *curr = root;
    // We now loop through the tree to print the inorder representation. We stop when the stack is empty.
    while (!isEmpty(stac))
    {
        // We pop the top element present in the stack and print it's corresponding data.
        curr = Pop(stac);
        cout << curr->data << " ";
        // If the given node is the considered the root of it's subtrees and
        // Case 1: It's right child is not nullptr: We push it into the stack to print it after we print the left child.
        if (curr->right != nullptr)
        {
            Push(stac, curr->right);
        }
        // Case 2: It's left child is not nullptr: We push it into the stack to print it before we print the right child.
        if (curr->left != nullptr)
        {
            Push(stac, curr->left);
        }
    }
    cout << endl;
}

// Time complexity = O(n)
// Space complexity = O(n)
// Non-recursive implementation of postorder traversal of a tree.
void postorder(struct node *root)
{
    // Handling the edge case when the root is nullptr, we print nothing.
    if (root == nullptr)
    {
        cout << endl;
        return;
    }
    // Handling the edge case when the root has no children, we print root->data only.
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << endl;
        return;
    }
    // We create a new empty stack to store the nodes of the tree whose data are to be printed in postorder.
    Stack *stac = new Stack();
    // Curr is for looping through each node of the tree and visited is for checking if we have visited the node before.
    struct node *curr = root, *visited = nullptr;
    // We now loop through the tree to print the inorder representation. We stop when the stack is empty and we have reached a leaf node.
    while (curr != nullptr || !isEmpty(stac))
    {
        // We first reach the left most node of the tree and push all elements from the root to it's left most node in the stack.
        if (curr != nullptr)
        {
            Push(stac, curr);
            curr = curr->left;
        }
        // Once we have reached the left most element we have to now check the right child of the left most element and print it's elements in postorder.
        else
        {
            // We check if the last stack element has a right child and if we have visited it or not and set curr to the right child.
            struct node *temp = stac->arr[stac->top - 1];
            if (temp->right != nullptr && visited != temp->right)
            {
                curr = temp->right;
            }
            // If we have visited the right child or if the child itself doesn't exist, we recursively pop the stack until a non visited right child exists.
            // We print all the popped elements of the stack, first the left subtree elements, then the right subtree elements and their respective root.
            else
            {
                cout << temp->data << " ";
                visited = temp;
                Pop(stac);
            }
        }
    }
    cout << endl;
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
        inorder(root);
        preorder(root);
        postorder(root);
        k--;
    }
}