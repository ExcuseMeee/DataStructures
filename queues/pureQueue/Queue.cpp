#include <string>

template<typename T>
class Node {
public:
  T data;
  Node<T>* next;

  Node(const T& data = T()){
    this->data = data;
    this->next = nullptr;
  }

};

// pure queue using SLList-like structure (no sentinel nodes)
template<typename T>
class Queue {
public:
  Node<T>* frontNode; // sentinel node
  Node<T>* rearNode; // sentinel node

  Queue(){
    frontNode = nullptr;
    rearNode = nullptr;
  }

  void push(const T& val) {

  }



  T& front() const {
    if(!frontNode) throw std::string("[front] empty queue");

    return frontNode->data;
  }

};
