#include "AVLTree.h"
#include <iostream>
#include <algorithm>


using std::max;
template <typename T>
AVLTree<T>::AVLTree() {
  this->root = nullptr;
}


template <typename T>
void AVLTree<T>::print() const {
  print("", root, false);
}

template <typename T>
void AVLTree<T>::print(const std::string& prefix, const AVLNode<T>* node, bool isRight) const {
  if (node != nullptr) {
    std::cout << prefix;
    std::cout << (isRight ? "R--" : "L--");
    int heightLeft = get_height(node->left);
    int heightRight = get_height(node->right);
    int balance = heightLeft - heightRight;
    std::cout << node->data << ", " << balance << std::endl;

    // enter next tree level
    print(prefix + "   ", node->right, true);
    print(prefix + "   ", node->left, false);

  }
}

template <typename T>
void AVLTree<T>::insert(const T& val) {
  insert(val, root);
}

template <typename T>
void AVLTree<T>::insert(const T& val, AVLNode<T>*& node) {
  if (!node) {
    node = new AVLNode<T>(val);
    return;
  }

  if (val < node->data) {
    insert(val, node->left);
  }
  else if (val > node->data) {
    insert(val, node->right);
  }

  node->height = max(get_height(node->left), get_height(node->right)) + 1;

  balance(node);

}

template <typename T>
void AVLTree<T>::balance(AVLNode<T>*& node) {
  if (!node) return;

  int heightLeft = get_height(node->left);
  int heightRight = get_height(node->right);
  int node_balance = heightLeft - heightRight;

  if (node_balance < -1) {
    // right-unbalanced
    if (get_height(node->right->right) >= get_height(node->right->left)) {
      rotate_left(node);
    }
    else {
      rotate_left_double(node);
    }
  }
  if (node_balance > 1) {
    // left-unbalanced
    if (get_height(node->left->left) >= get_height(node->left->right)) {
      rotate_right(node);
    }
    else {
      rotate_right_double(node);
    }
  }
}

template <typename T>
void AVLTree<T>::rotate_right(AVLNode<T>*& node) {
  if (!node || !node->left) return;

  AVLNode<T>* left_kid = node->left;
  node->left = left_kid->right;
  left_kid->right = node;

  // update heights of nodes
  node->height = max(get_height(node->left), get_height(node->right)) + 1;
  left_kid->height = max(get_height(left_kid->left), get_height(left_kid->right)) + 1;

  node = left_kid;
}

template <typename T>
void AVLTree<T>::rotate_left(AVLNode<T>*& node) {
  if (!node || !node->right) return;

  AVLNode<T>* right_kid = node->right;
  node->right = right_kid->left;
  right_kid->left = node;

  // update heights of nodes
  node->height = max(get_height(node->right), get_height(node->left)) + 1;
  right_kid->height = max(get_height(right_kid->right), get_height(right_kid->left)) + 1;

  node = right_kid;
}

template <typename T>
void AVLTree<T>::rotate_right_double(AVLNode<T>*& node) {
  if (!node || !node->left) {
    return;
  }
  rotate_left(node->left);
  rotate_right(node);
}

template <typename T>
void AVLTree<T>::rotate_left_double(AVLNode<T>*& node) {
  if (!node || !node->right) {
    return;
  }
  rotate_right(node->right);
  rotate_left(node);
}

template <typename T>
int AVLTree<T>::get_height(AVLNode<T>* node) const {
  if (!node) return 0;
  else return node->height;

}

template <typename T>
void AVLTree<T>::remove(const T& val) {
  remove(val, this->root);
}
template <typename T>
void AVLTree<T>::remove(const T& val, AVLNode<T>*& node) {
  if (!node) return;

  if (val < node->data) {
    remove(val, node->left);
  }
  else if (val > node->data) {
    remove(val, node->right);
  }
  else if (node->left && node->right) { // two children
    node->data = get_min(node->right);
    remove(node->data, node->right);
  }
  else { // leaf or one child
    AVLNode<T>* to_delete = node;

    node = node->left ? node->left : node->right;

    delete to_delete;
  }

  // update height
  if (node) node->height = max(get_height(node->left), get_height(node->right)) + 1;

  balance(node);

}
template <typename T>
const T& AVLTree<T>::get_min(AVLNode<T>* node) const {
  if (!node) {
    throw std::string("Error:get_min\n");
  }
  else {
    AVLNode<T>* cur = node;
    while (cur->left) {
      cur = cur->left;
    }
    return cur->data;
  }
}

template<typename T>
int AVLTree<T>::size() const {
  return size(this->root);
}
template<typename T>
int AVLTree<T>::size(AVLNode<T>* node) const {
  if (!node) return 0;

  return 1 + size(node->left) + size(node->right);

}

template<typename T>
AVLNode<T>* AVLTree<T>::findKSmallest(int k) {
  int i = 0;
  return findKSmallest(k, this->root, i);
}

template<typename T>
AVLNode<T>* AVLTree<T>::findKSmallest(int k, AVLNode<T>* node, int& i) {
  if (!node) return nullptr;
  
  AVLNode<T>* left = findKSmallest(k, node->left, i);
  if (k == ++i) return node;
  AVLNode<T>* right = findKSmallest(k, node->right, i);

  return (left != nullptr) ? left : right;


}
