#include <iostream>
#include <cmath>


class Node {
public:
  int val;
  Node* next;
  Node(int v = 0, Node* n = nullptr) : val(v), next(n) {};
};

Node* reverse_list(Node* head);
Node* reverse_between(Node* head, int left, int right); // position, not index

int main() {

  Node* head = new Node(1);
  head->next = new Node(2);
  head->next->next = new Node(3);
  head->next->next->next = new Node(4);
  head->next->next->next->next = new Node(5);
  head->next->next->next->next->next = new Node(6);
  head->next->next->next->next->next->next = new Node(7);

  head = reverse_between(head, 1, 7);

  // print list
  Node* cur = head;
  while (cur) {
    std::cout << cur->val << " ";
    cur = cur->next;
  }

  return 0;
}

Node* reverse_list(Node* head) {
  if (!head || !head->next) {
    return head; // base case
  }
  else {
    Node* p = reverse_list(head->next);
    head->next->next = head;
    head->next = nullptr;

    return p;
  }
}

Node* reverse_between(Node* head, int left, int right) {
  // idk... i tried
  if (left >= right) {
    return head;
  }
  else {
    reverse_between(head, left, right - 1);
  }

}


