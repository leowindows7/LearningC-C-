#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

int storyOK(const char * story);

int wordLineOK(const char * wordLine);

void getInitWordNum(size_t * initWordList, size_t n, catarray_t * catArr);

void parseStory(const char * line, catarray_t * catArr, int reuse);

size_t parseWord(const char * line, catarray_t * catArr);

void freeCatArr(catarray_t * catArr, size_t * initWordList);

#endif
