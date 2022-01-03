#ifndef __LL_HPP__
#define __LL_HPP__
#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class Error : public std::exception {
 public:
  virtual const char * what() const throw() { return "Couldn't find the item\n"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(T()), next(NULL), prev(NULL) {}  //node constructor
    Node(const T & d) : data(d), next(NULL), prev(NULL) {}
    Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList<T>() : head(NULL), tail(NULL), size(0){};
  LinkedList<T>(const LinkedList & rhs) :

      head(NULL),
      tail(NULL),
      size(0) {
    Node * temp = rhs.head;
    while (temp != NULL) {
      addBack(temp->data);
      temp = temp->next;
    }
  }  //LinkedList constructor
  LinkedList<T> & operator=(const LinkedList<T> & rhs) {
    if (this != &rhs) {
      Node * temp = head;
      while (temp != NULL) {
        temp = temp->next;
        delete head;
        head = temp;
      }
      size = 0;
      Node * curr = rhs.head;
      while (curr != NULL) {
        addBack(curr->data);
        curr = curr->next;
      }
    }
    return *this;
  };
  ~LinkedList<T>() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
      size--;
    }
  };
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  };
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  };
  bool remove(const T & item) {
    if (head == NULL) {
      return false;
    }
    Node * temp = head;
    while (temp->next != NULL && temp->data != item) {
      temp = temp->next;
    }

    if ((temp->prev != NULL) && (temp->next != NULL)) {
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
      delete temp;
      size--;
      return true;
    }
    else if ((temp->prev == NULL) && (temp->next != NULL)) {
      head = temp->next;
      temp->next->prev = NULL;
      delete temp;
      size--;
      return true;
    }
    else if ((temp->prev != NULL) && (temp->next == NULL)) {
      if (temp->data != item) {
        return false;
      }
      temp->prev->next = NULL;
      tail = temp->prev;
      delete temp;
      size--;
      return true;
    }
    if (temp->data == item) {
      delete temp;
      size--;
      head = NULL;
      tail = NULL;
    }
    return false;
  };
  T & operator[](int index) {
    Node * temp = head;
    int i = 0;
    while ((temp != NULL)) {
      if (i == index) {
        return temp->data;
      }
      temp = temp->next;
      i++;
    }
    if (temp == NULL) {
      throw Error();
    }
    return temp->data;
  };
  const T & operator[](int index) const {
    Node * temp = head;
    int i = 0;
    while ((temp != NULL)) {
      if (i == index) {
        return temp->data;
      }
      temp = temp->next;
      i++;
    }
    if (temp == NULL) {
      throw Error();
    }
    return temp->data;
  };
  int find(const T & item) const {
    if (head == NULL) {
      return -1;
    }
    int index = -1;
    Node * temp = head;
    while (temp != NULL) {
      index++;
      if (temp->data == item) {
        return index;
      }
      temp = temp->next;
    }
    if (temp == NULL) {
      index = -1;
    }
    return index;
  };
  int getSize() const { return size; }
  friend class Tester;
};

#endif
