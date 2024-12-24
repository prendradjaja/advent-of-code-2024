#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


const int MAX_LINE_LENGTH = 100000;
const int MAX_MOVEMENTS = 100000;

typedef struct Vector {
  int r;
  int c;
} Vector;
typedef Vector Position;
typedef Vector PositionDelta;


char** read_grid(FILE* file, int size) {
  char** grid = malloc((size + 1) * sizeof(char*));
  for (int i = 0; i < size; i++) {
    char* row = malloc((size + 1) * sizeof(char));
    // fgets(row, size + 1, file); // Why didn't this work
    fgets(row, MAX_LINE_LENGTH, file);
    row[strcspn(row, "\r\n")] = '\0';
    grid[i] = row;
  }
  return grid;
}

char* read_movements(FILE* file, int count_movement_lines) {
  char* discard = malloc(MAX_LINE_LENGTH * sizeof(char));
  fgets(discard, MAX_LINE_LENGTH, file);

  char* result = malloc(MAX_MOVEMENTS * sizeof(char));
  char* result_start = result;
  int ch;
  while ((ch = getc(file)) != EOF) {
    if (ch != '\n' && ch != '\r') {
      *result = ch;
      result++;
    }
  }
  *result = '\0';
  result++;
  return result_start;
}

char get_item(char** grid, Position pos) {
  return grid[pos.r][pos.c];
}

void set_item(char** grid, Position pos, char value) {
  grid[pos.r][pos.c] = value;
}

Position find_robot(char** grid, int size) {
  for (int r = 0; r < size; r++) {
    for (int c = 0; c < size; c++) {
      Position pos = { r, c };
      if (get_item(grid, pos) == '@') {
        return pos;
      }
    }
  }
  fprintf(stderr, "Robot not found\n");
  exit(EXIT_FAILURE);
}

PositionDelta decode_move(char move) {
  switch (move) {
    case '^': return (Vector) { -1, 0 };
    case 'v': return (Vector) { 1, 0 };
    case '<': return (Vector) { 0, -1 };
    case '>': return (Vector) { 0, 1 };
  }
  fprintf(stderr, "Invalid input to decode_move()\n");
  exit(EXIT_FAILURE);
}

Vector add(Vector v1, Vector v2) {
  return (Vector){
    v1.r + v2.r,
    v1.c + v2.c,
  };
}

Vector negate(Vector v) {
  return (Vector) { -v.r, -v.c };
}

Position attempt_move(char** grid, Position robot, char _move) {
  PositionDelta move = decode_move(_move);
  PositionDelta unmove = negate(move);

  bool can_move = false;
  int distance_to_free_space = 0;
  Position free_space;
  for (Position pos = robot; get_item(grid, pos) != '#'; pos = add(pos, move)) {
    if (get_item(grid, pos) == '.') {
      can_move = true;
      free_space = pos;
      break;
    }
    distance_to_free_space++;
  }

  if (!can_move) {
    return robot;
  }

  Position pos = free_space;
  for (int i = 0; i < distance_to_free_space; i++) {
    Position dst = pos;
    pos = add(pos, unmove);
    Position src = pos;
    set_item(grid, dst, get_item(grid, src));
  }
  set_item(grid, robot, '.');
  return add(robot, move);
}

int main(int argc, char** argv) {
  if (argc < 4) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a ex 10 10\n");
    fprintf(stderr, " ./a in 50 20\n");
    exit(EXIT_FAILURE);
  }

  char* filename = argv[1];

  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Could not open input file\n");
    exit(EXIT_FAILURE);
  }


  int size = atoi(argv[2]);
  int count_movement_lines = atoi(argv[3]);
  char** grid = read_grid(file, size);
  char* movements = read_movements(file, count_movement_lines);

  Position robot = find_robot(grid, size);

  for (; *movements != '\0'; movements++) {
    robot = attempt_move(grid, robot, *movements);
  }

  int answer = 0;
  for (int r = 0; r < size; r++) {
    for (int c = 0; c < size; c++) {
      if (get_item(grid, (Vector) { r, c }) == 'O') {
        answer += 100 * r + c;
      }
    }
  }
  printf("%d\n", answer);
}
