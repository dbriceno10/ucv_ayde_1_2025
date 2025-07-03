#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <string>

using namespace std;

int main()
{
  // 1. std::list
  list<char> lchar = {'a', 'b', 'c'};
  list<char> lchar2;
  lchar2.push_back('d');
  lchar2.push_back('e');
  list<int> lint = {1, 2, 3};
  list<float> lfloat = {1.1f, 2.2f, 3.3f};
  list<string> lstring = {"uno", "dos", "tres"};
  int arr1[3] = {10, 20, 30};
  int arr2[2] = {100, 200};
  list<int *> lparr;
  lparr.push_back(arr1);
  lparr.push_back(arr2);

  cout << "List<char>: ";
  for (char c : lchar)
    cout << c << " ";
  cout << endl;

  cout << "List<int>: ";
  for (int n : lint)
    cout << n << " ";
  cout << endl;

  cout << "List<float>: ";
  for (float f : lfloat)
    cout << f << " ";
  cout << endl;

  cout << "List<string>: ";
  for (const string &s : lstring)
    cout << s << " ";
  cout << endl;

  cout << "List<int*> (arreglos): ";
  for (int *p : lparr)
    cout << "[" << p[0] << "," << p[1] << "," << p[2] << "] ";
  cout << endl;

  // 2. std::stack
  stack<char> schar;
  stack<int> sint;
  stack<float> sfloat;
  stack<string> sstring;
  stack<int *> sparr;

  schar.push('x');
  sint.push(42);
  sfloat.push(3.14f);
  sstring.push("stack");
  sparr.push(arr1);

  cout << "Stack<char>: " << schar.top() << endl;
  cout << "Stack<int>: " << sint.top() << endl;
  cout << "Stack<float>: " << sfloat.top() << endl;
  cout << "Stack<string>: " << sstring.top() << endl;
  cout << "Stack<int*>: [" << sparr.top()[0] << "," << sparr.top()[1] << "," << sparr.top()[2] << "]" << endl;

  // 3. std::queue
  queue<char> qchar;
  queue<int> qint;
  queue<float> qfloat;
  queue<string> qstring;
  queue<int *> qarr;

  qchar.push('y');
  qint.push(99);
  qfloat.push(2.71f);
  qstring.push("queue");
  qarr.push(arr2);

  cout << "Queue<char>: " << qchar.front() << endl;
  cout << "Queue<int>: " << qint.front() << endl;
  cout << "Queue<float>: " << qfloat.front() << endl;
  cout << "Queue<string>: " << qstring.front() << endl;
  cout << "Queue<int*>: [" << qarr.front()[0] << "," << qarr.front()[1] << "]" << endl;

  // 4. std::deque
  deque<char> dchar;
  deque<int> dint;
  deque<float> dfloat;
  deque<string> dstring;
  deque<int *> darr;

  dchar.push_back('z');
  dint.push_back(7);
  dfloat.push_back(1.23f);
  dstring.push_back("deque");
  darr.push_back(arr1);

  cout << "Deque<char>: " << dchar.front() << endl;
  cout << "Deque<int>: " << dint.front() << endl;
  cout << "Deque<float>: " << dfloat.front() << endl;
  cout << "Deque<string>: " << dstring.front() << endl;
  cout << "Deque<int*>: [" << darr.front()[0] << "," << darr.front()[1] << "," << darr.front()[2] << "]" << endl;

  // ...existing code...

  // Arreglo de enteros de tamaño fijo
  int arrfijo[3] = {7, 8, 9};

  // std::list con arreglo de enteros (copia los valores)
  list<int> larrfijo(arrfijo, arrfijo + 3);
  cout << "List<int> (arreglo fijo): ";
  for (int n : larrfijo)
    cout << n << " ";
  cout << endl;

  // std::stack con arreglo de enteros (empuja cada valor)
  stack<int> sarrfijo;
  for (int i = 0; i < 3; ++i)
    sarrfijo.push(arrfijo[i]);
  cout << "Stack<int> (arreglo fijo): ";
  while (!sarrfijo.empty())
  {
    cout << sarrfijo.top() << " ";
    sarrfijo.pop();
  }
  cout << endl;

  // std::queue con arreglo de enteros (empuja cada valor)
  queue<int> qarrfijo;
  for (int i = 0; i < 3; ++i)
    qarrfijo.push(arrfijo[i]);
  cout << "Queue<int> (arreglo fijo): ";
  while (!qarrfijo.empty())
  {
    cout << qarrfijo.front() << " ";
    qarrfijo.pop();
  }
  cout << endl;

  // std::deque con arreglo de enteros (empuja cada valor)
  deque<int> darrfijo;
  for (int i = 0; i < 3; ++i)
    darrfijo.push_back(arrfijo[i]);
  cout << "Deque<int> (arreglo fijo): ";
  for (int n : darrfijo)
    cout << n << " ";
  cout << endl;

  // ...existing code...

  return 0;
}