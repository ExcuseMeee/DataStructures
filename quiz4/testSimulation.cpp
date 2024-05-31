#include "Stack.h"
#include "Stack.cpp"
#include "Queue.h"
#include "Queue.cpp"

#include <cstdlib>

void init(Queue<int>& q, Stack<int>& s);
void print(Queue<int>& q, Stack<int>& s);
void feed_students(Queue<int>& q, Stack<int>& s);


int main() {
  srand(time(0));
  Queue<int> students;
  Stack<int> sandwiches;
  init(students, sandwiches);
  std::cout << "Students came to caffeteria\n";
  print(students, sandwiches);

  feed_students(students, sandwiches);

  return 0;
}

void init(Queue<int>& q, Stack<int>& s) {
  for (int i = 0; i < 6; i++) {
    q.enqueue(rand() % 2);
    s.push(rand() % 2);
  }
}

void print(Queue<int>& q, Stack<int>& s) {
  std::cout << "Stud: ";
  q.print();
  std::cout << "Sndw: ";
  s.print();
}

void feed_students(Queue<int>& q, Stack<int>& s) {
  int rotations = 0;
  bool failed = false;
  while (q.size() != 0) {
    int limit = q.size();
    std::cout << "--------------------" << std::endl;
    int student = q.front();
    int sandwich = s.top();

    if (student == sandwich) {
      std::cout << "Student takes sandwich and leaves" << std::endl;
      q.dequeue();
      s.pop();
      print(q, s);
      rotations = 0;
    }
    else {
      std::cout << "Student goes to back of line" << std::endl;
      q.dequeue();
      q.enqueue(student);
      print(q, s);
      rotations++;
    }
    if (rotations == limit) {
      failed = true;
      break;
    }

  }
  if (failed) {
    std::cout << "STUDENTS STARVED TO DEATH" << std::endl;

  }
  else {
    std::cout << "ALL STUDENTS FED" << std::endl;

  }

}