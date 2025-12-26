#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Time complexity = O(n^2)
// Space complexity = O(n^2)

int no_of_sing_rot = 0, no_of_dou_rot = 0;
// Definition of each node of the tree.
struct node
{
    int data;
    int height; /* stores the height of the current node */
    struct node *left;
    struct node *right;
};

// Function to create a new node in the tree by setting up the pointers appropriately.
node *createNode(int key)
{
    node *root = new node;
    root->data = key;
    root->height = 0;
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

    // Updating the height attribute of the root node.
    root->height = getheight(root);
    // Balancing the AVL tree. Integer variable balance stores the balance factor of tree at the root after the insertion.
    int balance = getbalance(root);
    // Handling the difference cases of balancing the tree.
    // Case 1: Left-Left
    if (balance > 1 && getbalance(root->left) >= 0)
    {
        no_of_sing_rot++;
        return Right_rotate(root);
    }
    // Case 2: Left-Right
    else if (balance > 1 && getbalance(root->left) < 0)
    {
        no_of_dou_rot++;
        root->left = Left_rotate(root->left);
        return Right_rotate(root);
    }
    // Case 3: Right-Left
    else if (balance < -1 && getbalance(root->right) > 0)
    {
        no_of_dou_rot++;
        root->right = Right_rotate(root->right);
        return Left_rotate(root);
    }
    // Case 4: Right-Right
    else if (balance < -1 && getbalance(root->right) <= 0)
    {
        no_of_sing_rot++;
        return Left_rotate(root);
    }
    return root;
}

// Time complexity = O(h) = O(log n), h is the height of the AVL-Tree.
// Space complexity = O(h) = O(log n), h is the height of the AVL-Tree.
// Delete function is used to delete a node in the RB-Tree with the given data value key.
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
            return temp;
        }
        // If the right child of root doesn't exist, we store and return the left child of root.
        else if (root->right == nullptr)
        {
            struct node *temp = root->left;
            delete (root);
            return temp;
        }
        // We find the successor of root and store it in successor.
        node *successor = root->right;
        while (successor->left != nullptr)
        {
            successor = successor->left;
        }
        // We create a new node with data as the data of the successor of the root node.
        root->data = successor->data;
        // We delete the node corresponding to the data of the successor of the root node in the right subtree of root.
        root->right = del(root->right, successor->data);
    }

    // Updating the height attribute of the root node.
    root->height = getheight(root);
    // Balancing the AVL tree. Integer variable balance stores the balance factor of tree at the root after the insertion.
    int balance = getbalance(root);
    // Handling the difference cases of balancing the tree.
    // Case 1: Left-Left
    if (balance > 1 && getbalance(root->left) >= 0)
    {
        no_of_sing_rot++;
        return Right_rotate(root);
    }
    // Case 2: Left-Right
    else if (balance > 1 && getbalance(root->left) < 0)
    {
        no_of_dou_rot++;
        root->left = Left_rotate(root->left);
        return Right_rotate(root);
    }
    // Case 3: Right-Left
    else if (balance < -1 && getbalance(root->right) > 0)
    {
        no_of_dou_rot++;
        root->right = Right_rotate(root->right);
        return Left_rotate(root);
    }
    // Case 4: Right-Right
    else if (balance < -1 && getbalance(root->right) <= 0)
    {
        no_of_sing_rot++;
        return Left_rotate(root);
    }
    return root;
}

// Function inorder is used to print the inorder traversal of AVL-Tree.
void inorder(struct node *root)
{
    // If the root is null then we stop traversing the tree.
    if (root == nullptr)
    {
        return;
    }
    // If the tree has only 1 node, the root, then we print it's data and return.
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << " ";
        return;
    }
    // We recursively print the inorder traversal of the left subtree, then the root->data and the inorder traversal of the right subtree.
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Main function used to run the given code for user inputs.
int main()
{
    // Initialize the root of the AVL-Tree to nullptr.
    struct node *root = nullptr;
    // We take the number of operations to be performed as input to be stored in the variable no_of_ops.
    int no_of_ops;
    cin >> no_of_ops;
    // The char variable op stores the character corresponding to a given operation taken as user input.
    // op = 'I' - insert the given key in the AVL-Tree, op = 'D' - delete the given key from the AVL-Tree.
    char op;
    // We run till no_of_ops is 0.
    while (no_of_ops)
    {
        // We again take user input in a while loop, till the value of no_of_ops hits 0.
        cin >> op;
        // If the user inputs I, we insert a new node with the given value key, taken as user input, in the user constructed AVL-Tree, by calling the insert function.
        if (op == 'I')
        {
            int key;
            cin >> key;
            // If the key is not found, insert the key into the given B-Tree with root root and print <key> inserted.
            if (!search(root, key))
            {
                root = insert(root, key);
            }
        }
        // If the user inputs 'D', we delete the node with the given value key, taken as user input, in the user constructed AVL-Tree, by calling the delete function.
        else if (op == 'D')
        {
            int key;
            cin >> key;
            // If a node with the given data = key exists in the RB-Tree, then we delete the node and print the value deleted.
            if (search(root, key))
            {
                root = del(root, key);
            }
        }
        no_of_ops--;
    }
    // We print the inorder traversal of the resultant tree, total no of single rotations performed and the total no of double rotations performed after all operations.
    cout << "Inorder: ";
    inorder(root);
    cout << endl;
    cout << "Single rotations: " << no_of_sing_rot << endl;
    cout << "Double rotations: " << no_of_dou_rot << endl;
}