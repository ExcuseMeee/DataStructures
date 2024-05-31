#include <iostream>
using namespace std;

class Node {
public:
  int val;
  Node* next;
  Node(int x) {
    val = x;
    next = NULL;
  }
};

class FrontMiddleBackQueue {
public:
  Node* front, * back; // nodes point toward the back of the line, back points to nullptr
  int size;

  FrontMiddleBackQueue() {
    front = back = nullptr;
    size = 0;
  }

  void pushFront(int val) {
    if (size == 0) {
      front = back = new Node(val);
    }
    else {
      Node* newNode = new Node(val);
      newNode->next = front;
      front = newNode;
    }
    size++;
  }

  void pushMiddle(int val) {
    int midPosition = size / 2; // fractional values are truncated
    if (size == 0 || midPosition == 0) {
      pushFront(val);
    }
    else {
      Node* cur = front;
      // loop until the node before position mid
      for (int i = 0; i < midPosition - 1; i++) {
        cur = cur->next;
      }
      Node* newNode = new Node(val);
      newNode->next = cur->next;
      cur->next = newNode;
      size++;
    }
  }





  void pushBack(int val) {
    if (size == 0) {
      pushFront(val);
    }
    else {
      back->next = new Node(val);
      back = back->next;
      size++;
    }
  }

  int popFront() {
    if (size == 0) return -1;
    Node* oldFront = front;
    int data = oldFront->val;
    if (front == back) {
      front = back = nullptr;
    }
    else {
      front = front->next;
    }
    size--;
    delete oldFront;
    return data;
  }

  int popMiddle() {
    if (size == 0) return -1;
    int midIndex = (size - 1) / 2;
    if (midIndex == 0) {
      return popFront();
    }
    else {
      Node* cur = front;
      // loop until node before midIndex
      for (int i = 0; i < midIndex - 1; i++) {
        cur = cur->next;
      }
      Node* midNode = cur->next;
      int data = midNode->val;
      cur->next = cur->next->next;
      size--;
      delete midNode;
      return data;
    }
  }

  int popBack() {
    if (size == 0) return -1;
    if (size == 1) {
      return popFront();
    }
    else {
      Node* cur = front;
      // loop until node before back node
      while (cur->next != back) {
        cur = cur->next;
      }
      Node* oldBack = back;
      int data = oldBack->val;
      cur->next = nullptr;
      back = cur;
      size--;
      delete oldBack;
      return data;
    }
  }
  void reverse() {
    if (size == 0) return;
    Node* curNode = front;
    Node* prevNode = nullptr;
    Node* nextNode = front->next;
    while (curNode != nullptr) {
      curNode->next = prevNode;
      prevNode = curNode;
      curNode = nextNode;
      nextNode = nextNode != nullptr ? nextNode->next : nullptr;
    }
    back = front;
    front = prevNode;
  }
};


int main() {
  
  FrontMiddleBackQueue q;

  // Test case 1: Pushing elements to the front, middle, and back of the queue
  q.pushFront(1);   // 1
  q.pushMiddle(2); // 2 1
  q.pushBack(3);  // 2 1 3
  q.pushMiddle(4); // 2 4 1 3
  q.pushMiddle(5); // 2 4 5 1 3
  q.pushFront(6); // 6 2 4 5 1 3



  // Expected output: 6 2 4 5 1 3
  Node* temp = q.front;
  while (temp) {
    cout << temp->val << " ";
    temp = temp->next;
  }
  cout << endl;

  // Test case 2: Popping elements from the front, middle, and back of the queue
  cout << q.popFront() << endl;  // Expected output: 6
  cout << q.popMiddle() << endl; // Expected output: 5
  cout << q.popBack() << endl;   // Expected output: 3
  cout << q.popMiddle() << endl;   // Expected output: 4

  // Expected output after popping: 2 1
  temp = q.front;
  while(temp) {
      cout << temp->val << " ";
      temp = temp->next;
  }
  cout << endl;

  // Edge case: Popping elements from an empty queue
  FrontMiddleBackQueue q2;
  cout << q2.popFront() << endl;  // Expected output: -1
  cout << q2.popMiddle() << endl; // Expected output: -1
  cout << q2.popBack() << endl;   // Expected output: -1


  // Edge case: Popping elements from a queue of size 1
  FrontMiddleBackQueue q3;
  q3.pushFront(1);
  cout << q3.popFront() << endl;  // Expected output: -1
  q3.pushFront(1);
  cout << q3.popMiddle() << endl; // Expected output: -1
  q3.pushFront(1);
  cout << q3.popBack() << endl;   // Expected output: -1
  
  FrontMiddleBackQueue q4;

  // Test case 3: reversing the queue
  q4.pushFront(1);
  q4.pushFront(2);
  q4.pushFront(3);
  q4.pushFront(4);
  q4.reverse();

  temp = q4.front;
  while(temp) {
      cout << temp->val << " ";
      temp = temp->next;
  }
  cout << endl;

  /*
  */

  return 0;

}
