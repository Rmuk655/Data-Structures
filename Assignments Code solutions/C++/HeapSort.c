#include <stdio.h>

#define MAX_SIZE 1000

// Function to swap two elements in the array
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify subtree rooted at index i in array of size n (min-heap)
void heapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

// Build min-heap from array
void buildHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Delete-min operation: remove root (min) from heap and reheapify
int deleteMin(int arr[], int* n) {
    if (*n <= 0) {
        printf("Heap underflow\n");
        return -1;
    }
    int min = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    heapify(arr, *n, 0);
    return min;
}

// Heap sort: sorts arr of size n in ascending order (in-place)
void heapSort(int arr[], int n) {
    buildHeap(arr, n);
    int originalSize = n;
    for (int i = 0; i < originalSize; i++) {
        int min = deleteMin(arr, &n);
        arr[n] = min; // place min at the end progressively
    }
}

// Print array elements
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Test function: runs two test cases with predefined inputs
void testHeapSort() {
    printf("=== Running Test Case 1 ===\n");
    int test1[] = {57, 64, 72, 85, 93, 58, 69, 76, 88, 94, 61, 79, 66, 82, 97};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    printf("Input array:\n");
    printArray(test1, n1);

    heapSort(test1, n1);
    printf("Sorted array:\n");
    printArray(test1, n1);
    printf("\n");

    printf("=== Running Test Case 2 ===\n");
    int test2[] = {20, 5, 17, 8, 12, 3, 10};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    printf("Input array:\n");
    printArray(test2, n2);

    heapSort(test2, n2);
    printf("Sorted array:\n");
    printArray(test2, n2);
    printf("\n");
}

int main() {
    int choice;
    printf("Heap Sort Program\n");
    printf("=================\n");
    printf("Choose an option:\n");
    printf("1. Enter input manually\n");
    printf("2. Run test cases\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int arr[MAX_SIZE];
        int n;

        printf("Enter number of elements: ");
        scanf("%d", &n);
        if (n <= 0 || n > MAX_SIZE) {
            printf("Invalid number of elements.\n");
            return 1;
        }

        printf("Enter %d elements separated by space:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        heapSort(arr, n);

        printf("Sorted array:\n");
        printArray(arr, n);
    } else if (choice == 2) {
        testHeapSort();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
