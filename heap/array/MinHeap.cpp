#include <iostream>
#include <cmath>
#include "minHeap.h"


template<typename T>
MinHeap<T>::MinHeap() {};
template<typename T>
MinHeap<T>::MinHeap(std::vector<T> v) {
  // insert elements
  this->data = v;

  heapify();
}

template<typename T>
void MinHeap<T>::insert(const T& val) {
  this->data.push_back(val);

  int n = data.size() - 1; // index of last node

  // percolate UP
  while (data.at(n) < data.at((n - 1) / 2)) {
    swap(data.at(n), data.at((n - 1) / 2));
    n = (n - 1) / 2; // set index to parent index
  }

}

template<typename T>
void MinHeap<T>::print() const {
  std::cout << "[print]" << std::endl;
  int curLevel = 0;
  int newLevel = 1;

  for (const T& element : this->data) {
    std::cout << element << " ";
    curLevel++;
    if (curLevel == newLevel) {
      std::cout << "\n";
      newLevel *= 2;
      curLevel = 0;
    }
  }
  std::cout << std::endl;
}

template<typename T>
T MinHeap<T>::deleteMin() {
  if (data.empty()) throw std::string("[deletMin] empty heap");

  T res = data[0];
  data[0] = data[data.size() - 1]; // replace root with value of last node


  data.pop_back(); // remove last node

  // std::cout << data[0];

  // percolate DOWN
  percolate_down(0);

  return res;

}

template<typename T>
void MinHeap<T>::percolate_down() {
  if (data.empty() || data.size() == 1) return;

  int cur_index = 0;

  do
  {
    if ((cur_index * 2) + 1 >= data.size()) {
      // no kids. if looking for left kid goes out of bounds, then right kid definitely doesn't exist
      break;
    }
    else {
      // has kids
      T left = data.at((cur_index * 2) + 1); // this should exist since we passed the check
      T right = (cur_index * 2) + 2 >= data.size() ? left + 1 : data.at((cur_index * 2) + 2); // if dne then set val to be higher than left so left will be chosen for swap

      if (left < right) {
        // swap cur and left
        swap(data.at(cur_index), data.at((cur_index * 2) + 1));
        cur_index = (cur_index * 2) + 1;
      }
      else {
        // swap cur and right
        swap(data.at(cur_index), data.at((cur_index * 2) + 2));
        cur_index = (cur_index * 2) + 2;
      }
    }
  } while (true);



}

template<typename T>
void MinHeap<T>::percolate_down(int i) {
  if (i >= data.size() || i < 0) return;

  int parent_index = i;
  int new_index = i;

  do
  {
    if ((parent_index * 2) + 1 >= data.size()) {
      // no kids. if looking for left kid goes out of bounds, then right kid definitely doesn't exist
      break;
    }
    else if ((parent_index * 2) + 2 < data.size()) {
      // two kids
      new_index = min_index(parent_index * 2 + 1, parent_index * 2 + 2);

    }
    else if ((parent_index * 2) + 1 < data.size()) {
      // no right kid
      new_index = parent_index * 2 + 1;

    }

    // swap if smaller, else break from loop
    if (data.at(new_index) < data.at(parent_index)) {
      swap(data.at(parent_index), data.at(new_index));
      parent_index = new_index;
    }
    else {
      break;
    }
  } while (true);



}

template<typename T>
int MinHeap<T>::min_index(int i1, int i2) const {

  if (i1 >= data.size() || i2 >= data.size() || i1 < 0 || i2 < 0) throw std::string("[min_index] incorrect index");

  T val1 = data.at(i1);
  T val2 = data.at(i2);

  return (val1 > val2 ? i2 : i1);
}

template<typename T>
void MinHeap<T>::heapify() {
  for (int i = (data.size() / 2) - 1; i >= 0; i--) {
    percolate_down(i);
  }
}

