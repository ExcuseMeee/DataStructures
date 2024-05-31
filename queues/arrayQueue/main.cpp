#include <iostream>
#include "Queue.h"
#include "Queue.cpp"

int main(){

  // Queue<int> q = Queue<int>();

  // q.enqueue(1);
  // q.enqueue(2);
  // q.enqueue(3);
  // q.enqueue(4);
  // q.enqueue(5);
  // q.enqueue(6);
  // q.print();

  Queue<int> n = Queue<int>();
  n.enqueue(1);
  n.enqueue(2);
  n.enqueue(3);
  n.enqueue(4);
  n.enqueue(5);
  n.print();

  Queue<int> k = Queue<int>();
  k.print();

  k = n;
  k.print();



  return 0;
}
