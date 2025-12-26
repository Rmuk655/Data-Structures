#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Time complexity = O(m + log n)
// Space complexity = O(n)

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

// Uncomment the two functions below.
//  // Function to create an external node for all leaf nodes in the RB Tree.
//  struct Node *create_ext_node()
//  {
//      Node *ext_node = (Node *)malloc(sizeof(Node));
//      ext_node->data = INT_MIN;
//      // Note that we have set ext_node->left to ext_node itself to avoid nullptr access issues when we do something like node->left->color.
//      ext_node->left = ext_node;
//      ext_node->right = ext_node;
//      ext_node->parent = nullptr;
//      ext_node->color = BLACK;
//      // In theory, external (NIL) nodes are not real nodes, so they are said to be uncolored.
//      // But for defining black-height and ensuring balance, they're treated as black.
//      return ext_node;
//  }

// // Function to create a node in the RB Tree and initialize it's corresponding attributes.
// struct Node *create_new_node(int key)
// {
//     Node *temp = new Node;
//     temp->data = key;
//     // We create new external nodes(assigned to temp->left) by calling the above function and setting their parent pointers to the node created by this function itself.
//     temp->left = create_ext_node();
//     temp->left->parent = temp;
//     // We create new external nodes(assigned to temp->right) by calling the above function and setting their parent pointers to the node created by this function itself.
//     temp->right = create_ext_node();
//     temp->right->parent = temp;
//     temp->parent = nullptr;
//     temp->color = true;
//     return temp;
// }

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

// Uncomment all the commented functions below.
// // Time complexity = O(h) = O(log n), h is the height of the RB-Tree.
// // Space complexity = O(h) = O(log n), h is the height of the RB-Tree.
// // Search function searches for a given node in the RB-Tree whose data matches with key.
// Node *search(Node *root, int key)
// {
//     // If we search an empty tree or encounter an external node, we terminate search and return nullptr.
//     if (root == nullptr || is_ext_node(root))
//     {
//         return nullptr;
//     }
//     // If the root of the tree has no children, then we check if it's data value matches the key value.
//     else if (root->left == nullptr && root->right == nullptr)
//     {
//         // If the data value of the root node matches the key value, then we return root as the result of the search operation.
//         if (root->data == key)
//         {
//             return root;
//         }
//         // Else we return nullptr as the result of the search operation.
//         return nullptr;
//     }
//     // If the key is found in the left subtree of the RB-Tree, return the node containing key, i.e. search(root->left, key).
//     if (search(root->left, key))
//     {
//         return search(root->left, key);
//     }
//     // Else search the right subtree of root and return it, i.e. return search(root->right, key).
//     return search(root->right, key);
// }

// // Left rotate function is used to convert a given branch of a tree with parent paren, right child child to parent child and left child paren.
// void Left_rotate(Node *&root, Node *paren)
// {
//     // We store the right child of paren as child.
//     Node *child = paren->right;
//     // Left child of child becomes the root of paren's right subtree.
//     paren->right = child->left;
//     // If left child of child is not an external node we update it's parent pointer.
//     if (!is_ext_node(child->left))
//     {
//         child->left->parent = paren;
//     }
//     // We update child's parent pointer.
//     child->parent = paren->parent;
//     // If paren is root, it's parent is nullptr and hence we set root as child.
//     if (paren->parent == nullptr)
//     {
//         root = child;
//     }
//     // If paren is the left child of it's parent, then we set left child of paren's parent as child.
//     else if (paren->parent->left == paren)
//     {
//         paren->parent->left = child;
//     }
//     // If paren is the right child of it's parent, then we set right child of paren's parent as child.
//     else
//     {
//         paren->parent->right = child;
//     }
//     // We set paren as child's left child and paren's new parent as child.
//     child->left = paren;
//     paren->parent = child;
// }

// // Left rotate function is used to convert a given branch of a tree with parent paren, left child child to parent child and right child paren.
// void Right_rotate(Node *&root, Node *paren)
// {
//     // We store the right child of paren as child.
//     Node *child = paren->left;
//     // Right child of child becomes the root of paren's left subtree.
//     paren->left = child->right;
//     // If left child of child is not an external node we update it's parent pointer.
//     if (!is_ext_node(child->right))
//     {
//         child->right->parent = paren;
//     }
//     // We update child's parent pointer.
//     child->parent = paren->parent;
//     // If paren is root, it's parent is nullptr and hence we set root as child.
//     if (paren->parent == nullptr)
//     {
//         root = child;
//     }
//     // If paren is the left child of it's parent, then we set left child of paren's parent as child.
//     else if (paren->parent->left == paren)
//     {
//         paren->parent->left = child;
//     }
//     // If paren is the right child of it's parent, then we set right child of paren's parent as child.
//     else
//     {
//         paren->parent->right = child;
//     }
//     // We set paren as child's right child and paren's new parent as child.
//     child->right = paren;
//     paren->parent = child;
// }

// // Helper function other_child helps us find the sibling of child1.
// struct Node *other_child(struct Node *parent, struct Node *child1)
// {
//     // If child1 is left child, we return the right child.
//     if (parent->left == child1)
//     {
//         return parent->right;
//     }
//     // Else we return the left child.
//     return parent->left;
// }

// // Time complexity = O(h) = O(log n), h is the height of the RB-Tree.
// // Space complexity = O(h) = O(log n), h is the height of the RB-Tree.
// // Insert function is used to insert a new node into the RB tree with data key.
// Node *insert(Node *root, int key)
// {
//     // If the root is an external node, then we create a new node with value key after deleting this external node and join it to the tree.
//     if (is_ext_node(root))
//     {
//         Node *parent = root->parent;
//         free(root);
//         root = create_new_node(key);
//         root->parent = parent;
//         return root;
//     }

//     // If the element is already present in the tree, we return directly as we cannot insert duplicate values into the RB-Tree.
//     if (search(root, key))
//     {
//         cout << "Duplicate element inserted" << endl;
//         return root;
//     }
//     // If the tree doesn;t exist, then we create a new node with data as key and set it to root. We set root->color as BLACK.
//     else if (root == nullptr)
//     {
//         root = create_new_node(key);
//         root->color = BLACK;
//         return root;
//     }

//     // We store the value of the root of the tree in the variable temp to traverse through the RB-tree.
//     struct Node *temp = root;
//     while (!is_ext_node(temp))
//     {
//         // If key < temp->data we go traverse in the left subtree of temp.
//         if (key < temp->data)
//         {
//             // We break when we hit an external node and insert our new node by deleting this external node.
//             if (is_ext_node(temp->left))
//             {
//                 break;
//             }
//             temp = temp->left;
//         }
//         // If key > temp->data we go traverse in the right subtree of temp.
//         else
//         {
//             // We break when we hit an external node and insert our new node by deleting this external node.
//             if (is_ext_node(temp->right))
//             {
//                 break;
//             }
//             temp = temp->right;
//         }
//     }
//     // We store the newly created node to be inserted into the tree in new_node.
//     // If key < temp->data we insert it as the left child of temp.
//     struct Node *new_node = create_new_node(key);
//     if (key < temp->data)
//     {
//         delete (temp->left);
//         temp->left = new_node;
//         new_node->parent = temp;
//     }
//     // If key > temp->data we insert it as the right child of temp.
//     else
//     {
//         delete (temp->right);
//         temp->right = new_node;
//         new_node->parent = temp;
//     }

//     // We now check if the tree satisfied RB properties of a RED node has no RED child. If it doesn't, we perform rotations.
//     while (new_node->parent != nullptr && new_node->parent->color == true)
//     {
//         // We find the uncle of the newly inserted node's parent and store it in uncle.
//         struct Node *uncle = other_child(new_node->parent->parent, new_node->parent);
//         // If the uncle is red colored, then we just recolor new_node, it's parent, grandparent and uncle.
//         if (uncle != nullptr && uncle->color == true)
//         {
//             // grandparent is colored red, parent, uncle to black while new_node color remains unchanged.
//             new_node->parent->parent->color = true;
//             new_node->parent->color = false;
//             uncle->color = false;
//             // We set new_node to it's grandparent to check if RED node, no RED child property is violated in the tree above.
//             new_node = new_node->parent->parent;
//         }
//         // If the uncle is an external node or colored black, we handle it in 4 different cases.
//         else
//         {
//             // Case 1: The parent is the left child of it's grandparent.
//             if (new_node->parent == new_node->parent->parent->left)
//             {
//                 // Case 1a: The child is the right child of it's parent.
//                 if (new_node == new_node->parent->right)
//                 {
//                     new_node = new_node->parent;
//                     Left_rotate(root, new_node);
//                 }
//                 // Case 1b: The child is the left child of it's parent.
//                 new_node->parent->color = BLACK;
//                 new_node->parent->parent->color = RED;
//                 Right_rotate(root, new_node->parent->parent);
//             }
//             // Case 2: The parent is the right child of it's grandparent.
//             else
//             {
//                 // Case 2a: The child is the left child of it's parent.
//                 if (new_node == new_node->parent->left)
//                 {
//                     new_node = new_node->parent;
//                     Right_rotate(root, new_node);
//                 }
//                 // Case 2b: The child is the right child of it's parent.
//                 new_node->parent->color = BLACK;
//                 new_node->parent->parent->color = RED;
//                 Left_rotate(root, new_node->parent->parent);
//             }
//         }
//         // We recolor root to black, if it's color was changed by the above code.
//         root->color = BLACK;
//     }
//     // We return the root of the tree so that the root pointer can be reset to the new root, if there were changes to it after insertion.
//     return root;
// }

// Time complexity = O(m + log n), where m is the number of keys that are outputted, and n is the number of internal nodes in the given RB-Tree.
void RB_ENUMERATE(struct Node *root, int a, int b)
{
    // If the tree doesn't exist, or we reach an external node or if a > b (ideally no node can satisfy such a condition), then we return directly.
    if ((a > b) || root == nullptr || is_ext_node(root))
    {
        return;
    }
    // If root->data > a, there might be node data values satisfying a <= value <= b in the left subtree of root.
    // Hence, we search for them using RB_ENUMERATE(root->left, a, b).
    if (root->data > a)
    {
        RB_ENUMERATE(root->left, a, b);
    }
    // If the given root->data satisfies the given condition, a <= root->data <= b, we print it.
    if (root->data >= a && root->data <= b)
    {
        cout << root->data << " ";
    }
    // If root->data < b, there might be node data values satisfying a <= value <= b in the right subtree of root.
    // Hence, we search for them using RB_ENUMERATE(root->right, a, b).
    if (root->data < b)
    {
        RB_ENUMERATE(root->right, a, b);
    }
}

// Main function used to run the given code for user inputs.
int main()
{
    // Initialize the root of the RB-Tree to nullptr.
    struct Node *root = nullptr;
    // Uncomment the following code lines, all helper function codes and search, insert function codes to insert elements into the RB-Tree and
    // // test the RB_ENUMERATE(x, a, b) function for different RB-Trees and different values of a, b.
    // // cout << "Inserting elements into the RB-Tree." << endl;
    // // Take the input of the number of elements to be inserted into the RB-Tree as n.
    // int n;
    // cin >> n;
    // // Run a for loop taking each of the n elements as an input stored in the number x and insert each insert into the given RB-Tree with root root.
    // for (int i = 0; i < n; i++)
    // {
    //     int x;
    //     cin >> x;
    //     root = insert(root, x);
    // }
    // // Take user input for a, b for the lower and upper bound (as in a, b in RB_ENUMERATE(root, a, b)).
    // int a, b;
    // cin >> a >> b;
    // RB_ENUMERATE(root, a, b);
    // cout << endl;
}