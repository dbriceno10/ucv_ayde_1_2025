#include <iostream>
#include <string>

using namespace std;

// Función recursiva para convertir un número a binario
string convertirABinario(int n) {
    if (n == 0) {
        return "0";
    }
    if (n == 1) {
        return "1";
    }
    return convertirABinario(n / 2) + to_string(n % 2);
}

// Función recursiva para convertir un número a hexadecimal
string convertirAHexadecimal(int n) {
    if (n == 0) {
        return "0";
    }
    string hexChars = "0123456789ABCDEF";
    if (n < 16) {
        return string(1, hexChars[n]);
    }
    return convertirAHexadecimal(n / 16) + string(1, hexChars[n % 16]);
}

int main() {
    int numero;

    cout << "Ingrese un número entero positivo: ";
    cin >> numero;

    if (numero < 0) {
        cout << "El número debe ser positivo o nulo." << endl;
        return 1;
    }

    cout << "Representación en binario: " << convertirABinario(numero) << endl;
    cout << "Representación en hexadecimal: " << convertirAHexadecimal(numero) << endl;

    return 0;
}