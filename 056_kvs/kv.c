#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void kvdivision(const char * line, ssize_t length, kvpair_t * mykvpair) {
  // printf("%s,%ld", line, length);

  char * line_key = NULL;
  size_t key_len = length - strlen(strchr(line, '='));
  line_key = realloc(line_key, (key_len + 1) * sizeof(*line_key));
  strncpy(line_key, line, key_len);
  line_key[key_len] = '\0';
  char * line_value_ptr = strchr(line, '=');
  line_value_ptr++;
  char * line_value = NULL;
  size_t value_len = strlen(line_value_ptr) - 1;
  line_value = realloc(line_value, (value_len + 1) * sizeof(*line_value));
  strncpy(line_value, line_value_ptr, value_len);
  line_value[value_len] = '\0';
  mykvpair->key = line_key;
  mykvpair->value = line_value;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "No file opened\n");

    //exit(EXIT_FAILURE);
    return NULL;
  }

  kvarray_t * mykvarray = malloc(sizeof(*mykvarray));
  mykvarray->num_pair = 0;
  mykvarray->kvpair = NULL;
  char * line = NULL;
  size_t sz = 0;
  ssize_t length = 0;
  while ((length = getline(&line, &sz, f)) >= 0) {
    kvpair_t * mykvpair = malloc(sizeof(*mykvpair));
    mykvpair->key = NULL;
    mykvpair->value = NULL;
    kvdivision(line, length, mykvpair);
    mykvarray->kvpair = realloc(mykvarray->kvpair,
                                (mykvarray->num_pair + 1) * sizeof(*(mykvarray->kvpair)));
    mykvarray->kvpair[mykvarray->num_pair] = mykvpair;
    mykvarray->num_pair++;
    free(line);  // free
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "fclose failed\n");
    exit(EXIT_FAILURE);
  }

  return mykvarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->num_pair; i++) {
    free(pairs->kvpair[i]->value);
    free(pairs->kvpair[i]->key);
    free(pairs->kvpair[i]);
  }
  free(pairs->kvpair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->num_pair; i++) {
    printf("key ='%s' value = '%s'\n", pairs->kvpair[i]->key, pairs->kvpair[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->num_pair; i++) {
    if (strcmp(pairs->kvpair[i]->key, key) == 0) {
      return pairs->kvpair[i]->value;
    }
  }
  return NULL;
}
