#include <stdio.h>
#include <stdlib.h>

void rotateInput(FILE * f) {
  int c, row = 0, column = 0;
  char inputMatrix[10][10];
  int total = 0;
  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      if (column == 10) {
        column = 0;
        row++;
        continue;
      }
      else {
        perror("incorrect length of string");
        exit(EXIT_FAILURE);
      }
    }
    inputMatrix[row][column] = c;
    column++;
    total++;
  }
  if (total != 100) {
    perror("incorrect length of string");
    exit(EXIT_FAILURE);
  }
  // printf("%d", total);
  char rot_inputMatrix[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      rot_inputMatrix[j][9 - i] = inputMatrix[i][j];
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", rot_inputMatrix[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    perror("incorrect number of arguments !");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }

  rotateInput(f);
  if (fclose(f) != 0) {
    perror("Failed to close input file\n");
    return EXIT_FAILURE;
  }
}
