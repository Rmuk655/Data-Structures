#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <cmath>

using namespace std;

void printarray(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

int Delete_Min(int *arr, int n)
{
    return arr[n - 1];
}

void swap_int(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Heapify(int *array, int size, int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int minimum = index;

    if (left < size && array[left] > array[minimum])
    {
        minimum = left;
    }

    if (right < size && array[right] > array[minimum])
    {
        minimum = right;
    }

    if (minimum != index)
    {
        swap_int(&array[index], &array[minimum]);
        Heapify(array, size, minimum);
    }
}

void build_heap(int *arr, int n)
{
    for (int i = floor(n / 2) - 1; i >= 0; i--)
    {
        Heapify(arr, n, i);
        // printarray(arr, n);
    }
}

void heap_sort(int *arr, int n)
{
    build_heap(arr, n);
    int size = n;
    for (int i = size - 1; i >= 0; i--)
    {
        swap_int(&arr[i], &arr[0]);
        n--;
        Heapify(arr, n, 0);
        // printarray(arr, size);
    }
    n = size;
    printarray(arr, n);
}

// ---------- HELPER FUNCTION ----------
void run_and_check(int input[], int size)
{
    int expected[1000]; // large enough for our test
    for (int i = 0; i < size; ++i)
        expected[i] = input[i];

    sort(expected, expected + size); // expected correct result

    heap_sort(input, size); // apply your function

    for (int i = 0; i < size; ++i)
        assert(input[i] == expected[i]);
}

void test()
{
    {
        int arr[] = {5, 3, 8, 4, 1, 2};
        run_and_check(arr, 6);
    }
    {
        int arr[] = {1, 2, 3, 4, 5};
        run_and_check(arr, 5);
    }
    {
        int arr[] = {5, 4, 3, 2, 1};
        run_and_check(arr, 5);
    }
    {
        int arr[] = {7, 7, 7, 7, 7};
        run_and_check(arr, 5);
    }
    {
        int arr[] = {};
        run_and_check(arr, 0);
    }
    {
        int arr[] = {42};
        run_and_check(arr, 1);
    }
    {
        int arr[] = {-3, 14, -7, 0, 8, -1};
        run_and_check(arr, 6);
    }
    {
        int arr[] = {5, 1, 4, 2, 5, 1, 4};
        run_and_check(arr, 7);
    }
    {
        int arr[] = {100, 90, 80, 70, 60, 50, 40};
        run_and_check(arr, 7);
    }
    {
        int arr[] = {rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000};
        run_and_check(arr, 5);
    }

    cout << "All 10 array-based heap_sort test cases passed!" << endl;
}

int main()
{
    test();
    int n, num;
    cin >> n;
    int array[n];
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        array[i] = num;
    }
    heap_sort(array, n);
    printarray(array, n);
}