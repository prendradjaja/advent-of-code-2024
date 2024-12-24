#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int ordering_rules[100][100] = { 0 };

void print_int(int n) {
  printf("%d\n", n);
}

void read_ordering_rules(FILE* file) {
  const int MAX_LINE_LENGTH = 100000;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\r\n")] = '\0';

    if (line[0] == '\0') {
      return;
    }

    int first, second;
    sscanf(line, "%d|%d", &first, &second);
    ordering_rules[first][second] = -1;
    ordering_rules[second][first] = 1;
  }
}

void read_page_lists(FILE* file) {
  const int MAX_LINE_LENGTH = 100000;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\r\n")] = '\0';

    puts(line);
  }

  if (ferror(file)) {
    fprintf(stderr, "Error reading input file\n");
    exit(EXIT_FAILURE);
  }
}

int compare(const void* item1, const void* item2) {
  int n1 = *((int*) item1);
  int n2 = *((int*) item2);
  return ordering_rules[n1][n2];
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a ex\n");
    fprintf(stderr, " ./a in\n");
    exit(EXIT_FAILURE);
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
    fprintf(stderr, "Could not open input file\n");
    exit(EXIT_FAILURE);
  }

  read_ordering_rules(file);
  puts("Page lists:");
  read_page_lists(file);

  puts("\nExample qsort call:");
  int n = 5;
  int arr[] = {75,47,61,53,29};
  qsort(arr, n, sizeof(int), compare);
  for (int i = 0; i < n; i++) {
    print_int(arr[i]);
  }
}
