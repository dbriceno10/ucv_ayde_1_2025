#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <string>

using namespace std;

int main()
{
  // Ejemplo con list<int>
  list<int> lint = {1, 2, 3};
  cout << "Iterando list<int> con for clásico:" << endl;
  for (list<int>::iterator it = lint.begin(); it != lint.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;
  cout << "Iterando list<int> con while:" << endl;
  list<int>::iterator it = lint.begin();
  while (it != lint.end())
  {
    cout << *it << " ";
    ++it;
  }
  cout << endl;

  // Ejemplo con stack<int>
  stack<int> sint;
  sint.push(10);
  sint.push(20);
  sint.push(30);
  cout << "Iterando stack<int> (solo se puede usando pop/top):" << endl;
  stack<int> tempStack = sint; // Para no vaciar el original
  while (!tempStack.empty())
  {
    cout << tempStack.top() << " ";
    tempStack.pop();
  }
  cout << endl;

  // Ejemplo con queue<int>
  queue<int> qint;
  qint.push(100);
  qint.push(200);
  qint.push(300);
  cout << "Iterando queue<int> (solo se puede usando pop/front):" << endl;
  queue<int> tempQueue = qint; // Para no vaciar el original
  while (!tempQueue.empty())
  {
    cout << tempQueue.front() << " ";
    tempQueue.pop();
  }
  cout << endl;

  // Ejemplo con deque<int>
  deque<int> dint;
  dint.push_back(7);
  dint.push_back(8);
  dint.push_back(9);
  cout << "Iterando deque<int> con for clásico:" << endl;
  for (deque<int>::iterator it = dint.begin(); it != dint.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  cout << "Iterando deque<int> con while:" << endl;
  deque<int>::iterator dit = dint.begin();
  while (dit != dint.end())
  {
    cout << *dit << " ";
    ++dit;
  }
  cout << endl;

  // list<int>::iterator it = lint.begin();
  // cout << "begin " << *lint.begin() << endl;
  // cout << "end " << *(lint.end()) << endl;
  // while (it != lint.end())
  // {
  //   cout << "it: " << *it << " ";
  //   ++it;
  // }

  return 0;
}