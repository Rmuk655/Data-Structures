#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define MAX_SIZE 1000

struct Stack
{
    int top;
    int array[MAX_SIZE];
};

bool isEmpty(struct Stack stack)
{
    return stack.top == -1;
}

void push(struct Stack *stack, int item)
{
    if (stack == NULL)
    {
        printf("Stack is not initialized\n");
        return;
    }
    if (stack->top == MAX_SIZE - 1)
    {
        printf("Stack overflow\n");
        return;
    }
    stack->top++;
    stack->array[stack->top] = item;
}

int pop(struct Stack *stack)
{
    if (stack == NULL)
    {
        printf("Stack is not initialized\n");
        return -1;
    }
    if (isEmpty(*stack))
    {
        printf("Stack underflow\n");
        return -1;
    }
    int item = stack->array[stack->top];
    stack->top--;
    return item;
}

void moveStack(struct Stack *stack, struct Stack *rev_stack)
{
    while (!isEmpty(*stack))
    {
        int item = pop(stack);
        push(rev_stack, item);
    }
}

struct Queue
{
    struct Stack enqueue_stack;
    struct Stack dequeue_stack;
};

void enqueue(struct Queue *queue, int item)
{
    if (queue == NULL)
    {
        printf("Queue is not initialized\n");
        return;
    }
    push(&queue->enqueue_stack, item);
}

int dequeue(struct Queue *queue)
{
    if (queue == NULL)
    {
        printf("Queue is not initialized\n");
        return -1;
    }
    if (isEmpty(queue->dequeue_stack))
    {
        moveStack(&queue->enqueue_stack, &queue->dequeue_stack);
    }
    pop(&queue->dequeue_stack);
}

void printQueue(struct Queue *queue)
{
    if (isEmpty(queue->enqueue_stack) && isEmpty(queue->dequeue_stack))
    {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    for (int i = queue->dequeue_stack.top; i >= 0; i--)
    {
        printf("%d ", queue->dequeue_stack.array[i]);
    }
    for (int i = 0; i <= queue->enqueue_stack.top; i++)
    {
        printf("%d ", queue->enqueue_stack.array[i]);
    }
    printf("\n");
}

void test_basic_sequence()
{
    struct Queue queue;
    queue.enqueue_stack.top = -1;
    queue.dequeue_stack.top = -1;
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);
    assert(dequeue(&queue) == 1);
    assert(dequeue(&queue) == 2);
    assert(dequeue(&queue) == 3);
    printf("test_basic_sequence passed\n");
}
void test_alternating_ops()
{
    struct Queue queue;
    queue.enqueue_stack.top = -1;
    queue.dequeue_stack.top = -1;

    enqueue(&queue, 5);
    assert(dequeue(&queue) == 5);
    enqueue(&queue, 10);
    enqueue(&queue, 15);
    assert(dequeue(&queue) == 10);
    enqueue(&queue, 20);
    assert(dequeue(&queue) == 15);
    assert(dequeue(&queue) == 20);
    printf("test_alternating_ops passed\n");
}

void test_empty_dequeue()
{
    struct Queue queue;
    queue.enqueue_stack.top = -1;
    queue.dequeue_stack.top = -1;

    assert(dequeue(&queue) == -1); // Empty
    enqueue(&queue, 42);
    assert(dequeue(&queue) == 42);
    assert(dequeue(&queue) == -1); // Empty again
    printf("test_empty_dequeue passed\n");
}

void test_long_sequence()
{
    struct Queue queue;
    queue.enqueue_stack.top = -1;
    queue.dequeue_stack.top = -1;

    for (int i = 1; i <= 1000; i++)
    {
        enqueue(&queue, i);
    }
    for (int i = 1; i <= 1000; i++)
    {
        assert(dequeue(&queue) == i);
    }
    assert(dequeue(&queue) == -1); // Empty now
    printf("test_long_sequence passed\n");
}

void test_single_element()
{
    struct Queue queue;
    queue.enqueue_stack.top = -1;
    queue.dequeue_stack.top = -1;

    enqueue(&queue, 999);
    assert(dequeue(&queue) == 999);
    assert(dequeue(&queue) == -1); // Empty now
    printf("test_single_element passed\n");
}

void test_enqueue_after_emptying()
{
    struct Queue queue;
    queue.enqueue_stack.top = -1;
    queue.dequeue_stack.top = -1;

    enqueue(&queue, 100);
    assert(dequeue(&queue) == 100);
    enqueue(&queue, 200);
    enqueue(&queue, 300);
    assert(dequeue(&queue) == 200);
    assert(dequeue(&queue) == 300);
    printf("test_enqueue_after_emptying passed\n");
}

void given_tests()
{
    // Case 1
    struct Queue queue;
    queue.enqueue_stack.top = -1;
    queue.dequeue_stack.top = -1;
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    assert(dequeue(&queue) == 10); // Remove 10
    enqueue(&queue, 30);
    assert(dequeue(&queue) == 20); // Remove 20
    assert(dequeue(&queue) == 30); // Remove 30

    // Case 2
    struct Queue queue2;
    queue2.enqueue_stack.top = -1;
    queue2.dequeue_stack.top = -1;
    assert(dequeue(&queue2) == -1); // Empty dequeue
    printf("given_tests passed\n");
}
void tests()
{
    test_basic_sequence();
    test_alternating_ops();
    test_empty_dequeue();
    test_long_sequence();
    test_single_element();
    test_enqueue_after_emptying();
    given_tests();
    printf("All tests passed!\n");
}

int main()
{
    struct Stack stac;
    stac.top = -1;
    struct Stack rev_stack;
    rev_stack.top = -1;
    struct Queue queue;
    queue.enqueue_stack = stac;
    queue.dequeue_stack = rev_stack;
    char s[MAX_SIZE];
    int n = 0;
    while (n != 3)
    {
        printf("Enter 1 to push (along with the number), 2 to pop, or 3 to exit: ");
        fgets(s, sizeof(s), stdin);
        n = atoi(strtok(s, " "));
        if (n < 1 || n > 3)
        {
            printf("Invalid input. Please enter 1, 2, or 3.\n");
            continue;
        }
        else if (n == 1)
        {
            int value = atoi(strtok(NULL, " ")); // Convert string to integer
            enqueue(&queue, value);
        }
        else if (n == 2)
        {
            int value = dequeue(&queue);
            printf("Dequeued: %d\n", value);
        }
        printQueue(&queue);
    }
    tests();
}