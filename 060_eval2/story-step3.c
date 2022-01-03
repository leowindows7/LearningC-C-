#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

/*
  in this step, story and words are handled by the same function parseStory and parseWord
  to cope with Int requirement, we introduced "checkNumber" function in rand_story.c and the result will be printed by storyTeller as well.
*/

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Incorrect input of command line args\n");
    exit(EXIT_FAILURE);
  }
  // working on story
  FILE * storyFile = fopen(argv[2], "r");
  if (storyFile == NULL) {
    fprintf(stderr, "Couldn't open the file\n");
    exit(EXIT_FAILURE);
  }
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
  FILE * wordsFile = fopen(argv[1], "r");
  if (wordsFile == NULL) {
    fprintf(stderr, "Couldn't open the file\n");
    exit(EXIT_FAILURE);
  }
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

  parseStory(wholeStory, catArr, 1);

  //free storyLines
  for (size_t j = 0; j < i; j++) {
    free(lines[j]);
  }
  free(lines);
  free(wholeStory);
  //free struct
  freeCatArr(catArr, initWordList);
}
