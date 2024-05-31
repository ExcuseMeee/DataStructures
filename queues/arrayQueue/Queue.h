#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Queue {
public:
  Queue(unsigned capacity = 10);
  // BIG THREE (destructor, copy, assignment)
  ~Queue();
  Queue(const Queue<T>& other);
  Queue<T>& operator=(const Queue<T>& other);
  

  unsigned size() const;
  bool empty() const;
  bool full() const;
  void print() const;

  void enqueue(const T& val); // add value to back of queue
  void dequeue(); // remove value from the front of queue
  void clear(); // empty the queue

  const T& front() const; // return the first element in queue (readonly)

private:
  T* data; // pointer to array that will actually hold the data
  unsigned queueSize; // how many elements in queue
  unsigned capacity; // how many elements queue can hold
  int frnt; // index of the first element in queue
  int bck; // index of the last position in queue (we enqueue to the back)
};


#endif