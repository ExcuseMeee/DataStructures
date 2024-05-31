#ifndef TRIE_H
#define TRIE_H
#include "TrieNode.h"
#include <string>

class Trie {
public:
  Trie();
  void insert(const std::string& word);
  bool search(const std::string& word) const;
  void remove(const std::string& word);

private:
  TrieNode* root;
};


#endif