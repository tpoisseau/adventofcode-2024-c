#include "01-1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main_01_1(void) {
  FILE *pFile;
  unsigned short lineMax = 255;
  char line[lineMax];

  pFile = fopen("./inputs/01.txt", "r");

  if (pFile == NULL) {
    perror("Error opening file.");
    return 1;
  }

  while (fgets(line, lineMax, pFile)) {
    size_t length = strlen(line);

    char *left = strtok(line, "   ");
    char *right = strtok(NULL, "   ");
  }

  return 0;
}
