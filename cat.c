#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Copying the features of cat cli program */
void print_file(FILE *fp);
FILE * open_file(char *filepath);

int main(int argc, char *argv[]) {
  int exit_status = 0;
  int i;


  // will contain CLI flags
  typedef struct {
    int number_lines;
    int show_all;
  }

  // needs to get number of arguments if not 2 then reject
  if (argc == 1) {
    print_file(stdin);
    return exit_status;
  }

  // parse any flags
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i][0], '-') == 0) {
      if ((strcmp(argv[i], "-n") == 0) || ((strcmp(argv[i], "--number") == 0))) {
        number = 1;
      }
      if ((strcmp(argv[i], "-A") == 0) || ((strcmp(argv[i], "--show-all") == 0))) {
        show_all = 1;
    }
  }

  // opens each file path and displays them one after another
  FILE *fp;
  for (i = 1; i < argc; i++) {
    // if argument is "-" takes input from stdin until EOF (ctrl+D) then continues  to next argument
    if (strcmp("-", argv[i]) == 0) {
      print_file(stdin); 
    }
    else {
      fp = open_file(argv[i]);
      if (fp == NULL) {
        exit_status = 1;
        continue;
      }
      print_file(fp);
      fclose(fp);
    }
  }
  
  return exit_status;
}

// displays the contents of fp to stdout
void print_file(FILE *fp) {
  if (fp == NULL) {
    return;
  }

  int c;
  while (( c = fgetc(fp)) != EOF) {
    fputc(c, stdout);
  }

}

FILE * open_file(char *filepath) {
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) {
    perror(filepath);
    return NULL;
  }
  return fp;
}
