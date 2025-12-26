#include <iostream>
#include <vector>

using namespace std;

// Time Complexity = O(n)
// Space Complexity = O(n)
struct Node
{
    int data;
    struct Node *next;
};

Node *create_list(Node *head, int data)
{
    if (head == nullptr)
    {
        head = new struct Node();
        head->data = data;
        head->next = nullptr;
        return head;
    }
    struct Node *node = new struct Node();
    node->data = data;
    node->next = nullptr;
    struct Node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = node;
    return head;
}

void reverse(struct Node *&list)
{
    struct Node *head = list, *tail = list;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }
    while (head != tail)
    {
        struct Node *temp = tail->next;
        tail->next = head;
        head = head->next;
        tail->next->next = temp;
    }
    list = head;
}

int main()
{
    int n;
    cin >> n;
    struct Node *list = nullptr;
    int x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        list = create_list(list, x);
    }
    reverse(list);
    while (list != nullptr)
    {
        cout << list->data << " ";
        list = list->next;
    }
}