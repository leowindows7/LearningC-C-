#ifndef _CYOA_
#define _CYOA_
#include <glob.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
template<typename T>
class Story {
 public:
  std::vector<std::string> pageFileNameList;
  std::vector<T> pageList;
  std::vector<bool> pageLinked;
  std::vector<int> map;
  std::vector<int> pageDepth;
  std::vector<int> pagePrevOption;
  int storyRange;
  Story() :
      pageFileNameList(),
      pageList(),
      pageLinked(),
      map(),
      pageDepth(),
      pagePrevOption(),
      storyRange() {}
  std::vector<std::string> getFilesInDir(const std::string & pattern);
  void storyCheck();

  bool navigatePage(const std::string & str);
  ~Story() {}
};

//this function check if the pages are linked correctly to form our story
template<typename T>
void Story<T>::storyCheck() {
  (this->pageLinked).resize(this->storyRange);
  (this->pageDepth).resize(this->storyRange);
  (this->pagePrevOption).resize(this->storyRange);
  int haveWinPage = 0;
  int haveLosePage = 0;
  for (int i = 0; i < this->storyRange; i++) {
    if (!this->pageLinked[i]) {
      std::cerr << "found unlinked page " << i + 1 << std::endl;
      exit(EXIT_FAILURE);
    }
    for (unsigned j = 0; j < this->pageList[this->map[i]].adjacentPage.size(); j++) {
      if (atoi(this->pageList[this->map[i]].adjacentPage[j].c_str()) > this->storyRange) {
        std::cerr << this->pageList[this->map[i]].pageName << " referenc to page "
                  << this->pageList[this->map[i]].adjacentPage[j] << " outside of story"
                  << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    if (this->pageList[this->map[i]].pageAttribute == 0) {
      haveWinPage = 1;
    }
    if (this->pageList[this->map[i]].pageAttribute == 1) {
      haveLosePage = 1;
    }
  }
  if (!haveWinPage) {
    std::cerr << "Story must have at least one WIN page" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (!haveLosePage) {
    std::cerr << "Story must have at least one LOSE page" << std::endl;
    exit(EXIT_FAILURE);
  }
}
// this function helps to check if input of the page number are within acceptable range
template<typename T>
bool Story<T>::navigatePage(const std::string & str) {
  if (atoi(str.c_str()) <= 0 || atoi(str.c_str()) > this->storyRange) {
    return false;
  }
  return true;
}

// get files from directory
template<typename T>
std::vector<std::string> Story<T>::getFilesInDir(const std::string & pattern) {
  glob_t glob_result;
  glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
  std::vector<std::string> files;
  for (size_t i = 0; i < glob_result.gl_pathc; ++i) {
    files.push_back(std::string(glob_result.gl_pathv[i]));
  }
  globfree(&glob_result);

  return files;
}

class Page {
 private:
  std::vector<std::string> navigations;
  std::vector<std::string> content;

 public:
  int pageIndex;
  std::string pageName;
  int pageAttribute;  // 0 for win, 1 for lose, 2 for play
  std::vector<std::string> adjacentPage;
  Page() : pageIndex(-1), pageAttribute(-1) {}
  void parseLines(std::istream & is);
  void printPage();
  void formatCheck(int hashDetect);
  void setPageName(const std::string & pageName);
  std::string getPageName();
  Page & operator=(const Page & rhs);
  ~Page() {}
};

#endif
