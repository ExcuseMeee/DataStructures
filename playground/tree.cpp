#include <iostream>
#include <string>

template<typename T>
class Node {
public:
  Node(const T& data = T(), Node<T>* left = nullptr, Node<T>* right = nullptr) {
    this->data = data;
    this->left = left;
    this->right = right;
  }

  T data;
  Node<T>* left;
  Node<T>* right;
};

template<typename T>
class AVL {
public:
  AVL() {
    this->root = nullptr;
  }

  void insert(const T& val) {
    insert(val, this->root);
  }

  bool empty() const {
    return this->root == nullptr;
  }

  void print() const {
    if (empty()) {
      std::cout << "[print] empty tree" << std::endl;
      return;
    }
    std::cout << "[print] " << std::endl;
    print("", root, false);
  }

  Node<T>* search(const T& val) {
    return search(val, root);
  }

  const T& getMin(const Node<T>* node) const {
    if (empty()) throw std::string("[getMin] empty tree");
    const Node<T>* cur = node;
    while (cur->left != nullptr) {
      cur = cur->left;
    }
    return cur->data;
  }

  void remove(const T& val) {
    remove(val, root);
  }

  int getHeight() const {
    return getHeight(root);
  }

  int getBalance(const Node<T>* node) const {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
  }

  int countLeaves(const Node<T>* node) const {
    if (!node) return 0;

    if (!node->left && !node->right) return 1;

    return countLeaves(node->left) + countLeaves(node->right);

  }

  Node<T>* getRoot() {
    return this->root;
  }

  int countNodes(const Node<T>* node) const {
    if (!node) return 0;

    return 1 + countNodes(node->left) + countNodes(node->right);

  }

  void rotateLeft(Node<T>*& node) {
    if (!node || !node->right) return;

    Node<T>* rightKid = node->right;

    node->right = rightKid->left;
    rightKid->left = node;
    node = rightKid;

  }

  void rotateRight(Node<T>*& node) {
    if (!node || !node->left) return;

    Node<T>* leftKid = node->left;
    node->left = leftKid->right;
    leftKid->right = node;
    node = leftKid;
  }

  void rotateLeftDouble(Node<T>*& node) {
    if (!node || !node->right) return;

    rotateRight(node->right);
    rotateLeft(node);
  }

  void rotateRightDouble(Node<T>*& node) {
    if (!node || !node->left) return;

    rotateLeft(node->left);
    rotateRight(node);
  }

  void balance(Node<T>*& node) {
    if (!node) return;

    int nodeBalance = getBalance(node);

    // left unbalanced
    if (nodeBalance > 1) {
      // we need to double rotate if leftKid is right-heavy (right subtree of leftKid is taller than left subtree)
      if (getHeight(node->left->right) > getHeight(node->left->left))
        rotateRightDouble(node);
      else
        rotateRight(node);
    }
    // right unbalanced
    else if (nodeBalance < -1) {
      // double rotate if rightKid left-heavy
      if (getHeight(node->right->left) > getHeight(node->right->right))
        rotateLeftDouble(node);
      else
        rotateLeft(node);
    }
  }

private:
  Node<T>* root;

  void insert(const T& val, Node<T>*& node) {
    if (!node) node = new Node<T>(val);

    if (val > node->data) insert(val, node->right);
    else if (val < node->data) insert(val, node->left);

    balance(node);
  }

  void print(const std::string& prefix, const Node<T>* node, bool isRight) const {
    if (node != nullptr) {
      std::cout << prefix;
      std::cout << (isRight ? "R--" : "L--");
      std::cout << node->data << std::endl;

      // enter next tree level
      print(prefix + "   ", node->right, true);
      print(prefix + "   ", node->left, false);

    }
  }

  Node<T>* search(const T& val, Node<T>* node) {
    if (!node) return nullptr;

    if (val > node->data) return search(val, node->right);
    else if (val < node->data) return search(val, node->left);
    else return node;
  }

  void remove(const T& val, Node<T>*& node) {
    if (!node) return;

    if (val > node->data) {
      remove(val, node->right);
    }
    else if (val < node->data) {
      remove(val, node->left);
    }
    else {
      // both kids
      if (node->left && node->right) {
        node->data = getMin(node->right);
        remove(node->data, node->right);
      }
      // one or zero kids
      else {
        Node<T>* to_delete = node;

        // copy either left or right kid to current. if zero kids, current node will be set to nullptr
        node = node->left ? node->left : node->right;

        delete to_delete;
      }

    }
    balance(node);
  }

  int getHeight(const Node<T>* node) const {
    if (!node) return 0;

    int left = getHeight(node->left);
    int right = getHeight(node->right);

    return 1 + (left > right ? left : right);

  }

};

int main() {

  try {

    AVL<int> tree;

    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(29);
    tree.insert(28);

    tree.remove(28);
    tree.remove(29);
    tree.remove(40);
    tree.remove(30);
    tree.remove(20);

    tree.print();

  }
  catch (const std::string& e) {
    std::cout << e << '\n';
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }



  return 0;
}