#include <iostream>
#include <string>

using namespace std;

class DNA
{
  struct Node
  {
    char type;
    int maxLinks;
    int currentLinks;
    Node *up;
    Node *down;
    Node *left;
    Node *right;
    Node(char t)
    {
      type = t;
      currentLinks = 0;
      // Define maxLinks based on type
      if (t == 'H')
        maxLinks = 1;
      else if (t == 'E')
        maxLinks = 4;
      else if (t == 'M')
        maxLinks = 2;
      else if (t == 'C')
        maxLinks = 2;
      up = nullptr;
      down = nullptr;
      left = nullptr;
      right = nullptr;
    }
  };
};