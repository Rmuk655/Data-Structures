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
// Only the first root->count keys of a node are valid, so we never look at the unused slots.
node *search(node *root, int key)
{
    if (root == nullptr)
    {
        // cout << "Key not found!" << endl;
        return nullptr;
    }
    int i = 0;
    while (i < root->count && key > root->data[i])
    {
        i++;
    }
    if (i < root->count && root->data[i] == key)
    {
        // cout << "Found " << root->data[i] << endl;
        return root;
    }
    // A leaf has no children, so the search ends here.
    if (no_of_children(root) == 0)
    {
        return nullptr;
    }
    return search(root->children[i], key);
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
    // The predecessor of root->data[index] is the right-most key of the left subtree.
    struct node *pred = root->children[index];
    while (pred->children[pred->count] != nullptr)
    {
        pred = pred->children[pred->count];
    }
    return pred->data[pred->count - 1];
}

int successor(struct node *root, int index)
{
    // The successor of root->data[index] is the left-most key of the right subtree.
    struct node *succ = root->children[index + 1];
    while (succ->children[0] != nullptr)
    {
        succ = succ->children[0];
    }
    return succ->data[0];
}

// Clears the unused key and child slots of a node after its count has shrunk.
void clear_unused(node *x)
{
    for (int i = x->count; i < 3; i++)
    {
        x->data[i] = INT_MAX;
    }
    for (int i = x->count + 1; i < 4; i++)
    {
        x->children[i] = nullptr;
    }
}

// Time complexity = O(h) = O(log n), h is the height of the (2-4)-Tree.
// Space complexity = O(h) = O(log n), h is the height of the (2-4)-Tree.
// Delete function is used to delete a node in the (2-4) tree with the given data value key.
// Every node on the way down is made to hold at least t = 2 keys (borrowing or merging) before we enter it,
// so the key can always be removed from a node without violating the minimum number of keys.
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

    // Case 1: the node is a leaf, so we remove the key and close the gap.
    if (no_of_children(root) == 0)
    {
        int ind = key_index(root, key);
        for (int i = ind; i < root->count - 1; i++)
        {
            root->data[i] = root->data[i + 1];
        }
        root->count--;
        clear_unused(root);
        if (root->count == 0)
        {
            // The tree became empty.
            delete root;
            root = nullptr;
        }
        return key;
    }

    // Case 2: the key is in this internal node.
    int ind = key_index(root, key);
    if (ind >= 0 && ind < root->count)
    {
        struct node *prev_child = root->children[ind];
        struct node *next_child = root->children[ind + 1];

        // Case 2a: the left child has at least t keys, so we replace the key by its predecessor.
        if (prev_child->count >= t)
        {
            int pred = predecessor(root, ind);
            root->data[ind] = pred;
            del(root->children[ind], pred);
        }
        // Case 2b: the right child has at least t keys, so we replace the key by its successor.
        else if (next_child->count >= t)
        {
            int succ = successor(root, ind);
            root->data[ind] = succ;
            del(root->children[ind + 1], succ);
        }
        // Case 2c: both children have t - 1 keys, so we merge them with the key and delete from the merged node.
        else
        {
            prev_child->data[t - 1] = root->data[ind];
            for (int j = 0; j < next_child->count; j++)
            {
                prev_child->data[j + t] = next_child->data[j];
            }
            if (no_of_children(next_child) > 0)
            {
                for (int j = 0; j <= next_child->count; j++)
                {
                    prev_child->children[j + t] = next_child->children[j];
                }
            }
            prev_child->count += next_child->count + 1;

            // We close the gap in the parent (keys from ind, children from ind + 1).
            for (int j = ind; j < root->count - 1; j++)
            {
                root->data[j] = root->data[j + 1];
            }
            for (int j = ind + 1; j < root->count; j++)
            {
                root->children[j] = root->children[j + 1];
            }
            root->count--;
            clear_unused(root);
            delete next_child;

            // If the parent is the root and became empty, the merged node is the new root.
            if (root->count == 0)
            {
                node *old_root = root;
                root = prev_child;
                delete old_root;
                del(root, key);
            }
            else
            {
                del(prev_child, key);
            }
        }
        return key;
    }

    // Case 3: the key is not in this node, so we continue into the child whose subtree contains it.
    ind = 0;
    while (ind < root->count && key > root->data[ind])
    {
        ind++;
    }

    struct node *child_with_key = root->children[ind];
    struct node *sibling_1 = (ind > 0) ? root->children[ind - 1] : nullptr;
    struct node *sibling_2 = (ind < root->count) ? root->children[ind + 1] : nullptr;

    // Before going down, we make sure that the child has at least t keys.
    if (child_with_key->count == t - 1)
    {
        // Case 3a: borrow a key from the left sibling through the parent.
        if (sibling_1 != nullptr && sibling_1->count >= t)
        {
            for (int i = child_with_key->count - 1; i >= 0; i--)
            {
                child_with_key->data[i + 1] = child_with_key->data[i];
            }
            if (no_of_children(child_with_key) > 0)
            {
                for (int i = child_with_key->count; i >= 0; i--)
                {
                    child_with_key->children[i + 1] = child_with_key->children[i];
                }
            }
            child_with_key->data[0] = root->data[ind - 1];
            if (no_of_children(sibling_1) > 0)
            {
                child_with_key->children[0] = sibling_1->children[sibling_1->count];
                sibling_1->children[sibling_1->count] = nullptr;
            }
            root->data[ind - 1] = sibling_1->data[sibling_1->count - 1];
            sibling_1->count--;
            child_with_key->count++;
            clear_unused(sibling_1);
        }
        // Case 3a: borrow a key from the right sibling through the parent.
        else if (sibling_2 != nullptr && sibling_2->count >= t)
        {
            child_with_key->data[child_with_key->count] = root->data[ind];
            if (no_of_children(sibling_2) > 0)
            {
                child_with_key->children[child_with_key->count + 1] = sibling_2->children[0];
            }
            root->data[ind] = sibling_2->data[0];
            for (int i = 1; i < sibling_2->count; i++)
            {
                sibling_2->data[i - 1] = sibling_2->data[i];
            }
            if (no_of_children(sibling_2) > 0)
            {
                for (int i = 1; i <= sibling_2->count; i++)
                {
                    sibling_2->children[i - 1] = sibling_2->children[i];
                }
            }
            sibling_2->count--;
            child_with_key->count++;
            clear_unused(sibling_2);
        }
        // Case 3b: merge the child with the left sibling and the separating key from the parent.
        else if (sibling_1 != nullptr)
        {
            sibling_1->data[t - 1] = root->data[ind - 1];
            for (int j = 0; j < child_with_key->count; j++)
            {
                sibling_1->data[j + t] = child_with_key->data[j];
            }
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
                root->data[j] = root->data[j + 1];
            }
            for (int j = ind; j < root->count; j++)
            {
                root->children[j] = root->children[j + 1];
            }
            root->count--;
            clear_unused(root);
            delete child_with_key;
            child_with_key = sibling_1;
            if (root->count == 0)
            {
                node *old_root = root;
                root = sibling_1;
                delete old_root;
            }
        }
        // Case 3b: merge the child with the right sibling and the separating key from the parent.
        else if (sibling_2 != nullptr)
        {
            child_with_key->data[t - 1] = root->data[ind];
            for (int j = 0; j < sibling_2->count; j++)
            {
                child_with_key->data[j + t] = sibling_2->data[j];
            }
            if (no_of_children(sibling_2) > 0)
            {
                for (int j = 0; j <= sibling_2->count; j++)
                {
                    child_with_key->children[j + t] = sibling_2->children[j];
                }
            }
            child_with_key->count += sibling_2->count + 1;
            for (int j = ind; j < root->count - 1; j++)
            {
                root->data[j] = root->data[j + 1];
            }
            for (int j = ind + 1; j < root->count; j++)
            {
                root->children[j] = root->children[j + 1];
            }
            root->count--;
            clear_unused(root);
            delete sibling_2;
            if (root->count == 0)
            {
                node *old_root = root;
                root = child_with_key;
                delete old_root;
            }
        }
    }

    // Finally we continue the deletion in the child.
    del(child_with_key, key);
    return key;
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

    // The loop stops when op = 0 or when the input ends.
    while (op != 0 && cin)
    {
        // If the user inputs 1, we search for the node with the given value key, taken as user input, in the user constructed (2-4) tree, by calling the search function.
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