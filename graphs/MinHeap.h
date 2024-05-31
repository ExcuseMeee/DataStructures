#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>

template<typename T>
class MinHeap {
public:
  MinHeap();
  MinHeap(std::vector<T> v);

  void insert(const T& val);
  void print() const;
  T deleteMin();

private:
  std::vector<T> data;

  void swap(T& v1, T& v2) {
    T tmp = v1;
    v1 = v2;
    v2 = tmp;
  }

  void percolate_down();
  void percolate_down(int i);

  int min_index(int i1, int i2) const;
  void heapify();

};



#endif