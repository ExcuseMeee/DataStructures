#include <iostream>
#include "AVLTree.h"
#include "AVLTree.cpp"

int main() {

  AVLTree<int> tree;

  tree.insert(10);
  tree.insert(5);
  tree.insert(20);
  tree.insert(3);
  tree.insert(6);
  tree.insert(15);
  tree.insert(30);

  tree.print();

  // auto n = tree.findKSmallest(6);

  // if(n) {
  //   std::cout << n->data;
  // }
  // else {
  //   puts("none");
  // }

  return 0;
}