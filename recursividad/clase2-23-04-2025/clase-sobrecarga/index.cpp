#include <iostream>

using namespace std;

class NumeroComplejo
{
private:
  double real;
  double imaginario;

public:
  NumeroComplejo(double r = 0.0, double i = 0.0) : real(r), imaginario(i) {}

  NumeroComplejo operator+(const NumeroComplejo &otro) const
  {
    return NumeroComplejo(real + otro.real, imaginario + otro.imaginario);
  }

  NumeroComplejo operator-(const NumeroComplejo &otro) const
  {
    double r = real - otro.real;
    if (r < 0)
    {
      r = 0;
    }
    return NumeroComplejo(r, imaginario - otro.imaginario);
  }

  friend ostream &operator<<(ostream &os, const NumeroComplejo &otro)
  {
    // cout << real << imaginario <<endl;
    os << otro.real << " + " << otro.imaginario;
    return os;
  }

  friend istream &operator>>(istream &is, NumeroComplejo &otro)
  {
    cout << "ingrese el numero real" << endl;
    is >> otro.real;
    cout << "ingrese el numero imaginario" << endl;
    is >> otro.imaginario;
    return is;
  }
};

int main()
{
  int x, y;
  int r = x + y;
  cout << r;
  NumeroComplejo a(3.0, 4.0), b(1.0, 2.0);
  NumeroComplejo c = a - b;
  cout << c;
  cin >> a;
}