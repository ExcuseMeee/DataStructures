#include <iostream>
#include "BST.h"

template<typename T>
BST<T>::BST() : root(nullptr) {}

template<typename T>
BST<T>::~BST() {
  while (!empty()) {
    delete_node(root->data);
  }
}

template<typename T>
BST<T>::BST(const BST& other) {
  this->root = nullptr;
  this->copyTree(other.root);
}

template<typename T>
bool BST<T>::empty() const {
  return root == nullptr;
}

template<typename T>
void BST<T>::insert(const T& val) {
  if (empty()) {
    root = new BTNode<T>(val);
    return;
  }

  BTNode<T>* cur = root;
  BTNode<T>* prev = root;

  while (cur != nullptr) {
    prev = cur;
    if (val < cur->data) {
      cur = cur->left;
    }
    else {
      cur = cur->right;
    }

  }
  // cur is now nullptr, prev is parent of cur
  if (val < prev->data) {
    prev->left = new BTNode<T>(val);

  }
  else {
    prev->right = new BTNode<T>(val);
  }

}

template<typename T>
void BST<T>::preorder() const {
  std::cout << "Preorder [ ";
  preorder(root);
  std::cout << "]" << std::endl;
}

template<typename T>
void BST<T>::inorder() const {
  std::cout << "Inorder [ ";
  inorder(root);
  std::cout << "]" << std::endl;
}

template<typename T>
void BST<T>::postorder() const {
  std::cout << "Postorder [ ";
  postorder(root);
  std::cout << "]" << std::endl;
}

template<typename T>
void BST<T>::print() const {
  if (empty()) {
    std::cout << "[print] empty tree" << std::endl;
    return;
  }
  std::cout << "[print] " << std::endl;
  print("", root, false);
}

template<typename T>
void BST<T>::preorder(BTNode<T>* node) const {
  if (!node) {
    return;
  }
  else {
    std::cout << node->data << " "; // immediately print (this is parent)
    preorder(node->left); // traverse left (this will print left child)
    preorder(node->right); // after traversing, traverse right (this will print right child)
    // overall print order is: parent, left, right
  }
}

template<typename T>
void BST<T>::inorder(BTNode<T>* node) const {
  if (!node) {
    return;
  }
  else {
    inorder(node->left); // traverse left (this will print left child)
    std::cout << node->data << " "; // (this is parent)
    inorder(node->right); // travervse right (this will print right child)
    // overall print order is: left, parent, right
  }
}

template<typename T>
void BST<T>::postorder(BTNode<T>* node) const {
  if (!node) {
    return;
  }
  else {
    postorder(node->left); // traverse left (this will print left child)
    postorder(node->right); // travervse right (this will print right child)
    std::cout << node->data << " "; // print after left and right node prints
    // overall print order is: left, right, parent
  }
}

template<typename T>
void BST<T>::print(const std::string& prefix, const BTNode<T>* node, bool isRight) const {
  if (node != nullptr) {
    std::cout << prefix;
    std::cout << (isRight ? "R--" : "L--");
    std::cout << node->data << ", " << get_balance(node) << std::endl;

    // enter next tree level
    print(prefix + "   ", node->right, true);
    print(prefix + "   ", node->left, false);

  }
}

template<typename T>
const T& BST<T>::get_min() const {
  BTNode<T>* cur = root;

  if (empty()) throw std::string("Empty Tree");

  // loop until we are at the last left node
  while (cur->left != nullptr) {
    cur = cur->left;
  }

  return cur->data;
}

template<typename T>
const T& BST<T>::get_min(BTNode<T>* node) const {
  BTNode<T>* cur = node;

  if (empty()) throw std::string("Empty Tree");

  // loop until we are at the last left node
  while (cur->left != nullptr) {
    cur = cur->left;
  }

  return cur->data;
}

template<typename T>
const T& BST<T>::get_max() const {
  BTNode<T>* cur = root;

  if (empty()) throw std::string("Empty Tree");

  // loop until we are at the last right node
  while (cur->right != nullptr) {
    cur = cur->right;
  }

  return cur->data;
}

template<typename T>
BTNode<T>* BST<T>::search(const T& val) const {
  if (empty()) throw std::string("Empty Tree");

  BTNode<T>* cur = root;

  while (cur != nullptr) {
    if (cur->data > val) {
      cur = cur->left;
    }
    else if (cur->data < val) {
      cur = cur->right;
    }
    else if (cur->data == val) {
      return cur;
    }
  }

  return nullptr; // node not found

}

template<typename T>
BTNode<T>* BST<T>::search_parent(const T& val) const {
  if (empty()) throw std::string("Empty Tree");
  if (root->data == val) return nullptr;

  BTNode<T>* cur = root;
  BTNode<T>* parent = root;


  while (cur != nullptr) {
    if (cur->data > val) {
      parent = cur;
      cur = cur->left;
    }
    else if (cur->data < val) {
      parent = cur;
      cur = cur->right;
    }
    else if (cur->data == val) {
      return parent;
    }
  }

  return nullptr; // no parent of node

}

template<typename T>
void BST<T>::delete_node(const T& val) {
  if (empty()) throw std::string("Empty tree");

  BTNode<T>* node = search(val);

  if (!node) throw std::string("No node");

  BTNode<T>* parent = search_parent(val);

  if (!node->left && !node->right) {
    // leaf node. no children
    delete_leaf(node, parent);
  }
  else if (!node->left || !node->right) {
    // only one child missing
    delete_one_child(node, parent);

  }
  else if (node->left && node->right) {
    // to delete node with 2 children, find min node of the RIGHT subtree. replace node with found min node and delete min node

    // find min node
    T min = get_min(node->right);
    BTNode<T>* min_node = search(min);

    // delete the min node (2 cases: min node has NO child or ONE child)
    if (!min_node->left && !min_node->right) {
      delete_leaf(min_node, search_parent(min));
    }
    else if (!min_node->left || !min_node->right) {
      delete_one_child(min_node, search_parent(min));
    }

    node->data = min; // set node to found min value

  }
  else {
    // wtf
  }

}

template<typename T>
void BST<T>::delete_leaf(BTNode<T>* child, BTNode<T>* parent) {
  if (!child) throw std::string("[delete_leaf] no node to delete");

  if (!parent) {
    // if no parent, aka root node
    delete root;
    root = nullptr;
    return;
  }

  if (parent->left == child) {
    // child is the left kid
    parent->left = nullptr;

  }
  else if (parent->right == child) {
    // child is the right kid
    parent->right = nullptr;
  }
  else {
    // child is neither left or right kid of parent
    throw std::string("[delete_leaf] invalid child of parent");
  }

  delete child; // release memory


}

template<typename T>
void BST<T>::delete_one_child(BTNode<T>* child, BTNode<T>* parent) {
  // child itself has one kid.

  if (!child) throw std::string("[delete_one_child] no node to delete");

  if (child->left && child->right) throw std::string("[delete_one_child] node has two children");

  if (child == root) {
    // deleting root node (should only have exactly 1 child)
    // puts("WDWd");
    root = child->left ? child->left : child->right;
  }
  else {
    // delete non root node

    // check if child has left or right kid
    if (child->left && !child->right) {
      // child has left kid

      if (child == parent->left) {
        // child is left of parent
        parent->left = child->left; // replace child with its kid (child->left). so parent points left to kid

      }
      else if (child == parent->right) {
        // child is right of parent
        parent->right = child->left; // replace child with its kid (child->left). so parent points right to kid
      }

    }
    else if (child->right && !child->left) {
      // child has right kid

      if (child == parent->left) {
        // child is left of parent
        parent->left = child->right; // replace child with its kid (child->right). so parent points left to kid

      }
      else if (child == parent->right) {
        // child is right of parent
        parent->right = child->right; // replace child with its kid (child->right). so parent points right to kid
      }

    }
    else {
      throw std::string("[delete_one_child] node has no children");
    }
  }

  delete child;

}

template<typename T>
int BST<T>::get_height() const {
  return getDeepestLevel(root, 1);
}

template<typename T>
int BST<T>::getDeepestLevel(BTNode<T>* node, int level) const {
  if (!node) return 0; // if no node, no level
  if (!node->left && !node->right) return level; // if leaf, return its level

  int leftLevel = getDeepestLevel(node->left, level + 1); // get level of left node
  int rightLevel = getDeepestLevel(node->right, level + 1); // get level of right node

  int max = leftLevel > rightLevel ? leftLevel : rightLevel; // propagate max level
  return max;
}

template<typename T>
void BST<T>::copyTree(BTNode<T>* node) {
  if (!node) return;

  this->insert(node->data);

  copyTree(node->left);
  copyTree(node->right);
}

template<typename T>
bool BST<T>::find_target(const T& val) const {
  return findTargetHelper(root, val);
}

template<typename T>
bool BST<T>::findTargetHelper(BTNode<T>* node, const T& val) const {
  if (!node) return false;

  T difference = val - node->data;
  BTNode<T>* foundNode = this->search(difference);

  if (foundNode && (foundNode != node)) {
    return true;
  }
  else {
    bool leftFound = findTargetHelper(node->left, val);
    bool rightFound = findTargetHelper(node->right, val);
    return (leftFound || rightFound);
  }
}

template<typename T>
BTNode<T>* BST<T>::search_recursive(const T& val) const {
  if (empty()) throw std::string("[search_recursive] empty tree");
  BTNode<T>* node = search_recursive(val, root);

  return node;

}

template<typename T>
BTNode<T>* BST<T>::search_recursive(const T& val, BTNode<T>* node) const {
  if (!node) return nullptr;

  if (node->data == val) return node;

  BTNode<T>* left = search_recursive(val, node->left);
  BTNode<T>* right = search_recursive(val, node->right);

  return (left == nullptr ? right : left);

}

template<typename T>
void BST<T>::remove(const T& val) {
  remove(val, root);
}

template<typename T>
void BST<T>::remove(const T& val, BTNode<T>*& node) {
  if (!node) return;

  if (val < node->data) {
    remove(val, node->left);
  }
  else if (val > node->data) {
    remove(val, node->right);
  }
  else if (node->left && node->right) {
    node->data = get_min(node->right);
    remove(node->data, node->right);
  }
  else {
    BTNode<T>* to_delete = node;

    node = node->left ? node->left : node->right;

    delete to_delete;
  }

  balance(node); // do not ask me why this works

}

template<typename T>
void BST<T>::insert_recursive(const T& val) {
  insert_recursive(val, root);
}

template<typename T>
void BST<T>::insert_recursive(const T& val, BTNode<T>*& node) {

  if (!node) {
    node = new BTNode<T>(val);
    return;
  }

  if (val > node->data) {
    insert_recursive(val, node->right);
  }
  else if (val < node->data) {
    insert_recursive(val, node->left);
  }

  balance(node);

  // two-liner for fun
  // if (!node) node = new BTNode<T>(val);
  // else insert_recursive(val, (val > node->data ? node->right : node->left));

}

template<typename T>
int BST<T>::get_balance(const BTNode<T>* node) const {
  if (!node) {
    return 0;
  }

  return getDeepestLevel(node->left, 1) - getDeepestLevel(node->right, 1);

}

template<typename T>
void BST<T>::rotate_right(BTNode<T>*& node) {
  if (!node || !node->left) return;

  BTNode<T>* left_kid = node->left;
  node->left = left_kid->right;
  left_kid->right = node;
  node = left_kid;

}

template<typename T>
void BST<T>::rotate_left(BTNode<T>*& node) {
  if (!node || !node->right) return;

  BTNode<T>* right_kid = node->right;
  node->right = right_kid->left;
  right_kid->left = node;
  node = right_kid; // set the node POINTER REFERENCE to the right_kid POINTER. we ARE NOT copying right_kid to node.

}

template<typename T>
void BST<T>::rotate_right_double(BTNode<T>*& node) {
  if (!node || !node->left) return;

  rotate_left(node->left);
  rotate_right(node);

}

template<typename T>
void BST<T>::rotate_left_double(BTNode<T>*& node) {
  if (!node || !node->right) return;

  rotate_right(node->right);
  rotate_left(node);

}

template<typename T>
void BST<T>::balance(BTNode<T>*& node) {
  if (!node) return;

  int node_balance = get_balance(node);
  if (node_balance < -1) {
    // right-unbalanced
    if (getDeepestLevel(node->right->right, 1) >= getDeepestLevel(node->right->left, 1)) {
      rotate_left(node);
    }
    else {
      rotate_left_double(node);
    }
  }
  if (node_balance > 1) {
    // left-unbalanced
    if (getDeepestLevel(node->left->left, 1) >= getDeepestLevel(node->left->right, 1)) {
      rotate_right(node);
    }
    else {
      rotate_right_double(node);
    }
  }
}