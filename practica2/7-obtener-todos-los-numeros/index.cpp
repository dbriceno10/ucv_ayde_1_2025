#include <iostream>
using namespace std;

const int MAX_M = 9; // Máximo valor de m

// Función para verificar si un número parcial es válido
bool esValido(int numero[], int n) {
    int valor = 0;
    for (int i = 0; i < n; i++) {
        valor = valor * 10 + numero[i]; // Construir el número parcial
        if (valor % (i + 1) != 0) {    // Verificar si es múltiplo de (i + 1)
            return false;
        }
    }
    return true;
}

// Función recursiva para generar números válidos
void generarNumeros(int numero[], bool usado[], int m, int index) {
    if (index == m) {
        // Si se generó un número completo, imprimirlo
        for (int i = 0; i < m; i++) {
            cout << numero[i];
        }
        cout << endl;
        return;
    }

    for (int i = 1; i <= 9; i++) { // Probar dígitos del 1 al 9
        if (!usado[i]) {           // Si el dígito no ha sido usado
            numero[index] = i;     // Asignar el dígito al número
            usado[i] = true;       // Marcar el dígito como usado

            if (esValido(numero, index + 1)) { // Verificar si el número parcial es válido
                generarNumeros(numero, usado, m, index + 1); // Llamada recursiva
            }

            usado[i] = false; // Desmarcar el dígito (backtracking)
        }
    }
}

int main() {
    int m;
    cout << "Ingrese el valor de m (m <= " << MAX_M << "): ";
    cin >> m;

    if (m <= 0 || m > MAX_M) {
        cout << "Valor de m inválido." << endl;
        return 1;
    }

    int numero[MAX_M];  // Arreglo para almacenar el número actual
    bool usado[10] = {}; // Arreglo para marcar los dígitos usados (1-9)

    cout << "Números válidos:" << endl;
    generarNumeros(numero, usado, m, 0);

    return 0;
}