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

  // get files from directory and construct them to page then form story
  Story<Page> myStory;
  std::string dir = argv[1];
  std::vector<std::string> files = myStory.getFilesInDir(dir + "/*");
  if (files.empty()) {
    std::cerr << "check your directory" << std::endl;
    exit(EXIT_FAILURE);
  }

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
      myStory.pagePrevOption.push_back(0);
    }
    else {
      std::cerr << "couldn't open the file\n" << std::endl;
      exit(EXIT_FAILURE);
    }
    ++it;
  }
  // start checking if all pages are properly linked to form story and what is the valid story range
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
            true;  // pageNum-1 change to index
      }
      storyRange++;
      myStory.pageLinked[i];
    }
  }
  //check if we have page1!
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
  //check story format before proceeding
  myStory.storyCheck();

  // contructing a vector holding all adjacentpages
  std::vector<std::vector<std::string> > totalAdj;
  for (unsigned i = 0; i < myStory.map.size(); i++) {
    std::vector<std::string> eachAdjPage;
    Page currPage = myStory.pageList[myStory.map[i]];
    for (unsigned j = 0; j < currPage.adjacentPage.size(); j++) {
      eachAdjPage.push_back(currPage.adjacentPage[j]);
    }
    totalAdj.push_back(eachAdjPage);
    eachAdjPage.clear();
  }
  //constructing all story paths with myQ
  //every time we pop up an adjacentpage vector, we append the pages linking to it in PathConnector
  //if the last page of the pathConstructor is a win/lose page, we reached the end of this story path and push it to totalPath
  std::vector<std::vector<std::string> > totalPath;
  std::queue<std::vector<std::string> > myQ;
  std::vector<std::string> seedPage;
  seedPage.push_back("1");
  myQ.push(seedPage);
  while (!myQ.empty()) {
    std::vector<std::string> pathConstructor = myQ.front();
    myQ.pop();
    int currLastPageNum = atoi(pathConstructor[pathConstructor.size() - 1].c_str());
    int currLastPageInd = currLastPageNum - 1;
    if (totalAdj[currLastPageInd].empty()) {
      totalPath.push_back(pathConstructor);
    }
    else {
      for (unsigned i = 0; i < totalAdj[currLastPageInd].size(); i++) {
        std::vector<std::string> pathConnector;
        std::vector<std::string>::iterator itPath;  // for checking cycle path
        for (unsigned j = 0; j < pathConstructor.size(); j++) {
          pathConnector.push_back(pathConstructor[j].c_str());
        }
        itPath =
            find(pathConnector.begin(),
                 pathConnector.end(),
                 totalAdj[currLastPageInd][i]);  //check if page to add is already in path
        if (itPath !=
            pathConnector.end()) {  //break if the page to add is already in path
          break;
        }
        pathConnector.push_back(totalAdj[currLastPageInd][i]);
        myQ.push(pathConnector);
        pathConnector.clear();
      }
    }
  }
  // iterate through all story Path and print out winnable path(s) only
  int winnable = 0;
  for (unsigned j = 0; j < totalPath.size(); j++) {
    int lastPageInd = atoi(totalPath[j][totalPath[j].size() - 1].c_str()) - 1;
    Page lastPage = myStory.pageList[myStory.map[lastPageInd]];
    if (lastPage.pageAttribute == 0) {  // pageAttribute 0 means win
      for (unsigned k = 0; k < totalPath[j].size(); k++) {
        int eachPageInd = atoi(totalPath[j][k].c_str()) - 1;
        Page eachPage = myStory.pageList[myStory.map[eachPageInd]];
        std::cout << totalPath[j][k] << "(";
        if (k < totalPath[j].size() - 1) {
          for (unsigned l = 0; l < eachPage.adjacentPage.size(); l++) {
            if (eachPage.adjacentPage[l] == totalPath[j][k + 1]) {
              std::cout << l + 1 << "),";
              break;
            }
          }
        }
        else {
          std::cout << "win)" << std::endl;
        }
      }
      winnable = 1;
    }
  }
  if (!winnable) {
    std::cout << "This story is unwinnable!" << std::endl;
  }

  return EXIT_SUCCESS;
}
