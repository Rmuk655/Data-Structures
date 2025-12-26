#include <iostream>
#include <vector>

using namespace std;

// Time complexity = O(k) for the rev_k function while it is O(1) for both enqueue and dequeue operations.
// Space complexity = O(n).
//  Using a struct Queue to store it's properties like head, tail index position.
struct Queue
{
    int *arr;
    int length;
    int head;
    int tail;
};

// This function is used to check if the queue is full or not by checking 2 cases
// a)If the number of elements = queue.length
// b)queue.tail + 1 and queue.head point to the same index meaning the array has wrapped around itself.
bool QueueFull(Queue queue)
{
    if ((queue.head == 1 && queue.tail == queue.length) || (queue.tail + 1 == queue.head))
    {
        return true;
    }
    return false;
}

// This function is used to check if the queue is full or not by checking if head and tail indices match.
bool QueueEmpty(Queue queue)
{
    if (queue.head == queue.tail)
    {
        return true;
    }
    return false;
}

// Function for adding elements to the queue - enqueuing
void enqueue(Queue &queue, int ele)
{
    // Basic check to see if the queue is full or not, as we cannot add elements to a full Queue.
    if (QueueFull(queue))
    {
        cout << "Overflow Error! Cannot insert element into a full Queue." << endl;
        return;
    }
    // If the tail index reaches the end, we set it to 1 so that it can wrap around the array to use up the whole space in the array.
    if ((queue.tail == queue.length) && (queue.tail - queue.head < queue.length))
    {
        *(queue.arr + (queue.tail)) = ele;
        queue.tail = 1;
        return;
    }
    // Normal case when queue.tail keeps increasing as we keep enqueueing elements in the array (queue).
    *(queue.arr + (queue.tail)) = ele;
    queue.tail++;
}

// Function for removing elements to the queue - dequeuing
int dequeue(Queue &queue)
{
    // Basic check to see if the queue is empty or not as we cannot remove elements from an empty queue.
    if (QueueEmpty(queue))
    {
        cout << "Underflow Error! Cannot delete element from an empty Queue." << endl;
        return INT_MIN; // By returning INT_MIN, the function tells us there was an error dequeuing the element.
    }
    // Finding the element to dequeue and storing it in the variable x.
    int x = *(queue.arr + (queue.head));
    // If the head index reaches the end of the array, then we wrap it around the array by setting it to 1.
    if (queue.head == queue.length)
    {
        queue.head = 1;
        return x;
    }
    // Normal case when we delete the element and add 1 to the queue.head index.
    queue.head++;
    return x;
}

void rev_k(Queue &queue, int k)
{
    // Handling edge cases which are not possible.
    if (k > queue.length || k < 0)
    {
        cout << "The number of elements to be reversed cannot be greater than the total number of elements and must be positive. No change in the array." << endl;
        return;
    }
    // Handling trivial edge cases.
    else if (k == queue.length || k == 0 || k == 1)
    {
        return;
    }
    // Initializing the struct Queue queue1.
    int arr1[k];
    Queue queue1;
    queue1.arr = arr1;
    queue1.head = 0;
    queue1.tail = 0;
    queue1.length = k + 1;
    // Enqueuing elements into the Queue queue1.
    for (int i = 0; i < k; i++)
    {
        enqueue(queue1, queue.arr[i]);
    }
    // Reversing the first k elements of the Queue queue.
    for (int i = 0; i < k; i++)
    {
        queue.arr[k - 1 - i] = dequeue(queue1);
    }
}

int main()
{
    // Storing the inputs as asked in the question in the given variables.
    // n - no of elements in the Queue, k - number of elements in the front of the Queue to reverse
    // x - storing each integer inputted and Enqueueing it.
    int n, k, x;
    cin >> n;
    int arr[n];
    // Using the struct Queue and initializing the values of the variables part of the Queue struct.
    Queue queue;
    queue.arr = arr;
    queue.length = n;
    queue.head = 0;
    queue.tail = 0;
    // Taking in input for the elements of the Queue and enqueueing it into the Queue.
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        enqueue(queue, x);
    }
    // Taking in input for the number of elements to reverse in the Queue.
    cin >> k;
    // Calling the function to reverse the first k elements of the Queue.
    rev_k(queue, k);
    // Printing the elements of Queue.
    for (int i = 0; i < n; i++)
    {
        cout << queue.arr[i] << " ";
    }
}