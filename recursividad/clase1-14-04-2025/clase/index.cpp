#include <iostream>
using namespace std;

int factorial(int n)
{
  if (n <= 1)
    return 1;
  return n * factorial(n - 1);
}

int fibonacci(int n)
{
  if (n <= 1)
    return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int binarySearch(int arr[], int left, int right, int target)
{
  if (left > right)
    return -1;

  int mid = left + (right - left) / 2;

  if (arr[mid] == target)
    return mid;
  else if (arr[mid] > target)
    return binarySearch(arr, left, mid - 1, target);
  else
    return binarySearch(arr, mid + 1, right, target);
}

int main()
{
  // Factorial
  cout << "Factorial de 5: " << factorial(5) << endl;

  // Fibonacci
  cout << "Fibonacci de 6: " << fibonacci(6) << endl;

  // Binary Search
  int arr2[] = {1, 3, 5, 7, 9, 11};
  int n2 = sizeof(arr2) / sizeof(arr2[0]);
  int target = 7;
  int result = binarySearch(arr2, 0, n2 - 1, target);
  if (result != -1)
    cout << "Elemento " << target << " encontrado en la posición: " << result << endl;
  else
    cout << "Elemento " << target << " no encontrado." << endl;

  return 0;
}