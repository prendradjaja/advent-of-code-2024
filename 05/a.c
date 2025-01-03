#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


int ordering_rules[100][100] = { 0 };

typedef struct ArrayWithSize {
  int* data;
  int size;
} ArrayWithSize;

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

// Parses a string of comma-separated ints
//
// Warning: Mutates s
//
// To do the same thing without mutating s, copy the string first.
// See this gist:
// https://gist.github.com/prendradjaja/de4af37c8b7be046742838886e25056f
ArrayWithSize parse_ints(char *s) {
  const int MAX_ARRAY_SIZE = 100;
  int* data = malloc(MAX_ARRAY_SIZE * sizeof(int));
  int size = 0;
  char* token = strtok(s, ",");
  while (token) {
    data[size++] = atoi(token);
    token = strtok(NULL, ",");
  }
  return (ArrayWithSize) { data, size };
}

void read_page_lists(FILE* file, ArrayWithSize* page_lists, int* count_page_lists) {
  const int MAX_LINE_LENGTH = 100000;
  char line[MAX_LINE_LENGTH];

  *count_page_lists = 0;

  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\r\n")] = '\0';

    ArrayWithSize page_list = parse_ints(line);
    page_lists[*count_page_lists] = page_list;
    (*count_page_lists)++;
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

// Arguments are the same as qsort()
bool is_sorted(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
  char* base_char = base;
  for (int i = 1; i < nel; i++) {
    char* prev = base_char + width * (i - 1);
    char* curr = base_char + width * i;
    if (compar(prev, curr) == 1) {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  const int MAX_COUNT_PAGE_LISTS = 1000;

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

  int count_page_lists;
  ArrayWithSize* page_lists = malloc(MAX_COUNT_PAGE_LISTS * sizeof(ArrayWithSize));
  read_page_lists(file, page_lists, &count_page_lists);

  int answer = 0;
  for (int i = 0; i < count_page_lists; i++) {
    int* page_list = page_lists[i].data;
    int count_pages = page_lists[i].size;
    if (is_sorted(page_list, count_pages, sizeof(int), compare)) {
      int median = page_list[count_pages / 2];
      answer += median;
    }
  }
  printf("%d\n", answer);
}
