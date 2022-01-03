#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

/*
  in this step, words are getlined and  parsed by parsedWord function 
  words without correct format such as no proper delimiter : will be rejected  

*/

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Not enough commands\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Couldn't open the file\n");
    exit(EXIT_FAILURE);
  }
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  catarray_t * catArr = malloc(sizeof(*catArr));
  catArr->arr = NULL;
  catArr->n = 0;
  size_t totalName = 0;
  while ((len = getline(&line, &sz, f)) >= 0) {
    if (!wordLineOK(line)) {
      fprintf(stderr, "please check words file format\n");
      exit(EXIT_FAILURE);
    }
    totalName = parseWord(line, catArr);
    free(line);
    line = NULL;
  }
  size_t initWordList[totalName];
  getInitWordNum(initWordList, totalName, catArr);
  free(line);
  fclose(f);

  printWords(catArr);
  freeCatArr(catArr, initWordList);
}
