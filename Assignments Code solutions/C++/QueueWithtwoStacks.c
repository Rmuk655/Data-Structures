#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//Problem 3: Queue Using Two Stacks
//This implements a queue using two stacks with optimal time complexity:
//Stack1: Used for enqueue operations
//Stack2: Used for dequeue operations
//Enqueue: O(1) - simply push to stack1
//Dequeue: Amortized O(1) - elements are moved from stack1 to stack2 only when needed
// Stack structure
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// Queue using two stacks
typedef struct {
    Stack stack1; // For enqueue operations
    Stack stack2; // For dequeue operations
} QueueUsingStacks;

// Stack operations
void initStack(Stack* s) {
    s->top = -1;
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

int isStackFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack* s, int value) {
    if (!isStackFull(s)) {
        s->data[++s->top] = value;
    }
}

int pop(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->data[s->top--];
    }
    return -1; // Error case
}

// Queue operations
void initQueue(QueueUsingStacks* q) {
    initStack(&q->stack1);
    initStack(&q->stack2);
}

// Enqueue operation - O(1) time complexity
void enqueue(QueueUsingStacks* q, int value) {
    push(&q->stack1, value);
    printf("Enqueued: %d\n", value);
}

// Dequeue operation - Amortized O(1) time complexity
int dequeue(QueueUsingStacks* q) {
    // If both stacks are empty, queue is empty
    if (isStackEmpty(&q->stack1) && isStackEmpty(&q->stack2)) {
        printf("Queue is empty\n");
        return -1;
    }
    
    // If stack2 is empty, move all elements from stack1 to stack2
    if (isStackEmpty(&q->stack2)) {
        while (!isStackEmpty(&q->stack1)) {
            push(&q->stack2, pop(&q->stack1));
        }
    }
    
    // Pop from stack2
    int value = pop(&q->stack2);
    printf("Dequeued: %d\n", value);
    return value;
}

// Function to print the current state of the queue
void printQueue(QueueUsingStacks* q) {
    if (isStackEmpty(&q->stack1) && isStackEmpty(&q->stack2)) {
        printf("Queue is empty\n");
        return;
    }
    
    printf("Current Queue (front to rear): ");
    
    // Print elements in stack2 (these are in correct order for dequeue)
    // We need to print them in reverse order since stack2 has front elements at top
    if (!isStackEmpty(&q->stack2)) {
        // Print stack2 elements from bottom to top (front to middle of queue)
        for (int i = 0; i <= q->stack2.top; i++) {
            printf("%d ", q->stack2.data[i]);
        }
    }
    
    // Print elements in stack1 (these need to be reversed for correct queue order)
    // We need to print them from top to bottom (middle to rear of queue)
    if (!isStackEmpty(&q->stack1)) {
        for (int i = q->stack1.top; i >= 0; i--) {
            printf("%d ", q->stack1.data[i]);
        }
    }
    
    printf("\n");
}

// Alternative more detailed print function showing internal stack states
void printQueueDetailed(QueueUsingStacks* q) {
    printf("=== Queue State ===\n");
    
    // Print Stack1 state
    printf("Stack1 (newest at top): ");
    if (isStackEmpty(&q->stack1)) {
        printf("Empty");
    } else {
        for (int i = q->stack1.top; i >= 0; i--) {
            printf("%d ", q->stack1.data[i]);
        }
    }
    printf("\n");
    
    // Print Stack2 state
    printf("Stack2 (oldest at top): ");
    if (isStackEmpty(&q->stack2)) {
        printf("Empty");
    } else {
        for (int i = q->stack2.top; i >= 0; i--) {
            printf("%d ", q->stack2.data[i]);
        }
    }
    printf("\n");
    
    // Print logical queue order
    printf("Logical Queue (front->rear): ");
    if (isStackEmpty(&q->stack1) && isStackEmpty(&q->stack2)) {
        printf("Empty");
    } else {
        // Elements in stack2 are in correct dequeue order (front elements at top)
        if (!isStackEmpty(&q->stack2)) {
            for (int i = 0; i <= q->stack2.top; i++) {
                printf("%d ", q->stack2.data[i]);
            }
        }
        // Elements in stack1 need to be reversed to show queue order
        if (!isStackEmpty(&q->stack1)) {
            for (int i = q->stack1.top; i >= 0; i--) {
                printf("%d ", q->stack1.data[i]);
            }
        }
    }
    printf("\n==================\n");
}

int main() {
    QueueUsingStacks q;
    initQueue(&q);
    
    int operation, value;
    
    while (1) {
        printf("Enter the operation 1. Enqueue 2. Dequeue 3. print 4. Exit \n");
        scanf("%d", &operation);
        
        switch (operation) {
            case 1: // Enqueue
                printf("Enter the value to be added to the queue \n");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
                
            case 2: // Dequeue
                dequeue(&q);
                break;
                

            case 3: // print
                printQueueDetailed(&q);
                break;

            case 4: // Exit
                printf("Exiting...\n");
                return 0;

                
            default:
                printf("Invalid operation\n");
                break;
        }
    }
    
    return 0;
}

/*
Time Complexity Analysis:

1. Enqueue Operation:
   - Time Complexity: O(1)
   - We simply push the element to stack1

2. Dequeue Operation:
   - Worst Case: O(n) - when stack2 is empty and we need to move all elements from stack1
   - Best Case: O(1) - when stack2 is not empty
   - Amortized Time Complexity: O(1)
   - Each element is moved at most once from stack1 to stack2

3. Space Complexity: O(n) where n is the number of elements in the queue

The amortized analysis shows that even though individual dequeue operations might take O(n) time,
the average time per operation over a sequence of operations is O(1).
*/