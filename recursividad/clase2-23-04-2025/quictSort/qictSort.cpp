#include <iostream>

using namespace std;

//quick sort

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void quickSort(int arr[], int low, int high) {
    if (low >= high) {
        return;
    }

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i+1], arr[high]);
    int aux = i + 1;//4

    quickSort(arr, low, aux - 1);
    quickSort(arr, aux +1, high);
}

int main()
{

    int arr[] = { 10,9,3,8,5,7 };
    quickSort(arr, 0, 5);
    for (int i = 0; i < 6; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}