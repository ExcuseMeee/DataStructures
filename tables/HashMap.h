#ifndef HASHMAP_H
#define HASHMAP_H
#include <vector>
#include "HashNode.h"

template<typename K, typename V>
class HashMap {
public:
  HashMap(unsigned capacity = 101);
  ~HashMap();
  bool empty() const;
  bool full() const;
  void insert(const K& key, const V& value);

  void display() const;

  const V search(const K& key) const;

  void remove(const K& key);

private:
  std::vector<HashNode<K, V>*> data; // we store pointers to allow for null values
  HashNode<K,V>* dummy; // represents a deleted node 
  int n; // size of table (how many nodes are there?)
  int search_index(const K& key) const; // return position in map of record having the given key

  // int nextPrime(int starting) const; // finds next prime starting from starting

  int hash(const K& key) const;


};


#endif