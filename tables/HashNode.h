#ifndef HASHNODE_H
#define HASHNODE_H

template<typename K, typename V>
class HashNode {
public:

  HashNode(const K& key, const V& value) {
    this->key = key;
    this->value = value;
  }

  K key;
  V value;
};


#endif