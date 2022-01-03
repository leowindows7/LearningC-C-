#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 public:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL){};
    Node(const K k, const V v) : key(k), value(v), left(NULL), right(NULL){};
  };
  Node * root;
  void inOrderTraversal(Node * current);

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs);
  BstMap & operator=(const BstMap & rhs);
  virtual ~BstMap();
  virtual void add(const K & key, const V & value);
  virtual const V & lookup(const K & key) const throw(std::invalid_argument);
  virtual void remove(const K & key);
  Node * copy(Node * current);
  void destroy(Node * current);
};
template<typename K, typename V>
void BstMap<K, V>::inOrderTraversal(Node * current) {
  if (current != NULL) {
    inOrderTraversal(current->left);
    std::cout << current->value << "\n";
    inOrderTraversal(current->right);
  }
}

template<typename K, typename V>
BstMap<K, V>::BstMap(const BstMap & rhs) {
  root = copy(rhs.root);
}
//copy helper function
template<typename K, typename V>
typename BstMap<K, V>::Node * BstMap<K, V>::copy(Node * current) {
  if (current == NULL) {
    return NULL;
  }
  Node * mynode = new Node(current->key, current->value);
  mynode->left = copy(current->left);
  mynode->right = copy(current->right);
  return mynode;
}

//assignment operator
template<typename K, typename V>
BstMap<K, V> & BstMap<K, V>::operator=(const BstMap & rhs) {
  if (this != &rhs) {
    BstMap<K, V> tmp(rhs);
    std::swap(root, tmp.root);
  }
  return *this;
}

//destructor
template<typename K, typename V>
BstMap<K, V>::~BstMap() {
  destroy(root);
}
//destroy helper function
template<typename K, typename V>
void BstMap<K, V>::destroy(Node * current) {
  if (current == NULL) {
    return;
  }
  destroy(current->left);
  destroy(current->right);
  delete current;
}

//add
template<typename K, typename V>
void BstMap<K, V>::add(const K & key, const V & value) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key < (*current)->key) {
      current = &(*current)->left;
    }
    else {
      current = &(*current)->right;
    }
  }
  *current = new Node(key, value);
}

//lookup
template<typename K, typename V>
const V & BstMap<K, V>::lookup(const K & key) const throw(std::invalid_argument) {
  Node * current = root;
  while (current != NULL) {
    if (key == current->key) {
      break;
    }
    else if (key < current->key) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }

  if (current == NULL) {
    throw std::invalid_argument("key not find\n");
  }
  return current->value;
}

//remove
template<typename K, typename V>
void BstMap<K, V>::remove(const K & key) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key == (*current)->key) {
      break;
    }
    else if (key < (*current)->key) {
      current = &(*current)->left;
    }
    else {
      current = &(*current)->right;
    }
  }
  if (*current == NULL) {
    throw std::invalid_argument("key not find\n");
  }
  if ((*current)->left == NULL) {
    Node * temp = (*current)->right;
    delete (*current);
    *current = temp;
  }
  else if ((*current)->right == NULL) {
    Node * temp = (*current)->left;
    delete (*current);
    *current = temp;
  }
  else {
    Node * findnode = (*current)->left;
    while (findnode->right != NULL) {
      findnode = findnode->right;
    }

    K tempkey = findnode->key;
    V tempvalue = findnode->value;
    remove(findnode->key);
    (*current)->key = tempkey;
    (*current)->value = tempvalue;
  }
}
