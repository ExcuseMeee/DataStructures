#ifndef TRIENODE_H
#define TRIENODE_H

#define ALPHABET_SIZE 26

class TrieNode {
public:
  TrieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      children[i] = nullptr;
    }

    endOfWord = false;
  }

  TrieNode* children[ALPHABET_SIZE];
  bool endOfWord;
};

#endif

#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>


class Trie {
public:
  Trie();
  Trie(const std::vector<std::string>& v);
  bool empty() const;
  void insert(const std::string& word);
  bool search(const std::string& word) const;

  int count_words() const;
  void print() const;
  int longest_word() const;

private:
  int count_words(TrieNode* node) const;
  void print(TrieNode* node, std::string prefix, int index) const;
  int longest_word(TrieNode* node, int length, int longest) const;
  TrieNode* root;
};

#endif

#include <iostream>

Trie::Trie() : root(nullptr) {}

Trie::Trie(const std::vector<std::string>& v) {
  this->root = nullptr;
  for (const std::string& s : v) {
    this->insert(s);
  }
}

bool Trie::empty() const {
  return (root == nullptr);
}

void Trie::insert(const std::string& word) {
  if (empty()) {
    root = new TrieNode();
  }
  TrieNode* cur = root;

  for (int i = 0; i < word.size(); i++) {
    int index = word[i] - 'a';
    if (!cur->children[index]) {
      cur->children[index] = new TrieNode();
    }

    cur = cur->children[index];
  }
  cur->endOfWord = true;
}

bool Trie::search(const std::string& word) const {
  if (empty()) {
    return false;
  }
  TrieNode* cur = root;

  for (int i = 0; i < word.size(); i++) {
    int index = word[i] - 'a';
    if (!cur->children[index]) {
      return false;
    }

    cur = cur->children[index];
  }

  return (cur->endOfWord);
}

int Trie::count_words() const {
  return count_words(this->root);
}

int Trie::count_words(TrieNode* node) const {
  if (!node) return 0;

  int count = 0;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    TrieNode* n = node->children[i];
    if (n && n->endOfWord) count++; // check if this node is end of word
    count += count_words(n); // check children of this node
  }

  return count;

}

void Trie::print() const {
  std::cout << "[print]" << std::endl;
  print(root, "", 0);
}

void Trie::print(TrieNode* node, std::string prefix, int charCode) const {
  if (!node) return;

  std::string str = prefix + char(charCode); // continually construct word

  if (node->endOfWord) std::cout << str << std::endl; // print if is word


  for (int i = 0; i < ALPHABET_SIZE; i++) {
    print(node->children[i], str, 'a' + i);
  }

}

int Trie::longest_word() const {
  return longest_word(root, 0, 0);
}

int Trie::longest_word(TrieNode* node, int length, int longest) const {
  if (!node) return longest;

  if (node->endOfWord) longest = length;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    int len = longest_word(node->children[i], length + 1, longest); // get longest length of children
    if (len > longest) longest = len;
  }

  return longest;

}

int main() {

  std::vector<std::string> s = { "pickle", "squiggle", "bumblebee", "whippersnapper", "jellybean", "noodle", "kerplunk", "giggle", "muffin", "penguin" };

  Trie test = Trie(s);

  std::cout << "Word Count: " << test.count_words() << std::endl;
  test.print();
  std::cout << "Longest word length: " << test.longest_word() << std::endl;



  return 0;
}