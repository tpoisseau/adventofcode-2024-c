#include "03-1.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("The value of argc is %d\n", argc);

  for (int i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }

  return main_03_1();

  // return 0;
}
