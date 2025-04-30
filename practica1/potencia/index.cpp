#include <iostream>

using namespace std;

// Función recursiva para calcular la potencia
double potencia(double x, int n) {
    if (n == 0) {
        return x;
    }
    if (n % 2 == 0) {
        // Si n es par: x^n = (x * x)^(n / 2)
        return potencia(x * x, n / 2);
    } else {
        // Si n es impar: x^n = x * x^(n - 1)
        return x * potencia(x, n - 1);
    }
}

int main() {
    double x;
    int n;

    cout << "Ingrese la base (x): ";
    cin >> x;
    cout << "Ingrese el exponente (n): ";
    cin >> n;

    if (n < 0) {
        cout << "El exponente debe ser un entero positivo." << endl;
        return 1;
    }

    cout << x << " elevado a la " << n << " es: " << potencia(x, n) << endl;

    return 0;
}