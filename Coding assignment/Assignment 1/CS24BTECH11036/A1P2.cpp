#include <iostream>
#include <vector>

using namespace std;

// Defining node of a doubly XOR linked list which stores a value and the xor of the addresses of next node and previous node in np.
struct node
{
    int data;
    node *np;
};

// Defining XORlist which stores the head and tail of the linked list for easily accessing the last element in O(1).
struct XORList
{
    node *head;
    node *tail;
};

// Function xxor finds the XOR of the addresses of 2 nodes and returns the answer as an address/pointer to a node.
struct node *xxor(struct node *prev, struct node *curr)
{
    return (struct node *)((uintptr_t)(prev) ^ (uintptr_t)(curr));
}

// Search function that searches for a given element in the xor linked list.
// Time complexity = O(n)
// Space complexity = O(1)
struct node *search(struct XORList *list, int val)
{
    // Handling the case when list/list->head is null, where we return nullptr itself.
    if (list == nullptr || list->head == nullptr)
    {
        return nullptr;
    }
    // We use variables prev, curr, next to traverse through the xor list.
    // Notice that curr->np = XOR(prev, next), XOR(prev, curr->np) = XOR(prev, XOR(prev, next)) = XOR(XOR(prev, prev), next) = next
    struct node *prev = nullptr, *curr = list->head, *next = xxor(prev, curr->np);
    while (curr != nullptr && curr->data != val)
    {
        prev = curr;
        curr = next;
        // If curr = nullptr, we cannot access curr->np.
        if (curr != nullptr)
        {
            next = xxor(prev, curr->np);
        }
    }
    // We return the node containing the given element/nullptr if the element is not found.
    return curr;
}

// Insert function that inserts a given element in the xor linked list.
// Time complexity = O(n)
// Space complexity = O(1)
struct XORList *insert(struct XORList *list, int val)
{
    // Handling the list = null case where we create a new list, new list->head pointer and return the list.
    if (list == nullptr)
    {
        // Creating a new XORList and initializing its head, tail to nullptr.
        list = new struct XORList();
        list->head = nullptr;
        list->tail = nullptr;
    }
    // Handling the list->head = null case where we create a new list->head pointer and return the list.
    if (list->head == nullptr)
    {
        // Creating a new node for the list->head and initializing its values data as val, np as nullptr, tail as head.
        list->head = new struct node();
        list->head->data = val;
        list->head->np = nullptr;
        list->tail = list->head;
        return list;
    }
    // prev, curr, next are variables used to traverse through the linked list till the end.
    struct node *prev = nullptr, *curr = list->head, *next = xxor(prev, curr->np);
    while (next != nullptr)
    {
        prev = curr;
        curr = next;
        next = xxor(prev, curr->np);
    }
    // Once we reach the end of the linked list where next = nullptr, we have to attach a new node with the given value val.
    // For that we first create a new node and update its attributes.
    node *newnode = new node();
    newnode->data = val;
    // newnode->np = xxor(curr, next) = xxor(curr, null)
    newnode->np = xxor(curr, nullptr);
    // Updating the tail of the list.
    list->tail = newnode;
    // Updating curr->np.
    curr->np = xxor(prev, newnode);
    // We return modified list.
    return list;
}

// Delete function that deletes a given element in the xor linked list.
// Time complexity = O(n)
// Space complexity = O(1)
struct XORList *del(struct XORList *list, int val)
{
    // If the element is not present in the list, return the list unchanged.
    if (!search(list, val))
    {
        return list;
    }
    // Case when head->next == nullptr, head->data = val as we know that the element is present in the list (from above if).
    else if (xxor(nullptr, list->head->np) == nullptr)
    {
        // Delete head and set it to nullptr, set tail to nullptr and return list.
        delete list->head;
        list->head = nullptr;
        list->tail = nullptr;
        return list;
    }
    // Handling the case when list->head->data = val.
    else if (list->head->data == val)
    {
        // Store the head in a temp variable and delete it while updating list->head pointer with list->head->next and its np too.
        struct node *temp = list->head;
        list->head = xxor(nullptr, list->head->np);
        list->head->np = xxor(xxor(temp, list->head->np), nullptr);
        delete temp;
        return list;
    }
    // Handling the case when list->tail->data = val.
    else if (list->tail->data == val)
    {
        // Store the tail in a temp variable and delete it while updating list->tail pointer with list->tail->next and its np too.
        node *temp = list->tail;
        list->tail = xxor(temp->np, nullptr);
        list->tail->np = xxor(xxor(list->tail->np, temp), nullptr);
        delete temp;
        return list;
    }
    // In all other cases we first traverse the list to find the element.
    struct node *prev = nullptr, *curr = list->head, *next = xxor(prev, curr->np);
    while (curr != nullptr && curr->data != val)
    {
        prev = curr;
        curr = next;
        next = xxor(prev, curr->np);
    }
    // Once found, we update the np's of the prev and next pointer of the element appropriately.
    prev->np = xxor(next, xxor(prev->np, curr));
    if (next != nullptr)
    {
        next->np = xxor(prev, xxor(next->np, curr));
    }
    // Delete the element with data = val.
    delete curr;
    return list;
}

// Reverse function that reverses the elements of the given xor linked list.
// Time complexity = O(1)
// Space complexity = O(1)
struct XORList *reverse(struct XORList *list)
{
    // Handling the case when list = nullptr/list->head = nullptr where we dont need to do anything. So, we return the list as it is.
    if (list == nullptr || list->head == nullptr)
    {
        return list;
    }
    // We store the head in a temp node and swap the tail and head pointer effectively reversing the list.
    struct node *temp = list->head;
    list->head = list->tail;
    list->tail = temp;
    return list;
}

// Function used to print the elements of a given linked list.
void print(struct XORList *list)
{
    // If the list = nullptr, list->head = nullptr, we dont need to print anything as the list is empty.
    if (list == nullptr || list->head == nullptr)
    {
        cout << endl;
        return;
    }
    // We use prev, curr, next node pointers to traverse through the list to reach it's end.
    struct node *prev = nullptr, *curr = list->head, *next = xxor(prev, curr->np);
    while (next != nullptr)
    {
        prev = curr;
        curr = next;
        next = xxor(prev, curr->np);
    }
    // We now traverse towards the head while printing the elements of the linked list in the reverse order - recent element first.
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

// Test function to check the validity of the code.
//  void test()
//  {
//      XORList *list = nullptr;

//     cout << "Test 1:" << endl;
//     list = insert(list, 10);
//     print(list); // 10
//     list = insert(list, 20);
//     print(list); // 10 20
//     list = insert(list, 30);
//     print(list); // 10 20 30
//     list = insert(list, 40);
//     print(list); // 10 20 30 40
//     list = insert(list, 50);
//     print(list); // 10 20 30 40 50

//     cout << "Test 2:" << endl;
//     cout << (search(list, 20) ? "Element is present" : "Element is not present") << endl;
//     cout << (search(list, 99) ? "Element is present" : "Element is not present") << endl;

//     cout << "Test 3:" << endl;
//     list = del(list, 10);
//     print(list); // 20 30 40 50

//     cout << "Test 4:e" << endl;
//     list = del(list, 30);
//     print(list); // 20 40 50

//     cout << "Test 5:" << endl;
//     list = del(list, 50);
//     print(list); // 20 40

//     cout << "Test 6:" << endl;
//     list = reverse(list);
//     print(list); // 40 20

//     cout << "Test 7" << endl;
//     list = del(list, 40);
//     print(list); // 20
//     list = del(list, 20);
//     print(list); // empty

//     cout << "Test 8:" << endl;
//     list = reverse(list);
//     print(list); // empty

//     cout << "Test 9:" << endl;
//     list = insert(list, 99);
//     print(list); // 99
//     list = reverse(list);
//     print(list); // 99
//     list = del(list, 99);
//     print(list); // empty

//     cout << "All tests executed." << endl;
// }

int main()
{
    // test();
    struct XORList *list = nullptr;
    // Taking the number of operations as input in k.
    int k;
    cin >> k;
    while (k > 0)
    {
        // For each operation, we identify the operation use op code.
        int op;
        cin >> op;
        // When op == 1, we perform the search operation.
        if (op == 1)
        {
            // Input element to search.
            int x;
            cin >> x;
            // If search returns a non null pointer, we print element is present, else we print element is not present.
            if (search(list, x))
            {
                cout << "Element is present" << endl;
            }
            else
            {
                cout << "Element is not present" << endl;
            }
        }
        // When op == 2, we perform the insert operation.
        else if (op == 2)
        {
            // Input element to insert.
            int x;
            cin >> x;
            // Insert returns a the list.
            list = insert(list, x);
            // We print the resulting list.
            print(list);
        }
        // When op == 3, we perform the delete operation.
        else if (op == 3)
        {
            // Input element to delete.
            int x;
            cin >> x;
            // If the element is present in the list, we perform the delete operation and print the list.
            if (search(list, x))
            {
                list = del(list, x);
                print(list);
            }
            // Else we just print the element is not present.
            else
            {
                cout << "Element is not present" << endl;
            }
        }
        // When op == 4, we perform the reverse operation and subsequently print the resultant list.
        else if (op == 4)
        {
            list = reverse(list);
            print(list);
        }
        k--;
    }
}