#include <iostream>
#include "BST.h"
#include "BST.cpp"

void test(int*& pI) {
  pI = new int(10);
}


int main() {

  BST<int> tree = BST<int>();
  // tree.insert(10);
  // tree.insert(7);
  // tree.insert(4);
  // tree.insert(8);
  // tree.insert(20);
  // tree.insert(16);
  // tree.insert(30);
  // tree.insert(24);
  // tree.insert(25);
  tree.insert_recursive(10);
  tree.insert_recursive(7);
  tree.insert_recursive(4);
  tree.insert_recursive(8);
  tree.insert_recursive(20);
  tree.insert_recursive(16);
  tree.insert_recursive(30);
  tree.insert_recursive(24);
  tree.insert_recursive(25);
  tree.print();


  tree.remove(10);
  // tree.print();
  tree.remove(25);
  // tree.print();
  tree.remove(7);
  // tree.print();
  tree.remove(4);
  // tree.print();
  tree.remove(8);
  tree.print();


  // tree.print();

  
  return 0;
}