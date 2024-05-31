#include <iostream>
#include "CDLList.h"
#include "CDLList.cpp"

int main() {

  CDLList<int> l;
  l.push_front(1);
  l.push_front(2);
  l.push_front(3);
  l.push_back(11);
  l.push_back(22);
  l.push_back(33);
  l.print();

  CDLList<int> n = CDLList<int>();
  n.push_back(1);
  n.push_back(1);
  n.push_back(1);
  n.push_back(1);
  n.push_back(1);
  n.push_back(1);
  n.print();

  n = l;

  n.print();
  n.clear();
  l.print();


  return 0;
}