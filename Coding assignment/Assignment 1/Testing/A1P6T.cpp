#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define SIZE_STACK 100

// Time complexity = O(1) for enqueue and O(n) for dequeue.
// Space complexity = O(n).
// Using a struct Stack to store it's top element's index + 1.
struct Stack
{
    int *arr;
    int top;
};

// Function to check if the Stack is empty or not by checking if it's top value is 0 which means the no of elements in the stack = 0.
bool isEmpty(Stack stack)
{
    if (stack.top == 0)
    {
        return true;
    }
    return false;
}

// Function to check if the Stack is full or not by checking if it's top value is SIZE_STACK which means the no of elements in the stack
// = max no of possible elements in the stack = SIZE_STACK.
bool isFull(Stack stack)
{
    if (stack.top == SIZE_STACK)
    {
        return true;
    }
    return false;
}

// Function to insert an element into the stack.
void Push(Stack &stack, int ele)
{
    // Checking if the stack is full as we cannot any element into a full stack.
    if (isFull(stack))
    {
        cout << "Cannot insert an element into a full stack." << endl;
        return;
    }
    // If the stack is not full, we add the integer ele at the top's position and increase stack.top by 1 as we have added an element to the stack.
    *(stack.arr + stack.top) = ele;
    stack.top++;
}

// Function to delete an element from the stack.
int Pop(Stack &stack)
{
    // Checking if the stack is empty as we cannot remove an element from an empty stack.
    if (isEmpty(stack))
    {
        // cout << "Cannot delete an element from an empty stack." << endl;
        return INT_MIN; // Returning INT_MIN means that we have got an underflow error.
    }
    // Normal case when the stack is not empty, we decrease stack.top by 1 as we are removing an element.
    int x = *(stack.arr + stack.top - 1);
    stack.top--;
    return x;
}

int findMiddle(Stack &stac)
{
    if (isEmpty(stac))
    {
        return INT_MIN;
    }
    return stac.arr[(stac.top - 1) / 2];
}

int deleteMiddle(Stack &stac)
{
    if (isEmpty(stac))
    {
        return INT_MIN;
    }
    int x = stac.arr[(stac.top - 1) / 2];
    for (int i = (stac.top - 1) / 2; i < stac.top - 1; i++)
    {
        stac.arr[i] = stac.arr[i + 1];
    }
    Pop(stac);
    return x;
}

void test()
{
    Stack stac;
    stac.arr = new int[SIZE_STACK];
    stac.top = 0;

    cout << "=== Test Case 1: Push elements and find middle ===" << endl;
    Push(stac, 10);
    Push(stac, 20);
    Push(stac, 30);
    Push(stac, 40);
    Push(stac, 50);
    cout << "Expected middle: 30, Got: " << findMiddle(stac) << endl;

    cout << "\n=== Test Case 2: Delete middle ===" << endl;
    int mid = deleteMiddle(stac);
    cout << "Deleted middle (expected 30): " << mid << endl;
    cout << "New middle (expected 20): " << findMiddle(stac) << endl;

    cout << "\n=== Test Case 3: Pop elements ===" << endl;
    cout << "Pop (expected 50): " << Pop(stac) << endl;
    cout << "Pop (expected 40): " << Pop(stac) << endl;
    cout << "Pop (expected 20): " << Pop(stac) << endl;
    cout << "Pop (expected 10): " << Pop(stac) << endl;
    cout << "Pop from empty (expected Stack Underflow / INT_MIN): " << Pop(stac) << endl;

    cout << "\n=== Test Case 4: Middle operations on small stacks ===" << endl;
    Push(stac, 5);
    Push(stac, 15);
    cout << "Middle (expected 5): " << findMiddle(stac) << endl;
    deleteMiddle(stac);
    cout << "Middle after delete (expected 15): " << findMiddle(stac) << endl;

    cout << "All test cases passed" << endl;
    delete[] stac.arr; // free memory
}

int main()
{
    test();
    Stack stac;
    stac.top = 0;
    int n;
    cin >> n;
    while (n > 0)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int ele;
            cin >> ele;
            Push(stac, ele);
        }
        else if (op == 2)
        {
            int x = Pop(stac);
            if (x == INT_MIN)
            {
                cout << "Stack Underflow" << endl;
            }
            else
            {
                cout << x << endl;
            }
        }
        else if (op == 3)
        {
            int x = findMiddle(stac);
            if (x == INT_MIN)
            {
                cout << "Stack Empty" << endl;
            }
            else
            {
                cout << x << endl;
            }
        }
        else if (op == 4)
        {
            int x = deleteMiddle(stac);
            if (x == INT_MIN)
            {
                cout << "Stack Empty" << endl;
            }
            else
            {
                cout << x << endl;
            }
        }
        n--;
    }
}