#include <iostream>
#include <string>
#include <vector>
#include <climits>

#define TRUE 1
#define FALSE 0
#define PRIORITY_QUEUE_SIZE 100
using namespace std;

// Definition of a node of a PriorityQueue data structure.
struct PriorityQueue
{
    pair<int, int> *arr;
    int size;
    int capacity;
};

// Function to initialize the PriorityQueue.
struct PriorityQueue *initPQ()
{
    struct PriorityQueue *pq = new struct PriorityQueue();
    pq->arr = new pair<int, int>[PRIORITY_QUEUE_SIZE];
    pq->size = 0;
    pq->capacity = PRIORITY_QUEUE_SIZE;
    return pq;
}

// Function to check if the PriorityQueue is empty or not.
bool isEmptyPQ(struct PriorityQueue *pq)
{
    return pq->size == 0;
}

// Function to add a pair of elements (endpoint vertex of an edge, weight of an edge) to an existing PriorityQueue for a given starting vertex.
void push(struct PriorityQueue *pq, pair<int, int> p)
{
    // If the queue is full, we cannot insert any more elements to it.
    if (pq->size == pq->capacity)
    {
        cout << "Overflow Error\n";
        return;
    }

    // We insert the pair into the PriorityQueue.
    pq->arr[pq->size] = p;
    // We store the size of the PriorityQueue in an integer variable pq_size.
    int pq_size = pq->size;
    // We update the size of the PriorityQueue.
    pq->size++;

    // We perform heapify logic and reorder the elements of the priority queue in such a way that no child is smaller than it's parent, else we swap them.
    // We run it in a while loop so that we can perform the same logic on the children of the node swapped with it's child too.
    while (pq_size > 0 && pq->arr[(pq_size - 1) / 2].first > pq->arr[pq_size].first)
    {
        pair<int, int> temp = pq->arr[pq_size];
        pq->arr[pq_size] = pq->arr[(pq_size - 1) / 2];
        pq->arr[(pq_size - 1) / 2] = temp;
        pq_size = (pq_size - 1) / 2;
    }
}

// Function extract_min identifies and removes the smallest element present in the PriorityQueue.
pair<int, int> extract_min(struct PriorityQueue *pq)
{
    // Basic check to see if the PriorityQueue is empty or not as we cannot remove elements from an empty PriorityQueue.
    if (isEmptyPQ(pq))
    {
        cout << "Underflow Error\n";
        return {INT_MAX, -1}; // By returning {INT_MIN, -1}, the function tells us there was an error dequeuing the element.
    }

    // The smallest value is the first element of the PriorityQueue by definition.
    pair<int, int> root = pq->arr[0];
    // We remove the last element of the PriorityQueue and place it at the first element of the PriorityQueue.
    pq->arr[0] = pq->arr[pq->size - 1];
    // We update the size of the PriorityQueue accordingly.
    pq->size--;

    // We perform the heapify logic to ensure that the PriorityQueue properties are not violated after deletion of the smallest element.
    // We start with the first element of the PriorityQueue and continue down the PriorityQueue to check for it's children.
    int i = 0;
    while (true)
    {
        // l - left child of i, r - right child of i, smallest - smallest value in the PriorityQueue.
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;

        // If left child is smaller than the current smallest element of the PriorityQueue, we set the smallest element as l.
        if (l < pq->size && pq->arr[l].first < pq->arr[smallest].first)
        {
            smallest = l;
        }
        // If right child is smaller than the current smallest element of the PriorityQueue, we set the smallest element as r.
        if (r < pq->size && pq->arr[r].first < pq->arr[smallest].first)
        {
            smallest = r;
        }
        // If the smallest element of the PriorityQueue is unchanged, then it means the PriorityQueue is valid, hence we break.
        if (smallest == i)
        {
            break;
        }

        // Otherwise, we swap pq->arr[i] with pq->arr[smallest] and set i = smallest and check for it's children in the next iteration of the while loop.
        pair<int, int> temp = pq->arr[i];
        pq->arr[i] = pq->arr[smallest];
        pq->arr[smallest] = temp;
        i = smallest;
    }

    // We return the smallest element after deletion.
    return root;
}

// Main function min_span_tree_prim uses the Prim's algorithm on the given graph using the PriorityQueue data structure implemented above.
void min_span_tree_prim(vector<vector<pair<int, int>>> graph, int start)
{
    // We initialize the PriorityQueue pq using the function initPQ().
    struct PriorityQueue *pq = initPQ();
    // key[v] represents the minimum weight of any edge that connects vertex v to the current MST (from the tree built so far).
    // parent[v] gives the parent vertex of vertex v, inMST[v] tells us if the given vertex is present in the MST of the graph or not.
    vector<int> key(graph.size() + 1, INT_MAX), parent(graph.size() + 1, -1), inMST(graph.size() + 1, FALSE);
    // We initialize values for the start vertex.
    key[start] = 0;
    // We push the start vertex into the PriorityQueue.
    push(pq, {0, start});

    // We loop till the PriorityQueue is empty.
    while (!isEmptyPQ(pq))
    {
        // We get the minimum weight edge present in the PriorityQueue, find it's end vertex, weight and store it in w, u.
        pair<int, int> p = extract_min(pq);
        int w = p.first, u = p.second;

        // If the vertex is already present in the PriorityQueue, then we go with the next minimum edge.
        if (inMST[u] == TRUE)
        {
            continue;
        }

        // We set inMST[u] to TRUE as we will add it to the MST as below.
        inMST[u] = TRUE;

        // For each element in the adjacency matrix of the minimum element, if any edge weight is lesser than the current edge weight, we push it in our MST.
        for (int i = 0; i < graph[u].size(); i++)
        {
            pair<int, int> p1 = graph[u][i];
            // v is the end vertex, w is the weight of the edge between u, v.
            int v = p1.first, w = p1.second;
            // If the edge (u, v) is not included in the MST and it's weight is lesser than the min weight of all edges connected to v, then we update key[v].
            if (inMST[v] == FALSE && w < key[v])
            {
                // Update key[v].
                key[v] = w;
                // Update parent[v]
                parent[v] = u;
                // Push the pair into the PriorityQueue for further iterations forming the MST by linking graph nodes via it's parent vector values.
                pair<int, int> p2 = {key[v], v};
                push(pq, p2);
            }
        }
    }

    // For each edge in the MST of the graph, we print it's weight and the total weight of all the edges.
    cout << "Edges in MST:" << endl;
    // weight_sum stores the sum of weights of all edges in the graph.
    int weight_sum = 0;
    // For all vertices, if the vertex has not been traversed, meaning it's parent is still -1, then we ignore it. We print the remaining as they are part of MST.
    for (int v = 0; v < graph.size(); v++)
    {
        if (parent[v] != -1)
        {
            cout << "(" << parent[v] << ", " << v << ") weight = " << key[v] << endl;
            // Update weight_sum by adding key[v] to it, weight of the corresponding edge of v.
            weight_sum = weight_sum + key[v];
        }
    }
    // We print the total weight of all the edges.
    cout << "Total weight = " << weight_sum << endl;
}

// Main function to take in inputs and execute the program.
int main()
{
    // We take in input, the number of vertices in the graph and further set the start node for traversal in the graph and store it in start.
    int n, start;
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
        // We set the first vertex taken as user input as the start vertex.
        if (i == 0)
        {
            start = u;
        }
    }
    // We create the minimum spanning tree of the graph using Prim's algorithm by calling the corresponding function.
    min_span_tree_prim(graph, start);
}