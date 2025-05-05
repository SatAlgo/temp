#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int>& arr, int n, int i, bool ascending) {
    int extreme = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (ascending) {
        if (left < n && arr[left] > arr[extreme])
            extreme = left;
        if (right < n && arr[right] > arr[extreme])
            extreme = right;
    } else {
        if (left < n && arr[left] < arr[extreme])
            extreme = left;
        if (right < n && arr[right] < arr[extreme])
            extreme = right;
    }

    if (extreme != i) {
        swap(arr[i], arr[extreme]);
        heapify(arr, n, extreme, ascending);
    }
}

void heapSort(vector<int>& arr, bool ascending) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, ascending);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, ascending);
    }
}

void printArray(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> arrAsc = arr;
    vector<int> arrDesc = arr;

    heapSort(arrAsc, true);
    cout << "\nArray sorted in Ascending Order:\n";
    printArray(arrAsc);

    heapSort(arrDesc, false);
    cout << "\nArray sorted in Descending Order:\n";
    printArray(arrDesc);

    return 0;
}
