#include "02-2.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("The value of argc is %d\n", argc);

  for (int i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }

  main_02_2();

  return 0;
}
