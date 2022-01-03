#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "set.h"

template<typename K>
class BstSet : public Set<K> {
 public:
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL){};
    Node(const K k) : key(k), left(NULL), right(NULL){};
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}
  BstSet & operator=(const BstSet & rhs);
  virtual void add(const K & key);
  virtual bool contains(const K & key) const;
  virtual void remove(const K & key);
  BstSet(const BstSet & rhs);
  Node * copy(Node * current);
  virtual ~BstSet();
  void destroy(Node * current);
};
template<typename K>
void BstSet<K>::add(const K & key) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key < (*current)->key) {
      current = &(*current)->left;
    }
    else {
      current = &(*current)->right;
    }
  }
  *current = new Node(key);
}
template<typename K>
BstSet<K>::~BstSet() {
  destroy(root);
}

template<typename K>
void BstSet<K>::destroy(Node * current) {
  if (current == NULL) {
    return;
  }
  destroy(current->left);
  destroy(current->right);
  delete current;
}

template<typename K>
bool BstSet<K>::contains(const K & key) const {
  Node * current = root;
  if (current == NULL) {
    return false;
  }
  while (current != NULL) {
    if (key == current->key) {
      return true;
    }
    else if (key > current->key) {
      current = current->right;
    }
    else {
      current = current->left;
    }
  }
  return false;
}
template<typename K>
void BstSet<K>::remove(const K & key) {
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
    remove(findnode->key);
    (*current)->key = tempkey;
  }
}
template<typename K>
BstSet<K> & BstSet<K>::operator=(const BstSet & rhs) {
  if (this != &rhs) {
    BstSet<K> tmp(rhs);
    std::swap(root, tmp.root);
  }
  return *this;
}

template<typename K>
BstSet<K>::BstSet(const BstSet & rhs) {
  root = copy(rhs.root);
}

template<typename K>
typename BstSet<K>::Node * BstSet<K>::copy(Node * current) {
  if (current == NULL) {
    return NULL;
  }
  Node * mynode = new Node(current->key);
  mynode->left = copy(current->left);
  mynode->right = copy(current->right);
  return mynode;
}
