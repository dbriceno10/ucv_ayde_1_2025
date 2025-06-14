#include <iostream>
#include <exception>
#include <string>
#include "stack.hpp"
#include "queue.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
  // /* code */
  // try
  // {
  //   1 / 0;
  // }
  // catch (const std::exception &e)
  // {
  //   // std::cerr << e.what() << '\n';
  //   cout << "Error: " << e.what() << endl;
  // }

  // try
  // {
  //   /* code */
  //   Stack<string> stringStack;
  //   stringStack.Push("Hello");
  //   stringStack.Push("World");
  //   stringStack.Push("!");
  //   cout << "Size of stack: " << stringStack.Size() << endl;
  //   cout << "Top element: " << stringStack.Top() << endl;
  //   stringStack.Pop();
  //   cout << "Size of stack after pop: " << stringStack.Size() << endl;
  //   cout << "Top element after pop: " << stringStack.Top() << endl;
  //   stringStack.Clear();
  //   cout << "Size of stack after clear: " << stringStack.Size() << endl;
  //   cout << "Is stack empty? " << (stringStack.IsEmpty() ? "Yes" : "No") << endl;
  // }
  // catch(const std::exception& e)
  // {
  //   std::cerr << e.what() << '\n';
  // }

  try
  {
    Queue<string> stringQueue;
    stringQueue.Enqueue("Hello");
    stringQueue.Enqueue("World");
    stringQueue.Enqueue("!");
    cout << "Size of queue: " << stringQueue.Size() << endl;
    cout << "Front element: " << stringQueue.Front() << endl;
    stringQueue.Dequeue();
    cout << "Size of queue after dequeue: " << stringQueue.Size() << endl;
    cout << "Front element after dequeue: " << stringQueue.Front() << endl;
    stringQueue.Clear();
    cout << "Size of queue after clear: " << stringQueue.Size() << endl;
    cout << "Is queue empty? " << (stringQueue.IsEmpty() ? "Yes" : "No") << endl;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  

  return 0;
}
