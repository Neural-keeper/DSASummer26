#include <iostream>
#include <algorithm> // For std::swap
#include <vector>



// Insertion Sort
/*
Builds the sorted array one element at a time. It iterates through the input array and removes 
one element per iteration, finds the location it belongs within the sorted list, and inserts it 
there. Excellent for small or nearly sorted datasets.
*/
void InsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
/*
COMPLEXITIES:
Time: O(n^2) worst and average case. O(n) best case (if already sorted).
Space: O(1) auxiliary space (in-place).
*/



// Selection Sort
/*
Divides the input list into a sorted and an unsorted region. Repeatedly finds the minimum element 
from the unsorted region and swaps it with the leftmost unsorted element, moving the sublist 
boundaries one element to the right.
*/
void SelectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[min_idx], arr[i]);
        }
    }
}
/*
COMPLEXITIES:
Time: O(n^2) for best, average, and worst cases.
Space: O(1) auxiliary space (in-place).
*/



// Quick Sort
/*
A Divide and Conquer algorithm. It picks an element as a pivot and partitions the given array 
around the pivot by placing smaller elements before it and larger elements after it. The sub-arrays 
are then recursively sorted.
*/
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing the last element as pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void QuickSortRecursive(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        QuickSortRecursive(arr, low, pi - 1);
        QuickSortRecursive(arr, pi + 1, high);
    }
}

// Wrapper to match standard signature
void QuickSort(int arr[], int n) {
    QuickSortRecursive(arr, 0, n - 1);
}
/*
COMPLEXITIES:
Time: O(n log n) average and best case. O(n^2) worst case (if already sorted and poorly pivoted).
Space: O(log n) average for recursion stack. O(n) worst case stack space.
*/



// Helper Function for Merge Sorts
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


// Merge Sort (Top-Down)
/*
A recursive Divide and Conquer algorithm. It continuously splits the array in half until sub-arrays 
contain only one element, then recursively merges the sub-arrays back together in a sorted manner.
*/
void MergeSortTopDownRecursive(int arr[], int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    MergeSortTopDownRecursive(arr, left, mid);
    MergeSortTopDownRecursive(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Wrapper to match standard signature
void MergeSortTopDown(int arr[], int n) {
    MergeSortTopDownRecursive(arr, 0, n - 1);
}
/*
COMPLEXITIES:
Time: O(n log n) for best, average, and worst cases.
Space: O(n) auxiliary space for the temporary sub-arrays during merge.
*/



// Merge Sort (Bottom-Up)
/*
An iterative version of Merge Sort. It treats the array as 'n' sublists of size 1. It repeatedly 
merges adjacent sublists to produce sorted sublists of size 2, then 4, 8, etc., until the entire 
array is sorted.
*/
void MergeSortBottomUp(int arr[], int n) {
    // curr_size varies from 1 to n/2
    for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        // Pick starting point of different sub-arrays of current size
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            
            // Find ending point of left sub-array (mid+1 is starting point of right)
            int mid = std::min(left_start + curr_size - 1, n - 1);
            
            // Find ending point of right sub-array
            int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);
            
            // Merge sub-arrays arr[left_start...mid] & arr[mid+1...right_end]
            merge(arr, left_start, mid, right_end);
        }
    }
}
/*
COMPLEXITIES:
Time: O(n log n) for best, average, and worst cases.
Space: O(n) auxiliary space for the temporary sub-arrays during merge.
*/