#include <iostream>
#include <string>
using namespace std;
// Proyecto 2

int main()
{
  cout << "PROYECTO #2" << endl;

  string str;
  cin >> str;
  char c[str.length() + 1];

  for (int i = 0; i < sizeof(c); i++)
  {
    c[i] = str[i];

    if (str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9')
    {

      cout << "numero detectado" << endl;
      int numero = c[i] - '0';
      int h = i;
      for (int j = i + 1; j < numero + i + 1; j++)
      {
        c[j] = str[i - 1];
        cout << c[j] << " ";
        h++;
      }
      i = h;
    }

    cout << c[i] << " ";
  }

  return 0;
}