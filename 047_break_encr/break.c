#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void decrypt(FILE * f) {
  int alphabetFreq[26];
  int c;
  int globMax = 0;
  int globMaxIndex = 0;

  for (int i = 0; i < 26; i++) {
    alphabetFreq[i] = 0;
  }
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      alphabetFreq[c] += 1;
    }
  }

  for (int j = 0; j < 26; j++) {
    if (alphabetFreq[j] > globMax) {
      globMax = alphabetFreq[j];
      globMaxIndex = j;
    }
  }
  printf("%d\n", (26 + globMaxIndex - 4) % 26);
}

int main(int argc, char ** argv) {
  // FILE * f = fopen(argv[1], "r");
  if (argc != 2) {
    perror(NULL);
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  decrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
