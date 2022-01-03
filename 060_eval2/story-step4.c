#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

/*
  most of the steps/ functions are the same as previous steps, this steps  only add a new part to handle  addition -n requirements
*/

int main(int argc, char ** argv) {
  FILE * storyFile = NULL;
  FILE * wordsFile = NULL;
  int reuse = 1;
  if (argc == 3) {
    storyFile = fopen(argv[2], "r");
    wordsFile = fopen(argv[1], "r");
  }
  else if (argc == 4) {
    storyFile = fopen(argv[3], "r");
    wordsFile = fopen(argv[2], "r");
    if (strcmp(argv[1], "-n") == 0) {
      reuse = 0;
      // printf("%s\n", "oh yeah");
    }
    else {
      fprintf(stderr, "Incorrect input of command line\n");
      exit(EXIT_FAILURE);
    }
  }
  else {
    fprintf(stderr, "Incorrect input of command line args\n");
    exit(EXIT_FAILURE);
  }
  // check input files
  if (storyFile == NULL) {
    fprintf(stderr, "Couldn't open the story file\n");
    exit(EXIT_FAILURE);
  }

  if (wordsFile == NULL) {
    fprintf(stderr, "Couldn't open the words file\n");
    exit(EXIT_FAILURE);
  }
  // working on story
  char ** lines = NULL;
  size_t linecap;
  size_t i = 0;
  char * line = NULL;
  while (getline(&line, &linecap, storyFile) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = line;
    line = NULL;
    i++;
  }
  size_t lineLen = 0;
  for (size_t k = 0; k < i; k++) {
    lineLen += strlen(lines[k]);
  }
  char * wholeStory = malloc((lineLen + 1) * sizeof(*wholeStory));
  char * wholeStoryPtr = wholeStory;
  for (size_t k = 0; k < i; k++) {
    strcpy(wholeStoryPtr, lines[k]);
    wholeStoryPtr += strlen(lines[k]);
  }
  wholeStoryPtr = '\0';
  free(line);
  fclose(storyFile);
  if (!storyOK(wholeStory)) {
    fprintf(stderr, "please check story file format\n");
    exit(EXIT_FAILURE);
  }
  // working on words

  size_t sz = 0;
  ssize_t len = 0;
  char * wordLine = NULL;
  char ** wordLines = NULL;
  size_t numOfWordLine = 0;
  catarray_t * catArr = malloc(sizeof(*catArr));
  catArr->arr = NULL;
  catArr->n = 0;
  while ((len = getline(&wordLine, &sz, wordsFile) >= 0)) {
    wordLines = realloc(wordLines, (numOfWordLine + 1) * sizeof(*wordLines));
    wordLines[numOfWordLine] = wordLine;
    wordLine = NULL;
    numOfWordLine++;
  }
  size_t totalName = 0;
  for (size_t m = 0; m < numOfWordLine; m++) {
    if (!wordLineOK(wordLines[m])) {
      fprintf(stderr, "please check words file format\n");
      exit(EXIT_FAILURE);
    }
    totalName = parseWord(wordLines[m], catArr);
    free(wordLines[m]);
  }
  size_t initWordList[totalName];
  getInitWordNum(initWordList, totalName, catArr);

  free(wordLine);
  free(wordLines);
  fclose(wordsFile);
  //start manipulating words and story

  parseStory(wholeStory, catArr, reuse);

  //free storyLines
  for (size_t j = 0; j < i; j++) {
    free(lines[j]);
  }
  free(lines);
  free(wholeStory);
  //free struct

  freeCatArr(catArr, initWordList);
}
