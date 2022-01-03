#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sortLines(std::istream & is) {
  std::string line;
  std::vector<std::string> lines;
  while (getline(is, line)) {
    lines.push_back(line);
  }
  if (is.good() != 1 && is.eof() != 1) {
    std::cerr << "read line failure" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::sort(lines.begin(), lines.end());
  std::vector<std::string>::iterator myLine = lines.begin();
  while (myLine != lines.end()) {
    std::cout << *myLine << std::endl;
    ++myLine;
  }
}

void sortFromFile(int numOfFiles, char ** fileNames) {
  for (int i = 1; i < numOfFiles; i++) {
    std::ifstream ifs(fileNames[i], std::ifstream::in);
    if (ifs.is_open()) {
      sortLines(ifs);
      ifs.close();
    }
    else {
      std::cerr << "couldn't open the file" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortLines(std::cin);
  }
  else if (argc > 1) {
    sortFromFile(argc, argv);
  }

  return EXIT_SUCCESS;
}
