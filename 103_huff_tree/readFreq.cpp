#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  FILE * ifs = fopen(fname, "r");
  uint64_t * array = new uint64_t[257]();
  if (ifs != NULL) {
    int c;
    while ((c = getc(ifs)) != EOF) {
      array[c]++;
    }
    array[256] = 1;
    fclose(ifs);
  }
  else {
    std::cerr << "couldn't open the file\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  return array;
}
