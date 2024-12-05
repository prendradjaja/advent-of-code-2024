#include <stdio.h>
#include <stdlib.h>

/* fprintf(stderr, "Input too long\n"); */
/* exit(EXIT_FAILURE); */

const int PATTERN_SIZE = 4;
const int PATTERN[PATTERN_SIZE] = { 'A', 'B', 'C', 'D', };

typedef struct Grid {
  int* arr;
  int row_count;
  int col_count;
} Grid;

const int example_arr[] = {
  'A', 'B', 'C', 'D', 'O', 'O', 'A', 'B', 'C', 'D',
  'O', 'A', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'A',
  'B', 'C', 'D', '.', '.', '.', '.', '.', '.', '.',
};

const Grid example_grid = {
  .row_count = 3,
  .col_count = 10,
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
  .arr = example_arr,
#pragma GCC diagnostic pop
};

void print_int(int n) {
  printf("%d\n", n);
}

// todo: Try using a macro maybe
int get_grid_item(Grid grid, int r, int c) {
  return grid.arr[r * grid.col_count + c];
}

void set_grid_item(Grid grid, int r, int c, int value) {
  grid.arr[r * grid.col_count + c] = value;
}

Grid transpose(Grid grid) {
  int* arr_copy = (int*) malloc(sizeof(int) * grid.row_count * grid.col_count);
  Grid grid_copy = grid;
  grid_copy.arr = arr_copy;
  grid_copy.row_count = grid.col_count;
  grid_copy.col_count = grid.row_count;

  for (int r = 0; r < grid.row_count; r++) {
    for (int c = 0; c < grid.col_count; c++) {
      set_grid_item(grid_copy, c, r, get_grid_item(grid, r, c));
    }
  }

  return grid_copy;
}

// "Simple occurrences" = horizontal and forwards
int count_simple_occurrences(Grid grid) {
  int positions = grid.col_count - PATTERN_SIZE + 1;
  int result = 0;
  for (int r = 0; r < grid.row_count; r++) {
    for (int c = 0; c < positions; c++) {
      if (
        get_grid_item(grid, r, c) == PATTERN[0] &&
        get_grid_item(grid, r, c + 1) == PATTERN[1] &&
        get_grid_item(grid, r, c + 2) == PATTERN[2] &&
        get_grid_item(grid, r, c + 3) == PATTERN[3]
      ) {
        result++;
      }
    }
  }
  return result;
}

void show_grid(Grid grid) {
  for (int r = 0; r < grid.row_count; r++) {
    for (int c = 0; c < grid.col_count; c++) {
      printf("%c ", get_grid_item(grid, r, c));
    }
    puts("");
  }
}

int main() {
  /* FILE *file = fopen("ex", "r"); */
  /* FILE *file = fopen("in", "r"); */

  /* int* arr = (int*) malloc(10 * sizeof(int)); */
  /* arr[0] = 1; */
  /* print_int(arr[0]); */

  /* int answer = 0; */
  /* printf("%d\n", answer); */

  show_grid(example_grid);
  printf("%d\n", count_simple_occurrences(example_grid));

  // full solution pseudocode
  //
  // count(grid)
  // count(flip(grid))
  // count(transpose(grid))
  // count(flip(transpose(grid)))
  //
  // todo: Diagonals
}
