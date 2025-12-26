#include <iostream>
#include <vector>

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

// Enqueue function to add an element into the Queue using 2 Stacks (Push function)
void enqueue(Stack &stack1, Stack &stack2, int ele)
{
    Push(stack1, ele);
}

// Dequeue function to remove an element into the Queue using 2 Stacks (Push function)
int dequeue(Stack &stack1, Stack &stack2)
{
    // Checking if stack2 is empty so we can empty all elements of stack1 into stack in the reverse order.
    if (isEmpty(stack2))
    {
        // We now empty all elements of stack1 into stack in the reverse order.
        while (!isEmpty(stack1))
        {
            // Pop(stack1) gives the last element of stack1 and inserting that in order into stack2 effectively reverses stack1 and adds it into stack2.
            Push(stack2, Pop(stack1));
        }
    }
    // We return the deleted element to print it in the main function.
    return Pop(stack2);
}

int main()
{
    // We initialize the 2 stacks used to implement a Queue data structure.
    Stack stack1, stack2;
    int arr1[SIZE_STACK], arr2[SIZE_STACK];
    stack1.arr = arr1;
    stack1.top = 0;
    stack2.arr = arr2;
    stack2.top = 0;
    // Taking input for the operation to be performed on the Queue data structure.
    int op;
    cin >> op;
    // This loop runs till the user input for op = 3 where it breaks.
    while (op != 3)
    {
        // op == 1 is for enqueuing where we take the element to be enqueued as an input and call the enqueue function defined above on the 2 stacks, element.
        if (op == 1)
        {
            int ele;
            cin >> ele;
            enqueue(stack1, stack2, ele);
        }
        // op == 2 is for dequeueing - removing the top element of Queue using the 2 Stacks.
        else if (op == 2)
        {
            // Checking for the case where both the Stacks used for implementation are empty indicating that the Queue is also empty.
            if (isEmpty(stack2) && isEmpty(stack1))
            {
                cout << "Queue is empty." << endl;
                // We continue taking input for the operation, but skip the current operation of dequeueing.
                cin >> op;
                continue;
            }
            // We print the dequeued element.
            cout << "Dequeued: " << dequeue(stack1, stack2) << endl;
        }
        // Handling invalid vase when user inputs an integer other than 1, 2, 3 as the op value.
        else
        {
            // We print the following error message and prompt the user to re-enter a correct value for the variable op.
            cout << "Invalid value of operation! Enter a valid value for operation 1: Enqueue, 2: Dequeue, 3: Exit." << endl;
        }
        cin >> op;
    }
}