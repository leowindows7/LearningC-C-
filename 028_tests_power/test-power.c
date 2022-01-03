#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
int myCheck(unsigned a[][3]) {
  for (int i = 0; i < 10; i++) {
    if (power(a[i][0], a[i][1]) != a[i][2]) {
      exit(EXIT_FAILURE);
    }
  }
  return EXIT_SUCCESS;
}

int main(void) {
  unsigned a[][3] = {{2, 2, 4},
                     {1, 2, 1},
                     {0, 2, 0},
                     {2, 5, 32},
                     {5, 2, 25},
                     {3, 2, 9},
                     {0, 0, 1},
                     {0, 2, 0},
                     {-2, 1, (unsigned)-2},
                     {'(', 1, 40}};
  return myCheck(a);
}
