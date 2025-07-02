#include <iostream>
using namespace std;

class IntList
{
  struct Node
  {
    int value;
    Node *next;
    Node(int val) : value(val), next(nullptr) {}
  };
  Node *head;
  Node *tail;
public:
  IntList() : head(nullptr), tail(nullptr) {}
  ~IntList()
  {
    Node *current = head;
    while (current)
    {
      Node *nextNode = current->next;
      delete current;
      current = nextNode;
    }
  }
  void Insert(int value)
  {
    Node *newNode = new Node(value);
    if (!head)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      tail->next = newNode;
      tail = newNode;
    }
  }
  int Sum() const
  {
    int total = 0;
    Node *current = head;
    while (current)
    {
      total += current->value;
      current = current->next;
    }
    return total;
  }
};

int main()
{
  IntList list;
  for (int i = 1; i <= 10; ++i)
  {
    list.Insert(i);
  }
  
  cout << "Sum: " << list.Sum() << endl;
  
  return 0;
}