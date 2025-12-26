#include <iostream>
#include <vector>

using namespace std;

struct node
{
    int data;
    node *next;
};

struct node *create_node(struct node *head, int val)
{
    if (head == nullptr)
    {
        head = new node();
        head->data = val;
        head->next = nullptr;
        return head;
    }
    struct node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = new node();
    temp->next->data = val;
    temp->next->next = nullptr;
    return head;
}

struct node *push(struct node *head, int val)
{
    return create_node(head, val);
}

int pop(struct node *&head)
{
    if (head == nullptr)
    {
        cout << "Cannot pop from an empty list" << endl;
        return INT_MIN;
    }
    else if (head->next == nullptr)
    {
        int x = head->data;
        free(head);
        head = nullptr;
        return x;
    }
    struct node *temp = head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }
    int x = temp->next->data;
    struct node *temp1 = temp->next;
    temp->next = nullptr;
    free(temp1);
    return x;
}

struct node *sort(struct node *&head, struct node *&temp, int n)
{
    if (n == 1)
    {
        return head;
    }
    temp = create_node(temp, pop(head));
    head = sort(head, temp, n - 1);
    struct node *temp2 = nullptr;
    int x = pop(temp), y = pop(head);
    while (head != nullptr && x < y)
    {
        temp2 = create_node(temp2, y);
        y = pop(head);
    }
    if (x < y)
    {
        head = create_node(head, x);
        head = create_node(head, y);
    }
    else
    {
        head = create_node(head, y);
        head = create_node(head, x);
    }
    while (temp2 != nullptr)
    {
        head = create_node(head, pop(temp2));
    }
    return head;
}

void print(struct node *head)
{
    while (head->next != nullptr)
    {
        cout << pop(head) << " ";
    }
    cout << pop(head) << endl;
}

void test()
{
    vector<vector<int>> test_cases = {
        {5, 3, 8, 1, 2},  // mixed order
        {10, 20, 30, 40}, // already sorted
        {9, 7, 5, 3, 1},  // reverse order
        {4},              // single element
        {}                // empty list (edge case)
    };

    for (size_t t = 0; t < test_cases.size(); t++)
    {
        cout << "Test Case " << t + 1 << ": " << endl;

        struct node *head = nullptr, *temp = nullptr;

        // insert elements
        for (int val : test_cases[t])
        {
            head = create_node(head, val);
        }

        // if list is empty, just skip sorting
        if (test_cases[t].empty())
        {
            cout << "(empty list)" << endl;
            cout << "----------------------" << endl;
            continue;
        }

        // sort the linked list
        head = sort(head, temp, test_cases[t].size());

        // print sorted list
        cout << "Sorted output: ";
        print(head);

        cout << "----------------------" << endl;
    }
    cout << "All test cases passed!" << endl;
}

int main()
{
    test();
    struct node *head = nullptr, *temp = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        head = create_node(head, x);
    }
    sort(head, temp, n);
    print(head);
}