#include <iostream>
#include <vector>

using namespace std;

struct node
{
    int data;
    node *np;
};

struct node *xxor(struct node *prev, struct node *curr)
{
    return (struct node *)((uintptr_t)(prev) ^ (uintptr_t)(curr));
}

struct node *search(struct node *head, int val)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    struct node *prev = nullptr, *curr = head, *next = xxor(prev, curr->np);
    while (curr != nullptr && curr->data != val)
    {
        prev = curr;
        curr = next;
        if (curr != nullptr)
        {
            next = xxor(prev, curr->np);
        }
    }
    return curr;
}

struct node *insert(struct node *head, int val)
{
    if (head == nullptr)
    {
        head = new struct node();
        head->data = val;
        head->np = nullptr;
        return head;
    }
    struct node *prev = nullptr, *curr = head, *next = xxor(prev, curr->np);
    while (next != nullptr)
    {
        prev = curr;
        curr = next;
        next = xxor(prev, curr->np);
    }
    node *newnode = new node();
    newnode->data = val;
    newnode->np = xxor(curr, nullptr);
    curr->np = xxor(prev, newnode);
    return head;
}

struct node *del(struct node *head, int val)
{
    if (!search(head, val))
    {
        return head;
    }
    else if (xxor(nullptr, head->np) == nullptr)
    {
        delete head;
        head = nullptr;
        return head;
    }
    else if (head->data == val)
    {
        struct node *temp = head;
        head = xxor(nullptr, head->np);
        head->np = xxor(xxor(temp, head->np), nullptr);
        delete temp;
        return head;
    }
    struct node *prev = nullptr, *curr = head, *next = xxor(prev, curr->np);
    while (curr != nullptr && curr->data != val)
    {
        prev = curr;
        curr = next;
        next = xxor(prev, curr->np);
    }
    prev->np = xxor(next, xxor(prev->np, curr));
    if (next != nullptr)
    {
        next->np = xxor(prev, xxor(next->np, curr));
    }
    return head;
}

struct node *reverse(struct node *head)
{
    if (head == nullptr)
    {
        return head;
    }
    struct node *prev = nullptr, *curr = head, *next = xxor(prev, curr->np);
    while (next != nullptr)
    {
        prev = curr;
        curr = next;
        next = xxor(prev, curr->np);
    }
    head = curr;
    return head;
}

void print(struct node *head)
{
    if (head == nullptr)
    {
        cout << endl;
        return;
    }
    struct node *prev = nullptr, *curr = head, *next = xxor(prev, curr->np);
    while (next != nullptr)
    {
        // cout << curr->data << " ";
        prev = curr;
        curr = next;
        next = xxor(prev, curr->np);
    }
    while (curr != nullptr)
    {
        cout << curr->data << " ";
        next = curr;
        curr = prev;
        if (curr != nullptr)
        {
            prev = xxor(next, curr->np);
        }
    }
    cout << endl;
}

void test()
{
    struct node *head = nullptr;

    cout << "===== Test 1: Basic Insertion =====" << endl;
    head = nullptr;
    head = insert(head, 10);
    print(head); // 10
    head = insert(head, 20);
    print(head); // 20 10
    head = insert(head, 30);
    print(head); // 30 20 10
    head = insert(head, 40);
    print(head); // 40 30 20 10
    head = insert(head, 50);
    print(head); // 50 40 30 20 10

    cout << "===== Test 2: Search =====" << endl;
    cout << (search(head, 20) ? "Element is present" : "Element is not present") << endl;
    cout << (search(head, 99) ? "Element is present" : "Element is not present") << endl;

    cout << "===== Test 3: Delete Head =====" << endl;
    head = del(head, 10);
    print(head); // 50 40 30 20

    cout << "===== Test 4: Delete Middle =====" << endl;
    head = del(head, 30);
    print(head); // 50 40 20

    cout << "===== Test 5: Delete Last =====" << endl;
    head = del(head, 50);
    print(head); // 40 20

    cout << "===== Test 6: Reverse =====" << endl;
    head = reverse(head);
    print(head); // 20 40

    cout << "===== Test 7: Delete Remaining =====" << endl;
    head = del(head, 40);
    print(head); // 20
    head = del(head, 20);
    print(head); // empty

    cout << "===== Test 8: Reverse Empty =====" << endl;
    head = reverse(head);
    print(head); // empty

    cout << "===== Test 9: Single Node Ops =====" << endl;
    head = insert(head, 99);
    print(head); // 99
    head = reverse(head);
    print(head); // 99
    head = del(head, 99);
    print(head); // empty

    cout << "All tests executed." << endl;
}

int main()
{
    test();
    struct node *head = nullptr;
    int k;
    cin >> k;
    while (k > 0)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x;
            cin >> x;
            if (search(head, x))
            {
                cout << "Element is present" << endl;
            }
            else
            {
                cout << "Element is not present" << endl;
            }
        }
        else if (op == 2)
        {
            int x;
            cin >> x;
            head = insert(head, x);
            print(head);
        }
        else if (op == 3)
        {
            int x;
            cin >> x;
            if (search(head, x))
            {
                head = del(head, x);
                print(head);
            }
            else
            {
                cout << "Element is not present" << endl;
            }
        }
        else if (op == 4)
        {
            head = reverse(head);
            print(head);
        }
        k--;
    }
}