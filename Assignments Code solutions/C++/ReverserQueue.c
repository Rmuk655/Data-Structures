#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//Problem 2: Reverse First K Elements of Queue
// Stack structure for reversing
//This solution uses an auxiliary stack to reverse the first k elements:
//Dequeue first k elements and push them onto a stack
//Pop from stack and enqueue back (this reverses the order)
//Move the remaining elements to maintain queue order

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// Queue structure
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// Stack operations
void initStack(Stack* s) {
    s->top = -1;
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    s->data[++s->top] = value;
}

int pop(Stack* s) {
    return s->data[s->top--];
}

// Queue operations
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isQueueEmpty(Queue* q) {
    return q->size == 0;
}
//implement a circular queue (also called a ring buffer)

void enqueue(Queue* q, int value) {
    //When rear reaches MAX_SIZE-1, the next increment wraps it back to 0 
    q->rear = (q->rear + 1) % MAX_SIZE; 
    q->data[q->rear] = value;
    q->size++;
}

int dequeue(Queue* q) {
    int value = q->data[q->front];
    //When front reaches MAX_SIZE-1, the next increment wraps it back to 0
    q->front = (q->front + 1) % MAX_SIZE; //ensures that indices wrap around:
    q->size--;
    return value;
}

// Function to reverse first k elements of queue
void reverseFirstK(Queue* q, int k) {
    if (k <= 0 ) {
        return;
    }
    
    if (k > q->size)
        k = q-> size;
    Stack s;
    initStack(&s);
    
    // Step 1: Dequeue first k elements and push to stack
    for (int i = 0; i < k; i++) {
        push(&s, dequeue(q));
    }
    
    // Step 2: Pop from stack and enqueue back to queue
    while (!isStackEmpty(&s)) {
        enqueue(q, pop(&s));
    }
    
    // Step 3: Move remaining (n-k) elements from front to back
    int remaining = q->size - k;
    for (int i = 0; i < remaining; i++) {
        enqueue(q, dequeue(q));
    }
}

// Function to print queue
void printQueue(Queue* q) {
    int temp_front = q->front;
    for (int i = 0; i < q->size; i++) {
        printf("%d", q->data[temp_front]);
        if (i < q->size - 1) {
            printf(" ");
        }
        temp_front = (temp_front + 1) % MAX_SIZE;
    }
    printf("\n");
}

int main() {
    int n, k;
    Queue q;
    initQueue(&q);
    
    // Read number of elements
    printf("How many Elements do you have in your queue?\n");
    scanf("%d", &n);
    
    // Read queue elements
    printf("Enter the Elements of the queue with spaces between each element\n");
    for (int i = 0; i < n; i++) {
        int element;
        scanf("%d", &element);
        enqueue(&q, element);
    }
    
    // Read k
    printf("Till which element do you want to reverse?\n"); 
    scanf("%d", &k);
    
    // Reverse first k elements
    reverseFirstK(&q, k);
    
    // Print the modified queue
    printQueue(&q);
    
    return 0;
}