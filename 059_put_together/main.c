#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the file");
    return NULL;
  }
  counts_t * counts = createCounts();
  char * line = NULL;
  size_t sz;
  ssize_t len = 0;
  // char * ptr = strchr(line, '\n');
  char * ptr = NULL;
  //char * value = malloc((ptr - line + 1) * sizeof(*value));
  char * value = NULL;
  while ((len = getline(&line, &sz, f)) > -0) {
    ptr = strchr(line, '\n');
    value = realloc(value, (ptr - line + 1) * sizeof(*value));
    strncpy(value, line, ptr - line);
    value[ptr - line] = '\0';
    addCount(counts, lookupValue(kvPairs, value));
    free(value);
    free(line);
    line = NULL;
    value = NULL;
  }

  free(line);
  fclose(f);

  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "Not enough args\n");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)

  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    if (c == NULL) {
      break;
    }
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f != NULL) {
      //print the counts from c into the FILE f
      printCounts(c, f);
    }
    //close f
    if (fclose(f)) {
      fprintf(stderr, "cannot close file\n");
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
    //free(c);
  }
  //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
