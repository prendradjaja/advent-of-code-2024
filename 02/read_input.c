#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void print_int(int n) {
  printf("%d\n", n);
}

void read_ints_from_line(char* line) {
  int n;
  int inc;
  while (sscanf(line, "%d%n", &n, &inc) == 1) {
    line += inc;
    print_int(n);
  }
  puts("");
}

void read_input_file(char* filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Could not open input file\n");
    exit(EXIT_FAILURE);
  }

  const int MAX_LINE_LENGTH = 100000;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\r\n")] = '\0';
    read_ints_from_line(line);
  }

  if (ferror(file)) {
    fprintf(stderr, "Error reading input file\n");
    exit(EXIT_FAILURE);
  }
}

int main() {
  read_input_file("ex");
}
