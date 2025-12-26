#include <stdio.h>
#include <stdlib.h>

// Node structure as specified
struct node {
    int data;
    struct node *left;
    struct node *right;
};

// Function to create a new node
struct node* createNode(int key) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert left child
struct node* insertLeft(struct node* root, int key) {
    if (root == NULL) return NULL;
    root->left = createNode(key);
    return root->left;
}

// Function to insert right child
struct node* insertRight(struct node* root, int key) {
    if (root == NULL) return NULL;
    root->right = createNode(key);
    return root->right;
}

// Helper function to find index of element in inorder array
int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Main function to build tree from preorder and inorder traversals
struct node* buildTree(int preorder[], int inorder[], int inStart, int inEnd, int* preIndex) {
    // Base case
    if (inStart > inEnd) {
        return NULL;
    }
    
    // Create root node with current preorder element
    struct node* root = createNode(preorder[*preIndex]);
    (*preIndex)++;
    
    // If this node has no children, return
    if (inStart == inEnd) {
        return root;
    }
    
    // Find the index of root in inorder array
    int inIndex = findIndex(inorder, inStart, inEnd, root->data);
    
    // Recursively build left and right subtrees
    root->left = buildTree(preorder, inorder, inStart, inIndex - 1, preIndex);
    root->right = buildTree(preorder, inorder, inIndex + 1, inEnd, preIndex);
    
    return root;
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

// Postorder traversal
void postorderTraversal(struct node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Function to free the tree memory
void freeTree(struct node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Function to fill test data - uncomment to use predefined test cases
void fillTestData(int testCase, int* n, int preorder[], int inorder[]) {
    if (testCase == 0) {
        // First test case from the problem
        *n = 9;
        int pre[] = {1, 2, 4, 5, 6, 7, 3, 8, 9};
        int in[] = {4, 2, 6, 5, 7, 1, 3, 9, 8};
        for (int i = 0; i < *n; i++) {
            preorder[i] = pre[i];
            inorder[i] = in[i];
        }
    } else if (testCase == 1) {
        // Second test case from the problem
        *n = 9;
        int pre[] = {3, 5, 6, 2, 7, 4, 1, 0, 8};
        int in[] = {6, 5, 7, 2, 4, 3, 0, 1, 8};
        for (int i = 0; i < *n; i++) {
            preorder[i] = pre[i];
            inorder[i] = in[i];
        }
    } else if (testCase == 2) {
        // Additional test case - simple tree
        *n = 5;
        int pre[] = {1, 2, 4, 5, 3};
        int in[] = {4, 2, 5, 1, 3};
        for (int i = 0; i < *n; i++) {
            preorder[i] = pre[i];
            inorder[i] = in[i];
        }
    } else if (testCase == 3) {
        // Additional test case - single node
        *n = 1;
        int pre[] = {42};
        int in[] = {42};
        for (int i = 0; i < *n; i++) {
            preorder[i] = pre[i];
            inorder[i] = in[i];
        }
    } else {
        // Default case - simple 3-node tree
        *n = 3;
        int pre[] = {1, 2, 3};
        int in[] = {2, 1, 3};
        for (int i = 0; i < *n; i++) {
            preorder[i] = pre[i];
            inorder[i] = in[i];
        }
    }
}

int main() {
    // Set USE_TEST_DATA to 1 to use predefined test data, 0 to use scanf
    int USE_TEST_DATA = 1;
    
    int k; // number of test cases
        
    if (USE_TEST_DATA) {
        k = 2; // Use the two test cases from the problem
        printf("Using predefined test data with %d test cases:\n\n", k);
    } else {
        scanf("%d", &k);
    }
    
    for (int t = 0; t < k; t++) {
        int n; // number of nodes
        int preorder[100], inorder[100]; // Using fixed size arrays for test data
        
        if (USE_TEST_DATA) {
            fillTestData(t, &n, preorder, inorder);
            printf("Test Case %d (n=%d):\n", t + 1, n);
            printf("Preorder input: ");
            for (int i = 0; i < n; i++) printf("%d ", preorder[i]);
            printf("\nInorder input:  ");
            for (int i = 0; i < n; i++) printf("%d ", inorder[i]);
            printf("\n");
        } else {
            scanf("%d", &n);
            
            // Read preorder array
            for (int i = 0; i < n; i++) {
                scanf("%d", &preorder[i]);
            }
            
            // Read inorder array
            for (int i = 0; i < n; i++) {
                scanf("%d", &inorder[i]);
            }
        }
        
        // Build the tree
        int preIndex = 0;
        struct node* root = buildTree(preorder, inorder, 0, n - 1, &preIndex);
        
        // Print traversals
        printf("Preorder:  ");
        preorderTraversal(root);
        printf("\n");
        
        printf("Postorder: ");
        postorderTraversal(root);
        printf("\n");
        
        printf("Inorder:   ");
        inorderTraversal(root);
        printf("\n\n");
        
        // Free memory
        freeTree(root);
    }
    
    return 0;
}