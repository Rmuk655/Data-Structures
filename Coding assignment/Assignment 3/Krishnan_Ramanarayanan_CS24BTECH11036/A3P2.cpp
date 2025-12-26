#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

// Definition of each node of the tree.
struct node
{
    int data[3];
    int count;
    struct node *children[4];
};

node *create_new_node(int key)
{
    node *root = new node();
    root->data[0] = key;
    for (int i = 1; i < 3; i++)
    {
        root->data[i] = INT_MAX;
    }
    root->count = 1;
    for (int i = 0; i < 4; i++)
    {
        root->children[i] = nullptr;
    }
    return root;
}

int no_of_children(node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int ch = 0;
    for (int i = 0; i <= 3; i++)
    {
        if (node->children[i] != nullptr)
        {
            ch++;
        }
    }
    return ch;
}

// Time complexity = O(h) = O(log n), h is the height of the (2-4)-Tree.
// Space complexity = O(h) = O(log n), h is the height of the (2-4)-Tree.
// Search function searches for a given node in a tree with data key.
node *search(node *root, int key)
{
    if (root == nullptr)
    {
        // cout << "Key not found!" << endl;
        return nullptr;
    }
    else if (no_of_children(root) == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            if (root->data[i] == key)
            {
                // cout << "Found " << root->data[i] << endl;
                return root;
            }
        }
        return nullptr;
    }
    if (key < root->data[0])
    {
        return search(root->children[0], key);
    }
    for (int i = 0; i < 2; i++)
    {
        if (root->data[i] == key)
        {
            // cout << "Found " << root->data[i] << endl;
            return root;
        }
        else if (key > root->data[i] && key < root->data[i + 1])
        {
            return search(root->children[i + 1], key);
        }
    }
    if (key == root->data[root->count - 1])
    {
        return root;
    }
    return search(root->children[root->count], key);
}

void splitchild(node *x, int i)
{
    if (x->count >= 3)
    {
        return;
    }
    node *y = x->children[i - 1];
    if (y == nullptr)
    {
        return;
    }
    node *z = create_new_node(y->data[2]);
    z->count = 1; // (3 + 1) / 2 - 1 = 1;
    if (no_of_children(y) > 0)
    {
        for (int j = 0; j <= z->count; j++)
        {
            z->children[j] = y->children[j + z->count + 1];
            y->children[j + z->count + 1] = nullptr;
        }
    }
    y->count = z->count;
    for (int j = x->count; j >= i; j--)
    {
        x->children[j + 1] = x->children[j];
    }
    x->children[i] = z;
    for (int j = (x->count - 1); j >= (i - 1); j--)
    {
        x->data[j + 1] = x->data[j];
    }
    x->data[i - 1] = y->data[1];
    x->count++;
    y->data[1] = INT_MAX;
    y->data[2] = INT_MAX;
}

node *splitroot(node *&root)
{
    node *split = create_new_node(INT_MAX);
    split->count = 0;
    split->children[0] = root;
    root = split;
    splitchild(split, 1);
    split->children[0]->data[1] = INT_MAX;
    split->children[0]->data[2] = INT_MAX;
    return split;
}

void insertnonfull(node *node, int key)
{
    int index = node->count;
    if (no_of_children(node) == 0)
    {
        while (index > 0 && key < node->data[index - 1])
        {
            node->data[index] = node->data[index - 1];
            index--;
        }
        node->data[index] = key;
        node->count++;
    }
    else
    {
        while (index >= 1 && key < node->data[index - 1])
        {
            index--;
        }
        index++;
        if (node->children[index - 1]->count == 3)
        {
            splitchild(node, index);
            if (key > node->data[index - 1])
            {
                index++;
            }
        }
        insertnonfull(node->children[index - 1], key);
    }
}

// Time complexity = O(h) = O(log n), h is the height of the (2-4)-Tree.
// Space complexity = O(h) = O(log n), h is the height of the (2-4)-Tree.
// Insert function is used to insert a new node into the tree with data key.
node *insert(node *root, int key)
{
    if (root == nullptr)
    {
        root = create_new_node(key);
        return root;
    }
    else if (search(root, key) != nullptr)
    {
        cout << "Cannot insert duplicate value" << endl;
        return root;
    }
    if (root->count == 3)
    {
        node *split = splitroot(root);
        insertnonfull(split, key);
    }
    else
    {
        insertnonfull(root, key);
    }
    return root;
}

int key_index(struct node *node, int key)
{
    if (node == nullptr)
    {
        return -1;
    }
    for (int i = 0; i < 3; i++)
    {
        if (node->data[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int key_child_index(struct node *node, int key)
{
    if (node == nullptr)
    {
        return -1;
    }
    for (int i = 0; i < 4; i++)
    {
        if (node->children[i] != nullptr && search(node->children[i], key))
        {
            return i;
        }
    }
    return -1;
}

int predecessor(struct node *root, int index)
{
    struct node *pred = root->children[index];
    while (pred->children[no_of_children(pred) - 1] != nullptr)
    {
        pred = pred->children[no_of_children(pred) - 1];
    }
    return pred->data[no_of_children(pred) - 1];
}

int successor(struct node *root, int index)
{
    struct node *succ = root->children[index + 1];
    while (succ->children[0] != nullptr)
    {
        succ = succ->children[0];
    }
    return succ->data[0];
}

// Time complexity = O(h) = O(log n), h is the height of the (2-4)-Tree.
// Space complexity = O(h) = O(log n), h is the height of the (2-4)-Tree.
// Delete function is used to delete a node in the RB tree with the given data value key.
int del(node *&root, int key)
{
    // We search for the node whose data equals key and store it z.
    node *temp = search(root, key);
    // If the node to be deleted doesn't exist then we cannot delete it. Hence, we return -1 indicating error.
    // We handle this for safety purposes.
    if (!temp)
    {
        // cout << key << " not found in the tree. Cannot delete." << endl;
        return -1;
    }

    int t = 2; // minimum degree for 2-4 tree

    // Case 1: root is a leaf
    if (no_of_children(root) == 0)
    {
        int ind = key_index(root, key);
        for (int i = ind; i < 2; i++)
        {
            root->data[i] = root->data[i + 1];
        }
        root->count--;
        return key;
    }

    // Case 2: key is in this node
    int ind = key_index(root, key);
    if (ind >= 0)
    {
        struct node *prev_child = root->children[ind];
        struct node *next_child = root->children[ind + 1];

        // Case 2a: left child has ≥ t keys
        if (prev_child->count >= t)
        {
            int pred = predecessor(root, ind);
            root->data[ind] = pred;
            del(prev_child, pred);
        }
        // Case 2b: right child has ≥ t keys
        else if (next_child->count >= t)
        {
            int succ = successor(root, ind);
            root->data[ind] = succ;
            del(next_child, succ);
        }
        // Case 2c: both children have t - 1 keys → merge
        else
        {
            // merge prev_child, key[ind], and next_child
            prev_child->data[1] = root->data[ind];
            prev_child->data[2] = next_child->data[0];

            // move children if internal
            if (no_of_children(next_child) > 0)
            {
                prev_child->children[2] = next_child->children[0];
                prev_child->children[3] = next_child->children[1];
            }
            prev_child->count += next_child->count + 1;
            // shift keys/children left in parent
            for (int j = ind; j < root->count - 1; j++)
            {
                root->data[j] = root->data[j + 1];
            }
            for (int j = ind + 1; j <= root->count; j++)
            {
                root->children[j - 1] = root->children[j];
            }

            root->count--;
            delete next_child;

            root->children[root->count] = nullptr;

            for (int j = prev_child->count; j < 3; j++)
            {
                prev_child->data[j] = INT_MAX;
            }
            for (int j = no_of_children(prev_child); j < 4; j++)
            {
                prev_child->children[j] = nullptr;
            }

            // if root is empty → collapse tree
            if (root->count == 0)
            {
                root = prev_child;
            }

            del(prev_child, key);
        }
        return key;
    }

    // Case 3: key is not in this node, then we recurse into proper child
    ind = key_child_index(root, key);
    if (ind < 0)
    {
        return -1;
    }

    struct node *child_with_key = root->children[ind];
    struct node *sibling_1 = (ind > 0) ? root->children[ind - 1] : nullptr;
    struct node *sibling_2 = (ind < root->count) ? root->children[ind + 1] : nullptr;

    // Fix child before recursion if it has only t - 1 keys (i.e., 1 key)
    if (child_with_key->count == t - 1)
    {
        // Case 3a: borrow from left sibling
        if (sibling_1 != nullptr && sibling_1->count >= t)
        {
            // shift right in child
            child_with_key->data[1] = child_with_key->data[0];
            child_with_key->data[0] = root->data[ind - 1];

            if (no_of_children(child_with_key) > 0)
            {
                child_with_key->children[1] = child_with_key->children[0];
                child_with_key->children[0] = sibling_1->children[sibling_1->count];
            }

            root->data[ind - 1] = sibling_1->data[sibling_1->count - 1];
            sibling_1->count--;
            child_with_key->count++;
        }
        // Case 3a: borrow from right sibling
        else if (sibling_2 != nullptr && sibling_2->count >= t)
        {
            child_with_key->data[1] = root->data[ind];
            root->data[ind] = sibling_2->data[0];

            if (no_of_children(sibling_2) > 0)
            {
                child_with_key->children[2] = sibling_2->children[0];
            }

            // shift sibling left
            sibling_2->data[0] = sibling_2->data[1];
            sibling_2->data[1] = sibling_2->data[2];
            sibling_2->count--;
            child_with_key->count++;
        }
        // Case 3b: merge with sibling
        else
        {
            if (sibling_1 != nullptr)
            {
                // merge left sibling + parent key + child
                sibling_1->data[1] = root->data[ind - 1];
                sibling_1->data[2] = child_with_key->data[0];
                sibling_1->count = 3;
                sibling_1->children[2] = child_with_key->children[0];
                sibling_1->children[3] = child_with_key->children[1];
                delete child_with_key;

                for (int j = ind - 1; j < root->count - 1; j++)
                {
                    root->data[j] = root->data[j + 1];
                }
                for (int j = ind; j < root->count; j++)
                {
                    root->children[j] = root->children[j + 1];
                }
                root->children[root->count] = nullptr;
                root->count--;

                if (root->count == 0)
                {
                    root = sibling_1;
                }

                child_with_key = sibling_1;
            }
            else if (sibling_2 != nullptr)
            {
                // merge child + parent key + right sibling
                child_with_key->data[1] = root->data[ind];
                child_with_key->data[2] = sibling_2->data[0];
                child_with_key->count = 3;
                child_with_key->children[2] = sibling_2->children[0];
                child_with_key->children[3] = sibling_2->children[1];
                delete sibling_2;

                // shift parent
                for (int j = ind; j < root->count - 1; j++)
                {
                    root->data[j] = root->data[j + 1];
                }
                for (int j = ind + 1; j <= root->count; j++)
                {
                    root->children[j] = root->children[j + 1];
                }
                root->children[root->count] = nullptr;
                root->count--;

                if (root->count == 0)
                {
                    root = child_with_key;
                }
            }
        }
    }

    // Finally recurse into child
    return del(child_with_key, key);
    // return 0;
}

int height(struct node *root)
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

// Helper function print_level prints a given level i of the (2-4)-Tree.
void print_level(struct node *root, int level)
{
    // If we reach a null node, we return directly as we have reached the end of a given subtree after traversing through all possible nodes in it.
    if (root == nullptr)
    {
        return;
    }
    // If we are printing the first node (base case), we print the root->data[i], for all i directly as it is the only node in the first level.
    else if (level == 1)
    {
        for (int i = 0; i < root->count; i++)
        {
            cout << root->data[i] << " ";
        }
    }
    // We print the print_level recursively by calling it on each of the children subtrees of the (2-4)-Tree.
    for (int i = 0; i < no_of_children(root); i++)
    {
        print_level(root->children[i], level - 1);
    }
}

// Time complexity = O(n^2).
// Space complexity = O(n).
// Function print_level_order prints the level order traversal of the (2-4)-Tree.
void print_level_order(struct node *root)
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
    // Initialize the root of the (2-4)-Tree to nullptr.
    struct node *root = nullptr;
    // Take the input of the number of elements to be inserted into the (2-4)-Tree as n.
    int n;
    cin >> n;
    // Run a for loop taking each of the n elements as an input stored in the number x and insert each insert into the given (2-4)-Tree with root root.
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
        // If the user inputs 2, we insert a new node with the given value key, taken as user input, in the user constructed (2-4)-Tree, by calling the insert function.
        else if (op == 2)
        {
            int key;
            cin >> key;
            // If the key is found, print <key> already present. So no need to insert.
            if (search(root, key))
            {
                cout << key << " already present. So no need to insert." << endl;
            }
            // If the key is not found, insert the key into the given (2-4)-Tree with root root and print <key> inserted.
            else
            {
                root = insert(root, key);
                cout << key << " inserted" << endl;
            }
            // Uncomment for verifying if the level order traversal of the (2-4)-Tree is correct or not after delete.
            // cout << "Tree after insertion is: ";
            // print_level_order(root);
            // cout << endl;
        }
        // If the user inputs 3, we delete the node with the given value key, taken as user input, from the user constructed (2-4)-Tree, by calling the delete function.
        else if (op == 3)
        {
            int key;
            cin >> key;
            // If a node with the given data = key exists in the (2-4)-Tree, then we delete the node and print the value deleted.
            if (search(root, key))
            {
                del(root, key);
                cout << key << " deleted" << endl;
            }
            // If a node with the given data = key doesn't exist in the (2-4)-Tree, then we cannot delete it and hence we print the error message given below.
            else
            {
                cout << key << " not present. So it can not be deleted" << endl;
            }
            // Uncomment for verifying if the level order traversal of the (2-4)-Tree is correct or not after delete.
            // cout << "Tree after deletion is: ";
            // print_level_order(root);
            // cout << endl;
        }
        // If the user inputs 4, we print the level order of the (2-4)-Tree by calling the print_level_order function.
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