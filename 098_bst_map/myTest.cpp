#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> map;
  try {
    map.add(30, 3);
    map.add(20, 2);
    map.add(40, 4);
    map.add(10, 1);
    map.add(50, 5);
    map.add(0, 0);
    map.add(-10, -1);
    map.add(70, 7);
    std::cout << "Lookup key is: " << 30 << " value is: " << map.lookup(30) << std::endl;
    std::cout << "Lookup key is: " << 40 << " value is: " << map.lookup(40) << std::endl;
    //map.inOrderTraversal(map.root);
    //map.remove(40);
    // map.remove(30);
    map.remove(30);
    map.inOrderTraversal(map.root);
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
