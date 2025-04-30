#include <iostream>

using namespace std;

int sumaNaturales(int n)
{
  if (n < 1)
  {
    return 0;
  }
  return n + sumaNaturales(n - 1);
}

int main(int argc, char const *argv[])
{
  int n = 0;
  cout << "numero" << endl;
  cin >> n;
  cout << sumaNaturales(n) << endl;
  return 0;
}
