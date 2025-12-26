#include <iostream>
#include <string>
#include <vector>
#include <climits>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define QUEUE_SIZE 100
using namespace std;

// Definition of a node of a Queue data structure.
struct Queue
{
    int *arr;
    int length;
    int head;
    int tail;
    int count;
};

// Function to initialize the Queue.
struct Queue *initQ()
{
    struct Queue *queue = new struct Queue();
    queue->arr = new int[QUEUE_SIZE];
    queue->length = QUEUE_SIZE;
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    return queue;
}

// Function to check if the Queue is empty or not.
bool isEmptyQ(struct Queue *queue)
{
    return queue->count == 0;
}

// Function to check if the Queue is full or not.
bool isFullQ(struct Queue *queue)
{
    return queue->count == queue->length;
}

// Function to add an element to an existing Queue.
void enqueue(struct Queue *queue, int ele)
{
    // Basic check to see if the Queue is full or not, as we cannot add elements to a full Queue.
    if (isFullQ(queue))
    {
        printf("Overflow Error! Cannot insert element into a full Queue.\n");
        return;
    }
    // We add the element at the end of the Queue, set the tail of the Queue appropriately.
    queue->arr[queue->tail] = ele;
    queue->tail = (queue->tail + 1) % queue->length;
    // Increase the count of elements in the queue by 1.
    queue->count++;
}

// Function to remove an element from an existing Queue.
int dequeue(struct Queue *queue)
{
    // Basic check to see if the Queue is empty or not as we cannot remove elements from an empty Queue.
    if (isEmptyQ(queue))
    {
        printf("Underflow Error! Cannot delete element from an empty Queue.");
        return INT_MIN; // By returning INT_MIN, the function tells us there was an error dequeuing the element.
    }
    // Finding the element to dequeue and storing it in the variable x.
    int x = queue->arr[queue->head];
    // Set it to 0;
    queue->arr[queue->head] = 0;
    // We now set the head value of Queue
    queue->head = (queue->head + 1) % queue->length;
    // Decrease the count of elements in the queue by 1.
    queue->count--;
    return x;
}

// Main function bfs performs a breadth first search on the given graph using the Queue data structure implemented above.
void bfs(int start, vector<vector<int>> graph)
{
    // We initialize the queue using the initQ() function.
    struct Queue *queue = initQ();
    // We initialize vectors with their respective values.
    vector<int> color(graph.size(), WHITE), parent(graph.size(), -1), dist(graph.size(), INT_MAX);
    // We set the values for the start node in the above vectors.
    color[start] = GRAY;
    dist[start] = 0;
    // Enqueue start to the Queue in the beginning.
    enqueue(queue, start);
    // Iterate until empty Queue.
    while (!isEmptyQ(queue))
    {
        // We get the integer value corresponding to the data of a node in the graph at the head of the Queue
        int u = queue->arr[queue->head];
        // For each node of the graph, we explore the nodes in it's adjacency matrix and enqueue them.
        for (int i = 0; i < graph[u].size(); i++)
        {
            // If the node is unexplored, it's color will be white.
            if (color[graph[u][i]] == WHITE)
            {
                // Set the values in the above vectors appropriately.
                color[graph[u][i]] = GRAY;
                dist[graph[u][i]] = dist[u] + 1;
                parent[graph[u][i]] = u;
                // Add the given matrix in the Queue.
                enqueue(queue, graph[u][i]);
            }
        }
        // We dequeue the element whose adjacency matrix elements have been explored and set it's color to black.
        dequeue(queue);
        color[u] = BLACK;
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
    vector<vector<int>> graph(n + 1);
    // We take in input, the number of edges in the graph.
    int m;
    cin >> m;
    // We loop for each edge and get the corresponding edge starting and ending points to add it to the graph.
    for (int i = 0; i < m; i++)
    {
        // We take in input the start, end points of an edge in the graph.
        int u, v;
        cin >> u >> v;
        // We add edges to the given undirected graph (both edges from u to v and v to u are added by pushing v to u's adjacency list and vice versa).
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    // We take in input, the starting vertex of the graph for our traversal.
    int s;
    cin >> s;
    // We perform the bfs traversal and print the corresponding minimum path length and path
    bfs(s, graph);
}