#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    node *root = new node;
    root->data = key;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}

// Helper function getheight is used to calculate the height of the AVL tree.
int getheight(node *node)
{
    // If the tree doesn't exist, then it's height is 0.
    if (node == nullptr)
    {
        return 0;
    }
    // If the root of the tree has only 1 child, then it's height is 1.
    else if (node->left == nullptr && node->right == nullptr)
    {
        return 1;
    }
    // Else, we recursively find the height by adding 1 to the max height of the children of the root node.
    return 1 + max(getheight(node->left), getheight(node->right));
}

// Helper function getbalance is used to calculate the balance factor of the AVL tree at a given node.
int getbalance(node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    // We find the heights of the left and right child of node and return it's difference as the balance of the AVL tree.
    int a = getheight(node->left), b = getheight(node->right);
    return a - b;
}

// Time complexity = O(h) = O(log n), h is the height of the AVL-Tree.
// Space complexity = O(h) = O(log n), h is the height of the AVL-Tree.
// Search function searches for a given node in a tree with data key.
node *search(node *root, int key)
{
    // If the tree doesn't exist, the search has failed.
    if (root == nullptr)
    {
        return nullptr;
    }
    // We implement search recursively. The search terminates when root->data matches key.
    if (root->data == key)
    {
        return root;
    }
    // If root->data > key, then we search for the node with data value key in the left subtree of the RB-tree.
    else if (root->data > key)
    {
        return search(root->left, key);
    }
    // Else if root->data < key, then we search for the node with data value key in the right subtree of the RB-tree.
    else
    {
        return search(root->right, key);
    }
}

// Left rotate function is used to convert a given branch of a tree with node node, it's right child of node to node's
// parent and right child's left child as node.
struct node *Left_rotate(node *&node)
{
    // We store the right child of node as child.
    struct node *child = node->right;
    // Left child of child becomes the right child of node.
    node->right = child->left;
    // We set node as child's left child.
    child->left = node;
    // Return the new root of the subtree originally rooted at node.
    return child;
}

// Right rotate function is used to convert a given branch of a tree with node node, it's left child of node to node's
// parent and left child's right child as node.
struct node *Right_rotate(node *&node)
{
    // We store the left child of node as child.
    struct node *child = node->left;
    // Right child of child becomes the left child of node.
    node->left = child->right;
    // We set node as child's right child.
    child->right = node;
    // Return the new root of the subtree originally rooted at node.
    return child;
}

// Time complexity = O(h) = O(log n), h is the height of the AVL-Tree.
// Space complexity = O(h) = O(log n), h is the height of the AVL-Tree.
// Insert function is used to insert a new node into the tree with data key.
node *insert(node *root, int key)
{
    // If the element is already present in the tree, we return directly as we cannot insert duplicate values into the Tree.
    if (search(root, key))
    {
        cout << "Duplicate elements cannot be inserted into the AVL tree." << endl;
        return root;
    }
    // If the tree doesn't exist, then we create a new node with data as key and set it to root.
    else if (root == nullptr)
    {
        root = createNode(key);
        return root;
    }

    // If key < root->data we go traverse in the left subtree of root.
    if (key < root->data)
    {
        root->left = insert(root->left, key);
    }
    // If key > root->data we go traverse in the right subtree of root.
    else if (key > root->data)
    {
        root->right = insert(root->right, key);
    }

    // Balancing the AVL tree. Integer variable balance stores the balance factor of tree at the root after the insertion.
    int balance = getbalance(root);
    // Handling the difference cases of balancing the tree.
    // Case 1: Left-Left
    if (balance > 1 && getbalance(root->left) >= 0)
    {
        return Right_rotate(root);
    }
    // Case 2: Left-Right
    else if (balance > 1 && getbalance(root->left) < 0)
    {
        root->left = Left_rotate(root->left);
        return Right_rotate(root);
    }
    // Case 3: Right-Left
    else if (balance < -1 && getbalance(root->right) > 0)
    {
        root->right = Right_rotate(root->right);
        return Left_rotate(root);
    }
    // Case 4: Right-Right
    else if (balance < -1 && getbalance(root->right) <= 0)
    {
        return Left_rotate(root);
    }
    return root;
}

// Time complexity = O(h) = O(log n), h is the height of the AVL-Tree.
// Space complexity = O(h) = O(log n), h is the height of the AVL-Tree.
// Delete function is used to delete a node in the RB tree with the given data value key.
node *del(node *root, int key)
{
    // If the given key is not present in the given RB-Tree with root node, we print Key not found and return the root of the tree.
    if (search(root, key) == nullptr)
    {
        cout << "Key not found!" << endl;
        return root;
    }
    // If root->data > key, we search for the key in the left subtree of root and delete it by recursively calling del(root->left, key).
    if (root->data > key)
    {
        root->left = del(root->left, key);
    }
    // If root->data < key, we search for the key in the left subtree of root and delete it by recursively calling del(root->right, key).
    else if (root->data < key)
    {
        root->right = del(root->right, key);
    }
    // If the key is found, then we check if the key has left or right children or not (as it might require rotation with 4 cases - LL, LR, RL, RR), store and return them.
    else if (root->data == key)
    {
        // If the left child of root doesn't exist, we store and return the right child of root.
        if (root->left == nullptr)
        {
            struct node *temp = root->right;
            delete (root);
            return nullptr;
        }
        // If the right child of root doesn't exist, we store and return the left child of root.
        else if (root->right == nullptr)
        {
            struct node *temp = root->left;
            delete (root);
            return temp;
        }
        // We find the successor of root and store it in successor.
        node *x = root->right;
        while (x->left != nullptr)
        {
            x = x->left;
        }
        // We create a new node with data as the data of the successor of the root node.
        root = createNode(x->data);
        // We delete the node corresponding to the data of the successor of the root node in the right subtree of root.
        root->right = del(root->right, x->data);
    }

    // Balancing the AVL tree. Integer variable balance stores the balance factor of tree at the root after the insertion.
    int balance = getbalance(root);
    // Handling the difference cases of balancing the tree.
    // Case 1: Left-Left
    if (balance > 1 && getbalance(root->left) >= 0)
    {
        return Right_rotate(root);
    }
    // Case 2: Left-Right
    else if (balance > 1 && getbalance(root->left) < 0)
    {
        root->left = Left_rotate(root->left);
        return Right_rotate(root);
    }
    // Case 3: Right-Left
    else if (balance < -1 && getbalance(root->left) > 0)
    {
        root->right = Right_rotate(root->right);
        return Left_rotate(root);
    }
    // Case 4: Right-Right
    else if (balance < -1 && getbalance(root->left) <= 0)
    {
        return Left_rotate(root);
    }
    return root;
}

// Helper function print_level prints a given level i of the AVL-Tree.
void print_level(struct node *root, int level)
{
    // If we reach a null node, we return directly as we have reached the end of a given subtree after traversing through all possible nodes in it.
    if (root == nullptr)
    {
        return;
    }
    // If we are printing the first node (base case), we print the root->data directly as it is the only node in the first level.
    else if (level == 1)
    {
        cout << root->data << " ";
    }
    // We print the print_level recursively by calling it on the left and right subtrees of the AVL-Tree.
    print_level(root->left, level - 1);
    print_level(root->right, level - 1);
}

// Time complexity = O(n^2).
// Space complexity = O(n).
// Function print_level_order prints the level order traversal of the AVL-Tree.
void print_level_order(struct node *root)
{
    // If the tree doesn't exist, return without printing anything.
    if (root == nullptr)
    {
        return;
    }
    // We find the height of the tree.
    int h = getheight(root);
    // We print the level order by calling the helper function print_level for each level of the tree from min level 1 to the max level height of the tree or h.
    for (int i = 1; i <= h; i++)
    {
        print_level(root, i);
        cout << endl;
    }
}

// Main function used to run the given code for user inputs.
int main()
{
    // Initialize the root of the AVL-Tree to nullptr.
    struct node *root = nullptr;
    // Take the input of the number of elements to be inserted into the AVL-Tree as n.
    int n;
    cin >> n;
    // Run a for loop taking each of the n elements as an input stored in the number x and insert each insert into the given AVL-Tree with root root.
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        root = insert(root, x);
    }

    // Uncomment for detailed instructions to be printed on the output screen.
    // cout << "Enter your choice: " << endl;
    // cout << "1 - Search for an element" << endl;
    // cout << "2 - Insert an element" << endl;
    // cout << "3 - Delete an element" << endl;
    // cout << "4 - Print level order of traversal tree" << endl;
    // We again take in user input, store it in the integer variable op, for either searching, inserting or deleting an element as shown below.
    int op;
    cin >> op;

    while (true)
    {
        // If the user inputs 1, we search for the node with the given value key, taken as user input, in the user constructed RB-Tree, by calling the search function.
        if (op == 1)
        {
            int key;
            cin >> key;
            // If the key is found, print <key> present.
            if (search(root, key))
            {
                cout << key << " present" << endl;
            }
            // Else print <key> not present.
            else
            {
                cout << key << " not present" << endl;
            }
        }
        // If the user inputs 2, we insert a new node with the given value key, taken as user input, in the user constructed RB-Tree, by calling the insert function.
        else if (op == 2)
        {
            int key;
            cin >> key;
            // If the key is found, print <key> already present. So no need to insert.
            if (search(root, key))
            {
                cout << key << " already present. So no need to insert." << endl;
            }
            // If the key is not found, insert the key into the given AVL tree with root root and print <key> inserted.
            else
            {
                root = insert(root, key);
                cout << key << " inserted" << endl;
            }
        }
        // If the user inputs 3, we delete the node with the given value key, taken as user input, from the user constructed RB-Tree, by calling the delete function.
        else if (op == 3)
        {
            int key;
            cin >> key;
            // If a node with the given data = key exists in the RB-Tree, then we delete the node and print the value deleted.
            if (search(root, key))
            {
                root = del(root, key);
                cout << key << " deleted" << endl;
            }
            // If a node with the given data = key doesn't exist in the RB-Tree, then we cannot delete it and hence we print the error message given below.
            else
            {
                cout << key << " not present. So it can not be deleted" << endl;
            }
        }
        // If the user inputs 4, we print the level order of the AVL-Tree by calling the print_level_order function.
        else if (op == 4)
        {
            print_level_order(root);
        }
        // Uncomment for detailed instructions to be printed on the output screen.
        // cout << "Enter your choice: " << endl;
        // cout << "1 - Search for an element" << endl;
        // cout << "2 - Insert an element" << endl;
        // cout << "3 - Delete an element" << endl;
        // cout << "4 - Print level order of traversal tree" << endl;
        // We again take in user input, store it in the integer variable op, for either searching, inserting or deleting an element as shown below.
        cin >> op;
    }
}