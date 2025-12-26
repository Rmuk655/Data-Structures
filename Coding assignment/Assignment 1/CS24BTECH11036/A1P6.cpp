#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define SIZE_STACK 100

// Time complexity = O(1) for enqueue and O(n) for dequeue.
// Space complexity = O(n).

struct node
{
    int data;
    node *prev;
    node *next;
};
// Using a struct Stack to store it's top element's index + 1.
struct Stack
{
    node *head;
    node *middle;
    int top;
};

// Function to check if the Stack is empty or not by checking if it's top value is 0 which means the no of elements in the stack = 0.
bool isEmpty(Stack *stack)
{
    if (stack->top == 0)
    {
        return true;
    }
    return false;
}

// Function to check if the Stack is full or not by checking if it's top value is SIZE_STACK which means the no of elements in
// the stack = max no of possible elements in the stack = SIZE_STACK.
bool isFull(Stack *stack)
{
    if (stack->top == SIZE_STACK)
    {
        return true;
    }
    return false;
}

// Function to insert an element into the stack.
// Time complexity = O(1)
// Space complexity = O(1)
void Push(Stack *&stack, int ele)
{
    // Checking if the stack is full as we cannot any element into a full stack.
    if (isFull(stack))
    {
        cout << "Cannot insert an element into a full stack." << endl;
        return;
    }
    // We create a new node temp and initialize it with data as ele, next as nullptr and prev as stack->head.
    struct node *temp = new node();
    temp->data = ele;
    temp->next = nullptr;
    temp->prev = stack->head;
    // If the stack is not full, we add the integer ele at the top's position and increase stack.top by 1 as we have added an
    // element to the stack.
    if (stack->head != nullptr)
    {
        stack->head->next = temp;
    }
    stack->head = temp;
    stack->top++;
    // We update the middle pointer in 2 cases:
    // Case 1: stack->top == 1 which implies that we have just added an element to an empty stack.
    // Hence, we set stack->middle to the first element of the stack.
    if (stack->top == 1)
    {
        stack->middle = temp;
    }
    // Case 2: stack->top % 2 == 1 which implies that we have just added an element to a stack and now it has an odd no of elements.
    // Hence, we set stack->middle to the next element of the current middle element of the stack.
    else if (stack->top % 2 == 1)
    {
        stack->middle = stack->middle->next;
    }
}

// Function to delete an element from the stack.
// Time complexity = O(1)
// Space complexity = O(1)
int Pop(Stack *&stack)
{
    // Checking if the stack is empty as we cannot remove an element from an empty stack.
    if (isEmpty(stack))
    {
        // cout << "Cannot delete an element from an empty stack." << endl;
        return INT_MIN; // Returning INT_MIN means that we have got an underflow error which we print in the main function.
    }
    // When the stack is not empty, we decrease stack.top by 1 as we are removing an element.
    // We update the head, next, top etc accordingly.
    struct node *topnode = stack->head;
    int ele = topnode->data;
    stack->head = topnode->prev;
    if (stack->head != nullptr)
    {
        stack->head->next = nullptr;
    }
    stack->top--;
    // If stack->top % 2 == 0 which implies that we have just deleted an element to a stack and now it has an even no of elements.
    // Hence, we set stack->middle to the previous element of the current middle element of the stack.
    // Note that to access stack->middle->prev, stack->middle must not be nullptr.
    if (stack->top % 2 == 0 && stack->middle != nullptr)
    {
        stack->middle = stack->middle->prev;
    }
    // We delete the top element and return it's value which we had stored in the integer ele.
    delete topnode;
    return ele;
}

// Time complexity = O(1)
// Space complexity = O(1)
// Function to find the middle element of a stack.
int findMiddle(Stack *&stac)
{
    // We cannot find a middle element from an empty stack. Hence we return INT_MIN and print Stack Empty in the main.
    if (isEmpty(stac))
    {
        return INT_MIN;
    }
    // We directly return the middle element's data using the stac->middle pointer we had stored above.
    return stac->middle->data;
}

// Time complexity = O(1)
// Space complexity = O(1)
// Function to delete the middle element of a stack.
int deleteMiddle(Stack *&stac)
{
    // We cannot delete a middle element from an empty stack. Hence we return INT_MIN and print Stack Empty in the main.
    if (isEmpty(stac))
    {
        return INT_MIN;
    }
    // If head == middle, then the stac has only 1 element which implies we have to delete the head
    // and reinitialize it to nullptr and its attributes to appropriate values.
    else if (stac->head == stac->middle)
    {
        // We store the data in mid_data to return it and delete the head pointer.
        int mid_data = stac->head->data;
        delete stac->head;
        // Reinitializing the head of the stack and its attributes.
        stac->head = nullptr;
        stac->middle = nullptr;
        stac->top--;
        return mid_data;
    }
    // We store the middle element in middlenode to delete it and its data in mid_data to return it.
    struct node *middlenode = stac->middle;
    int mid_data = middlenode->data;
    // We modify the prev, next pointers of the middle node (if they exist) to accommodate for the deleted node.
    if (middlenode->prev != nullptr)
    {
        middlenode->prev->next = middlenode->next;
    }
    if (middlenode->next != nullptr)
    {
        middlenode->next->prev = middlenode->prev;
    }
    // We reduce stac->top as we are deleting an element.
    stac->top--;
    // If stac->top is odd, which means we deleted an element from a stack with even number of elements,
    // we have to modify the middle pointer to point to the next element.
    if (stac->top % 2 == 1)
    {
        stac->middle = stac->middle->next;
    }
    // If stac->top is even, which means we deleted an element from a stack with odd number of elements,
    // we have to modify the middle pointer to point to the prev element.
    else
    {
        stac->middle = stac->middle->prev;
    }
    // We delete the middle element and return the data which was stored in it.
    delete middlenode;
    return mid_data;
}

// // Test function to check the validity of the code.
// void test()
// {
//     Stack *st = new Stack();
//     st->head = nullptr;
//     st->middle = nullptr;
//     st->top = 0;

//     Push(st, 10);
//     Push(st, 20);
//     Push(st, 30);
//     Push(st, 40);
//     Push(st, 50);

//     cout << "Middle: " << findMiddle(st) << endl;           // 30
//     cout << "Deleted middle: " << deleteMiddle(st) << endl; // 30
//     cout << "New middle: " << findMiddle(st) << endl;       // 20

//     cout << "Popped: " << Pop(st) << endl;            // 50
//     cout << "Popped: " << Pop(st) << endl;            // 40
//     cout << "Middle now: " << findMiddle(st) << endl; // 20

//     deleteMiddle(st);
//     cout << "Middle after deleting: " << findMiddle(st) << endl; // 10
//     Pop(st);
//     Pop(st);
//     cout << "Middle of empty stack: " << findMiddle(st) << endl; // INT_MIN
// }

int main()
{
    // test();
    // Creating a new stack stac and initializing its head, middle, top accordingly.
    Stack *stac = new Stack();
    stac->head = nullptr;
    stac->middle = nullptr;
    stac->top = 0;
    // We take an input for the number of operations to be performed in the integer n.
    int n;
    cin >> n;
    while (n > 0)
    {
        // For each operation, we take an input to identify the operation we have to do.
        int op;
        cin >> op;
        // op == 1 refers to the push operation.
        if (op == 1)
        {
            // We take an input for the element to be pushed onto the stack.
            int ele;
            cin >> ele;
            Push(stac, ele);
        }
        // op == 2 refers to the pop operation.
        else if (op == 2)
        {
            // We pop the element and check for the case if the return value == INT_MIN which implies that the stack is empty.
            int x = Pop(stac);
            if (x == INT_MIN)
            {
                cout << "Stack Underflow" << endl;
            }
            // Else we print the popped element.
            else
            {
                cout << x << endl;
            }
        }
        // op == 3 refers to the findMiddle operation.
        else if (op == 3)
        {
            // We find the middle element and check for the case if the return value == INT_MIN which implies that the stack is empty.
            int x = findMiddle(stac);
            if (x == INT_MIN)
            {
                cout << "Stack Empty" << endl;
            }
            // Else we print the middle element.
            else
            {
                cout << x << endl;
            }
        }
        // op == 3 refers to the deleteMiddle operation.
        else if (op == 4)
        {
            // We delete the middle element and check for the case if the return value == INT_MIN which implies that the stack is empty.
            int x = deleteMiddle(stac);
            if (x == INT_MIN)
            {
                cout << "Stack Empty" << endl;
            }
            // Else we print the deleted middle element.
            else
            {
                cout << x << endl;
            }
        }
        n--;
    }
}