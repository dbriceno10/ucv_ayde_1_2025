#include <iostream>

using namespace std;

struct node
{
  int info;
  node *next;
};
int main()
{
  node *p, *r, *s;
  p = new node();
  s = new node();
  r = new node();
  p->next = r;
  r->next = s;
  s->next = p;
  s->info = 3;
  p->next->next->next->info = 2;
  s->next->next->info = 1;
  p = s->next;
  cout << p->info << " " << s->info << " " << p->info << endl;
  return 0;
}