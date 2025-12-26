#include <iostream>
#include <vector>

using namespace std;

// Time complexity = O(n)
// Space complexity = O(n)
struct node
{
    int data;
    struct node *left;
    struct node *right;
};

node *create_node(int data)
{
    node *root = new node;
    root->data = data;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}

struct QNode
{
    node *Tnode;
    QNode *next;
};

struct Queue
{
    QNode *front;
    QNode *back;
};

void initQueue(Queue &q)
{
    q.front = q.back = nullptr;
}

bool isEmpty(Queue &q)
{
    return q.front == nullptr;
}

void enqueue(Queue &q, node *n)
{
    QNode *temp = new QNode{n, nullptr};
    if (isEmpty(q))
    {
        q.front = q.back = temp;
    }
    else
    {
        q.back->next = temp;
        q.back = q.back->next;
    }
}

node *dequeue(Queue &q)
{
    if (isEmpty(q))
    {
        return nullptr;
    }
    QNode *temp = q.front;
    node *Tnode = temp->Tnode;
    q.front = q.front->next;
    if (q.front == nullptr)
    {
        q.back = nullptr;
    }
    delete temp;
    return Tnode;
}

struct node *create_tree(vector<int> &vec, int i)
{
    if (vec.empty() || vec[0] == -1)
    {
        return nullptr;
    }
    node *root = create_node(vec[0]);
    Queue q;
    initQueue(q);
    enqueue(q, root);

    int ind = 1;
    while (ind < vec.size() && !isEmpty(q))
    {
        node *current = dequeue(q);
        if (ind < vec.size() && vec[ind] != -1)
        {
            current->left = create_node(vec[ind]);
            enqueue(q, current->left);
        }
        ind++;
        if (ind < vec.size() && vec[ind] != -1)
        {
            current->right = create_node(vec[ind]);
            enqueue(q, current->right);
        }
        ind++;
    }
    return root;
}

void preorder(struct node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << " ";
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << " ";
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(struct node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << " ";
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int main()
{
    struct node *root = nullptr;
    int n;
    cin >> n;
    vector<int> vec;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        vec.push_back(x);
    }
    root = create_tree(vec, 0);
    preorder(root);
    cout << endl;
    inorder(root);
    cout << endl;
    postorder(root);
}