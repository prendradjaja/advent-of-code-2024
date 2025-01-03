#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


const int EMPTY = 0;
const int WALL = 1;
const int VISITED = 2;


typedef struct Vector {
  int r;
  int c;
} Vector;
typedef Vector Position;
typedef Vector PositionDelta;

void print_int(int n) {
  printf("%d\n", n);
}

int get_item(int* grid, int grid_size, Position pos) {
  return grid[pos.r * grid_size + pos.c];
}

void set_item(int* grid, int grid_size, Position pos, int value) {
  grid[pos.r * grid_size + pos.c] = value;
}

void read_input_file(char* filename, int grid_size, int* grid, int count_walls) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Could not open input file\n");
    exit(EXIT_FAILURE);
  }

  const int MAX_LINE_LENGTH = 100000;
  char line[MAX_LINE_LENGTH];
  for (int i = 0; i < count_walls; i++) {
    fgets(line, MAX_LINE_LENGTH, file);
    line[strcspn(line, "\r\n")] = '\0';
    int r, c;
    sscanf(line, "%d,%d", &c, &r);
    set_item(grid, grid_size, (Vector) { r, c }, WALL);
  }

  if (ferror(file)) {
    fprintf(stderr, "Error reading input file\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char** argv) {
  if (argc < 3) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a INPUT_FILE MAX_GRID_COORDINATE COUNT_WALLS\n");
    fprintf(stderr, " ./a ex 6 12\n");
    fprintf(stderr, " ./a in 70 1024\n");
    exit(EXIT_FAILURE);
  }
  int grid_size = atoi(argv[2]) + 1;
  int count_walls = atoi(argv[3]);

  int* grid = malloc(grid_size * grid_size * sizeof(int));

  read_input_file(argv[1], grid_size, grid, count_walls);

  for (int r = 0; r < grid_size; r++) {
    for (int c = 0; c < grid_size; c++) {
      char ch = get_item(grid, grid_size, (Vector) { r, c }) == 0 ? '.' : '#';
      printf("%c", ch);
    }
    puts("");
  }

  // CONTINUE_HERE: Pathfinding (probably BFS)

  /* int answer = 0; */
  /* puts("\nAnswer:"); */
  /* printf("%d\n", answer); */
}
