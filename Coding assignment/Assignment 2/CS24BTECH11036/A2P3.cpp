#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Time complexity = O(n^2)
// Space complexity = O(n^2)

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

// Helper function used to insert a left child to the node root with data = key.
struct node *insertLeft(struct node *root, int key)
{
    struct node *newnode = createNode(key);
    root->left = newnode;
    return root;
}

// Helper function used to insert a right child to the node root with data = key.
struct node *insertRight(struct node *root, int key)
{
    struct node *newnode = createNode(key);
    root->right = newnode;
    return root;
}

// Time complexity = O(n^2)
// Space complexity = O(n^2)
//  Construct_tree function constructs the tree with given preorder and inorder traversals and returns the root node of the tree.
struct node *construct_tree(vector<int> preord, vector<int> inord, int n)
{
    // If no element exists in pre/inorder then return nullptr as tree has 0 elements.
    if (n == 0)
    {
        return nullptr;
    }
    // If 1 element exists in pre/inorder then return root with value preord[0] as tree has only 1 element.
    struct node *root = createNode(preord[0]);
    if (n == 1)
    {
        return root;
    }
    // Otherwise we find the number of elements in the left subtree and right subtree as left and right respectively.
    int left = 0, right = 0;
    for (int i = 0; i < n; i++)
    {
        if (inord[i] == preord[0])
        {
            left = i;
            break;
        }
    }
    right = n - 1 - left;
    // We now create 4 vectors for the pre, in orders of the left and right subtrees respectively and construct the left and right subtrees of root recursively.
    vector<int> left_pre, left_in, right_pre, right_in;
    for (int i = 0; i < left; i++)
    {
        left_pre.push_back(preord[1 + i]);
        left_in.push_back(inord[i]);
    }
    for (int i = 0; i < right; i++)
    {
        right_pre.push_back(preord[1 + left + i]);
        right_in.push_back(inord[1 + left + i]);
    }
    // Once we fill the vectors with the respective values, we construct the left, right subtrees by calling the function construct_tree again recursively.
    struct node *l_child = construct_tree(left_pre, left_in, left);
    struct node *r_child = construct_tree(right_pre, right_in, right);
    // If there exists non zero number of elements in the left subtree we insert the l_child as root->left.
    if (left)
    {
        insertLeft(root, l_child->data);
        root->left = l_child;
    }
    // If there exists non zero number of elements in the right subtree we insert the r_child as root->right.
    if (right)
    {
        insertRight(root, r_child->data);
        root->right = r_child;
    }
    return root;
}

// Time complexity = O(n^2)
// Space complexity = O(n^2)
// We use the helper function node_search which updates the distance frequency array count.
vector<int> node_search(struct node *root, vector<int> &count)
{
    // Handling the edge case where root is nullptr. We return an empty array with size 0.
    if (root == nullptr)
    {
        vector<int> temp;
        return temp;
    }
    // Vectors left_searched, right_searched which store the distances between the root->left, root->right and the elements in it's left, right subtrees respectively.
    vector<int> left_searched = node_search(root->left, count), right_searched = node_search(root->right, count);
    // We loop through the left, right subtrees and update frequency array with distances between every possible node of the left subtree with every
    // possible node of the right subtree.
    for (int i = 0; i < left_searched.size(); i++)
    {
        for (int j = 0; j < right_searched.size(); j++)
        {
            // We check if the distance is within the size of the frequency array count.
            if (left_searched[i] + right_searched[j] + 2 < count.size())
            {
                count[left_searched[i] + right_searched[j] + 2]++;
            }
        }
    }
    // Vector result stores the result we return as left_searched, right_searched, the distances between root and it's respective left/right subtrees.
    vector<int> result;
    // The distance between root and itself is 0. We don't update this in the frequency array though.
    result.push_back(0);
    // We count distances between every element in the left subtree of root and root and update it in the frequency array.
    for (int i = 0; i < left_searched.size(); i++)
    {
        result.push_back(left_searched[i] + 1);
        // We check if the distance is within the size of the frequency array count.
        if (left_searched[i] + 1 < count.size())
        {
            count[left_searched[i] + 1]++;
        }
    }
    // We count distances between every element in the right subtree of root and root and update it in the frequency array.
    for (int i = 0; i < right_searched.size(); i++)
    {
        result.push_back(right_searched[i] + 1);
        // We check if the distance is within the size of the frequency array count.
        if (right_searched[i] + 1 < count.size())
        {
            count[right_searched[i] + 1]++;
        }
    }
    return result;
}

// Time complexity = O(n)
// Space complexity = O(n)
// Function mo_fr_pa_dist finds the most frequent pair distance in the tree with root 'root'.
int mo_fr_pa_dist(struct node *root, int n)
{
    // If the number of elements in the tree is 0 or 1, we just return 0 as distances are not defined for such trees.
    if (n == 0 || n == 1)
    {
        return 0;
    }
    // We create a frequency array named count which stores the frequency of distances 1 to n - 1.
    vector<int> count(n, 0);
    // node_search updates the frequency array to store the frequency of distances 1 to n - 1 in tree.
    node_search(root, count);
    // max_f finds the maximum frequency of distances among all distances.
    // min_dist finds the minimum distance among the distances having maximum frequencies.
    int max_f = 0, min_dist = INT_MAX;
    // We loop throught the frequency array.
    for (int i = 1; i < n; i++)
    {
        // We first focus on finding the maximum frequency (max_f).
        if (count[i] > max_f)
        {
            max_f = count[i];
            min_dist = i;
        }
        // Among the elements with max_f, we select the one with the minimum value of distance.
        else if (count[i] == max_f && i < min_dist)
        {
            min_dist = i;
        }
    }
    // We return this minimum value of distance.
    return min_dist;
}

// Main function which takes in inputs from the user and calls the respective functions to print the respective outputs.
int main()
{
    // We take the number of nodes in the tree as input.
    int n;
    cin >> n;
    // We store the preord and inord traversals of the tree in the vectors preord, inord.
    vector<int> preord, inord;
    // Taking the first n elements as input for preord.
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        preord.push_back(x);
    }
    // Taking the first n elements as input for inord.
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        inord.push_back(x);
    }
    // We construct the tree using preorder and inorder traversals.
    struct node *root = construct_tree(preord, inord, n);
    // We print the most frequent pair distance as the output by calling the mo_fr_pa_dist function.
    cout << mo_fr_pa_dist(root, n) << endl;
}