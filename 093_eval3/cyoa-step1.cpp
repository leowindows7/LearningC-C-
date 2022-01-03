#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "cyoa.cpp"
#include "cyoa.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "please check command line arg" << std::endl;
    exit(EXIT_FAILURE);
  }
  // we take command line argument to open the file we then parse the line in the pages and print it out
  Page myPage;
  std::ifstream ifs(argv[1], std::ifstream::in);
  myPage.setPageName(argv[1]);
  if (ifs.is_open()) {
    myPage.parseLines(ifs);
    ifs.close();
  }
  else {
    std::cerr << "couldn't open the file" << std::endl;
    exit(EXIT_FAILURE);
  }
  myPage.printPage();

  return EXIT_SUCCESS;
}
