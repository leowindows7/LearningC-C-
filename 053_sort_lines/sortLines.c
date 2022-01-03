#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  size_t i = 0;
  size_t sz;
  ssize_t len = 0;
  char * line = NULL;
  char ** data = NULL;
  if (argc == 1) {
    while ((len = getline(&line, &sz, stdin)) >= 0) {
      data = realloc(data, (i + 1) * sizeof(*data));
      data[i] = line;
      line = NULL;
      i++;
    }

    sortData(data, i);
    for (size_t j = 0; j < i; j++) {
      printf("%s", data[j]);
      free(data[j]);
    }
    free(line);
    free(data);
  }
  else if (argc > 1) {
    for (int k = 1; k < argc; k++) {
      FILE * f = fopen(argv[k], "r");
      if (f != NULL) {
        while ((len = getline(&line, &sz, f)) >= 0) {
          data = realloc(data, (i + 1) * sizeof(*data));
          data[i] = line;
          line = NULL;
          i++;
        }
        if (fclose(f) != 0) {
          perror("Fail to close the file");
          return EXIT_FAILURE;
        }

        sortData(data, i);
        for (size_t j = 0; j < i; j++) {
          printf("%s", data[j]);
          free(data[j]);
        }
      }
      else {
        perror("No such file");
        free(line);
        free(data);
        return EXIT_FAILURE;
      }
      i = 0;
    }
    free(line);
    free(data);
  }

  return EXIT_SUCCESS;
}
