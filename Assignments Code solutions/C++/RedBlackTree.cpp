#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Node structure as specified in the assignment
struct node {
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
    bool color;        // true for RED, false for BLACK
    int black_depth;   // optional field as mentioned
};

// Color definitions for better readability
#define RED true
#define BLACK false

// NIL node (sentinel) - all leaf nodes point to this
struct node* NIL;

// Function to initialize NIL node
void initializeNIL() {
    NIL = (struct node*)malloc(sizeof(struct node));
    NIL->data = 0;
    NIL->left = NULL;
    NIL->right = NULL;
    NIL->parent = NULL;
    NIL->color = BLACK;
    NIL->black_depth = 0;
}

// Function to create a new node
struct node* createNode(int key) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = key;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NIL;
    newNode->color = RED;  // New nodes are always inserted as RED
    newNode->black_depth = 0;
    return newNode;
}

// Function to perform left rotation
void leftRotate(struct node** root, struct node* x) {
    struct node* y = x->right;
    
    // Turn y's left subtree into x's right subtree
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    }
    
    // Link x's parent to y
    y->parent = x->parent;
    if (x->parent == NIL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    // Put x on y's left
    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(struct node** root, struct node* y) {
    struct node* x = y->left;
    
    // Turn x's right subtree into y's left subtree
    y->left = x->right;
    if (x->right != NIL) {
        x->right->parent = y;
    }
    
    // Link y's parent to x
    x->parent = y->parent;
    if (y->parent == NIL) {
        *root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    
    // Put y on x's right
    x->right = y;
    y->parent = x;
}

// Function to fix Red-Black tree violations after insertion
void insertFixup(struct node** root, struct node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            // z's parent is left child of z's grandparent
            struct node* y = z->parent->parent->right;  // Uncle of z
            
            if (y->color == RED) {
                // Case 1: Uncle is RED
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2: Uncle is BLACK and z is right child
                    z = z->parent;
                    leftRotate(root, z);
                }
                // Case 3: Uncle is BLACK and z is left child
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            // z's parent is right child of z's grandparent (symmetric to above)
            struct node* y = z->parent->parent->left;  // Uncle of z
            
            if (y->color == RED) {
                // Case 1: Uncle is RED
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Case 2: Uncle is BLACK and z is left child
                    z = z->parent;
                    rightRotate(root, z);
                }
                // Case 3: Uncle is BLACK and z is right child
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;  // Root is always BLACK
}

// Insert function for Red-Black tree
struct node* insert(struct node* root, int key) {
    // Create new node
    struct node* z = createNode(key);
    struct node* y = NIL;
    struct node* x = root;
    
    // Find the position to insert the new node
    while (x != NIL) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else if (z->data > x->data) {
            x = x->right;
        } else {
            // Key already exists, don't insert duplicate
            free(z);
            return root;
        }
    }
    
    // Set parent of new node
    z->parent = y;
    
    // Insert the new node
    if (y == NIL) {
        root = z;  // Tree was empty
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    // Fix any Red-Black tree violations
    insertFixup(&root, z);
    
    return root;
}

// Search function
struct node* search(struct node* root, int key) {
    struct node* current = root;
    
    while (current != NIL) {
        if (key == current->data) {
            printf("Key %d found in the Red-Black tree.\n", key);
            return current;
        } else if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    printf("Error: Key %d not found in the Red-Black tree.\n", key);
    return NULL;
}

// Inorder traversal
void inorderTraversal(struct node* root) {
    if (root != NIL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Preorder traversal
void preorderTraversal(struct node* root) {
    if (root != NIL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED_COLOR     "\033[1;31m"
#define BLACK_COLOR   "\033[1;30m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

// Helper: Get color for Red-Black nodes
const char* getNodeColor(struct node* node) {
    if (node == NIL) return WHITE;
    return node->color == RED ? RED_COLOR : WHITE;  // Red nodes in red, black nodes in white
}

// Recursive function to print the tree top-down in ASCII (no UTF-8 chars)
void printTreePretty(struct node* root, const char* prefix, bool isLeft) {
    if (root == NIL) return;
    
    // Print current node
    printf("%s", prefix);
    printf("%s", isLeft ? "+- " : "`- ");
    
    printf("%s%d(%c)%s\n", 
           getNodeColor(root), 
           root->data, 
           root->color == RED ? 'R' : 'B', 
           RESET);
    
    // Construct new prefix for children
    char newPrefix[1024];
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLeft ? "|   " : "    ");
    
    // Recursively print children (left first, then right)
    if (root->left != NIL || root->right != NIL) {
        printTreePretty(root->left, newPrefix, true);
        printTreePretty(root->right, newPrefix, false);
    }
}

// Function to print tree structure with colors (for debugging)
void printTree(struct node* root, int space) {
    int COUNT = 10;
    if (root == NIL)
        return;
    
    space += COUNT;
    printTree(root->right, space);
    
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s%d(%c)%s\n", getNodeColor(root), root->data, root->color == RED ? 'R' : 'B', RESET);
    
    printTree(root->left, space);
}

// Function to calculate and update black depth for each node
void calculateBlackDepth(struct node* root, int depth) {
    if (root == NIL) {
        return;
    }
    
    if (root->color == BLACK) {
        depth++;
    }
    root->black_depth = depth;
    
    calculateBlackDepth(root->left, depth);
    calculateBlackDepth(root->right, depth);
}

// Function to free the tree
void freeTree(struct node* root) {
    if (root != NIL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Test function for Red-Black tree construction and operations
void testRedBlackTree() {
    struct node* root = NIL;
    
    // Initial keys to insert as specified in the assignment
    int keys[] = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    printf("=== Red-Black Tree Construction ===\n");
    printf("Inserting keys: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", keys[i]);
    }
    printf("\n\n");
    
    // Insert all keys
    for (int i = 0; i < n; i++) {
        printf("Inserting %d:\n", keys[i]);
        root = insert(root, keys[i]);
        printf("Inorder:  ");
        inorderTraversal(root);
        printf("\nPreorder: ");
        preorderTraversal(root);
        printf("\n\n");
    }
    
    printf("=== Final Red-Black Tree Structure ===\n");
    printf("(Red nodes shown in red color, Black nodes in white)\n");
    printf("ASCII Tree Visualization:\n");
    printTreePretty(root, "", false);
    //printf("\nTraditional Tree View:\n");
    //printTree(root, 0);
    printf("\n");
    
    // Calculate black depths
    calculateBlackDepth(root, 0);
    
    printf("=== Search Operations ===\n");
    // Search for specific keys as requested in assignment
    int searchKeys[] = {32, 56, 90};
    int searchCount = sizeof(searchKeys) / sizeof(searchKeys[0]);
    
    for (int i = 0; i < searchCount; i++) {
        printf("Searching for %d: ", searchKeys[i]);
        search(root, searchKeys[i]);
    }
    printf("\n");
    
    printf("=== Additional Insertions ===\n");
    // Additional insertions as requested in assignment
    int additionalKeys[] = {132, 156, 11, 7};
    int additionalCount = sizeof(additionalKeys) / sizeof(additionalKeys[0]);
    
    for (int i = 0; i < additionalCount; i++) {
        printf("Inserting %d:\n", additionalKeys[i]);
        root = insert(root, additionalKeys[i]);
        printf("Inorder:  ");
        inorderTraversal(root);
        printf("\nPreorder: ");
        preorderTraversal(root);
        printf("\n\n");
    }
    
    printf("=== Final Tree Structure After All Insertions ===\n");
    printf("(Red nodes shown in red color, Black nodes in white)\n");
    printf("ASCII Tree Visualization:\n");
    printTreePretty(root, "", false);
    //printf("\nTraditional Tree View:\n");
    //printTree(root, 0);
    printf("\n");
    
    printf("Final Inorder:  ");
    inorderTraversal(root);
    printf("\nFinal Preorder: ");
    preorderTraversal(root);
    printf("\n\n");
    
    // Update black depths for final tree
    calculateBlackDepth(root, 0);
    
    // Clean up
    freeTree(root);
}

int main() {
    printf("Red-Black Tree Implementation\n");
    printf("=============================\n");
    printf("CS2233 Lab Assignment 6\n\n");
    
    // Initialize NIL node
    initializeNIL();
    
    // Run the test
    testRedBlackTree();
    
    // Clean up NIL node
    free(NIL);
    
    return 0;
}