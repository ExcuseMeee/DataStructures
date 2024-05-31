#include "Trie.h"


Trie::Trie() {
  root = nullptr;
}

void Trie::insert(const std::string& word) {
  if (!root) {
    root = new TrieNode();
  }

  TrieNode* cur = root;
  for (int i = 0; i < word.size(); i++) {
    int index = word[i] - 'a';
    if (!cur->children[index]) {
      // if there is no node representing this letter, create it!
      cur->children[index] = new TrieNode();
    }

    cur = cur->children[index];

  }

  cur->endOfWord = true;

}

bool Trie::search(const std::string& word) const {
  if (!root) {
    return false;
  }

  TrieNode* cur = root;
  for (int i = 0; i < word.size(); i++) {
    int index = word[i] - 'a';
    if (!cur->children[index]) return false;
    cur = cur->children[index]; // move to the node representing this char

  }

  // we are at last letter of word after loop

  return cur->endOfWord;

}

void Trie::remove(const std::string& word) {
  if (!root) return;

  TrieNode* cur = root;
  for (int i = 0; i < word.size(); i++) {
    int index = word[i] - 'a';
    if(!cur->children[index]) return; // if we can't get to the end of the word, word doesn't exist, so return.
    cur = cur->children[index]; // move to the next node
  }

  cur->endOfWord = false; // set endOfWord to false

}