#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  int track = 1;
  int globMax = 1;
  for (int i = 1; i < n; i++) {
    if (array[i - 1] < array[i]) {
      track++;
      if (track > globMax) {
        globMax = track;
      }
    }
    else {
      track = 1;
    }
  }
  return globMax;
}
