#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  country_t ans;
  // get length of input and check if need to further process
  int length = strlen(line);
  if (line == NULL || length == 0) {
    fprintf(stderr, "Invalid input");
    exit(EXIT_FAILURE);
  }
  // clean up name field with \0
  for (int j = 0; j < 64; j++) {
    ans.name[j] = '\0';
  }
  // Capture country names, loop through characters in line until we see a comma. (only English alphebets and space are accepted)
  // since the length of  ans.name is 64, we won't allow anything greater than that to be input to it
  size_t i = 0;
  while (i < length && line[i] != ',' && i < 64) {
    if ((tolower(line[i]) - 'a' <= 25 && tolower(line[i]) - 'a' >= 0) || line[i] == ' ') {
      ans.name[i] = line[i];
    }
    else {
      fprintf(stderr, "Invalid input");
      exit(EXIT_FAILURE);
    }
    i++;
  }
  // check if we have comma right after processed country names
  if (line[i] != ',') {
    fprintf(stderr, "No proper delimeter");
    exit(EXIT_FAILURE);
  }
  i++;
  // clean up population, only numbers not starting from 0 is allowed i.e. 0012344 will be considered invalid
  ans.population = 0;
  while (i < length && line[i] != '\n') {
    if (line[i] - '0' > 9 || line[i] - '0' < 0) {
      fprintf(stderr, "Not a valid population dat");
      exit(EXIT_FAILURE);
    }
    ans.population = ans.population * 10 + (uint64_t)(line[i] - '0');
    i++;
  }
  // all countries should have at least 1 living person
  if (ans.population == 0) {
    fprintf(stderr, "How come there is no one in your country??");
    exit(EXIT_FAILURE);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  // corner case check, don't accept data less than 7 days
  if (data == NULL || n_days < 7) {
    return;
  }
  // calculate seven days data. derive total cases per 7 days first then divide it by 7
  for (int i = 0; i < n_days - 6; i++) {
    avg[i] = 0;

    for (int j = 0; j < 7; j++) {
      avg[i] += data[i + j];
    }
    avg[i] /= 7.0;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  // corner case check, abort if not enough data
  if (data == NULL || n_days < 7) {
    return;
  }
  // calculate cumulative data first by adding data of each run with previous number in cum[i]
  // after deriving the sum of cumulative data each day, dividing 100000 to covert to per 100000 case
  cum[0] = data[0];
  for (int i = 1; i < n_days; i++) {
    cum[i] = cum[i - 1] + data[i];
  }
  for (int j = 0; j < n_days; j++) {
    cum[j] = cum[j] * 100000 / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //corner case check
  if (countries == NULL || data == NULL || n_countries == 0 || n_days == 0) {
    return;
  }
  // check every data and update country_name  & number_cases if new Max is found
  // update tie if any
  char * country_name = countries[0].name;
  unsigned number_cases = data[0][0];
  int tie = 0;

  for (int i = 0; i < n_countries; i++) {
    for (int j = 0; j < n_days; j++) {
      if (data[i][j] > number_cases) {
        country_name = countries[i].name;
        number_cases = data[i][j];
      }
      else if (data[i][j] == number_cases && country_name != countries[i].name && i > 0 &&
               j >= 0) {
        tie++;
      }
    }
  }
  if (tie) {
    printf("There is a tie between at least two countries\n");
    return;
  }
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
