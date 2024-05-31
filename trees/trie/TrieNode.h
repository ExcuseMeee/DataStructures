#ifndef TRIENODE_H
#define TRIENODE_H

#define ALPHABET_SIZE 26
class TrieNode {
public:
  TrieNode() : children{ nullptr }, endOfWord(false) {
    // for (int i = 0; i < ALPHABET_SIZE; i++) {
    //   children[i] = nullptr;
    // }
  }

  // the position of the child represents the "data". for example children[0] represents the char 'a' (because 'a' is the first letter in the alphabet)
  TrieNode* children[ALPHABET_SIZE]; 
  bool endOfWord;
};


#endif