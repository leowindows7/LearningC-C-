#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t myPQ;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      myPQ.push(new Node(i, counts[i]));
    }
  }
  while (myPQ.size() > 1) {
    Node * nodeOne = myPQ.top();
    myPQ.pop();
    Node * nodeTwo = myPQ.top();
    myPQ.pop();
    Node * combo = new Node(nodeOne, nodeTwo);
    myPQ.push(combo);
  }
  Node * root = myPQ.top();
  myPQ.pop();
  return root;
}
