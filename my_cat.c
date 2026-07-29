#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Copying the features of cat cli program */
// will contain CLI flags
typedef struct {
  bool number_lines;
  bool show_all;
} Options;

void print_file(FILE *fp, Options * flag, int * line_ptr);
FILE * open_file(char *filepath);
Options * init_options(void);
int parse_flags(char *argv[], int size, Options *flags); 


int main(int argc, char *argv[]) {
  int exit_status = 0;
  int line = 1; 
  int * line_ptr = &line;
  int flag_set;
  
  Options * flags = init_options();
  if (flags == NULL) {
    return 1;
  }
  flag_set = parse_flags(argv, argc, flags);
  
  // if no arguments or if only flags as arguments
  if (argc == 1 || (flag_set == (argc - 1))) {
    print_file(stdin, flags, line_ptr);
    return exit_status;
  }

  // opens each file path and displays them one after another
  FILE *fp;
  for (int i = 1; i < argc; i++) {
    // if argument is "-" takes input from stdin until EOF (ctrl+D) then continues  to next argument
    if (strcmp("-", argv[i]) == 0) {
      print_file(stdin, flags, line_ptr); 
    } else if (argv[i][0] == '-') {
        continue;
    }
    else {
      fp = open_file(argv[i]);
      if (fp == NULL) {
        exit_status = 1;
        continue;
      }
      print_file(fp, flags, line_ptr); 
      fclose(fp);
    }
  }
  
  return exit_status;
}

// displays the contents of fp to stdout
void print_file(FILE *fp, Options * flags, int * line_ptr) {
  if (fp == NULL) {
    return;
  }

  // char input[4096];
  
  int c;
  bool line_start = true;
  while ((c = fgetc(fp)) != EOF) {

      if (line_start && flags->number_lines) {
      printf("    %d  ", (*line_ptr)++);
      line_start = false;
    }
    if (c == '\n') {
      line_start = true;
    }
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

// Sets all flags to 0
Options * init_options(void) {
  Options * flags = malloc(sizeof(Options));
  if (flags == NULL) {
    perror("Initialize Options Error");
    return NULL;
  }

  flags->number_lines = false;
  flags->show_all = false;
  return flags;
  }

// goes through the input and sets and flag in the CL args
// returns a count of number of flags set
int parse_flags(char *argv[], int size, Options *flags) {
  int flag_set = 0;
  for (int i = 1; i < size; i++) {
    if (argv[i][0] == '-') {
      if ((strcmp(argv[i], "-n") == 0) || ((strcmp(argv[i], "--number") == 0))) {
        flags->number_lines = true;
        flag_set++;
      }
      if ((strcmp(argv[i], "-A") == 0) || ((strcmp(argv[i], "--show-all") == 0))) {
        flags->show_all = true;
        flag_set++;
      }
    }
  }
  return flag_set;
}
