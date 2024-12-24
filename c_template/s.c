#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void print_int(int n) {
  printf("%d\n", n);
}

void read_input_file(char* filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Could not open input file\n");
    exit(EXIT_FAILURE);
  }

  const int MAX_LINE_LENGTH = 100000;
  char line[MAX_LINE_LENGTH];
  int r = 0;
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\r\n")] = '\0';

    puts(line);

    // for (int c = 0; line[c] != '\0'; c++) {
    //   unsigned char ch = line[c];
    // }

    r++;
  }

  // This check is here because the loop exits if fgets() returns a null pointer, which happens in
  // both the end-of-file case and the error case (it does not distinguish; ferror() is needed for
  // that). (Source: fgets() documentation)
  if (ferror(file)) {
    fprintf(stderr, "Error reading input file\n");
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

  // int answer = 0;
  // puts("\nAnswer:");
  // printf("%d\n", answer);
}
