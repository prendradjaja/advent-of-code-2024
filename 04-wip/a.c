#include <stdio.h>
#include <stdlib.h>

/* fprintf(stderr, "Input too long\n"); */
/* exit(EXIT_FAILURE); */

const int PATTERN_SIZE = 4;
const int PATTERN[PATTERN_SIZE] = { 'A', 'B', 'C', 'D', };

const int GRID_SIZE = 10;
const int GRID[GRID_SIZE][GRID_SIZE] = {
  { 'A', 'B', 'C', 'D', 'O', 'O', 'A', 'B', 'C', 'D', },
  { 'O', 'A', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'O', },
  { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
  { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
  { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
  { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
  { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
  { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
  { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
  { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
};

void print_int(int n) {
  printf("%d\n", n);
}

int count_occurrences(const int* row, int row_size) {
  int positions = row_size - PATTERN_SIZE + 1;
  int result = 0;
  for (int i = 0; i < positions; i++) {
    if (
      row[i] == PATTERN[0] &&
      row[i + 1] == PATTERN[1] &&
      row[i + 2] == PATTERN[2] &&
      row[i + 3] == PATTERN[3]
    ) {
      result++;
    }
  }
  return result;
}

/* void show_grid(int grid[10][10], int grid_size) { */
/*   for (int r = 0; r < grid_size; r++) { */
/*     for (int c = 0; c < grid_size; c++) { */
/*       printf("%d ", grid[r][c]); */
/*     } */
/*     puts(""); */
/*   } */
/* } */

int main() {
  /* FILE *file = fopen("ex", "r"); */
  /* FILE *file = fopen("in", "r"); */

  int* arr = (int*) malloc(10 * sizeof(int));
  arr[0] = 1;
  print_int(arr[0]);

  /* show_grid(GRID, GRID_SIZE); */

  int answer = 0;
  printf("%d\n", count_occurrences(GRID[0], GRID_SIZE));
}
