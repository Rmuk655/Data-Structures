#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;
// Time complexity = O(n)
// Space complexity = O(n + m)

int index(int n, int x)
{
    if (x > 0)
    {
        return n + x - 1;
    }
    return n + x;
}

void dfs(vector<vector<int>> &graph, int ind, vector<bool> &visited)
{
    visited[ind] = true;
    for (int i = 0; i < graph[ind].size(); i++)
    {
        if (!visited[graph[ind][i]])
        {
            dfs(graph, graph[ind][i], visited);
        }
    }
}

bool satisfiable(vector<vector<int>> &graph, int n)
{
    for (int i = (-1) * n; i <= n; i++)
    {
        if (i == 0)
        {
            continue;
        }
        vector<bool> visited(2 * n, false);
        dfs(graph, index(n, i), visited);
        if (visited[index(n, (-1) * i)])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int t;
    cin >> t;
    while (t > 0)
    {
        int m, n;
        cin >> n >> m;
        vector<vector<int>> graph(2 * n);
        for (int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            graph[index(n, (-1) * x)].push_back(index(n, y));
            graph[index(n, (-1) * y)].push_back(index(n, x));
        }
        if (satisfiable(graph, n))
        {
            cout << "Satisfiable" << endl;
        }
        else
        {
            cout << "Unsatisfiable" << endl;
        }
        t--;
    }
}