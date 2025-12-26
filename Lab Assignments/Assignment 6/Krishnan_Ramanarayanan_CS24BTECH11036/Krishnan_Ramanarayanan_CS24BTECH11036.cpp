#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define RED true
#define BLACK false

// Definition of node of the RB-Tree.
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    bool color;
};

// Function to create an external node for all leaf nodes in the RB Tree.
struct Node *create_ext_node()
{
    Node *ext_node = (Node *)malloc(sizeof(Node));
    ext_node->data = INT_MIN;
    // Note that we have set ext_node->left to ext_node itself to avoid nullptr access issues when we do something like node->left->color.
    ext_node->left = ext_node;
    ext_node->right = ext_node;
    ext_node->parent = nullptr;
    ext_node->color = BLACK;
    // In theory, external (NIL) nodes are not real nodes, so they are said to be uncolored.
    // But for defining black-height and ensuring balance, they're treated as black.
    return ext_node;
}

// Function to create a node in the RB Tree.
struct Node *create_new_node(int key)
{
    Node *temp = new Node;
    temp->data = key;
    // We create new external nodes(assigned to temp->left) by calling the above function and setting their parent pointers to the node created by this function itself.
    temp->left = create_ext_node();
    temp->left->parent = temp;
    // We create new external nodes(assigned to temp->right) by calling the above function and setting their parent pointers to the node created by this function itself.
    temp->right = create_ext_node();
    temp->right->parent = temp;
    temp->parent = nullptr;
    temp->color = true;
    return temp;
}

// Function used to check if a given node is an external node or not. Useful in cases when we want to identify external nodes, so that we can handle them separately.
bool is_ext_node(Node *node)
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->data == INT_MIN && node->color == BLACK)
    {
        return 1;
    }
    return 0;
}

// Search function searches for a given node in a tree with data key.
Node *search(Node *root, int key)
{
    // If the tree doesn't exist, the search has failed.
    if (root == nullptr || is_ext_node(root))
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

// Left rotate function is used to convert a given branch of a tree with parent paren, right child child to parent child and left child paren.
void Left_rotate(Node *&root, Node *paren)
{
    // We store the right child of paren as child.
    Node *child = paren->right;
    // Left child of child becomes the root of paren's right subtree.
    paren->right = child->left;
    // If left child of child is not an external node we update it's parent pointer.
    if (!is_ext_node(child->left))
    {
        child->left->parent = paren;
    }
    // We update child's parent pointer.
    child->parent = paren->parent;
    // If paren is root, it's parent is nullptr and hence we set root as child.
    if (paren->parent == nullptr)
    {
        root = child;
    }
    // If paren is the left child of it's parent, then we set left child of paren's parent as child.
    else if (paren->parent->left == paren)
    {
        paren->parent->left = child;
    }
    // If paren is the right child of it's parent, then we set right child of paren's parent as child.
    else
    {
        paren->parent->right = child;
    }
    // We set paren as child's left child and paren's new parent as child.
    child->left = paren;
    paren->parent = child;
}

// Left rotate function is used to convert a given branch of a tree with parent paren, left child child to parent child and right child paren.
void Right_rotate(Node *&root, Node *paren)
{
    // We store the right child of paren as child.
    Node *child = paren->left;
    // Right child of child becomes the root of paren's left subtree.
    paren->left = child->right;
    // If left child of child is not an external node we update it's parent pointer.
    if (!is_ext_node(child->right))
    {
        child->right->parent = paren;
    }
    // We update child's parent pointer.
    child->parent = paren->parent;
    // If paren is root, it's parent is nullptr and hence we set root as child.
    if (paren->parent == nullptr)
    {
        root = child;
    }
    // If paren is the left child of it's parent, then we set left child of paren's parent as child.
    else if (paren->parent->left == paren)
    {
        paren->parent->left = child;
    }
    // If paren is the right child of it's parent, then we set right child of paren's parent as child.
    else
    {
        paren->parent->right = child;
    }
    // We set paren as child's right child and paren's new parent as child.
    child->right = paren;
    paren->parent = child;
}

// Helper function other_child helps us find the sibling of child1.
struct Node *other_child(struct Node *parent, struct Node *child1)
{
    // If child1 is left child, we return the right child.
    if (parent->left == child1)
    {
        return parent->right;
    }
    // Else we return the left child.
    return parent->left;
}

// Insert function is used to insert a new node into the RB tree with data key.
Node *insert(Node *root, int key)
{
    // If the root is an external node, then we create a new node with value key after deleting this external node and join it to the tree.
    if (is_ext_node(root))
    {
        Node *parent = root->parent;
        free(root);
        root = create_new_node(key);
        root->parent = parent;
        return root;
    }

    // If the element is already present in the tree, we return directly as we cannot insert duplicate values into the RB-Tree.
    if (search(root, key))
    {
        cout << "Duplicate element inserted" << endl;
        return root;
    }
    // If the tree doesn;t exist, then we create a new node with data as key and set it to root. We set root->color as BLACK.
    else if (root == nullptr)
    {
        root = create_new_node(key);
        root->color = BLACK;
        return root;
    }

    // We store the value of the root of the tree in the variable temp to traverse through the RB-tree.
    struct Node *temp = root;
    while (!is_ext_node(temp))
    {
        // If key < temp->data we go traverse in the left subtree of temp.
        if (key < temp->data)
        {
            // We break when we hit an external node and insert our new node by deleting this external node.
            if (is_ext_node(temp->left))
            {
                break;
            }
            temp = temp->left;
        }
        // If key > temp->data we go traverse in the right subtree of temp.
        else
        {
            // We break when we hit an external node and insert our new node by deleting this external node.
            if (is_ext_node(temp->right))
            {
                break;
            }
            temp = temp->right;
        }
    }
    // We store the newly created node to be inserted into the tree in new_node.
    // If key < temp->data we insert it as the left child of temp.
    struct Node *new_node = create_new_node(key);
    if (key < temp->data)
    {
        delete (temp->left);
        temp->left = new_node;
        new_node->parent = temp;
    }
    // If key > temp->data we insert it as the right child of temp.
    else
    {
        delete (temp->right);
        temp->right = new_node;
        new_node->parent = temp;
    }

    // We now check if the tree satisfied RB properties of a RED node has no RED child. If it doesn't, we perform rotations.
    while (new_node->parent != nullptr && new_node->parent->color == true)
    {
        // We find the uncle of the newly inserted node's parent and store it in uncle.
        struct Node *uncle = other_child(new_node->parent->parent, new_node->parent);
        // If the uncle is red colored, then we just recolor new_node, it's parent, grandparent and uncle.
        if (uncle != nullptr && uncle->color == true)
        {
            // grandparent is colored red, parent, uncle to black while new_node color remains unchanged.
            new_node->parent->parent->color = true;
            new_node->parent->color = false;
            uncle->color = false;
            // We set new_node to it's grandparent to check if RED node, no RED child property is violated in the tree above.
            new_node = new_node->parent->parent;
        }
        // If the uncle is an external node or colored black, we handle it in 4 different cases.
        else
        {
            // Case 1: The parent is the left child of it's grandparent.
            if (new_node->parent == new_node->parent->parent->left)
            {
                // Case 1a: The child is the right child of it's parent.
                if (new_node == new_node->parent->right)
                {
                    new_node = new_node->parent;
                    Left_rotate(root, new_node);
                }
                // Case 1b: The child is the left child of it's parent.
                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                Right_rotate(root, new_node->parent->parent);
            }
            // Case 2: The parent is the right child of it's grandparent.
            else
            {
                // Case 2a: The child is the left child of it's parent.
                if (new_node == new_node->parent->left)
                {
                    new_node = new_node->parent;
                    Right_rotate(root, new_node);
                }
                // Case 2b: The child is the right child of it's parent.
                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                Left_rotate(root, new_node->parent->parent);
            }
        }
        // We recolor root to black, if it's color was changed by the above code.
        root->color = BLACK;
    }
    // We return the root of the tree so that the root pointer can be reset to the new root, if there were changes to it after insertion.
    return root;
}

// Helper function transplant is used to replace the subtree rooted at node1 with the subtree rooted at node2 in the RB tree.
// The function then returns the modified root of the tree.
Node *transplant(Node *root, Node *node1, Node *node2)
{
    // If node1 is the root, we swap node2 with node1 by setting node2 as the new root of the tree.
    if (node1->parent == nullptr)
    {
        root = node2;
    }
    // If node1 is the left child of it's parent, we set node2 as the left child of node1's parent.
    else if (node1 == node1->parent->left)
    {
        node1->parent->left = node2;
    }
    // If node1 is the right child of it's parent, we set node2 as the right child of node1's parent.
    else
    {
        node1->parent->right = node2;
    }
    // If node2 is not an external node, then we can set it's parent pointer to node1's parent pointer. The if check is for safety purposes.
    if (!is_ext_node(node2))
    {
        node2->parent = node1->parent;
    }
    return root;
}

// Helper function treefixup is used to verify if the resulting RB tree after deletion of a given node with data value key still satisfies RB tree properties.
// If it doesn't satisfy the RB tree properties, we perform rotations to make sure it does satisfy the RB tree properties.
void treefixup(Node *&root, Node *node)
{
    // We traverse throughout the tree till the unequal black depths of external nodes issue is fixed.
    while (node != root && node->color == BLACK)
    {
        // We find the given node's sibling and store it in the variable sibling.
        Node *sibling = other_child(node->parent, node);
        // Case 1: node is a left child of it's parent.
        if (node == node->parent->left)
        {
            // Case 1a: Sibling is red, we left rotate the tree and set sibling to BLACK, parent to RED.
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                Left_rotate(root, node->parent);
                // As the left_rotate might have changed the value of the right pointer of parent.
                sibling = node->parent->right;
            }

            // Case 1b: both the children of the parent are black.
            if (sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
            }
            else
            {
                // Case 1c: Sibling and it's right child are both BLACK.
                if (sibling->right->color == BLACK)
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    Right_rotate(root, sibling);
                    sibling = node->parent->right;
                }
                // Case 1d: Sibling's right child is RED.
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                Left_rotate(root, node->parent);
                node = root;
            }
        }
        // Case 2: node is a right child of it's parent.
        else
        {
            // Case 1: Sibling is red, we right rotate the tree and set sibling to BLACK, parent to RED.
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                Right_rotate(root, node->parent);
                // As the left_rotate might have changed the value of the left pointer of parent.
                sibling = node->parent->left;
            }

            // Case 1b: both the children of the parent are black.
            if (sibling->right->color == BLACK && sibling->left->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
            }
            else
            {
                // Case 1c: Sibling and it's right child are both BLACK.
                if (sibling->left->color == BLACK)
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    Left_rotate(root, sibling);
                    sibling = node->parent->left;
                }
                // Case 1d: Sibling's right child is RED.
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                Right_rotate(root, node->parent);
                node = root;
            }
        }
    }
    // We set node color to black if it was changed in the above while loop.
    node->color = BLACK;
}

// Delete function is used to delete a node in the RB tree with the given data value key.
int del(Node *&root, int key)
{
    // We search for the node whose data equals key and store it z.
    Node *node_to_delete = search(root, key);
    // If the node to be deleted doesn't exist or is an external node, then we cannot delete it. Hence, we return -1 indicating error.
    // We handle this for safety purposes.
    if (!node_to_delete || is_ext_node(node_to_delete))
    {
        cout << key << " not found in the tree. Cannot delete." << endl;
        return -1;
    }

    // We store the node to be deleted in the variable successor, which will finally store the successor of the node to be deleted wherever necessary.
    // The variable node_to_be_fixed stores the first node which violates RB Tree's properties due to the deletion
    Node *successor = node_to_delete, *node_to_be_fixed;
    // We store the original color of the node to be deleted as if it is black, the tree might need some fixup, done using fixup function to make sure it follows
    // RB tree properties.
    bool successor_original_color = successor->color;

    // If the left child of the node to be deleted doesn't exist, we transplant it to it's parent.
    if (is_ext_node(node_to_delete->left))
    {
        node_to_be_fixed = node_to_delete->right;
        root = transplant(root, node_to_delete, node_to_delete->right);
    }
    // If the right child of the node to be deleted doesn't exist, we transplant it to it's parent.
    else if (is_ext_node(node_to_delete->right))
    {
        node_to_be_fixed = node_to_delete->left;
        root = transplant(root, node_to_delete, node_to_delete->left);
    }
    // If both children exist, then we find the successor to the given node and transplant it.
    else
    {
        // The variable temp stores the right child of the node to be deleted.
        Node *temp = node_to_delete->right;
        // Using the while loop, we the successor of the node, node_to_delete.
        while (!is_ext_node(temp->left))
        {
            temp = temp->left;
        }

        // We set the variable successor as the successor of the node to be deleted.
        successor = temp;
        // We need this variable to check if we removed a black node as it may violate RB-Tree properties and we need to fix it using fixup function.
        successor_original_color = successor->color;
        // The successor, being the left most node in the right subtree of node_to_delete does not have a left child.
        // Hence, we have to fix it's right child after deletion of the successor at it's original position as it may violate RB tree properties.
        node_to_be_fixed = successor->right;

        // If the successor is not the right child of the node to be deleted, then we transplant it's right subtree to itself.
        if (successor != node_to_delete->right)
        {
            root = transplant(root, successor, successor->right);
            successor->right = node_to_delete->right;
            successor->right->parent = successor;
        }
        // The parent pointer of node_to_be_fixed might be changed and hence we reset it correctly.
        else
        {
            node_to_be_fixed->parent = successor;
        }

        // We replace the node to be deleted with it's successor and modify pointer appropriately.
        root = transplant(root, node_to_delete, successor);
        // Left subtree of the deleted node must be the left subtree of the successor node as it has replaced the deleted node.
        // So we update successor's left pointer and the successor's left's parent pointer.
        successor->left = node_to_delete->left;
        successor->left->parent = successor;
        // Since successor replaces the node to be deleted, we set it's color also to the color of the deleted node.
        successor->color = node_to_delete->color;
    }

    // If we have deleted a black node, we might have reduced the black height of some external nodes and hence we need to fix up the tree.
    if (successor_original_color == BLACK)
    {
        // We set null nodes to external nodes to prevent segmentation faults.
        if (!node_to_be_fixed)
        {
            node_to_be_fixed = create_ext_node();
        }
        // We fix cases where RB-Tree properties are violated.
        treefixup(root, node_to_be_fixed);
    }

    // After fixing up the tree, we finally delete the node to be deleted and return the value of the node deleted.
    int value_of_del_node = node_to_delete->data;
    delete node_to_delete;
    return value_of_del_node;
}

// Function preorder is used to print the preorder traversal of RB-Tree.
void preorder(struct Node *root)
{
    // If we hit a null or an ext_node then we stop traversing the tree.
    if (root == nullptr || is_ext_node(root))
    {
        return;
    }
    // If the tree has only 1 node, the root, then we print it's data and return.
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << " ";
        return;
    }
    // We recursively print the root->data, then the preorder traversal of the left subtree and the preorder traversal of the right subtree.
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Function inorder is used to print the inorder traversal of RB-Tree.
void inorder(struct Node *root)
{
    // If we hit a null or an ext_node then we stop traversing the tree.
    if (root == nullptr || is_ext_node(root))
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

// Test function runs the given functions for the test case specified in the question for each function.
void test()
{
    // We set the root of the tree to nullptr.
    struct Node *root = nullptr;
    // We hard code the values to be inserted into the tree while constructing it as given in the problem statement and insert them by calling the insert function.
    vector<int> to_create = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    for (int i : to_create)
    {
        root = insert(root, i);
    }
    // We print the resulting inorder and preorder traversal of tree to verify insert function's correctness.
    cout << "The inorder traversal of the tree is: ";
    inorder(root);
    cout << endl;
    cout << "The preorder traversal of the tree is: ";
    preorder(root);
    cout << endl;
    // We hard code the values to be searched, inserted intro the tree and deleted from the tree after constructing it as given in the problem statement
    // and subsequently search, insert and delete them by calling the search, insert and delete functions respectively.
    vector<int> to_search = {32, 56, 90}, to_insert = {132, 156, 11, 7}, to_delete_1 = {21, 78, 132, 156, 112, 31, 5, 90}, to_delete = {332, 51, 71, 67};
    // We run the search function for the values to be searched.
    for (int i : to_search)
    {
        // If the value is present in the tree, we print it is present in the tree.
        if (search(root, i))
        {
            cout << i << " is present in the tree." << endl;
        }
        // Else if the value is not present in the tree, we print it is not present in the tree.
        else
        {
            cout << i << " is not present in the tree." << endl;
        }
    }
    // We run the insert function for the values to be inserted.
    for (int i : to_insert)
    {
        root = insert(root, i);
    }
    // We print the resulting inorder and preorder traversal of tree to verify insert function's correctness.
    cout << "The inorder traversal of the tree is: ";
    inorder(root);
    cout << endl;
    cout << "The preorder traversal of the tree is: ";
    preorder(root);
    cout << endl;
    // We run the delete function for the values to be deleted.
    for (int i : to_delete_1)
    {
        // If a node with the given value is found in the tree, we delete it.
        if (search(root, i))
        {
            cout << "Node with data " << del(root, i) << " deleted" << endl;
        }
        // If a node with the given value doesn't exist in the tree, we print the error message below.
        else
        {
            cout << "The element " << i << " is not present in the red-black tree. Hence, we cannot delete it." << endl;
        }
    }
    // We print the resulting inorder and preorder traversal of tree to verify delete function's correctness.
    cout << "The inorder traversal of the tree is: ";
    inorder(root);
    cout << endl;
    cout << "The preorder traversal of the tree is: ";
    preorder(root);
    cout << endl;
}

// The main function runs the code with user input.
int main()
{
    // We set the root of the tree to nullptr.
    struct Node *root = nullptr;
    // We run the test function to verify it for the test case given in the question.
    // We can comment this if we want to test our own test case.
    test();
    // We take the number of elements to be inserted in the tree as user input n.
    int n;
    cin >> n;
    // For each of the n numbers, we read it from the input stream, insert it into the tree.
    while (n > 0)
    {
        int x;
        cin >> x;
        root = insert(root, x);
        n--;
    }
    // We print the resulting inorder and preorder traversal of tree to verify insert function's correctness.
    cout << "The inorder traversal of the tree is: ";
    inorder(root);
    cout << endl;
    cout << "The preorder traversal of the tree is: ";
    preorder(root);
    cout << endl;

    // We again take in user input, store it in the integer variable op, for either searching, inserting or deleting an element as shown below.
    cout << "Enter your choice: " << endl;
    cout << "1 - Search for an element" << endl;
    cout << "2 - Insert an element" << endl;
    cout << "3 - Delete an element" << endl;
    cout << "0 - Exit" << endl;
    int op;
    cin >> op;
    // We continuously take user inputs until op = 0.
    while (op)
    {
        // If the user inputs 1, we search for the node with the given value key, taken as user input, in the user constructed RB-Tree, by running the search function.
        if (op == 1)
        {
            int key;
            cin >> key;
            search(root, key);
        }
        // If the user inputs 2, we insert a new node with the given value key, taken as user input, in the user constructed RB-Tree, by running the insert function.
        else if (op == 2)
        {
            int key;
            cin >> key;
            root = insert(root, key);
            // We subsequently print the inorder, preorder traversals of the tree to verify our insert function.
            cout << "The inorder traversal of the tree is: ";
            inorder(root);
            cout << endl;
            cout << "The preorder traversal of the tree is: ";
            preorder(root);
            cout << endl;
        }
        // If the user inputs 3, we delete the node with the given value key, taken as user input, from the user constructed RB-Tree, by running the delete function.
        else if (op == 3)
        {
            int key;
            cin >> key;
            // If a node with the given data = key exists in the RB-Tree, then we delete the node and print the value deleted.
            if (search(root, key))
            {
                cout << del(root, key) << " is deleted from the Red-Black Tree" << endl;
            }
            // If a node with the given data = key doesn't exist in the RB-Tree, then we cannot delete it and hence we print the error message given below.
            else
            {
                cout << "The element " << key << " is not present in the red-black tree. Hence, we cannot delete it." << endl;
            }
        }
        // We again take user input in an infinite loop, till op = 0 and print the user choices again.
        cout << "Enter your choice: " << endl;
        cout << "1 - Search for an element" << endl;
        cout << "2 - Insert an element" << endl;
        cout << "3 - Delete an element" << endl;
        cout << "0 - Exit" << endl;
        int op;
        cin >> op;
    }
}