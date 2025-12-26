#include <iostream>
#include <vector>

using namespace std;

// Time Complexity = O(n1 + n2)
// Space Complexity = O(n1 + n2)
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

struct Node *insert(Node *l1, Node *l2, Node *list)
{
    if (l1 == nullptr && l2 == nullptr)
    {
        return nullptr;
    }
    else if (l1 == nullptr)
    {
        list = l2;
        return list;
    }
    else if (l2 == nullptr)
    {
        list = l1;
        return list;
    }
    while (l1 != nullptr && l2 != nullptr)
    {
        if (l1->data < l2->data)
        {
            list = create_list(list, l1->data);
            l1 = l1->next;
        }
        else
        {
            list = create_list(list, l2->data);
            l2 = l2->next;
        }
    }
    if (l1 == nullptr && l2 != nullptr)
    {
        while (l2 != nullptr)
        {
            list = create_list(list, l2->data);
            l2 = l2->next;
        }
    }
    else if (l2 == nullptr && l1 != nullptr)
    {
        while (l1 != nullptr)
        {
            list = create_list(list, l1->data);
            l1 = l1->next;
        }
    }
    return list;
}

int main()
{
    int n1, n2;
    cin >> n1;
    struct Node *l1 = nullptr, *l2 = nullptr, *list = nullptr;
    int x;
    for (int i = 0; i < n1; i++)
    {
        cin >> x;
        l1 = create_list(l1, x);
    }
    cin >> n2;
    for (int i = 0; i < n2; i++)
    {
        cin >> x;
        l2 = create_list(l2, x);
    }
    list = insert(l1, l2, list);
    while (list != nullptr)
    {
        cout << list->data << " ";
        list = list->next;
    }
}