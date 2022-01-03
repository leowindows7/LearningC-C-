#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void myCheck(int * array, size_t n, int answer) {
  if (maxSeq(array, n) != answer) {
    exit(EXIT_FAILURE);
  }

  return;
}

int main(void) {
  int a0[2] = {1, 1};
  int a1[5] = {1, 1, 2, 3, 4};
  int a2[4] = {0, 2, 4, 6};
  int a3[7] = {1, 2, 3, 4, 1, 1, 1};
  int a4[5] = {5, 4, 3, 2, 1};
  int a5[6] = {1, 2, 3, 2, 1, 0};
  int a6[1] = {2};
  int a7[5] = {1, 2, 3, -6, -5};
  myCheck(a1, 4, 3);
  myCheck(a7, 5, 3);
  myCheck(a6, 1, 1);
  myCheck(a4, 5, 1);
  myCheck(a1, 5, 4);
  myCheck(a0, 0, 0);
  myCheck(a2, 4, 4);
  myCheck(a5, 6, 3);
  myCheck(a3, 7, 4);
  return EXIT_SUCCESS;
}
