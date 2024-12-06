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

typedef struct Vector {
  int r;
  int c;
} Vector;

const Vector NORTHWEST = { .r = -1, .c = -1 };
const Vector NORTHEAST = { .r = -1, .c = 1 };
const Vector SOUTHWEST = { .r = 1, .c = -1 };
const Vector SOUTHEAST = { .r = 1, .c = 1 };

/* const int example_arr[] = { */
/*   'M', 'M', 'M', 'S', 'X', 'X', 'M', 'A', 'S', 'M', */
/*   'M', 'S', 'A', 'M', 'X', 'M', 'S', 'M', 'S', 'A', */
/*   'A', 'M', 'X', 'S', 'X', 'M', 'A', 'A', 'M', 'M', */
/*   'M', 'S', 'A', 'M', 'A', 'S', 'M', 'S', 'M', 'X', */
/*   'X', 'M', 'A', 'S', 'A', 'M', 'X', 'A', 'M', 'M', */
/*   'X', 'X', 'A', 'M', 'M', 'X', 'X', 'A', 'M', 'A', */
/*   'S', 'M', 'S', 'M', 'S', 'A', 'S', 'X', 'S', 'S', */
/*   'S', 'A', 'X', 'A', 'M', 'A', 'S', 'A', 'A', 'A', */
/*   'M', 'A', 'M', 'M', 'M', 'X', 'M', 'M', 'M', 'M', */
/*   'M', 'X', 'M', 'X', 'A', 'X', 'M', 'A', 'S', 'X', */
/* }; */

const int example_arr[] = {
  '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
  't', '.', '.', '.', '.', '.', '.', '.', '.', 'b',
  's', '.', '.', '.', '.', '.', '.', '.', '.', 'c',
  'n', '.', '.', '.', '.', '.', '.', '.', '.', 'd',
  'q', '.', '.', '.', '.', '.', '.', '.', '.', 'e',
  'p', '.', '.', '.', '.', '.', '.', '.', '.', 'f',
  'o', '.', '.', '.', '.', '.', '.', '.', '.', 'g',
  'n', '.', '.', '.', '.', '.', '.', '.', '.', 'h',
  'm', '.', '.', '.', '.', '.', '.', '.', '.', 'i',
  'l', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A',
};

const Grid example_grid = {
  .row_count = 10,
  .col_count = 10,
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
  .arr = example_arr,
#pragma GCC diagnostic pop
};

/* Vector* a = (Vector*) malloc(sizeof(Vector) * 10); */

/* const Vector a[] = { */
/*   (Vector){ 0, 0 }, */
/*   (Vector){ 0, 1 }, */
/* }; */

void print_int(int n) {
  printf("%d\n", n);
}

// todo: Try using a macro maybe
int get_grid_item(Grid grid, int r, int c) {
  return grid.arr[r * grid.col_count + c];
}

int in_bounds(Grid grid, int r, int c) {
  return (
    0 <= r &&
    r < grid.row_count &&
    0 <= c &&
    c < grid.col_count
  );
}

Vector add(Vector v1, Vector v2) {
  return (Vector){
    .r = v1.r + v2.r,
    .c = v1.c + v2.c,
  };
}

void get_diagonal(Grid grid, Vector start, Vector direction) {
  Vector curr = start;
  while (in_bounds(grid, curr.r, curr.c)) {
    printf("%c\n", get_grid_item(grid, curr.r, curr.c));
    curr = add(curr, direction);
  }
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

  Vector origin = { .r = 0, .c = 0 };
  get_diagonal(example_grid, origin, SOUTHEAST);

  // top down
  // bottom up
  // leftside rightward
  // rightside leftward
  // L northwest
  // L northeast
  // L southwest
  // L southeast
}
