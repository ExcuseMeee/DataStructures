#ifndef BTNODE_H
#define BTNODE_H

template<typename T>
class BTNode
{
public:
  BTNode(const T& val = T(), BTNode<T>* l = nullptr, BTNode<T>* r = nullptr) : data(val), left(l), right(r) {}

  T data;
  BTNode<T>* left; // left child
  BTNode<T>* right; // right child



};



#endif