#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
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
  // getting directory name and store all the filenames in vector files
  Story<Page> myStory;
  std::string dir = argv[1];
  std::vector<std::string> files = myStory.getFilesInDir(dir + "/*");
  // if there is no file in directory exit failure
  if (files.empty()) {
    std::cerr << "check your directory" << std::endl;
    exit(EXIT_FAILURE);
  }
  // open and parse the file then construct them as page, after that, appending them to story
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
    }
    else {
      std::cerr << "couldn't open the file\n" << std::endl;
      exit(EXIT_FAILURE);
    }
    ++it;
  }
  //check if the story is valid(all page linked, valid story range)
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
        myStory.pageLinked[atoi(pageNum.c_str()) - 1] = true;  // pageNum change to index
      }
      storyRange++;
      myStory.pageLinked[i];
    }
  }
  if (!storyRange) {
    std::cerr << "no Page1.txt" << std::endl;
    exit(EXIT_FAILURE);
  }
  else {
    myStory.storyRange = storyRange;
  }
  for (unsigned i = 0; i < myStory.pageList.size(); i++) {
    myStory.pageList[myStory.map[i]].pageIndex = i;
  }

  myStory.storyCheck();
  //navigating through each page until reaching WIN/LOSE page
  unsigned mapInd = 0;
  Page currPage = myStory.pageList[myStory.map[mapInd]];
  currPage.printPage();
  while (currPage.pageAttribute == 2) {
    getline(std::cin, str);
    unsigned pageAdjInd = atoi(str.c_str());
    if (pageAdjInd > 0 && pageAdjInd <= currPage.adjacentPage.size()) {
      mapInd = atoi((currPage.adjacentPage[pageAdjInd - 1]).c_str()) - 1;
      currPage = myStory.pageList[myStory.map[mapInd]];
      currPage.printPage();
    }
    else {
      std::cout << "That is not a valid choice, please try again" << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
