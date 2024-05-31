#include <iostream>
#include <string>
#include "Trie.h"

int main() {

  Trie t;

  t.insert("dog");
  t.insert("doom");
  t.insert("bag");
  t.insert("train");
  t.insert("tree");
  t.insert("trees");
  t.remove("tree");

  std::cout << t.search("dog") << std::endl;
  std::cout << t.search("doom") << std::endl;
  std::cout << t.search("bag") << std::endl;
  std::cout << t.search("train") << std::endl;
  std::cout << t.search("tree") << std::endl;
  std::cout << t.search("trees") << std::endl;

  return 0;
}