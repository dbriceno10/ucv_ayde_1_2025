#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Dipolo {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d, Node* n = nullptr, Node* p = nullptr)
            : data(d), next(n), prev(p) {}
    };

    Node* front; // Primer elemento
    Node* rear;  // Último elemento
    int count;   // Contador de elementos

public:
    Dipolo() : front(nullptr), rear(nullptr), count(0) {}

    ~Dipolo() {
        Clear();
    }

    void Clear() {
        while (!IsEmpty()) {
            PopFront();
        }
    }

    bool IsEmpty() const {
        return count == 0;
    }

    int Size() const {
        return count;
    }

    // Inserta al inicio (como una pila)
    void PushFront(const T& x) {
        Node* newNode = new Node(x, front, nullptr);
        if (IsEmpty()) {
            front = rear = newNode;
        } else {
            front->prev = newNode;
            front = newNode;
        }
        count++;
    }

    // Inserta al final (como una cola)
    void PushBack(const T& x) {
        Node* newNode = new Node(x, nullptr, rear);
        if (IsEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    // Elimina del inicio
    void PopFront() {
        if (IsEmpty()) {
            throw std::out_of_range("Dipolo vacío");
        }
        Node* temp = front;
        front = front->next;
        if (front)
            front->prev = nullptr;
        else
            rear = nullptr;
        delete temp;
        count--;
    }

    // Elimina del final
    void PopBack() {
        if (IsEmpty()) {
            throw std::out_of_range("Dipolo vacío");
        }
        Node* temp = rear;
        rear = rear->prev;
        if (rear)
            rear->next = nullptr;
        else
            front = nullptr;
        delete temp;
        count--;
    }

    // Acceso al frente
    T Front() const {
        if (IsEmpty()) {
            throw std::out_of_range("Dipolo vacío");
        }
        return front->data;
    }

    // Acceso al final
    T Back() const {
        if (IsEmpty()) {
            throw std::out_of_range("Dipolo vacío");
        }
        return rear->data;
    }
};

// Ejemplo de uso
int main() {
    Dipolo<int> d;
    d.PushFront(10); // [10]
    d.PushBack(20);  // [10, 20]
    d.PushFront(5);  // [5, 10, 20]
    std::cout << "Front: " << d.Front() << std::endl; // 5
    std::cout << "Back: " << d.Back() << std::endl;   // 20
    d.PopFront(); // [10, 20]
    d.PopBack();  // [10]
    std::cout << "Front: " << d.Front() << std::endl; // 10
    std::cout << "Size: " << d.Size() << std::endl;   // 1
    return 0;
}