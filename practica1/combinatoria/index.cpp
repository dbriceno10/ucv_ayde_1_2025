#include <iostream>

using namespace std;

// Función para calcular el factorial de un número
long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// Función para calcular la combinatoria C(n, r)
long long combinatoria(int n, int r) {
    return factorial(n) / (factorial(r) * factorial(n - r));
}

int main() {
    int n, r;
    cout << "Ingrese el valor de n: ";
    cin >> n;
    cout << "Ingrese el valor de r: ";
    cin >> r;

    if (r > n) {
        cout << "r no puede ser mayor que n." << endl;
    } else {
        cout << "C(" << n << ", " << r << ") = " << combinatoria(n, r) << endl;
    }

    return 0;
}