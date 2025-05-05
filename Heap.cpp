#include <iostream>
using namespace std;

int arr[700];

// Input array
void getArray(int arr[], int n) {
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

// Print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Max heapify function
void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
    printArray(arr, n);
}

// Max heap sort (Descending)
void maxHeapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
        
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

// Min heapify function
void minHeapify(int arr[], int n, int i) {
    int smallest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

// Min heap sort (Ascending)
void minHeapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        minHeapify(arr, i, 0);
    }
}

int main() {
    int n, repeat = 1;

    cout << "\n=== Heap Sort Program ===\n";

    while (repeat == 1) {
        cout << "\n-------------------------------------";
        cout << "\nEnter the number of elements: ";
        cin >> n;

        getArray(arr, n);

        cout << "\nArray Before Sorting:\n";
        printArray(arr, n);

        cout << "\nArray After Sorting using Max Heap (Descending Order):\n";
        maxHeapSort(arr, n);
        printArray(arr, n);

        cout << "\nArray After Sorting using Min Heap (Ascending Order):\n";
        minHeapSort(arr, n);
        printArray(arr, n);

        cout << "\nDo you want to sort another array? (1 = Yes / 0 = No): ";
        cin >> repeat;
    }

    cout << "\nThank you!\n";
    return 0;
}
