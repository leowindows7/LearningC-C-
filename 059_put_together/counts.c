#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  c->cur_count = 0;
  c->unkown_count = 0;
  c->struct_arr = NULL;
  return c;
}
void addNew(counts_t * c, const char * name) {
  if (c == NULL) {
    return;
  }
  c->struct_arr = realloc(c->struct_arr, (++c->cur_count) * sizeof(*c->struct_arr));
  c->struct_arr[c->cur_count - 1] = malloc(sizeof(*(c->struct_arr[c->cur_count - 1])));
  c->struct_arr[c->cur_count - 1]->string = strdup(name);
  c->struct_arr[c->cur_count - 1]->count = 1;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unkown_count++;
    return;
  }
  int check = 1;
  for (int i = 0; i < c->cur_count; i++) {
    // c->struct_arr[i]->count = 0;

    if (strcmp(name, c->struct_arr[i]->string) == 0) {
      check = 0;
      c->struct_arr[i]->count++;
      break;
    }
  }
  if (check) {
    addNew(c, name);
    //c->cur_count++;
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (c == NULL || outFile == NULL) {
    return;
  }
  for (int i = 0; i < c->cur_count; i++) {
    fprintf(outFile, "%s: %zd\n", c->struct_arr[i]->string, c->struct_arr[i]->count);
  }
  if (c->unkown_count > 0) {
    fprintf(outFile, "<unknown>: %zd\n", c->unkown_count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  //free(c->cur_count);
  for (int i = 0; i < c->cur_count; i++) {
    free(c->struct_arr[i]->string);
    free(c->struct_arr[i]);
  }
  free(c->struct_arr);
  free(c);
}
