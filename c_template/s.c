#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// On pointer style:
//
// Probably shift from `int* foo` to `int *foo`. There's a handful of common arguments out there for
// each side. During AoC 2024 I stuck with what felt familiar instead of forming an opinion, but
// after reading those arguments I think I prefer the latter.


void print_int(int n) {
  printf("%d\n", n);
}

void read_input_file(char* filename) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  const int MAX_LINE_LENGTH = 100000;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    // I haven't tested this on a file with DOS line endings, but this loop should properly handle
    // both Unix and DOS line endings.
    line[strcspn(line, "\r\n")] = '\0';

    // Do something with `line` (e.g. here, just print it)
    puts(line);
  }

  // This check is here because the loop exits if fgets() returns a null pointer, which happens in
  // both the end-of-file case and the error case (it does not distinguish; ferror() is needed for
  // that). (Source: fgets() documentation)
  if (ferror(file)) {
    perror(NULL);
    exit(EXIT_FAILURE);
  }
}


int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a ex\n");
    fprintf(stderr, " ./a in\n");
    exit(EXIT_FAILURE);
  }
  read_input_file(argv[1]);
}
