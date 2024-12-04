#include "playground.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool p_is_valid_number(char *str);

// return 1 if should stop
int p_extract_mul(char **str) {
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

  if (!p_is_valid_number(left_number))
    return 1;

  char *parenthesis = strstr(end_comma, ")");
  if (parenthesis == NULL)
    return 1;

  char right_number[parenthesis - end_comma + 1];
  right_number[parenthesis - end_comma] = '\0';
  memcpy(right_number, end_comma, parenthesis - end_comma);

  if (!p_is_valid_number(left_number))
    return 1;

  char *end_ptr;
  int left_number_value = strtol(left_number, &end_ptr, 10);
  int right_number_value = strtol(right_number, &end_ptr, 10);

  printf("%d * %d = %d\n", left_number_value, right_number_value,
         left_number_value * right_number_value);

  *str = parenthesis;
  return 0;
}

int p_playground(void) {
  char *test = "[from()$&from()#mul(417,968)";
  printf("%s\n", test);
  while (!p_extract_mul(&test)) {
  }

  return 0;
}

bool p_is_valid_number(char *str) {
  bool is_number = true;
  size_t i = 0;
  while (str[i] != '\0') {
    if (isdigit(str[i++]))
      continue;

    is_number = false;
    break;
  }

  return is_number;
}
