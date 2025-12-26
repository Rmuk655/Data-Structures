#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define MAX_SIZE 100

struct Queue
{
    int front;
    int back;
    int array[MAX_SIZE];
};

bool isEmpty(struct Queue queue)
{
    return queue.back == queue.front - 1;
}

void enqueue(struct Queue *queue, double item)
{
    if (queue == NULL)
    {
        printf("Queue is not initialized\n");
        return;
    }
    if (queue->back > MAX_SIZE - 1)
    {
        printf("Queue overflow\n");
        return;
    }
    queue->back++;
    queue->array[queue->back] = item;
}

double dequeue(struct Queue *queue)
{
    if (queue == NULL)
    {
        printf("Queue is not initialized\n");
        return -1;
    }
    if (isEmpty(*queue))
    {
        printf("Queue underflow\n");
        return -1;
    }
    double item = queue->array[queue->front];
    queue->front++;
    return item;
}

void swapij(struct Queue *queue, int i, int j)
{
    if (queue == NULL || isEmpty(*queue) || i < queue->front || i >= queue->back)
    {
        printf("Queue is not initialized or index out of bounds\n");
        return;
    }
    double temp = queue->array[i];
    queue->array[i] = queue->array[j];
    queue->array[j] = temp;
}
void reverse(struct Queue *queue, int num)
{
    if (queue == NULL || isEmpty(*queue))
    {
        printf("Queue is not initialized or empty\n");
        return;
    }
    for (int i = 0; i < num / 2; i++)
    {
        swapij(queue, queue->front + i, queue->front + num - 1 - i);
    }
}

void printQueue(struct Queue *queue)
{
    if (isEmpty(*queue))
    {
        printf("Queue is empty\n");
        return;
    }
    for (int i = queue->front; i <= queue->back; i++)
    {
        printf("%d ", queue->array[i]);
    }
    printf("\n");
}

void basictests()
{
    // Check for reverse function using assert
    // Case 1: Reverse first 3 elements in a queue of 5 elements
    // Initial queue: 10, 20, 30, 40, 50
    // After reversing first 3 elements: 30, 20, 10, 40, 50
    struct Queue queue;
    queue.front = 0;
    queue.back = -1;
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);
    enqueue(&queue, 50);
    reverse(&queue, 3);
    assert(queue.array[0] == 30);
    assert(queue.array[1] == 20);
    assert(queue.array[2] == 10);
    assert(queue.array[3] == 40);
    assert(queue.array[4] == 50);

    // Case 2: Reverse first 5 elements in a queue of 5 elements
    //  Initial queue: 1, 2, 3, 4, 5
    //  After reversing first 5 elements: 5, 4, 3, 2, 1
    struct Queue queue2;
    queue2.front = 0;
    queue2.back = -1;
    enqueue(&queue2, 1);
    enqueue(&queue2, 2);
    enqueue(&queue2, 3);
    enqueue(&queue2, 4);
    enqueue(&queue2, 5);
    reverse(&queue2, 5);
    assert(queue2.array[0] == 5);
    assert(queue2.array[1] == 4);
    assert(queue2.array[2] == 3);
    assert(queue2.array[3] == 2);
    assert(queue2.array[4] == 1);

    // Case 3: Reverse first 0 elements in a queue of 5 elements
    // Initial queue: 1, 2, 3, 4, 5
    // After reversing first 0 elements: 1, 2, 3, 4, 5
    struct Queue queue3;
    queue3.front = 0;
    queue3.back = -1;
    enqueue(&queue3, 1);
    enqueue(&queue3, 2);
    enqueue(&queue3, 3);
    enqueue(&queue3, 4);
    enqueue(&queue3, 5);
    reverse(&queue3, 0);
    assert(queue3.array[0] == 1);
    assert(queue3.array[1] == 2);
    assert(queue3.array[2] == 3);
    assert(queue3.array[3] == 4);
    assert(queue3.array[4] == 5);

    // Case 4: Reverse first 1 element in a queue of 5 elements
    // Initial queue: 1, 2, 3, 4, 5
    // After reversing first 1 element: 1, 2, 3, 4, 5
    struct Queue queue4;
    queue4.front = 0;
    queue4.back = -1;
    enqueue(&queue4, 1);
    enqueue(&queue4, 2);
    enqueue(&queue4, 3);
    enqueue(&queue4, 4);
    enqueue(&queue4, 5);
    reverse(&queue4, 1);
    assert(queue4.array[0] == 1);
    assert(queue4.array[1] == 2);
    assert(queue4.array[2] == 3);
    assert(queue4.array[3] == 4);
    assert(queue4.array[4] == 5);
    printf("All basic tests passed!\n");
}

void advancedtests()
{
    // Case 1: Reverse first 3 elements in a queue of 5 elements with negative numbers
    struct Queue queue;
    queue.front = 0;
    queue.back = -1;
    enqueue(&queue, -10);
    enqueue(&queue, -20);
    enqueue(&queue, -30);
    enqueue(&queue, -40);
    enqueue(&queue, -50);
    reverse(&queue, 3);
    assert(queue.array[0] == -30);
    assert(queue.array[1] == -20);
    assert(queue.array[2] == -10);
    assert(queue.array[3] == -40);
    assert(queue.array[4] == -50);

    // Case 2: Reverse first 5 elements in a queue of 5 elements with mixed numbers
    struct Queue queue2;
    queue2.front = 0;
    queue2.back = -1;
    enqueue(&queue2, 1);
    enqueue(&queue2, -2);
    enqueue(&queue2, 3);
    enqueue(&queue2, -4);
    enqueue(&queue2, 5);
    reverse(&queue2, 5);
    assert(queue2.array[0] == 5);
    assert(queue2.array[1] == -4);
    assert(queue2.array[2] == 3);
    assert(queue2.array[3] == -2);
    assert(queue2.array[4] == 1);

    printf("All advanced tests passed!\n");
}

int main()
{
    int size, val = 0, k;
    printf("Enter the size of the queue (1 to %d): ", MAX_SIZE);
    scanf("%d", &size);
    if (size <= 0 || size > MAX_SIZE)
    {
        printf("Invalid size\n");
        return 1;
    }
    struct Queue queue;
    queue.front = 0;
    queue.back = -1;
    printf("Enter %d elements for the queue:\n", size);
    for (int i = 0; i < size; i++)
    {
        printf("Enter Element %d: ", i + 1);
        scanf("%d", &val);
        enqueue(&queue, val);
    }
    printf("Enter the number of queue elements to be reversed: ");
    scanf("%d", &k);
    if (k < 0 || k > size)
    {
        printf("Invalid k value\n");
        return 1;
    }
    printQueue(&queue);
    reverse(&queue, k);
    printQueue(&queue);
    basictests();
    advancedtests();
}