#include <iostream>
#include <string>
#include <vector>
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

class Trie {
public:
  Trie() : root(nullptr) {}

  Trie(const std::vector<std::string>& words) {
    this->root = nullptr;
    for (const std::string& s : words) {
      this->insertWord(s);
    }
  }

  bool empty() const {
    return root == nullptr;
  }

  void insertWord(const std::string& word) {
    if (empty()) root = new TrieNode();
    TrieNode* cur = root;
    for (const char c : word) {
      int index = c - 'a';
      if (cur->children[index] == nullptr) {
        cur->children[index] = new TrieNode();
      }
      cur = cur->children[index];
    }

    cur->endOfWord = true;
  }

  bool searchWord(const std::string& word) const {
    if (empty()) return false;
    TrieNode* cur = root;

    for (const char c : word) {
      int index = c - 'a';
      if (cur->children[index] == nullptr) return false;

      cur = cur->children[index];
    }
    return cur->endOfWord;
  }

  void print() const {
    print(root, "", '\0');
  }

  int countWords() const {
    return countWords(root);
  }

  int longestWord() const {
    return longestWord(root, 0);
  }


private:
  TrieNode* root;

  void print(TrieNode* node, std::string prefix, char character) const {
    if (!node) return;

    std::string word = prefix + character;

    if (node->endOfWord) std::cout << word << std::endl;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
      print(node->children[i], word, char('a' + i));
    }
  }

  int countWords(TrieNode* node) const {
    if (!node) return 0;

    int count = 0;
    if (node->endOfWord) count++;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
      count += countWords(node->children[i]);
    }

    return count;
  }

  int longestWord(TrieNode* node, int length) const {
    if (!node) return 0;

    int max = 0;

    if (node->endOfWord) max = length;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
      int len = longestWord(node->children[i], length + 1);
      if (len > max) max = len;
    }

    return max;



  }
};


int main() {

  std::vector<std::string> s = { "pickle", "squiggle", "bumblebee", "whippersnapper", "jellybean", "noodle", "kerplunk", "giggle", "muffin", "penguin" };

  Trie test = Trie(s);

  std::cout << "Word Count: " << test.countWords() << std::endl;
  test.print();
  std::cout << "Longest word length: " << test.longestWord() << std::endl;
  return 0;
}