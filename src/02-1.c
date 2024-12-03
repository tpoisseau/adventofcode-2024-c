#include "02-1.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main_02_1(void) {
  int result = 0;

  FILE *pFile;
  unsigned short lineMax = 255;
  char line[lineMax];

  pFile = fopen("./inputs/02.txt", "r");

  if (pFile == NULL) {
    perror("Error opening file.\n");
    return 1;
  }

  int i = 0;
  while (fgets(line, lineMax, pFile)) {
    size_t length = strlen(line);

    char *first = strtok(line, " ");
    char *second = strtok(NULL, " ");

    if (first == NULL || second == NULL) {
      printf("line %d do not include two numbers\n", i);
      return 1;
    }

    char *endPtr;
    int first_value = strtol(first, &endPtr, 10);
    if (endPtr == first) {
      printf("line %d first value is invalid\n", i);
      return 2;
    }

    int second_value = strtol(second, &endPtr, 10);
    if (endPtr == second) {
      printf("line %d second value is invalid\n", i);
      return 2;
    }

    bool is_increasing = second_value > first_value;

    int difference = second_value - first_value;
    bool is_safe = is_increasing && difference >= 1 && difference <= 3 ||
                   !is_increasing && difference <= -1 && difference >= -3;

    printf("%s %d %d start %s", is_increasing ? "increase" : "decrease",
           first_value, second_value, is_safe ? "safe" : "unsafe");

    if (!is_safe) {
      i++;
      printf("\n");
      continue;
    }

    int last_value = second_value;
    while (true) {
      char *nth = strtok(NULL, " ");
      if (nth == NULL)
        break;

      int nth_value = strtol(nth, &endPtr, 10);
      if (endPtr == nth) {
        printf("line %d, nth %s value is invalid", i, nth);
        return 2;
      }

      difference = nth_value - last_value;
      is_safe = is_increasing && difference >= 1 && difference <= 3 ||
                !is_increasing && difference <= -1 && difference >= -3;
      printf(" %d", nth_value);

      if (!is_safe)
        break;

      last_value = nth_value;
    }

    printf(" %s\n", is_safe ? "safe" : "unsafe");

    if (is_safe)
      result++;

    i++;
  }

  printf("Safe levels: %d", result);

  return 0;
}
