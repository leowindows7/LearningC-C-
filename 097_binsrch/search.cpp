#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  // high = high - 1;

  int mid;
  int result;

  while (high > low + 1) {
    mid = (high + low) / 2;
    result = f->invoke(mid);
    if (result == 0) {
      return mid;
    }
    else if (result > 0) {
      high = mid;
    }
    else if (result < 0) {
      low = mid;
    }
  }

  return low;
}
