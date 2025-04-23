#include <iostream>

using namespace std;

int fibonacci(int n)
{
  if (n <= 1)
  {
    return n;
  }
  else
  {
    int const suma = fibonacci(n - 1) + fibonacci(n - 2);
    cout << suma << endl;
    return suma;
  }
}

int main()
{
  /* code */
  int n;
  cout << "Enter a number: ";
  cin >> n;
  cout << "Fibonacci of " << n << " is " << fibonacci(n) << endl;
  return 0;
}