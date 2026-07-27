#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Copying the features of cat cli program */

int main(int argc, char *argv[]) {
  // needs to get number of arguments if not 2 then reject
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr,"Cannot open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  int c;

  while (( c = fgetc(fp)) != EOF) {
    fputc(c, stdout);
  }

  fclose(fp);


  // then needs to open the file, read it all, then close it, then stdout
  //
  //

  return 0;
}
