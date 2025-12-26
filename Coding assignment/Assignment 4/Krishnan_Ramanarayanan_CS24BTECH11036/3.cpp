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

// Main function Dijkstra uses the Dijikstra's algorithm to find the single source shortest path from the source to all vertices of the graph.
void Dijkstra(vector<vector<pair<int, int>>> graph, int start)
{
    // We initialize the PriorityQueue pq using the function initPQ().
    struct PriorityQueue *pq = initPQ();
    // dist[v] stores the shortest distance between the start node and v.
    // parent[v] gives the parent vertex of vertex v, inMST[v] tells us if the given vertex is present in the MST of the graph or not.
    vector<int> dist(graph.size(), INT_MAX), parent(graph.size(), -1);
    // visited[v] tells us if we have visited this node before or not.
    vector<bool> visited(graph.size(), false);

    // We initialize values for the start vertex.
    dist[start] = 0;
    // We push the start vertex into the PriorityQueue.
    push(pq, {dist[start], start});

    // We loop till the PriorityQueue is empty.
    while (!isEmptyPQ(pq))
    {
        // We get the closest vertex (from start) present in the PriorityQueue, find it's distance, closest vertex and store it in d, u.
        pair<int, int> p = extract_min(pq);
        int d = p.first, u = p.second;
        // If we have visited the vertex u, we proceed with the next iteration.
        if (visited[u])
        {
            continue;
        }
        // We set visited[u] as true as we just explored it's path from start.
        visited[u] = TRUE;

        // We iterate on each pair of elements in the adjacency matrix of the closest element.
        for (pair<int, int> p : graph[u])
        {
            // We store the weight of the edge between u and the element in it's adjacency matrix we are iterating on in w.
            // We update the distance between start and the element in it's adjacency matrix and store it in alt.
            int w = p.second, alt = d + w;
            // If we find an alternative path of shorter length than the previous paths for this matrix element, we update it.
            if (alt < dist[p.first])
            {
                // Update distance with the alternative shorter distance.
                dist[p.first] = alt;
                // Update parent of the element in u's adjacency matrix to u.
                parent[p.first] = u;
                // Push this edge into the PriorityQueue for the subsequent iteration.
                push(pq, {alt, p.first});
            }
        }
    }

    // For each element in the graph, we print the details of it's vertex, length of path from start and path.
    for (int v = 1; v < graph.size(); v++)
    {
        cout << "Vertex " << v << ": ";
        // If dist[v] = INT_MAX, means we have not set it, means we cannot reach the vertex from start s.
        if (dist[v] == INT_MAX)
        {
            cout << "Length = " << -1 << ", Path = Unreachable" << endl;
            continue;
        }
        cout << "Length = " << dist[v] << ", Path = ";

        // The vector path stores the path from start to the given vertex.
        vector<int> path;
        for (int x = v; x != -1; x = parent[x])
        {
            path.push_back(x);
        }

        // We print the elements of the vector path.
        for (int i = path.size() - 1; i > 0; i--)
        {
            cout << path[i] << " ";
        }
        cout << path[0] << endl;
    }
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
        // We add edges to the given directed graph (1 edge from u to v is added by pushing v to u's adjacency list).
        graph[u].push_back({v, w});
    }
    // We take in input, the starting vertex of the graph for our traversal.
    int s;
    cin >> s;
    // We print the length of the shortest path, shortest path from the starting vertex of the graph to all other vertices of the graph using Dijikstra's algorithm
    Dijkstra(graph, s);
}