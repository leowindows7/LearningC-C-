#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  if (inputName == NULL) {
    return NULL;
  }
  char * newInputName = NULL;
  newInputName = malloc((strlen(inputName) + 8) * sizeof(*newInputName));
  strcpy(newInputName, inputName);

  strcat(newInputName, ".counts\0");
  return newInputName;
}
