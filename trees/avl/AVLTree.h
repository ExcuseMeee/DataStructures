#ifndef AVLTREE_H
#define AVLTREE_H
#include "AVLNode.h"
#include <string>
template <typename T>
class AVLTree {
public:
  AVLTree();
  void print() const;
  void insert(const T& val);
  void remove(const T& val);
  int size() const;

  AVLNode<T>* findKSmallest(int k); // find the kth smallest node in tree. k=2 will find the 2nd smallest in the tree
  // void findKSmallest(int k); // find the kth smallest node in tree. k=2 will find the 2nd smallest in the tree

private:
  AVLNode<T>* root;
  void print(const std::string& prefix, const AVLNode<T>* node, bool isRight) const;
  void insert(const T& val, AVLNode<T>*& node);
  void rotate_right(AVLNode<T>*& node);
  void rotate_left(AVLNode<T>*& node);
  void rotate_right_double(AVLNode<T>*& node);
  void rotate_left_double(AVLNode<T>*& node);
  void balance(AVLNode<T>*& node);
  int get_height(AVLNode<T>* node) const;
  void remove(const T& val, AVLNode<T>*& node);
  const T& get_min(AVLNode<T>* node) const;
  int size(AVLNode<T>* node) const;

  AVLNode<T>* findKSmallest(int k, AVLNode<T>* node, int& i);
  // void findKSmallest(int k, AVLNode<T>* node, int i);

};
#endif
