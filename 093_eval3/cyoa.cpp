#include "cyoa.hpp"

#include <glob.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

void Page::formatCheck(int hashDetect) {
  if (!hashDetect) {
    std::cerr << "no hashtag detected" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (content.empty()) {
    std::cerr << "incomplete story" << std::endl;
    exit(EXIT_FAILURE);
  }
  switch (this->pageAttribute) {
    case 2: {  //play case
      std::vector<std::string>::iterator naviLine = navigations.begin();
      while (naviLine != navigations.end()) {
        if (naviLine->find(':') == std::string::npos) {
          std::cerr << "no colon detected" << std::endl;
          exit(EXIT_FAILURE);
        }
        else {
          std::string choice = (*naviLine).substr(0, (*naviLine).find(':'));
          adjacentPage.push_back(choice);
        }
        ++naviLine;
      }
      break;
    }
    case -1: {  // pageAttribute are initialized to be -1, if it's still -1 by this stage, there must be something wrong
      std::cerr << "Page not defined" << std::endl;
      exit(EXIT_FAILURE);
      break;
    }
  }
}
// this function parse page line by line and categorize each page
//the acceptable format of each page is described in readme

void Page::parseLines(std::istream & is) {
  std::string line;
  int hashDetect = 0;
  while (getline(is, line)) {
    if (line == "WIN") {
      pageAttribute = 0;
    }
    else if (line == "LOSE") {
      pageAttribute = 1;
    }
    else if (line[0] == '#') {
      hashDetect = 1;  //detect nagivation
      break;
    }
    else {
      if (pageAttribute == 0 ||
          pageAttribute == 1) {  // only play page are allowed to enter this part
        std::cerr << "check page format" << std::endl;
        exit(EXIT_FAILURE);
      }
      pageAttribute = 2;
      navigations.push_back(line);
    }
  }
  while (getline(is, line)) {
    content.push_back(line);
  }
  if (is.good() != 1 && is.eof() != 1) {
    std::cerr << "read line failure" << std::endl;
    exit(EXIT_FAILURE);
  }
  formatCheck(hashDetect);
}

void Page::printPage() {
  std::vector<std::string>::iterator contentLine = content.begin();
  while (contentLine != content.end()) {
    std::cout << *contentLine << std::endl;
    ++contentLine;
  }
  switch (this->pageAttribute) {
    case 2: {  //play page
      std::cout << "\nWhat would you like to do?\n" << std::endl;
      std::vector<std::string>::iterator naviLine = navigations.begin();
      int num = 1;
      while (naviLine != navigations.end()) {
        std::string choice = (*naviLine).substr(
            (*naviLine).find(':') + 1, (*naviLine).length() - (*naviLine).find(':'));
        std::cout << " " << num << ". " + choice << std::endl;
        num++;
        ++naviLine;
      }
      break;
    }
    case 1: {  //loose page
      std::cout << "\nSorry, you have lost. Better luck next time!" << std::endl;
      break;
    }
    case 0: {  // win page
      std::cout << "\nCongratulations! You have won. Hooray!" << std::endl;
      break;
    }
  }
}

void Page::setPageName(const std::string & pageName) {
  this->pageName = pageName;
}
std::string Page::getPageName() {
  return this->pageName;
}
//assignment operator
Page & Page::operator=(const Page & rhs) {
  if (this != &rhs) {
    navigations = rhs.navigations;
    content = rhs.content;
    pageName = rhs.pageName;
    pageAttribute = rhs.pageAttribute;
    adjacentPage = rhs.adjacentPage;
    pageIndex = rhs.pageIndex;
  }
  return *this;
}
