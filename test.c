#include <stdio.h>

int main(void) {

  int c;

  while ((c=fgetc(stdin)) != EOF) {
    if (c < 32) {
      printf(":%c")
    }
  }
:wq
:wq
:wq
}
