#include <iostream>
#include "SLLNode.h"
#include "SLList.h"
#include "SLList.cpp"

int main() {


  SLList<char> list = SLList<char>();
  list.push_back('a');
  list.push_back('b');
  list.push_back('c');
  list.push_back('d');
  list.push_back('e');
  list.print();


  return 0;
}