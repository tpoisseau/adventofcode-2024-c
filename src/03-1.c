#include "03-1.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_number(char *str);
int extract_mul(char **str, long *left, long *right);

int main_03_1(void) {
  FILE *pFile;

  pFile = fopen("./inputs/03.txt", "r");

  if (pFile == NULL) {
    perror("Error opening file.\n");
    return 1;
  }

  fseek(pFile, 0, SEEK_END);
  long fsize = ftell(pFile);
  fseek(pFile, 0, SEEK_SET);

  char *content = malloc(fsize + 1);
  fread(content, fsize, 1, pFile);
  fclose(pFile);

  content[fsize] = '\0';

  unsigned long result = 0;

  char *pContent = &content[0];
  long left = 0;
  long right = 0;
  while (!extract_mul(&pContent, &left, &right)) {
    result += left * right;
  }

  printf("Result: %lu\n", result);

  return 0;
}

bool is_valid_number(char *str) {
  bool is_number = true;
  size_t i = 0;
  while (str[i] != '\0') {
    if (i <= 3 && isdigit(str[i++]))
      continue;

    is_number = false;
    break;
  }

  return is_number;
}

int extract_mul(char **str, long *left, long *right) {
  char *mul = strstr(*str, "mul(");
  if (mul == NULL)
    return 1;
  char *end_mul = mul + 4;

  char *comma = strstr(end_mul, ",");
  if (comma == NULL)
    return 1;
  char *end_comma = comma + 1;

  char left_number[comma - end_mul + 1];
  left_number[comma - end_mul] = '\0';
  memcpy(left_number, end_mul, comma - end_mul);

  if (!is_valid_number(left_number)) {
    *str = end_mul - 1;
    return 0;
  }

  char *parenthesis = strstr(end_comma, ")");
  if (parenthesis == NULL)
    return 1;

  char right_number[parenthesis - end_comma + 1];
  right_number[parenthesis - end_comma] = '\0';
  memcpy(right_number, end_comma, parenthesis - end_comma);

  if (!is_valid_number(right_number)) {
    *str = end_comma - 1;
    return 0;
  }

  char *end_ptr;
  *left = strtol(left_number, &end_ptr, 10);
  *right = strtol(right_number, &end_ptr, 10);

  char match[parenthesis - mul + 2];
  match[parenthesis - mul + 1] = '\0';
  memcpy(match, mul, parenthesis - mul + 1);
  printf("%s = %ld * %ld = %ld\n", match, *left, *right, *left * *right);

  // printf("%ld * %ld = %ld\n", *left, *right, *left * *right);

  *str = parenthesis;
  return 0;
}
