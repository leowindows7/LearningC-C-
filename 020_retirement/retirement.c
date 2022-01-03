#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double calculation(double balance, double contribution, double rateOfReturn) {
  return balance += balance * rateOfReturn + contribution;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  int dontChange = startAge;
  for (int i = startAge; i < dontChange + working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", i / 12, i % 12, balance);
    balance = calculation(balance, working.contribution, working.rate_of_return);
    startAge += 1;
  }
  // printf("%d", startAge);
  for (int j = startAge; j < dontChange + working.months + retired.months; j++) {
    printf("Age %3d month %2d you have $%.2lf\n", j / 12, j % 12, balance);
    balance = calculation(balance, retired.contribution, retired.rate_of_return);
  }
}

int main() {
  retire_info w = {489, 1000, 0.045 / 12};
  retire_info r = {384, -4000, 0.01 / 12};
  retirement(327, 21345, w, r);
  return EXIT_SUCCESS;
}
