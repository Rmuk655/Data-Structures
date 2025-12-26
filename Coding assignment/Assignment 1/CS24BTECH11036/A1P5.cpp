#include <iostream>
#include <vector>

using namespace std;

// Node of the singly linked list used to implement the stack.
struct node
{
    int data;
    node *next;
};

// Function to create a new node and add it to the existing linked list with head pointer head, value val.
struct node *create_node(struct node *head, int val)
{
    // Dealing with the special case when the linked list doesnt exist - head == nullptr.
    // We just create the new node, store it in head itself and return head after updating its data and next fields.
    if (head == nullptr)
    {
        head = new node();
        head->data = val;
        head->next = nullptr;
        return head;
    }
    // We use a temp pointer to traverse through the list to reach the last element to which we attach the new node as it's next.
    struct node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    // Creating a new node, updating it's data, next attributes and attaching it to the list
    temp->next = new node();
    temp->next->data = val;
    temp->next->next = nullptr;
    // We return the head pointer as we always traverse through the list starting from the head.
    return head;
}

// Stack data structure.
struct Stack
{
    struct node *head;
};

// Push function of stack is nothing but inserting into the linked list using create_node.
struct Stack *push(Stack *stac, int val)
{
    if (stac == nullptr)
    {
        stac = new Stack();
        stac->head = nullptr;
        stac->head = create_node(stac->head, val);
        return stac;
    }
    stac->head = create_node(stac->head, val);
    return stac;
}

// Pop function implementation of stack using singly linked list.
int pop(Stack *stac)
{
    // If head is nullptr, we cannot pop from the empty stack.
    if (stac == nullptr || stac->head == nullptr)
    {
        cout << "Stack Underflow error!" << endl;
        return INT_MIN;
    }
    // If there is only 1 element in the stack, we delete the head directly and assign head as nullptr.
    // We store the data of the node popped and return it.
    else if (stac->head->next == nullptr)
    {
        int popped = stac->head->data;
        delete stac->head;
        stac->head = nullptr;
        return popped;
    }
    // We use a temp node to traverse through the list till the last element to pop it.
    struct node *temp = stac->head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }
    // Store the popped node's data in popped to return it.
    int popped = temp->next->data;
    // We store the node to be deleted in temp node temp1 and free it while setting the temp->next as nullptr.
    // temp->next was the position of the tail/deleted node.
    struct node *temp1 = temp->next;
    temp->next = nullptr;
    delete temp1;
    // Returning the data of the deleted node which we stored in variable popped above.
    return popped;
}

// Sort function to sort the elements of the stack in descending order.
// We take temp too as an argument to store the popped elements of the stack across various calls/stacks of the recursive function.
struct Stack *sort(Stack *stac, Stack *temp, int n)
{
    if (stac == nullptr || stac->head == nullptr)
    {
        return stac;
    }
    // If stack is empty do nothing and return null pointer.
    if (n == 0)
    {
        return stac;
    }
    // If stack has only 1 element, do nothing and return the head pointer.
    else if (n == 1)
    {
        return stac;
    }
    // We pop the last element and sort the remaining recursively until n == 1.
    temp = push(temp, pop(stac));
    stac = sort(stac, temp, n - 1);
    // Once the function stack starts unwinding, we sort the elements by placing a given element in it's correct position.
    // For that we need a temp2 to pop elements in the given sorted stack so that we can insert the new element in it's correct
    // position and then push the popped elements back into the original stack.
    struct Stack *temp2 = nullptr;
    // We get the new element to be inserted in the stack from temp and the top of the stack stac.
    int x = pop(temp), y = pop(stac);
    // Until we find an element such that the new element to be inserted is less than it's next element keep pushing into temp2 stack.
    // Unless we reach the bottom of the stack, as we cannot pop further.
    while (stac->head != nullptr && x < y)
    {
        temp2 = push(temp2, y);
        y = pop(stac);
    }
    // Handling the edge case when stac/stac->head is null
    if (y == INT_MIN)
    {
        stac = push(stac, x);
    }
    // Compare the new element and the last popped element (which we didnt push into the stack) and insert it accordingly into the stack.
    else
    {
        if (x < y)
        {
            // x < y means x is pushed in first.
            stac = push(stac, x);
            stac = push(stac, y);
        }
        else
        {
            // x >= y means y is pushed in first.
            stac = push(stac, y);
            stac = push(stac, x);
        }
    }
    // Now we have to push in the remaining elements without disturbing the order since they were already sorted in the previous function
    // call. We do this by pushing the popped element from temp2 stack into the head stack.
    while (temp2 != nullptr && temp2->head != nullptr)
    {
        stac = push(stac, pop(temp2));
    }
    return stac;
}

// We print the elements of the stack by traversing through the singly linked list.
// Since we want to print the elements from top to bottom instead of bottom to top we will have to pop the elements one by one
// from the stack and print them.
void print(struct Stack *stac)
{
    // If the stack is empty, print nothing.
    if (stac == nullptr || stac->head == nullptr)
    {
        cout << endl;
        return;
    }
    // Go through each element of the list, pop the element and print it.
    while (stac->head->next != nullptr)
    {
        cout << pop(stac) << " ";
    }
    // Print the last element and next line.
    cout << pop(stac) << endl;
}

// // test() function to check if the code is working.
// void test()
// {
//     // Test cases:
//     vector<vector<int>> test_cases = {
//         {5, 3, 8, 1, 2},  // mixed order
//         {10, 20, 30, 40}, // already sorted
//         {9, 7, 5, 3, 1},  // reverse order
//         {4},              // single element
//         {}                // empty list (edge case)
//     };
//     // Looping through each test case.
//     for (size_t t = 0; t < test_cases.size(); t++)
//     {
//         cout << "Test Case " << t + 1 << ": " << endl;

//         struct Stack *stac = nullptr, *stac1 = nullptr;

//         // Insert elements into the linked list with head head
//         for (int val : test_cases[t])
//         {
//             stac = push(stac, val);
//         }

//         // Sort the linked list.
//         stac = sort(stac, stac1, test_cases[t].size());

//         // print sorted list
//         cout << "Sorted output: ";
//         print(stac);

//         cout << "----------------------" << endl;
//     }
//     cout << "All test cases passed!" << endl;
// }

int main()
{
    // To run the test function by uncommenting.
    // test();
    // We set head of both the stacks to nullptr as the sort function takes in 3 arguments, 2 being struct Stack*.
    // stac1 is the temporary stack used to store popped elements of stac across function calls.
    Stack *stac = nullptr, *stac1 = nullptr;
    // Taking in input number of elements in the stack.
    int n;
    cin >> n;
    // Taking in input elements of the stack and pushing it into the stack.
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        stac = push(stac, x);
    }
    // Calling the sort function and printing the final output.
    sort(stac, stac1, n);
    print(stac);
}