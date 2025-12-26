#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define SIZE_STACK 100

// Using a struct Stack to store it's top element's index + 1.
struct Stack
{
    int *arr;
    int top;
};

// Function to check if the Stack is empty or not by checking if it's top value is 0 which means the no of elements in the stack = 0.
bool isEmpty(Stack *stack)
{
    if (stack->top == 0)
    {
        return true;
    }
    return false;
}

// Function to check if the Stack is full or not by checking if it's top value is SIZE_STACK which means the no of elements in the stack
// = max no of possible elements in the stack = SIZE_STACK.
bool isFull(Stack *stack)
{
    if (stack->top == SIZE_STACK)
    {
        return true;
    }
    return false;
}

// Function to insert an element into the stack.
void Push(Stack *&stack, int ele)
{
    // Checking if the stack is full as we cannot any element into a full stack.
    if (isFull(stack))
    {
        cout << "Cannot insert an element into a full stack." << endl;
        return;
    }
    // If the stack is not full, we add the integer ele at the top's position and increase stack.top by 1 as we have added an element to the stack.
    *(stack->arr + stack->top) = ele;
    stack->top++;
}

// Function to delete an element from the stack.
int Pop(Stack *&stack)
{
    // Checking if the stack is empty as we cannot remove an element from an empty stack.
    if (isEmpty(stack))
    {
        // cout << "Cannot delete an element from an empty stack." << endl;
        return INT_MIN; // Returning INT_MIN means that we have got an underflow error.
    }
    // Normal case when the stack is not empty, we decrease stack.top by 1 as we are removing an element.
    int x = *(stack->arr + stack->top - 1);
    stack->top--;
    return x;
}

void dfs(int start, vector<vector<int>> graph, int n)
{
    Stack *stac = new Stack();
    int *arr = new int[graph.size()];
    stac->arr = arr;
    stac->top = 0;

    vector<int> visited(graph.size(), 0);
    vector<int> parent(graph.size() + 1, -1);
    vector<int> dist(graph.size() + 1, INT_MAX);

    Push(stac, start);
    dist[start] = 0;
    parent[start] = -1;

    while (!isEmpty(stac))
    {
        int node = Pop(stac);
        if (visited.size() == 0 || visited[node] == 0)
        {
            visited[node] = 1;
            for (int i = 0; i < graph[node].size(); i++)
            {
                if (visited[graph[node][i]] == 0)
                {
                    Push(stac, graph[node][i]);
                    if (dist[graph[node][i]] > dist[node] + 1)
                    {
                        dist[graph[node][i]] = dist[node] + 1;
                        parent[graph[node][i]] = node;
                    }
                }
            }
        }
    }

    for (int v = 1; v <= n; v++)
    {
        cout << "Vertex " << v << ": ";
        if (dist[v] == INT_MAX)
        {
            cout << "Length = " << -1 << ", Path = Unreachable" << endl;
            return;
        }
        cout << "Length = " << dist[v] << ", Path = ";

        vector<int> path;
        for (int x = v; x != -1; x = parent[x])
        {
            path.push_back(x);
        }

        for (int i = path.size() - 1; i > 0; i--)
        {
            cout << path[i] << " ";
        }
        cout << path[0] << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int s;
    cin >> s;
    dfs(s, graph, n);
}