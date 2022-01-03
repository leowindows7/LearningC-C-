#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

/*
In this step, the input story will be getline to an array and stored as wholestory

wholestory will then be parsed by parsedStory. Final story will be printed out by storyTeller in rand_story.c
*/

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Check your command line argument\n");
    exit(EXIT_FAILURE);
  }
  size_t linecap;
  size_t i = 0;
  char ** lines = NULL;
  char * line = NULL;
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Fail to open the file\n");
    exit(EXIT_FAILURE);
  }
  while (getline(&line, &linecap, f) >= 0) {
    // printf("%s", line);
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = line;
    line = NULL;
    i++;
  }
  fclose(f);
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

  if (!storyOK(wholeStory)) {
    fprintf(stderr, "please check story file format\n");
    exit(EXIT_FAILURE);
  }
  parseStory(wholeStory, NULL, 1);
  for (size_t j = 0; j < i; j++) {
    free(lines[j]);
  }

  free(lines);
  free(wholeStory);
}
