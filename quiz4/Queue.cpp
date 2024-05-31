#include "Queue.h"
#include <iostream>


template<typename T>
Queue<T>::Queue(unsigned capacity) {
  //create an array
  data = new T[capacity];
  frnt = bck = 0;
  this->capacity = capacity;
  queueSize = 0;
}

template<typename T>
void Queue<T>::dequeue() {
  if (!empty()) {
    frnt = (frnt + 1) % capacity;
    queueSize--;
  }
}

template<typename T>
unsigned Queue<T>::size() const {
  return queueSize;
}


template<typename T>
bool Queue<T>::empty() const {
  return (queueSize == 0);
}

template<typename T>
bool Queue<T>::full() const {
  return (queueSize == capacity);
}

template<typename T>
void Queue<T>::enqueue(const T& val) {
  if (!full()) {
    data[bck] = val; //set the last element with the given value
    bck = (bck + 1) % capacity; //change the location of the next last element
    queueSize++;
  }
}

template<typename T>
void Queue<T>::clear() {
  frnt = bck = 0;
  queueSize = 0;
}

template<typename T>
void Queue<T>::print() const {
  if (empty()) {
    std::cout << "Empty queue\n";
    return;
  }
  std::cout << '[';
  int cur = frnt;
  do
  {
    std::cout << data[cur] << " ";
    cur = (cur + 1) % capacity;
  } while (cur != bck);

  std::cout << "]\n";
}

template<typename T>
const T& Queue<T>::front() const {
  if (empty()) {
    throw std::string("Emtpy queue");
  }
  else {
    return data[frnt];
  }
}