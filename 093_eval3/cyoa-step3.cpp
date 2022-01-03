#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "cyoa.cpp"
#include "cyoa.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "please check command line args" << std::endl;
    exit(EXIT_FAILURE);
  }
  // get page files from directory and construct our story
  Story<Page> myStory;
  std::string dir = argv[1];
  std::vector<std::string> files = myStory.getFilesInDir(dir + "/*");
  if (files.empty()) {
    std::cerr << "check your directory" << std::endl;
    exit(EXIT_FAILURE);
  }
  // start pushing pages to story
  std::vector<std::string>::iterator it = files.begin();
  while (it != files.end()) {
    std::ifstream ifs((*it).c_str(), std::ifstream::in);
    if (ifs.is_open()) {
      Page myPage;
      myPage.parseLines(ifs);
      myPage.setPageName((*it).c_str());
      ifs.close();
      myStory.pageList.push_back(myPage);
      myStory.pageLinked.push_back(false);
      myStory.map.push_back(0);
      myStory.pageDepth.push_back(0);
    }
    else {
      std::cerr << "couldn't open the file\n" << std::endl;
      exit(EXIT_FAILURE);
    }
    ++it;
  }
  // start checking if the story is in acceptable format(all pages should be linked properly)
  std::vector<std::string>::iterator itFile;
  std::string str;
  int storyRange = 0;
  myStory.pageLinked[0] = true;

  for (unsigned i = 0; i < myStory.pageList.size(); i++) {
    std::stringstream ss;
    ss << i + 1;
    ss >> str;
    itFile = find(files.begin(), files.end(), dir + "/page" + str + ".txt");
    if (itFile == files.end()) {
      break;
    }
    else {
      int index = itFile - files.begin();
      myStory.map[i] = index;
      for (unsigned k = 0; k < myStory.pageList[index].adjacentPage.size(); k++) {
        std::string pageNum = myStory.pageList[index].adjacentPage[k];
        myStory.pageLinked[atoi(pageNum.c_str()) - 1] =
            true;  // check if each page is linked
      }
      storyRange++;
      myStory.pageLinked[i];
    }
  }
  // check if we have page 1
  if (!storyRange) {
    std::cerr << "no Page1.txt" << std::endl;
    exit(EXIT_FAILURE);
  }
  else {
    myStory.storyRange = storyRange;
  }

  //map each page with int index for later use
  for (unsigned i = 0; i < myStory.pageList.size(); i++) {
    myStory.pageList[myStory.map[i]].pageIndex = i;
  }

  myStory.storyCheck();
  //start QQ!
  //use BFS to visit each page and determine its depth
  std::queue<Page> myQ;
  myQ.push(myStory.pageList[myStory.map[0]]);
  while (!myQ.empty()) {
    Page currPage = myQ.front();
    myQ.pop();
    int mapInd = myStory.map[currPage.pageIndex];
    int currDepth = myStory.pageDepth[currPage.pageIndex];

    for (unsigned i = 0; i < currPage.adjacentPage.size(); i++) {
      int adjPageNumInd = atoi(myStory.pageList[mapInd].adjacentPage[i].c_str()) - 1;
      // myQ.push(myStory.pageList[myStory.map[adjPageNumInd]]); only push unvisited page to queue!!
      if (myStory.pageDepth[myStory.pageList[myStory.map[adjPageNumInd]].pageIndex] ==
          0) {
        myQ.push(myStory.pageList[myStory.map[adjPageNumInd]]);
        myStory.pageDepth[myStory.pageList[myStory.map[adjPageNumInd]].pageIndex] =
            currDepth + 1;
      }
    }
  }
  myStory.pageDepth[0] = 0;
  //print pageDepth
  for (unsigned i = 0; i < myStory.pageDepth.size(); i++) {
    if (i > 0 && myStory.pageDepth[i] == 0) {
      std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
    }
    else {
      std::cout << "Page " << i + 1 << ":" << myStory.pageDepth[i] << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
