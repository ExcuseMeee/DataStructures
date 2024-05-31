#ifndef BST_H
#define BST_H
#include "BTNode.h"

// in BST, the left child is less, right is greater
template<typename T>
class BST {
public:
  BST();
  ~BST();
  BST(const BST& other);

  bool empty() const;
  void insert(const T& val);
  void insert_recursive(const T& val); // TODO


  void preorder() const; // preorder traversal: root, left, right
  // when you print a BST inorder, it will be sorted! if not, then it's not a BST
  void inorder() const; // inorder traversal: left, root, right
  void postorder() const; // postorder travsersal: left, right, root

  void print() const;

  const T& get_min() const; // return smallest value
  const T& get_max() const; // return largest value
  int get_height() const;

  BTNode<T>* search(const T& val) const;
  BTNode<T>* search_recursive(const T& val) const;
  BTNode<T>* search_parent(const T& val) const;
  bool find_target(const T& val) const;


  void delete_node(const T& val);
  void remove(const T& val); // recursively delete node



private:
  BTNode<T>* root;

  void preorder(BTNode<T>* node) const;
  void inorder(BTNode<T>* node) const;
  void postorder(BTNode<T>* node) const;

  void print(const std::string& prefix, const BTNode<T>* node, bool isRight) const;

  void delete_leaf(BTNode<T>* child, BTNode<T>* parent);
  void delete_one_child(BTNode<T>* child, BTNode<T>* parent);

  const T& get_min(BTNode<T>* node) const; // return smallest value starting at given node

  int getDeepestLevel(BTNode<T>* node, int level) const;
  void copyTree(BTNode<T>* node);
  bool findTargetHelper(BTNode<T>* node, const T& val) const;
  BTNode<T>* search_recursive(const T& val, BTNode<T>* node) const;

  void remove(const T& val, BTNode<T>*& node);
  void insert_recursive(const T& val, BTNode<T>*& node);

  int get_balance(const BTNode<T>* node) const;

  void rotate_right(BTNode<T>*& node);
  void rotate_right_double(BTNode<T>*& node);
  void rotate_left(BTNode<T>*& node);
  void rotate_left_double(BTNode<T>*& node);
  void balance(BTNode<T>*& node);

};


#endif