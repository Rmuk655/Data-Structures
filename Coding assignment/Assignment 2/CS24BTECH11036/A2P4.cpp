#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Time complexity = O(V^3), V is the number of elements in the vector visited.
// Space complexity = O(V)

// Definition of each node of the graph.
struct node
{
    int data;
    vector<struct node *> relations;
};

// Time complexity = O(1)
// Space complexity = O(1)
// Extra Space complexity = O(1)
// Function to create a new node in the graph by setting up the pointers appropriately.
struct node *create_node(int key)
{
    struct node *root = new struct node();
    root->data = key;
    return root;
}

// Time complexity = O(V), V is the number of elements in the vector visited.
// Space complexity = O(V)
// Helper function which tells us if a given node is present in a given vector of nodes or not.
bool not_in(struct node *node, vector<struct node *> visited)
{
    for (int i = 0; i < visited.size(); i++)
    {
        if (visited[i] == node)
        {
            // If we find the node in the vector, it means in is true and hence not_in is false.
            return false;
        }
    }
    // If we do not find the node in the vector, it means not_in is true.
    return true;
}

// Time complexity = O(V^2), V is the number of elements in the vector visited.
// Space complexity = O(V)
// Function path_search searches for the longest equal path starting from a given node of the graph.
int path_search(struct node *node, int &length, vector<struct node *> &visited)
{
    // Handling the edge case when we reach the end of a graph/graph has no nodes. The longest possible path is hence 0.
    if (node == nullptr)
    {
        return 0;
    }
    // Since we have visited the starting node, node, we push it inside the visited vector so that we don't come back to it again.
    visited.push_back(node);
    // Max_length is atleast 1 as we have a starting non null node.
    int max_length = 1;
    // We loop through each relation of the node to search for the relation with the same value as node to get the longest possible path.
    for (int i = 0; i < node->relations.size(); i++)
    {
        // We visit the relation only if it is not present in the visited vector.
        if (not_in(node->relations[i], visited))
        {
            // We find the path length from the relation only if the relation has the same value as the node itself.
            if (node->relations[i]->data == node->data)
            {
                // We now find the longest possible equal path length from the relation of the node as relation_length.
                int relation_length = path_search(node->relations[i], length, visited);
                // If we find a longer path we update max_length accordingly.
                max_length = max(max_length, relation_length + 1);
            }
        }
    }
    // Update the value of length only if the value of max_length exceeds that of length.
    length = max(length, max_length);
    // We return the max_length as we need to find relation_length using this returned length in recursion.
    return max_length;
}

// Time complexity = O(V^3), V is the number of elements in the vector visited.
// Space complexity = O(V)
// Function longest_equal_path searches for the longest equal path amongst all the path_search of each node of the graph.
int longest_equal_path(vector<struct node *> nodes, int n)
{
    // If n (number of nodes in the graph) is 0 or 1, the longest path can only be 0 or 1.
    if (n == 0 || n == 1)
    {
        return n;
    }
    // We store the max_length in a variable named max_length.
    int max_length = 0;
    for (int i = 0; i < n; i++)
    {
        // We store the nodes we have visited starting from a given nodes[i] for iteration i so that we don't visit these nodes again.
        vector<struct node *> visited;
        // We calculate the length of path from each node and store it the variable length.
        int length = 0;
        path_search(nodes[i], length, visited);
        // However, we store the max value in max_length which is returned.
        if (length > max_length)
        {
            max_length = length;
        }
    }
    return max_length;
}

// Main function which takes in inputs from the user and calls the respective functions to print the respective outputs.
int main()
{
    // We take the number of nodes in the graph as input.
    int n;
    cin >> n;
    // We store the nodes of the graph in the vector nodes.
    vector<struct node *> nodes;
    // Taking the first n elements as input for creating the n nodes of the graph and storing them in the vector nodes.
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        struct node *temp = create_node(x);
        nodes.push_back(temp);
    }
    // We now take the next n - 1 lines of input with each line having two integers x and y which represents the value of their respective nodes u and v.
    while (n > 1)
    {
        int x, y;
        cin >> x >> y;
        nodes[x - 1]->relations.push_back(nodes[y - 1]);
        nodes[y - 1]->relations.push_back(nodes[x - 1]);
        n--;
    }
    // We now calculate the longest equal path by calling the function longest_equal_path.
    cout << longest_equal_path(nodes, nodes.size()) << endl;
}