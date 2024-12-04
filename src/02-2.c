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
    size_t length = strlen(_line);

    int cells[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    for (char *str_value = strtok(_line, " "); str_value != NULL;
         str_value = strtok(NULL, " ")) {
      int value = strtol(str_value, &end_ptr, 10);
      cells[i++] = value;
    }

    bool is_safe = false;

    for (int i = 0; i < 8; i++) {
      int increase_cells[8] = {0, 0, 0, 0, 0, 0, 0, 0};
      int decrease_cells[8] = {0, 0, 0, 0, 0, 0, 0, 0};

      for (int ii = 0; ii < 8; ii++) {
        increase_cells[ii] = cells[ii];
        decrease_cells[ii] = cells[ii];
      }

      for (int ii = i, jj = i + 1; jj < 8; ii++, jj++) {
        increase_cells[ii] = increase_cells[jj];
        decrease_cells[ii] = decrease_cells[jj];
      }
      increase_cells[7] = 0;
      decrease_cells[7] = 0;

      bool is_safe_increase = true;
      for (int jj = 0, ii = 1; ii < 8; ii++, jj++) {
        int value = increase_cells[ii];
        if (value == 0)
          break;
        int prev_value = increase_cells[jj];

        int difference = value - prev_value;
        if (difference >= 1 && difference <= 3)
          continue;

        is_safe_increase = false;
        break;
      }

      if (is_safe_increase) {
        is_safe = true;
        break;
      }

      bool is_safe_decrease = true;
      for (int jj = 0, ii = 1; ii < 8; ii++, jj++) {
        int value = decrease_cells[ii];
        if (value == 0)
          break;
        int prev_value = decrease_cells[jj];

        int difference = value - prev_value;
        if (difference >= -3 && difference <= -1)
          continue;

        is_safe_decrease = false;
        break;
      }

      if (is_safe_decrease) {
        is_safe = true;
        break;
      }
    }

    if (is_safe)
      result++;

    i++;
  }

  printf("Safe levels: %d", result);

  return 0;
}
