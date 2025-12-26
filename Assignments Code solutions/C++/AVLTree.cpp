#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure as specified
struct node {
    int data;
    int height; /* stores the height of subtree rooted current node */
    struct node *left;
    struct node *right;
    struct node *parent;
};

// Function to create a new node
struct node* createNode(int key) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = key;
    newNode->height = 1; // New node is initially at height 1
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

// Function to get height of a node
int getHeight(struct node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to update height of a node
void updateHeight(struct node* node) {
    if (node != NULL) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// Function to get balance factor of a node
int getBalance(struct node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotate
struct node* rightRotate(struct node* y) {
    struct node* x = y->left;
    struct node* T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update parent pointers
    x->parent = y->parent;
    y->parent = x;
    if (T2 != NULL) {
        T2->parent = y;
    }
    
    // Update heights
    updateHeight(y);
    updateHeight(x);
    
    // Return new root
    return x;
}

// Left rotate
struct node* leftRotate(struct node* x) {
    struct node* y = x->right;
    struct node* T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update parent pointers
    y->parent = x->parent;
    x->parent = y;
    if (T2 != NULL) {
        T2->parent = x;
    }
    
    // Update heights
    updateHeight(x);
    updateHeight(y);
    
    // Return new root
    return y;
}

// Insert function  tells if inserted or duplicate
struct node* insert(struct node* root, int key, bool* inserted) {
    // Step 1: Perform normal BST insertion
    if (root == NULL) {
        *inserted = true;
        return createNode(key);
    }
    
    
    if (key < root->data) {
        root->left = insert(root->left, key, inserted);

        if (root->left != NULL) {
            root->left->parent = root;
        }
    } else if (key > root->data) {
        root->right = insert(root->right, key,inserted);
        if (root->right != NULL) {
            root->right->parent = root;
        }
    } else {
        // Equal keys not allowed
        *inserted = false;
        return root; // duplicate 
    }
    
    // Step 2: Update height of current node
    updateHeight(root);
    
    // Step 3: Get the balance factor
    int balance = getBalance(root);
    
    // Step 4: If unbalanced, there are 4 cases
    
    // Left Left Case
    if (balance > 1 && key < root->left->data) {
        return rightRotate(root);
    }
    
    // Right Right Case
    if (balance < -1 && key > root->right->data) {
        return leftRotate(root);
    }
    
    // Left Right Case
    if (balance > 1 && key > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right Left Case
    if (balance < -1 && key < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    // Return unchanged root
    return root;
}

// Search function
bool search(struct node* root, int key) {

    if (!root) return false;
    if (key == root->data) return true;
    if (key < root->data) return search(root->left, key);
    else return search(root->right, key);

}

// Preorder traversal
void preorderTraversal(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Inorder traversal
void inorderTraversal(struct node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Function to print tree structure (for debugging)
void printTree(struct node* root, int space) {
    int COUNT = 10;
    if (root == NULL)
        return;
    
    space += COUNT;
    printTree(root->right, space);
    
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d(h:%d)\n", root->data, root->height);
    
    printTree(root->left, space);
}
// Helper: Get color based on height 
// ANSI escape codes for colors 
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"

const char* colorForHeight(int h) {
    switch (h % 4) {
        case 0: return RED;
        case 1: return GREEN;
        case 2: return YELLOW;
        default: return CYAN;
    }
}

// Recursive function to print the tree top-down in ASCII (no UTF-8 chars)
void printTreePretty(struct node* root, const char* prefix, bool isLeft) {
    if (root == NULL) return;

    // Print current node
    printf("%s", prefix);
    printf("%s", isLeft ? "+- " : "`- ");

    printf("%s%d(h:%d)%s\n", colorForHeight(root->height), root->data, root->height, RESET);

    // Construct new prefix for children
    char newPrefix[1024];
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLeft ? "|   " : "    ");

    // Recursively print children
    printTreePretty(root->left, newPrefix, true);
    printTreePretty(root->right, newPrefix, false);
}


// Function to free the tree
void freeTree(struct node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}


// Helper function to find node with minimum value in a subtree
struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete a node with given key and rebalance AVL tree
struct node* deleteNode(struct node* root, int key, bool* deleted) {
    if (root == NULL) {
        *deleted = false;
        //printf("Error: Key %d not found in the AVL tree.\n", key);
        return root;
    }

    // BST delete
    if (key < root->data) {
        root->left = deleteNode(root->left, key,deleted);
        if (root->left != NULL)
            root->left->parent = root;
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key,deleted);
        if (root->right != NULL)
            root->right->parent = root;
    } else {
        // Node to delete found
        *deleted = true;
        if (root->left == NULL || root->right == NULL) {
            struct node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                // No child case
                temp = root;
                root = NULL;
            } else {
                // One child case
                *root = *temp;
            }
            free(temp);
        } else {
            // Two children: get inorder successor
            struct node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data,deleted);
            if (root->right != NULL)
                root->right->parent = root;
        }
    }

    // If tree had only one node
    if (root == NULL)
        return root;

    // Update height and rebalance
    updateHeight(root);
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        if (root->left != NULL)
            root->left->parent = root;
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        if (root->right != NULL)
            root->right->parent = root;
        return leftRotate(root);
    }

    return root;
}


// A simple queue for level order traversal
struct queueNode {
    struct node* treeNode;
    struct queueNode* next;
};

struct queue {
    struct queueNode* front;
    struct queueNode* rear;
};

void enqueue(struct queue* q, struct node* tn) {
    struct queueNode* newQN = (struct queueNode*)malloc(sizeof(struct queueNode));
    newQN->treeNode = tn;
    newQN->next = NULL;
    if (!q->rear) {
        q->front = q->rear = newQN;
    } else {
        q->rear->next = newQN;
        q->rear = newQN;
    }
}

struct node* dequeue(struct queue* q) {
    if (!q->front) return NULL;
    struct queueNode* temp = q->front;
    struct node* tn = temp->treeNode;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return tn;
}

bool isEmpty(struct queue* q) {
    return (q->front == NULL);
}

// Level order traversal - print each level on new line
void levelOrder(struct node* root) {
    if (!root) return;
    struct queue q = {NULL, NULL};
    enqueue(&q, root);
    while (!isEmpty(&q)) {
        int levelNodeCount = 0;
        struct queueNode* temp = q.front;
        // Count nodes at current level
        while (temp) {
            levelNodeCount++;
            temp = temp->next;
        }
        while (levelNodeCount--) {
            struct node* curr = dequeue(&q);
            printf("%d ", curr->data);
            if (curr->left) enqueue(&q, curr->left);
            if (curr->right) enqueue(&q, curr->right);
        }
        printf("\n");
    }
}


// Test function for AVL tree construction and operations
void testAVLTree() {
    struct node* root = NULL;
    
    // Initial keys to insert
    int keys[] = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    printf("=== AVL Tree Construction ===\n");
    printf("Inserting keys: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", keys[i]);
    }
    printf("\n\n");
    
    // Insert all keys
    bool inserted;
    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i], &inserted);
        if(!inserted)
            printf("Error inserting key \n");
        printf("After inserting %d:\n", keys[i]);
        printf("Inorder:  ");
        inorderTraversal(root);
        printf("\nPreorder: ");
        preorderTraversal(root);
        printf("\n\n");
    }
    
    printf("=== Final AVL Tree Structure ===\n");
    //printTree(root, 0);
    printTreePretty(root, "",false);
    printf("\n");
    
    printf("=== Search Operations ===\n");
    // Search for specific keys
    int searchKeys[] = {32, 56, 90};
    int searchCount = sizeof(searchKeys) / sizeof(searchKeys[0]);
    
    for (int i = 0; i < searchCount; i++) {
        printf("Searching for %d: ", searchKeys[i]);
        search(root, searchKeys[i]);
    }
    printf("\n");
    
    printf("=== Additional Insertions ===\n");
    // Additional insertions
    int additionalKeys[] = {132, 156, 11, 7};
    int additionalCount = sizeof(additionalKeys) / sizeof(additionalKeys[0]);
    
    
    for (int i = 0; i < additionalCount; i++) {
        printf("Inserting %d:\n", additionalKeys[i]);
        root = insert(root, additionalKeys[i],&inserted);
        if(!inserted)
            printf("Insertion failed:  ");
        printf("Inorder:  ");
        inorderTraversal(root);
        printf("\nPreorder: ");
        preorderTraversal(root);
        printf("\n\n");
    }
    
    printf("=== Final Tree Structure After All Insertions ===\n");
    //printTree(root, 0);
    printTreePretty(root, "",false);
    printf("\n");
    
    printf("Final Inorder:  ");
    inorderTraversal(root);
    printf("\nFinal Preorder: ");
    preorderTraversal(root);
    printf("\n\n");
 
    // Keys to delete
    int deleteKeys[] = {88, 9, 71, 67};
    int delCount = sizeof(deleteKeys) / sizeof(deleteKeys[0]);
    bool deleted;
    printf("=== Deletion Operations ===\n");
    for (int i = 0; i < delCount; i++) {
        printf("Deleting %d:\n", deleteKeys[i]);
        root = deleteNode(root, deleteKeys[i], &deleted);
        if(!deleted) 
            printf("Deletion failed \n ");
        printf("Inorder:  ");
        inorderTraversal(root);
        printf("\nPreorder: ");
        preorderTraversal(root);
        printf("\n\n");
    }

    printf("=== Final Tree Structure After All Deletionss ===\n");
    //printTree(root, 0);
    printTreePretty(root, "",false);
    printf("\n");
 
    // Clean up
    freeTree(root);
}

int main() {
    printf("AVL Tree Implementation\n");
    printf("=======================\n\n");
    testAVLTree();
    int n;
    scanf("%d", &n);

    struct node* root = NULL;

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        bool inserted = false;
        root = insert(root, val, &inserted);
    }

    while (1) {
        int qType, val;
        int ret = scanf("%d", &qType);
        if (ret == EOF) break; // End of input
        if (qType == 4) {
            levelOrder(root);
            continue;
        }
        scanf("%d", &val);

        if (qType == 1) {
            bool found = search(root, val);
            if (found)
                printf("%d present\n", val);
            else
                printf("%d not present\n", val);
        } else if (qType == 2) {
            bool inserted = false;
            root = insert(root, val, &inserted);
            if (inserted)
                printf("%d inserted\n", val);
            else
                printf("%d already present. So no need to insert.\n", val);
        } else if (qType == 3) {
            bool deleted = false;
            root = deleteNode(root, val, &deleted);
            if (deleted)
                printf("%d deleted\n", val);
            else
                printf("%d not present. So it can not be deleted.\n", val);
        } else {
            // Invalid query type - ignore or print error if you want
        }
    }

    // Free tree memory if needed here
   
    
    return 0;
}