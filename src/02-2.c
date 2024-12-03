#include "02-2.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main_02_2(void) {
  int result = 0;

  FILE *pFile;
  unsigned short lineMax = 255;
  char line[lineMax];

  pFile = fopen("./inputs/02.txt", "r");

  if (pFile == NULL) {
    perror("Error opening file.\n");
    return 1;
  }

  char *end_ptr;

  int i = 0;
  while (fgets(line, lineMax, pFile)) {
    char *_line = strtok(line, "\n");
    size_t length = strlen(line);

    char increase_line[length + 1];
    char decrease_line[length + 1];
    strcpy(increase_line, _line);
    strcpy(decrease_line, _line);

    bool had_one_tolerance;
    bool is_safe;
    char *str_value;
    int value;
    int last_value;
    int last_last_value;

    had_one_tolerance = false;
    is_safe = true;
    had_one_tolerance = false;
    str_value = strtok(increase_line, " ");
    value = strtol(str_value, &end_ptr, 10);

    printf("%d | %s ", i, str_value);

    last_last_value = value;
    last_value = value;
    while (true) {
      str_value = strtok(NULL, " ");
      if (str_value == NULL)
        break;

      value = strtol(str_value, &end_ptr, 10);
      int difference = value - last_value;

      printf("%i %s ", difference, str_value);

      bool invalid_tolerance = difference < 1 || difference > 3;
      if (had_one_tolerance && invalid_tolerance) {
        is_safe = false;
        printf("unsafe incr ");
        break;
      }

      if (invalid_tolerance) {
        difference = value - last_last_value;
        invalid_tolerance = difference < 1 || difference > 3;

        if (invalid_tolerance) {
            had_one_tolerance = true;
            printf("tolerance ");
            continue;
        }
      }

      last_last_value = last_value;
      last_value = value;
    }

    if (is_safe) {
      printf("safe incr\n");
      result++;
      i++;
      continue;
    }

    had_one_tolerance = false;
    is_safe = true;
    had_one_tolerance = false;
    str_value = strtok(decrease_line, " ");
    value = strtol(str_value, &end_ptr, 10);

    printf("| %s ", str_value);

    last_value = value;
    while (true) {
      str_value = strtok(NULL, " ");
      if (str_value == NULL)
        break;

      value = strtol(str_value, &end_ptr, 10);
      int difference = value - last_value;

      printf("%i %s ", difference, str_value);

      bool invalid_tolerance = difference < -3 || difference > -1;
      if (had_one_tolerance && invalid_tolerance) {
        is_safe = false;
        printf("unsafe decr ");
        break;
      }

      if (invalid_tolerance) {
        had_one_tolerance = true;
        printf("tolerance ");
        continue;
      }

      last_value = value;
    }

    if (is_safe) {
      printf("safe decr");
      result++;
    }

    printf("\n");
    i++;
  }

  printf("Safe levels: %d", result);

  return 0;
}
