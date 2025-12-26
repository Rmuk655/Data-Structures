#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;
// Time complexity = O(n)
// Space complexity = O(n + m)

struct node
{
    int data;
    int color;
    // int distance;
    // int finishing_time;
    // vector<int> path;
    vector<struct node *> adj_list, adj_list_rev;
};

struct node *create_node(struct node *graph_start, int ele)
{
    graph_start = new struct node();
    graph_start->data = ele;
    graph_start->color = WHITE;
    // graph_start->distance = 0;
    // graph_start->finishing_time = 0;
    return graph_start;
}

void dfs_1(struct node *&node, vector<int> &order)
{
    node->color = GRAY;
    // node->distance = time;
    // time++;
    for (int i = 0; i < node->adj_list.size(); i++)
    {
        if (node->adj_list[i]->color == WHITE)
        {
            dfs_1(node->adj_list[i], order);
        }
    }
    order.push_back(node->data);
    node->color = BLACK;
    // node->finishing_time = time;
    // time++;
}

void dfs_2(struct node *&node, int compID, vector<int> &component, int n)
{
    node->color = GRAY;
    // node->distance = time;
    // time++;
    int idx = node->data >= 0 ? n + node->data - 1 : n + node->data;
    component[idx] = compID;
    for (int i = 0; i < node->adj_list_rev.size(); i++)
    {
        if (node->adj_list_rev[i]->color == WHITE)
        {
            dfs_2(node->adj_list_rev[i], compID, component, n);
        }
    }
    node->color = BLACK;
    // node->finishing_time = time;
    // time++;
}

// void print_dfs(vector<struct node *> &nodes_list)
// {
//     for (int i = 0; i < nodes_list.size(); i++)
//     {
//         nodes_list[i]->color = WHITE;
//     }
//     int time = 0;
//     for (int i = 0; i < nodes_list.size(); i++)
//     {
//         if (nodes_list[i]->color == WHITE)
//         {
//             nodes_list[i]->path.push_back(nodes_list[i]->data);
//             dfs_visit(nodes_list[i], time);
//         }
//     }
// }

bool satisfiable(int n, vector<struct node *> nodes_list, struct node *graph_start)
{
    vector<int> order;
    for (int i = 0; i < 2 * n; i++)
    {
        if (nodes_list[i]->color == WHITE)
        {
            dfs_1(nodes_list[i], order);
        }
    }

    for (int i = 0; i < 2 * n; i++)
    {
        nodes_list[i]->color = WHITE;
    }

    vector<int> component(2 * n, -1);
    int comp_id = 0;

    struct node *temp = graph_start;
    // print_dfs(nodes_list);
    for (int i = (int)order.size() - 1; i >= 0; i--)
    {
        int index = order[i] > 0 ? n + order[i] - 1: n + order[i];
        if (nodes_list[index]->color == WHITE)
        {
            dfs_2(nodes_list[index], comp_id, component, n);
            comp_id++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (component[n - i] == component[n + i - 1])
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
        struct node *graph_start = nullptr;
        vector<struct node *> nodes_list;
        int n, m;
        cin >> n >> m;
        for (int i = -n; i <= n; i++)
        {
            if (n == 0)
            {
                continue;
            }
            struct node *node = create_node(graph_start, i);
            nodes_list.push_back(node);
        }
        for (int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            // int x_comp = (-1) * x, y_comp = (-1) * y;
            struct node *node_1 = x > 0 ? nodes_list[n + x - 1] : nodes_list[n + x]; // Stores x
            struct node *node_2 = x < 0 ? nodes_list[n + x - 1] : nodes_list[n + x]; // Stores x_comp
            struct node *node_3 = y > 0 ? nodes_list[n + y - 1] : nodes_list[n + y]; // Stores y
            struct node *node_4 = y < 0 ? nodes_list[n + y - 1] : nodes_list[n + y]; // Stores y_comp
            if (i == 0)
            {
                graph_start = node_1;
            }
            node_2->adj_list.push_back(node_3);
            node_3->adj_list_rev.push_back(node_2);

            node_1->adj_list.push_back(node_4);
            node_4->adj_list_rev.push_back(node_1);
        }
        if (satisfiable(n, nodes_list, graph_start))
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