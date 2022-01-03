unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  if (y == 1) {
    return x;
  }
  if (x == 0) {
    return 0;
  }
  return x * power(x, y - 1);
}
