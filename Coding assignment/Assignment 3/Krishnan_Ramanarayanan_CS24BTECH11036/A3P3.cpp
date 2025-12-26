#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

#define MAX 5
#define MIN ((MAX + 1) / 2 - 1)

// Definition of each node of the B-Tree.
struct BTreeNode
{
    int key[MAX];
    int count; /* count stores the number of keys in the current node */
    struct BTreeNode *children[MAX + 1];
};

// Function to create a new node in the tree by setting up the pointers appropriately.
BTreeNode *createNode(int key)
{
    BTreeNode *root = new BTreeNode;
    root->key[0] = key;
    for (int i = 1; i <= MAX; i++)
    {
        root->key[i] = INT_MAX;
    }
    for (int i = 0; i <= MAX; i++)
    {
        root->children[i] = nullptr;
    }
    if (key == INT_MAX)
    {
        root->count = 0;
        return root;
    }
    root->count = 1;
    return root;
}

int no_of_children(BTreeNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int ch = 0;
    for (int i = 0; i <= MAX; i++)
    {
        if (node->children[i] != nullptr)
        {
            ch++;
        }
    }
    return ch;
}

// Time complexity = O(h) = O(log n), h is the height of the B-Tree.
// Space complexity = O(h) = O(log n), h is the height of the B-Tree.
// Search function searches for a given node in the B-tree with data key.
BTreeNode *search(BTreeNode *root, int key)
{
    // If the tree doesn't exist, the search has failed.
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (no_of_children(root) == 0)
    {
        for (int i = 0; i < root->count; i++)
        {
            if (root->key[i] == key)
            {
                return root;
            }
        }
        return nullptr;
    }
    // We implement search recursively. The search terminates when any of root->key[i] matches key.
    if (key < root->key[0])
    {
        return search(root->children[0], key);
    }
    for (int i = 0; i < root->count - 1; i++)
    {
        if (root->key[i] == key)
        {
            // cout << "Found " << root->key[i] << endl;
            return root;
        }
        else if (key > root->key[i] && key < root->key[i + 1])
        {
            return search(root->children[i + 1], key);
        }
    }
    if (key == root->key[root->count - 1])
    {
        // cout << "Found " << root->key[root->count - 1] << endl;
        return root;
    }
    else if (key > root->key[root->count - 1])
    {
        return search(root->children[root->count], key);
    }
    return nullptr;
}

void splitchild(BTreeNode *&x, int i)
{
    int t = (MAX + 1) / 2;
    BTreeNode *y = x->children[i];
    BTreeNode *z = createNode(INT_MAX);
    int middle_key = y->key[t - 1];
    z->count = t - 1;
    for (int j = 0; j < t - 1; j++)
    {
        z->key[j] = y->key[j + t];
    }
    if (no_of_children(y) > 0)
    {
        for (int j = 0; j < t; j++)
        {
            z->children[j] = y->children[j + t];
        }
    }
    y->count = t - 1;
    for (int j = x->count; j >= i + 1; j--)
    {
        x->children[j + 1] = x->children[j];
    }
    x->children[i + 1] = z;
    for (int j = (x->count - 1); j >= i; j--)
    {
        x->key[j + 1] = x->key[j];
    }
    x->key[i] = middle_key;
    x->count++;
    for (int j = t; j < MAX; j++)
    {
        y->key[j] = INT_MAX;
    }
    for (int j = t; j <= MAX; j++)
    {
        y->children[j] = nullptr;
    }
}

void insertnonfull(BTreeNode *node, int key)
{
    int index = node->count - 1;
    if (no_of_children(node) == 0)
    {
        while (index >= 0 && key < node->key[index])
        {
            node->key[index + 1] = node->key[index];
            index--;
        }
        node->key[index + 1] = key;
        node->count++;
    }
    else
    {
        while (index >= 0 && key < node->key[index])
        {
            index--;
        }
        index++;
        if (node->children[index]->count == MAX)
        {
            splitchild(node, index);
            if (key > node->key[index])
            {
                index++;
            }
        }
        insertnonfull(node->children[index], key);
    }
}

struct BTreeNode *split_root(struct BTreeNode *&root)
{
    struct BTreeNode *split = createNode(INT_MAX);
    split->count = 0;
    split->children[0] = root;
    root = split;
    splitchild(split, 0);
    return split;
}

// Time complexity = O(h) = O(log n), h is the height of the B-Tree.
// Space complexity = O(h) = O(log n), h is the height of the B-Tree.
// Insert function is used to insert a new node into the tree with data key.
struct BTreeNode *insert(struct BTreeNode *root, int key)
{
    if (root == nullptr)
    {
        root = createNode(key);
        return root;
    }
    else if (search(root, key) != nullptr)
    {
        cout << "Cannot insert duplicate value" << endl;
        return root;
    }
    if (root->count == MAX)
    {
        struct BTreeNode *split = split_root(root);
        insertnonfull(split, key);
    }
    else
    {
        insertnonfull(root, key);
    }
    return root;
}

int key_index(struct BTreeNode *node, int key)
{
    for (int i = 0; i < node->count; i++)
    {
        if (node->key[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int key_child_index(struct BTreeNode *node, int key)
{
    for (int i = 0; i < node->count + 1; i++)
    {
        if (node->children[i] != nullptr && search(node->children[i], key))
        {
            return i;
        }
    }
    return -1;
}

int predecessor(struct BTreeNode *root, int index)
{
    struct BTreeNode *pred = root->children[index];
    while (pred->children[pred->count] != nullptr)
    {
        pred = pred->children[pred->count];
    }
    return pred->key[pred->count - 1];
}

int successor(struct BTreeNode *root, int index)
{
    struct BTreeNode *succ = root->children[index + 1];
    while (succ->children[0] != nullptr)
    {
        succ = succ->children[0];
    }
    return succ->key[0];
}

// Time complexity = O(h) = O(log n), h is the height of the B-Tree.
// Space complexity = O(h) = O(log n), h is the height of the B-Tree.
// Delete function is used to delete a node in the RB tree with the given data value key.
int del(struct BTreeNode *&root, int key)
{
    // We search for the node whose data equals key and store it z.
    struct BTreeNode *temp = search(root, key);
    // If the node to be deleted doesn't exist then we cannot delete it. Hence, we return -1 indicating error.
    if (temp == nullptr)
    {
        cout << key << " not found in the tree. Cannot delete." << endl;
        return -1;
    }

    int t = (MAX + 1) / 2;
    // Case 1: The search arrives at a leaf node x
    if (no_of_children(root) == 0)
    {
        int ind = key_index(root, key);
        for (int i = ind; i < root->count - 1; i++)
        {
            root->key[i] = root->key[i + 1];
        }
        root->count--;
        return key;
    }
    // Case 2: The search arrives at an internal node x that contains key k.
    if (key_index(root, key) >= 0)
    {
        int ind = key_index(root, key);
        struct BTreeNode *prev_child = root->children[ind], *next_child = root->children[ind + 1];
        int t = (MAX + 1) / 2;
        // Case 2a: x->ci has at least t keys.
        if (prev_child->count >= t)
        {
            int pred = predecessor(root, ind);
            root->key[ind] = pred;
            del(prev_child, pred);
        }
        // Case 2b: x->ci has t - 1 keys and x->ci+1 has at least t keys.
        else if (prev_child->count == t - 1 && next_child->count >= t)
        {
            int succ = successor(root, ind);
            root->key[ind] = succ;
            del(next_child, succ);
        }
        // Case 2c: Both x->ci and x->ci+1 have t - 1 keys.
        else if (prev_child->count == t - 1 && next_child->count == t - 1)
        {
            prev_child->key[t - 1] = root->key[ind];

            for (int j = 0; j < next_child->count; j++)
                prev_child->key[j + t] = next_child->key[j];

            if (no_of_children(next_child) > 0)
            {
                for (int j = 0; j <= next_child->count; j++)
                {
                    prev_child->children[j + t] = next_child->children[j];
                }
            }

            prev_child->count += next_child->count + 1;

            for (int j = ind; j < root->count - 1; j++)
                root->key[j] = root->key[j + 1];
            for (int j = ind + 1; j < root->count; j++)
                root->children[j] = root->children[j + 1];

            root->count--;
            delete next_child;

            if (root->count == 0)
            {
                root = prev_child;
            }

            del(prev_child, key);
        }
        return key;
    }
    // Case 3: The search arrives at an internal node x that does not contain key k.
    int ind = key_child_index(root, key);
    if (ind < 0)
    {
        return -1;
    }
    struct BTreeNode *child_with_key = root->children[ind];
    struct BTreeNode *sibling_1 = (ind > 0) ? root->children[ind - 1] : nullptr;
    struct BTreeNode *sibling_2 = (ind < root->count) ? root->children[ind + 1] : nullptr;
    // Case 3a: x->ci has only t - 1 keys but has an immediate sibling with at least t keys.
    if (child_with_key->count == t - 1 && sibling_1 != nullptr && sibling_1->count >= t)
    {
        for (int i = child_with_key->count - 1; i >= 0; i--)
        {
            child_with_key->key[i + 1] = child_with_key->key[i];
        }
        if (no_of_children(child_with_key) > 0)
        {
            for (int i = child_with_key->count; i >= 0; i--)
            {
                child_with_key->children[i + 1] = child_with_key->children[i];
            }
        }

        child_with_key->key[0] = root->key[ind - 1];
        if (no_of_children(sibling_1) > 0)
        {
            child_with_key->children[0] = sibling_1->children[sibling_1->count];
        }

        root->key[ind - 1] = sibling_1->key[sibling_1->count - 1];

        sibling_1->count--;
        child_with_key->count++;
    }
    // Case 3a: borrow from right sibling
    else if (child_with_key->count == t - 1 && sibling_2 != nullptr && sibling_2->count >= t)
    {
        child_with_key->key[child_with_key->count] = root->key[ind];
        if (no_of_children(sibling_2) > 0)
        {
            child_with_key->children[child_with_key->count + 1] = sibling_2->children[0];
        }

        root->key[ind] = sibling_2->key[0];

        for (int i = 1; i < sibling_2->count; i++)
        {
            sibling_2->key[i - 1] = sibling_2->key[i];
        }

        if (no_of_children(sibling_2) > 0)
        {
            for (int i = 1; i <= sibling_2->count; i++)
                sibling_2->children[i - 1] = sibling_2->children[i];
        }

        sibling_2->count--;
        child_with_key->count++;
    }
    // Case 3b: x->ci and each of x->ci’s immediate siblings have t - 1 keys.
    if (child_with_key->count == t - 1 && sibling_1 != nullptr && sibling_1->count == t - 1)
    {
        sibling_1->key[t - 1] = root->key[ind - 1];

        for (int j = 0; j < child_with_key->count; j++)
            sibling_1->key[j + t] = child_with_key->key[j];

        if (no_of_children(child_with_key) > 0)
        {
            for (int j = 0; j <= child_with_key->count; j++)
            {
                sibling_1->children[j + t] = child_with_key->children[j];
            }
        }

        sibling_1->count += child_with_key->count + 1;

        for (int j = ind - 1; j < root->count - 1; j++)
        {
            root->key[j] = root->key[j + 1];
        }
        for (int j = ind; j < root->count; j++)
        {
            root->children[j] = root->children[j + 1];
        }
        root->children[root->count] = nullptr;
        root->count--;
        delete child_with_key;

        if (root->count == 0)
            root = sibling_1;

        child_with_key = sibling_1;
    }
    else if (child_with_key->count == t - 1 && sibling_2 != nullptr && sibling_2->count == t - 1)
    {
        child_with_key->key[t - 1] = root->key[ind];

        for (int j = 0; j < sibling_2->count; j++)
            child_with_key->key[j + t] = sibling_2->key[j];

        if (no_of_children(sibling_2))
        {
            for (int j = 0; j <= sibling_2->count; j++)
            {
                child_with_key->children[j + t] = sibling_2->children[j];
            }
        }

        child_with_key->count += sibling_2->count + 1;

        for (int j = ind; j < root->count - 1; j++)
        {
            root->key[j] = root->key[j + 1];
        }
        for (int j = ind + 1; j < root->count; j++)
        {
            root->children[j] = root->children[j + 1];
        }
        root->children[root->count] = nullptr;
        root->count--;
        delete sibling_2;

        if (root->count == 0)
        {
            root = child_with_key;
        }
    }
    del(child_with_key, key);
    return 0;
}

int height(struct BTreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else if (no_of_children(root) == 0)
    {
        return 1;
    }
    int h = 0;
    for (int i = 0; i < no_of_children(root); i++)
    {
        h = max(h, height(root->children[i]));
    }
    return 1 + h;
}

// Helper function print_level prints a given level i of the B-Tree.
void print_level(struct BTreeNode *root, int level)
{
    // If we reach a null node, we return directly as we have reached the end of a given subtree after traversing through all possible nodes in it.
    if (root == nullptr)
    {
        return;
    }
    // If we are printing the first node (base case), we print the root->data[i], for all i with a valid value (not INT_MAX) directly as it is the only node in the first level.
    else if (level == 1)
    {
        for (int i = 0; i < root->count; i++)
        {
            cout << root->key[i] << " ";
        }
    }
    // We print the print_level recursively by calling it on each of the children subtrees of the B-Tree.
    for (int i = 0; i < no_of_children(root); i++)
    {
        print_level(root->children[i], level - 1);
    }
}

// Time complexity = O(n^2).
// Space complexity = O(n).
// Function print_level_order prints the level order traversal of the B-Tree.
void print_level_order(struct BTreeNode *root)
{
    // If the tree doesn't exist, return without printing anything.
    if (root == nullptr)
    {
        return;
    }
    // We find the height of the tree.
    int h = height(root);
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
    // Initialize the root of the B-Tree to nullptr.
    struct BTreeNode *root = nullptr;
    // Take the input of the number of elements to be inserted into the B-Tree as n.
    int n;
    cin >> n;
    // Run a for loop taking each of the n elements as an input stored in the number x and insert each insert into the given B-Tree with root root.
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

    // We again take user input in an infinite loop, till op = 0 and print the user choices again.
    int op;
    cin >> op;

    while (true)
    {
        // If the user inputs 1, we search for the node with the given value key, taken as user input, in the user constructed B-Tree, by calling the search function.
        if (op == 1)
        {
            int key;
            cin >> key;
            // If the key is found, print <key> present.
            if (search(root, key))
            {
                cout << key << " is present" << endl;
            }
            // Else print <key> not present.
            else
            {
                cout << key << " not present" << endl;
            }
        }
        // If the user inputs 2, we insert a new node with the given value key, taken as user input, in the user constructed B-Tree, by calling the insert function.
        else if (op == 2)
        {
            int key;
            cin >> key;
            // If the key is found, print <key> already present. So no need to insert.
            if (search(root, key))
            {
                cout << key << " already present. So no need to insert." << endl;
            }
            // If the key is not found, insert the key into the given B-Tree with root root and print <key> inserted.
            else
            {
                root = insert(root, key);
                cout << key << " inserted" << endl;
            }
        }
        // If the user inputs 3, we delete the node with the given value key, taken as user input, from the user constructed B-Tree, by calling the delete function.
        else if (op == 3)
        {
            int key;
            cin >> key;
            // If a node with the given data = key exists in the B-Tree, then we delete the node and print the value deleted.
            if (search(root, key))
            {
                del(root, key);
                cout << key << " deleted" << endl;
            }
            // If a node with the given data = key doesn't exist in the B-Tree, then we cannot delete it and hence we print the error message given below.
            else
            {
                cout << key << " not present. So it can not be deleted." << endl;
            }
        }
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

        // We again take user input in an infinite loop, till op = 0 and print the user choices again.
        cin >> op;
    }
}