#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

// Definition of a node of a Union Data Structure.
struct UnionDS
{
    vector<int> parent;
    vector<int> rank;
};

// Function to initialize the UnionDS.
struct UnionDS *create_unionDS(int n)
{
    struct UnionDS *UDS = new struct UnionDS();
    UDS->parent.resize(n);
    UDS->rank.resize(n, 0);
    for (int i = 0; i < n; i++)
    {
        UDS->parent[i] = i;
    }
    return UDS;
}

// Function find is used to find the root of the set containing x.
int find(struct UnionDS *UDS, int x)
{
    // If parent[x] = x, x is the root.
    // If parent[x] != x, recursively find the root, and update the parent.
    if (UDS->parent[x] != x)
    {
        UDS->parent[x] = find(UDS, UDS->parent[x]);
    }
    return UDS->parent[x];
}

// Function unionSET merges the two sets containing x, y.
void unionSET(struct UnionDS *UDS, int x, int y)
{
    // We find the roots of the two sets containing x and y and store them in rootX, rootY.
    int rootX = find(UDS, x);
    int rootY = find(UDS, y);

    // If they belong to the same set, roots are same, do nothing and return.
    if (rootX == rootY)
    {
        return;
    }

    // If rank of rootX is lesser, set rootX as the child of rootY or parent of rootX as rootY.
    if (UDS->rank[rootX] < UDS->rank[rootY])
    {
        UDS->parent[rootX] = rootY;
    }
    // If rank of rootY is lesser, set rootY as the child of rootX or parent of rootY as rootX.
    else if (UDS->rank[rootX] > UDS->rank[rootY])
    {
        UDS->parent[rootY] = rootX;
    }
    // Otherwise, if they have equal ranks, arbitrarily set the parent of rootY as rootX and add 1 to the rank of rootX.
    else
    {
        UDS->parent[rootY] = rootX;
        UDS->rank[rootX]++;
    }
}

// Function sort sorts the edges of the graph in ascending order of weights.
void sort(vector<vector<int>> &edges)
{
    for (int i = 0; i < edges.size(); i++)
    {
        for (int j = i + 1; j < edges.size(); j++)
        {
            // We compare the weights of the two edges i, j. Since edges are of the form {u, v, w}, edges[i][2] gives the weight corresponding to edge i.
            if (edges[i][2] > edges[j][2])
            {
                // If the weight of edge i < edge j, we swap them.
                vector<int> temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

// Main function min_span_tree_kruskal uses the Kruskal's algorithm on the given graph using the Union data structure implemented above.
void min_span_tree_kruskal(vector<vector<pair<int, int>>> graph)
{
    // We store all the edges of the graph once in the vector edge_set and the MST elements in the vector mst.
    vector<vector<int>> edge_set, mst;

    // For each vertex of the graph, we loop through it's adjacency list.
    for (int u = 1; u < graph.size(); u++)
    {
        // We loop through every pair in it's adjacency list/edge starting from vertex u.
        for (pair<int, int> p : graph[u])
        {
            // We find the end vertex of the edge starting from u to an element v in it's adjacenct list and the weight of the edge from u to v.
            int v = p.first, w = p.second;
            // To avoid duplicate edges, we only insert the edge u -> v once.
            if (u < v)
            {
                edge_set.push_back({u, v, w});
            }
        }
    }

    // We sort the edges of the mst.
    sort(edge_set);
    // We initialize the Union data structure.
    struct UnionDS *UDS = create_unionDS(graph.size() + 1);
    // total_weight stores the sum of weights of all edges in the graph.
    int total_weight = 0;

    // We loop through the edge details ({u, v, w}) of each edge in the MST.
    for (vector<int> vec : edge_set)
    {
        // We extract the info and store it in u, v, w.
        int u = vec[0], v = vec[1], w = vec[2];
        // If u and v are not in the same set, we join both the sets.
        if (find(UDS, u) != find(UDS, v))
        {
            unionSET(UDS, u, v);
            // We add the vertex u, v in the mst.
            mst.push_back(vec);
            // Update total_weight by adding key[v] to it, weight of the corresponding edge of v.
            total_weight = total_weight + w;
        }
    }

    // For each edge in the MST of the graph, we print it's weight and the total weight of all the edges.
    cout << "Edges in MST:" << endl;
    // For all vertices, if the vertex has not been traversed, meaning it's parent is still -1, then we ignore it. We print the remaining as they are part of MST.
    for (vector<int> e : mst)
    {
        cout << "(" << e[0] << ", " << e[1] << ") weight = " << e[2] << endl;
    }
    // We print the total weight of all the edges.
    cout << "Total weight = " << total_weight << endl;
}

// Main function to take in inputs and execute the program.
int main()
{
    // We take in input, the number of vertices in the graph.
    int n;
    cin >> n;
    // We store the graph as an adjacency matrix.
    vector<vector<pair<int, int>>> graph(n + 1);
    // We take in input, the number of edges in the graph.
    int m;
    cin >> m;
    // We loop for each edge and get the corresponding edge starting and ending points to add it to the graph.
    for (int i = 0; i < m; i++)
    {
        // We take in input the start and end points and the weight of an edge in the graph.
        int u, v, w;
        cin >> u >> v >> w;
        // We add edges to the given undirected graph (both edges from u to v and v to u are added by pushing v to u's adjacency list and vice versa).
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    // We create the minimum spanning tree of the graph using Kruskal's algorithm by calling the corresponding function.
    min_span_tree_kruskal(graph);
}