#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "minHeap.h"
#include "minHeap.cpp"

template<typename T>
void heap_sort(std::vector<T>& v);

int main() {

  srand(time(0));


  std::vector<int> v;
  for (int i = 0; i < 10; i++) {
    v.push_back(rand() % 100);
  }

  for(auto i : v) {
    std::cout << i << " ";
  }

  puts("");


  MinHeap<int> h(v);

  h.print();


  return 0;
}

template<typename T>
void heap_sort(std::vector<T>& v) {

  MinHeap<T> h;

  for (const T& val : v) {
    h.insert(val);
  }

  for (int i = 0; i < v.size(); i++) {
    v[i] = h.deleteMin();
  }
}

