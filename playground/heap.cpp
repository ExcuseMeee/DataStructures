#include <iostream>
#include <string>


template<typename T>
class Minheap {
public:
  Minheap(unsigned capacity = 100) {
    this->arr = new T[capacity];
    this->capacity = capacity;
    this->heapSize = 0;
  }

  void insert(const T& val) {
    if (heapSize == capacity) throw std::string("[insert] full heap");

    this->arr[heapSize] = val;
    heapSize++;

    // percolate up
    int i = heapSize - 1; // index of element just inserted

    while (arr[i] < arr[(i - 1) / 2]) {
      swap(arr[i], arr[(i - 1) / 2]);
      i = (i - 1) / 2;
    }


  }

  T popMin() {
    if (heapSize == 0) throw std::string("[popMin] empty heap");

    T val = this->arr[0]; // in minheap, min value is at the top

    // replace top of heap with last value, and delete last value
    this->arr[0] = this->arr[heapSize - 1];
    heapSize--;

    percolateDown(0);

    return val;


  }

  void print() const {
    std::cout << "[print]" << std::endl;
    int curLevel = 0;
    int newLevel = 1;

    for (int i = 0; i < heapSize; i++) {
      std::cout << this->arr[i] << " ";
      curLevel++;
      if (curLevel == newLevel) {
        std::cout << "\n";
        newLevel *= 2;
        curLevel = 0;
      }
    }
    std::cout << std::endl;
  }


private:
  T* arr;
  unsigned heapSize;
  unsigned capacity;

  void swap(T& v1, T& v2) {
    T temp = v1;
    v1 = v2;
    v2 = temp;
  }

  void percolateDown(int start) {
    int index = start;
    int newIndex = start;
    while (true) {
      if (index * 2 + 1 >= this->heapSize) {
        // went out of bounds looking for left kid. that means right kid doesn't exist either. stop percolating
        break;
      }
      else if (index * 2 + 2 >= this->heapSize) {
        // went out of bounds looking for right kid. right kid does not exist, but left kid does.
        newIndex = index * 2 + 1; // we will swap with LEFT kid
      }
      else if (index * 2 + 2 < this->heapSize) {
        // both kids exist. we want to swap with smaller value one
        T leftVal = this->arr[index * 2 + 1];
        T rightVal = this->arr[index * 2 + 2];
        newIndex = leftVal < rightVal ? index * 2 + 1 : index * 2 + 2;
      }

      // swap if child is less
      if (this->arr[newIndex] < this->arr[index]) {
        swap(arr[newIndex], arr[index]);
        index = newIndex;
      }
      else {
        // child is NOT less. stop percolating
        break;
      }

    }
  }


};

int main() {

  Minheap<int> h;

  h.insert(10);
  h.insert(20);
  h.insert(5);
  h.print();

  h.popMin();
  h.popMin();
  h.print();

  h.insert(13);
  h.insert(3);
  h.insert(6);
  h.insert(9);
  h.insert(1);
  h.print();

  h.popMin();
  h.popMin();
  h.print();

  return 0;
}