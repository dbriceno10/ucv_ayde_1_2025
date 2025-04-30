#include <iostream>

using namespace std;

float sumaInversa(int n)
{
  if (n <= 1)
  {
    return 1;
  }
  else
  {
    return (1 / float(n)) + sumaInversa(n - 1);
  }
}

int main(int argc, char const *argv[])
{
  /* code */
  int n = 0;
  cout << "Numero" << endl;
  cin >> n;
  cout << sumaInversa(n) << endl;
  // sumaInversa(n);

  return 0;
}
