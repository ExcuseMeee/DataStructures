#include <iostream>
#include <string>
using namespace std;

// AVL tree node
struct Node {
  int value;
  Node* left, * right;
  int height;
};

// Get the height of the tree
int height(Node* N) {
  if (!N) return 0;
  else return N->height;
}

// Get the balance factor of the node
int getBalance(Node* N) {
  if (!N) return 0;
  return height(N->left) - height(N->right);

}

// Right rotate the subtree rooted with y
Node* rightRotate(Node* y) {
  if (!y || !y->left) throw string("[rightRotate] cannot rotate");
  Node* leftKid = y->left;
  y->left = leftKid->right;
  leftKid->right = y;

  y->height = max(height(y->left), height(y->right)) + 1;
  leftKid->height = max(height(leftKid->left), height(leftKid->right)) + 1;

  return leftKid; // have to return because we don't use ptr reference... lame!

}

// Left rotate the subtree rooted with x
Node* leftRotate(Node* x) {
  if (!x || !x->right) throw string("[leftRotate] cannot rotate");

  Node* rightKid = x->right;
  x->right = rightKid->left;
  rightKid->left = x;

  x->height = max(height(x->left), height(x->right)) + 1;
  rightKid->height = max(height(rightKid->left), height(rightKid->right)) + 1;

  return rightKid;

}

Node* rotate_right_double(Node* node) {
  if (!node || !node->left) {
    throw string("[rotate_right_double] cannot rotate");
  }
  node->left = leftRotate(node->left);
  return rightRotate(node);
}

Node* rotate_left_double(Node* node) {
  if (!node || !node->right) {
    throw string("[rotate_left_double] cannot rotate");
  }
  node->right = rightRotate(node->right);
  return leftRotate(node);
}

Node* balance(Node* node) {
  if (!node) throw string("[balance] no node");

  int node_balance = getBalance(node);

  if (node_balance < -1) {
    // right-unbalanced
    if (height(node->right->right) >= height(node->right->left)) {
      return leftRotate(node);
    }
    else {
      return rotate_left_double(node);
    }
  }
  if (node_balance > 1) {
    // left-unbalanced
    if (height(node->left->left) >= height(node->left->right)) {
      return rightRotate(node);
    }
    else {
      return rotate_right_double(node);
    }
  }

  return node;
}

// Insert a node into the AVL tree
Node* insert(Node* node, int value) {
  if (!node) {
    Node* n = new Node();
    n->value = value;
    n->height = 1;
    n->left = nullptr; n->right = nullptr;
    return n;
  }

  if (value > node->value) {
    node->right = insert(node->right, value);
  }
  else if (value < node->value) {
    node->left = insert(node->left, value);
  }

  node->height = max(height(node->left), height(node->right)) + 1;

  node = balance(node);

  return node;

}

void countGreaterNodes_helper(Node* node, int value, int& count) {
  // traverse tree in whatever order...update count when node value > value
  if (!node) return;
  countGreaterNodes_helper(node->right, value, count);
  if (node->value > value) count = count + 1;
  countGreaterNodes_helper(node->left, value, count);
}

// Function to count nodes greater than a given value
int countGreaterNodes(Node* node, int value) {
  int count = 0;
  countGreaterNodes_helper(node, value, count); // pass count by reference to update
  return count;
}


int main() {
  Node* root = nullptr;

  // Construct AVL tree
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 5);
  root = insert(root, 15);
  root = insert(root, 30);

  // Count nodes greater than key
  int key = 15;
  cout << "Number of nodes greater than " << key << ": " << countGreaterNodes(root, key) << endl;

  return 0;
}
