#include <iostream>
#include "Queue.h"

template<typename T>
Queue<T>::Queue(unsigned capacity) {
  data = new T[capacity];
  frnt = bck = 0;
  this->capacity = capacity;
  queueSize = 0;
}

template<typename T>
Queue<T>::~Queue() {
  clear();
  delete[] data;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other) {
  // init this queue using info from other
  data = new T[other.capacity];
  capacity = other.capacity;
  frnt = other.frnt;
  bck = other.bck;
  queueSize = other.queueSize;

  // if(!empty) combined with do while handles edge cases where frnt = back
  if (!other.empty()) {
    // copy items over
    int cur = frnt;
    do
    {
      data[cur] = other.data[cur];
      cur = (cur + 1) % capacity;
    } while (cur != bck);
  }

}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
  // overwrite everything
  delete[] data;
  data = new T[other.capacity]; // create new array to store data from other
  capacity = other.capacity;
  frnt = other.frnt;
  bck = other.bck;
  queueSize = other.queueSize;

  // copy items over
  if (!other.empty()) {
    // copy items over
    int cur = frnt;
    do
    {
      data[cur] = other.data[cur];
      cur = (cur + 1) % capacity;
    } while (cur != bck);
  }

  return *this;

}

template<typename T>
unsigned Queue<T>::size() const {
  return queueSize;
}

template<typename T>
bool Queue<T>::empty() const {
  return queueSize == 0;
}

template<typename T>
bool Queue<T>::full() const {
  return queueSize == capacity;
}

template<typename T>
void Queue<T>::enqueue(const T& val) {
  if (full()) return;
  data[bck] = val;
  bck = (bck + 1) % capacity; // move the bck index one position. we use modulus so that the bck index can wrap around (a circular array)
  queueSize++;
}

template<typename T>
void Queue<T>::print() const {
  if (this->empty()) {
    std::cout << "Queue is empty" << std::endl;
    return;
  }

  int cur = frnt;
  do
  {
    std::cout << data[cur] << " ";
    cur = (cur + 1) % capacity;
  } while (cur != bck);

  std::cout << std::endl;

}

template<typename T>
void Queue<T>::dequeue() {
  if (empty()) return;
  frnt = (frnt + 1) % capacity; // move the frnt index one position. we use modulus so frnt can wrap around (a circular array)
  queueSize--;
}

template<typename T>
void Queue<T>::clear() {
  frnt = bck = 0; // reset both indices back to 0, effectively clearing it. (conceptually, the elements are physically still there but that doesnt matter since we can only access elements using the frnt and bck indices)
  queueSize = 0;
}

template<typename T>
const T& Queue<T>::front() const {
  // if empty, we must throw an error. we cant return nothing
  if (empty()) {
    throw std::string("Empty Queue");
  }
  return data[frnt];
}