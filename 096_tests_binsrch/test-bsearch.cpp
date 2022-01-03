#include <stdio.h>

#include <cmath>
#include <cstdlib>
#include <ostream>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high);
class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class LinearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int maxNum;
  if (high > low) {
    maxNum = log(high - low) / log(2) + 1;
  }
  else {
    maxNum = 1;
  }

  CountedIntFn * myCount = new CountedIntFn(maxNum, f, mesg);
  int ans = binarySearchForZero(myCount, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "Not expected %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  LinearFunction myLinear;
  check(&myLinear, 1, 6, 1, "all positive\n");
  check(&myLinear, -2, 4, 0, "normal\n");
  check(&myLinear, -4, -1, -2, "all negative\n");
  SinFunction mySin;
  check(&mySin, 0, 150000, 52359, "sin");

  return EXIT_SUCCESS;
}
