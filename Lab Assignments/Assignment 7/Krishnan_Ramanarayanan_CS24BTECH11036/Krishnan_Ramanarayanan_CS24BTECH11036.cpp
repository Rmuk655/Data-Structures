#include <iostream>
#include <cmath>

using namespace std;

// Time complexity = O(n log n)
// Space complexity = O(n)

// We create a struct Heap that stores the array of elements to be sorted and it's size.
struct Heap
{
    int *arr;
    int size;
};

// We print the elements in the Heap using the printarray helper function.
void printarray(Heap *heap)
{
    for (int i = 0; i < heap->size; i++)
    {
        cout << heap->arr[i] << " ";
    }
    cout << endl;
}

// Helper function swap_int swaps the values present in two integer pointers.
void swap_int(int *a, int *b)
{
    // Integer variable temp stores the integer value the pointer points to.
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Time complexity of Heapify function = O(log n)
// Space complexity of Heapify function = O(n)
// Additional space complexity of Heapify function = O(1)
// Heapify restores the heap property in any subtree whose root violates the heap property.
void Heapify(Heap *&heap, int index)
{
    // The variable left represents the index of the left child of the element at the given index when we see the heap as a tree.
    // The variable right represents the index of the right child of the element at the given index when we see the heap as a tree.
    // The variable minimum represents the index of the minimum value of the element which we will find and update recursively.
    int left = 2 * index + 1, right = 2 * index + 2, minimum = index;

    // If the assumed index is the minimum and it's left child has a greater value than itself, then we should heapify further down the array.
    // Hence, we change minimum to left index and repeat the same process using recursive Heapify calls.
    if (left < heap->size && heap->arr[left] > heap->arr[minimum])
    {
        minimum = left;
    }

    // If the assumed index is the minimum and it's right child has a greater value than itself, then we should heapify further down the array.
    // Hence, we change minimum to right index and repeat the same process using recursive Heapify calls.
    if (right < heap->size && heap->arr[right] > heap->arr[minimum])
    {
        minimum = right;
    }

    // If the given index is either smaller than it's left child or right child, then we heapify further down the heap after swapping.
    if (minimum != index)
    {
        swap_int(&heap->arr[index], &heap->arr[minimum]);
        Heapify(heap, minimum);
    }
}

// Time complexity of Delete_Min function = O(log n)
// Space complexity of Delete_Min function = O(n)
// Additional space complexity of Delete_Min function = O(1)
// Function delete min deletes the minimum element of the heap.
int Delete_Min(Heap *&heap)
{
    // The minimum element will be present at arr[0].
    int min = heap->arr[0];
    // We set it to the last element of the heap, reduce the size of the heap array.
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    // We heapify again as the array is not sorted now.
    Heapify(heap, 0);
    // We return the minimum element stored in min.
    return min;
}

// Time complexity of build_heap function = O(n*log n)
// Space complexity of build_heap function = O(n)
// Additional space complexity of build_heap function = O(1)
// Function build heap builds the heap from the given array elements by calling the Heapify function multiple times for each element.
void build_heap(Heap *&heap)
{
    // We call heapify for each element in the heap array.
    for (int i = floor(heap->size / 2) - 1; i >= 0; i--)
    {
        Heapify(heap, i);
    }
}

// Time complexity of heap_sort function = O(n*log n)
// Space complexity of heap_sort function = O(n)
// Additional space complexity of heap_sort function = O(n)
// Function heap_sort performs the array sorting in ascending order using build_heap and delete_min functions.
void heap_sort(Heap *&heap)
{
    build_heap(heap);
    // We store the initial size of the array in size as we decrease the size using Delete_Min and we need the original size after updating the array with the sorted array.
    int size = heap->size;
    // Sorted array which contains the elements of the initial heap array in sorted order (ascending).
    int *sorted = new int[size];
    // We call Delete_Min repeatedly to store the smallest element of the array first in the array sorted, remove it from the heap and then find the second smallest element and so on.
    for (int i = size - 1; i >= 0; i--)
    {
        sorted[i] = Delete_Min(heap);
    }
    // We update the size of the heap value with the initial stored value.
    heap->size = size;
    // We update the heap array using the sorted array (ascending order) which we constructed by calling Delete-Min repeatedly.
    heap->arr = sorted;
}

// Main function takes in user input and runs the code for different values.
int main()
{
    // We create a new heap to store the array of numbers.
    Heap *heap = new Heap();
    // Note that my input format first takes in the size of the array as n, then n integers of the array and outputs the sorted array (in ascending order).
    // Integer n stores the number of integers in the array from user input.
    int n;
    cin >> n;
    // Integer array, array[n] stores the n integers in the array from user input.
    int array[n];
    // We store the n integers taken as user input in this array.
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        array[i] = num;
    }
    // The array is now part of our heap struct along with it's size.
    heap->arr = array;
    heap->size = n;
    // We sort the elements of the array in ascending order and print them.
    heap_sort(heap);
    printarray(heap);
}