#include <iostream>
using namespace std;

void opArray(int arr[], int l, int index, int &suma, float &media, int &mayor, bool &ascendente, bool &descendente)
{
  if (index >= l)
  {
    media = float(suma) / l;
    return;
  }
  if (arr[index] > mayor)
  {
    mayor = arr[index];
  }
  suma += arr[index];
  if (index > 0)
  {
    // cout << arr[index - 1] << " " << arr[index] << endl;
    // cout << "index: " << index << endl;
    if (ascendente)
    {
      if (arr[index] < arr[index - 1])
      {
        ascendente = false;
      }
    }
    if (descendente)
    {
      if (arr[index] > arr[index - 1])
      {
        descendente = false;
      }
    }
  }
  opArray(arr, l, index + 1, suma, media, mayor, ascendente, descendente);
}

int main(int argc, char const *argv[])
{
  int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9,10};
  int suma = 0, mayor = 0;
  float media = 0;
  bool ascendente = true, descendente = true;
  opArray(array, 10, 0, suma, media, mayor, ascendente, descendente);
  cout << "suma: " << suma << endl;
  cout << "media: " << media << endl;
  cout << "ascendente: " << ascendente << endl;
  cout << "descendente: " << descendente << endl;
  cout << "mayor: " << mayor << endl;
  return 0;
}
