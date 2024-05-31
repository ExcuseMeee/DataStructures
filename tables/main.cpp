#include <iostream>
#include "HashMap.h"
#include "HashMap.cpp"


int main() {

  HashMap<int, int> map;

  map.insert(111, 1); // index 10
  map.insert(222, 2); // index 20
  map.insert(333, 3); // index 30
  map.insert(10, 123); // 11
  map.insert(20, 223); // 21
  map.insert(30, 323); // 31

  
  std::cout << map.search(30) << std::endl;

  map.remove(30);
  map.remove(30);

  std::cout << map.search(30) << std::endl;

  map.display();

  return 0;
}