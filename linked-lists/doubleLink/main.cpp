#include "DLList.h"
#include "DLList.cpp"

int main() {
  DLList<int> l = DLList<int>();

  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  l.push_back(5);

  l.print();

  DLList<int> n = DLList<int>();
  n.push_front(10);
  n.push_front(20);
  n.push_front(30);
  n.push_front(40);
  n.print();

  n = l;

  n.print();

  l.push_back(99);
  n.push_back(66);

  n.print();
  l.print();

  return 0;
}