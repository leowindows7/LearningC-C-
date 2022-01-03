#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

int storyOK(const char * story) {
  int checker = -1;
  for (size_t i = 0; i < strlen(story); i++) {
    if (story[i] == '_') {
      checker *= (-1);
    }
  }
  return checker - 1;
}

int wordLineOK(const char * wordLine) {
  if (strchr(wordLine, ':') == NULL) {
    return 0;
  }
  return 1;
}

void getInitWordNum(size_t * initWordList, size_t n, catarray_t * catArr) {
  for (size_t i = 0; i < n; i++) {
    initWordList[i] = catArr->arr[i].n_words;
  }
}

void freeCatArr(catarray_t * catArr, size_t * initWordList) {
  for (size_t i = 0; i < catArr->n; i++) {
    for (size_t j = 0; j < initWordList[i]; j++) {
      free(catArr->arr[i].words[j]);
    }
    free(catArr->arr[i].name);
    free(catArr->arr[i].words);
  }
  free(catArr->arr);
  free(catArr);
}
int isSameCat(const char * catFromLine, const char * catFromArr) {
  for (size_t i = 0; i < strlen(catFromLine) - 1; i++) {
    if (catFromArr[i] != catFromLine[i]) {
      return 0;
    }
  }
  return 1;
}
int checkNumber(const char * line) {
  int total = 0;
  for (size_t i = 0; i < strlen(line) - 1; i++) {
    if (atoi(&line[i])) {
      total = total * 10 + atoi(&line[i]);
    }
  }
  return total;
}

void trackUsedList(usedWords_t * wordlists, const char * word) {
  wordlists->list =
      realloc(wordlists->list, (wordlists->listLen + 1) * sizeof(*wordlists->list));
  wordlists->list[wordlists->listLen] = strdup(word);
  wordlists->listLen++;
}
void removeUsedWord(catarray_t * catArr, size_t nameIndex, const char * word) {
  for (size_t x = 0; x < catArr->arr[nameIndex].n_words; x++) {
    if (strcmp(catArr->arr[nameIndex].words[x], word) == 0) {
      free(catArr->arr[nameIndex].words[x]);
      catArr->arr[nameIndex].words[x] = NULL;
      catArr->arr[nameIndex].n_words--;
      break;
    }
  }
}
void storyTeller(char ** lines, size_t numofLines, catarray_t * catArr, int reuse) {
  usedWords_t * wordlists = malloc(sizeof(*wordlists));
  wordlists->list = NULL;
  wordlists->listLen = 0;
  for (size_t j = 0; j < numofLines; j++) {
    char * checkCat = strchr(lines[j], '_');
    if (checkCat != NULL) {  // lines[j] is a keyword
      if (catArr == NULL) {
        printf("%s", chooseWord("verb", catArr));
      }
      else {  // catArr is not NULL
        int wordFound = 0;
        for (size_t k = 0; k < catArr->n; k++) {
          if (isSameCat(lines[j], catArr->arr[k].name)) {
            const char * word = chooseWord(catArr->arr[k].name, catArr);
            printf("%s", word);
            trackUsedList(wordlists, word);
            if (!reuse) {
              removeUsedWord(catArr, k, word);
            }
            wordFound = 1;
            break;
          }
        }
        if (checkNumber(lines[j]) &&
            !wordFound) {  // if it's an integer, we will go to track our word list
          if ((wordlists->listLen - checkNumber(lines[j])) < 0) {
            fprintf(stderr, "We don't have that many used words lol\n");
            exit(EXIT_FAILURE);
          }
          printf("%s", wordlists->list[wordlists->listLen - checkNumber(lines[j])]);
          trackUsedList(wordlists,
                        wordlists->list[wordlists->listLen - checkNumber(lines[j])]);
          wordFound = 1;
        }
        if (!wordFound) {
          fprintf(stderr, "couldn't find proper words\n");
          exit(EXIT_FAILURE);
        }
      }
    }  // if lines[j] is not a key word
    else {
      printf("%s", lines[j]);
    }
  }
  if (wordlists->listLen > 0) {
    for (size_t i = 0; i < wordlists->listLen; i++) {
      free(wordlists->list[i]);
    }
    free(wordlists->list);
  }
  free(wordlists);
}
void parseStory(const char * line, catarray_t * catArr, int reuse) {
  size_t i = 0;
  char ** lines = NULL;
  char * underscore = NULL;
  int blankStart = 1;
  while (strchr(line, '_') != NULL) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    underscore = strchr(line, '_');
    if (blankStart) {
      lines[i] = strncpy(
          malloc((underscore - line + 1) * sizeof(*lines[i])), line, underscore - line);
      lines[i][underscore - line] = '\0';
      blankStart = 0;
    }
    else {
      lines[i] = strncpy(malloc((underscore - line + 1 + 1) * sizeof(*lines[i])),
                         line,
                         underscore - line + 1);
      lines[i][underscore - line + 1] = '\0';
      blankStart = 1;
    }
    line = underscore + 1;
    i++;
  }
  if (blankStart) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] =
        strncpy(malloc((strlen(line) + 1) * sizeof(*lines[i])), line, (strlen(line)));
    lines[i][strlen(line)] = '\0';
  }
  else {
    lines = realloc(lines, (i + 1 + 1) * sizeof(*lines));
    lines[i] = strncpy(
        malloc((strlen(line) + 1 + 1) * sizeof(*lines[i])), line, (strlen(line) + 1));
    lines[i][strlen(line) + 1] = '\0';
  }
  i++;
  storyTeller(lines, i, catArr, reuse);
  for (size_t j = 0; j < i; j++) {
    //  printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

void createNewCat(category_t * newCategory, const char * catName, const char * word) {
  newCategory->words = malloc(sizeof(*newCategory->words));
  newCategory->name = malloc(sizeof(*newCategory->name));
  newCategory->n_words = 1;
  newCategory->name = strcpy(
      realloc(newCategory->name, (strlen(catName) + 1) * sizeof(*newCategory->name)),
      catName);
  newCategory->words[0] = strncpy(
      malloc((strlen(word) + 1) * sizeof(*newCategory->words)), word, strlen(word));
  newCategory->words[0][strlen(word)] = '\0';
}

size_t parseWord(const char * line, catarray_t * catArr) {
  char * colon = strchr(line, ':');
  if (colon == NULL) {
    return 0;
  }

  char * catName = malloc((colon - line + 1) * sizeof(*catName));
  strncpy(catName, line, colon - line);
  catName[colon - line] = '\0';

  char * word = malloc((strlen(colon + 1)) * sizeof(*word));
  strncpy(word, colon + 1, strlen(colon + 1) - 1);
  word[strlen(colon + 1) - 1] = '\0';

  int catExist = 0;
  if (catArr->n == 0) {
    catArr->arr = malloc(sizeof(*catArr->arr));
    category_t * newCategory = malloc(sizeof(*newCategory));
    createNewCat(newCategory, catName, word);
    catArr->arr[catArr->n] = *newCategory;
    catArr->n += 1;
    catExist = 1;
    free(newCategory);
  }

  for (size_t i = 0; i < catArr->n; i++) {
    if (strcmp(catArr->arr[i].name, catName) == 0 && catArr->n > 0 && !catExist) {
      catArr->arr[i].words =
          realloc(catArr->arr[i].words,
                  (catArr->arr[i].n_words + 1) * sizeof(*catArr->arr[i].words));
      catArr->arr[i].words[catArr->arr[i].n_words] =
          strncpy(malloc((strlen(word) + 1) *
                         sizeof(*(catArr->arr[i].words[catArr->arr[i].n_words]))),
                  word,
                  strlen(word));
      catArr->arr[i].words[catArr->arr[i].n_words][strlen(word)] = '\0';
      catArr->arr[i].n_words++;
      catExist = 1;
      break;
    }
  }
  if (!catExist) {
    category_t * newCategory = malloc(sizeof(*newCategory));
    createNewCat(newCategory, catName, word);
    catArr->arr = realloc(catArr->arr, (catArr->n + 1) * sizeof(*catArr->arr));
    catArr->arr[catArr->n] = *newCategory;
    catArr->n++;
    free(newCategory);
  }

  free(catName);
  free(word);
  return catArr->n;
}
