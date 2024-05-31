#include <iostream>
#include <string>
#include "HashMap.h"
#include "HashNode.h"

template<typename K, typename V>
HashMap<K, V>::HashMap(unsigned capacity) {
  this->n = 0;
  for (int i = 0; i < capacity; i++) {
    this->data.push_back(nullptr);
  }
  dummy = new HashNode<K, V>(K(), V());
}


template<typename K, typename V>
bool HashMap<K, V>::empty() const {
  return this->n == 0;
}

template<typename K, typename V>
bool HashMap<K, V>::full() const {
  return this->n == this->data.size();
}

template<typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& value) {
  if (full()) return;

  // find the hash
  int index = hash(key);

  // linear probing
  while (data.at(index) != nullptr) {
    index = (index + 1) % data.size(); // go to next position wrap around
  }

  // we found the position, now insert
  data[index] = new HashNode<K, V>(key, value); // we store the ORIGINAL key

  this->n++; // increment size

}

template<typename K, typename V>
int HashMap<K, V>::hash(const K& key) const {
  return key % this->data.size(); // assuming key is an int??
}

template<typename K, typename V>
void HashMap<K, V>::display() const {
  for (int i = 0; i < data.size(); i++) {
    std::cout << i << " | ";
    if (data[i] == nullptr) std::cout << "NULLPTR";
    else if (data[i] == dummy) std::cout << "DELETED";
    else std::cout << "Key: " << data[i]->key << " Value: " << data[i]->value;
    std::cout << "\n";
  }
}
template<typename K, typename V>
int HashMap<K, V>::search_index(const K& key) const {
  int index = hash(key);

  int counter = 0;
  while (data.at(index) != nullptr && counter < data.size()) {
    if (data.at(index)->key == key && data.at(index) != dummy) return index;
    else index = (index + 1) % data.size();

    counter++;
  }
  return -1;
}

template<typename K, typename V>
const V HashMap<K, V>::search(const K& key) const {
  int index = search_index(key);

  if (index == -1) return V();
  else return data[index]->value;
}

template<typename K, typename V>
void HashMap<K, V>::remove(const K& key) {
  // int index = hash(key);
  // int counter = 0;
  // while (data[index] && data[index] != dummy) {
  //   if (counter++ > data.size()) {
  //     return;
  //   }
  //   if (data[index]->key == key) {
  //     delete data[index];
  //     data[index] = dummy;
  //     n--;
  //     return;
  //   }
  //   index = (index + 1) % data.size();
  // }

  int index = search_index(key);

  if (index == -1) return;

  delete data[index];
  data[index] = dummy;
  n--;

}


