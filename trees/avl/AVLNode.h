#ifndef AVLNODE_H
#define AVLNODE_H

template<typename T>
class AVLNode {
public:
  T data;
  AVLNode<T>* left;
  AVLNode<T>* right;
  int height;

  AVLNode(const T& val = T(), AVLNode<T>* left = nullptr, AVLNode<T>* right = nullptr) {
    data = val;
    this->left = left;
    this->right = right;
    height = 1;
  }

};




#endif