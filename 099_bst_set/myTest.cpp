#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "bstset.h"
#include "set.h"

int main(void) {
  BstSet<int> set;
  try {
    set.add(3);
    set.add(2);
    set.add(4);
    set.add(1);
    set.add(5);
    set.add(0);
    set.add(-1);
    set.add(7);

    //map.inOrderTraversal(map.root);
    //map.remove(40);
    // map.remove(30);
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
