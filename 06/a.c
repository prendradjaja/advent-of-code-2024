#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// SIZE = the width of the input = the height of the input
const int SIZE = 10;

// The example input with newlines removed
char input[] = "....#..............#............#..............#.............#..^.............#.#...............#...";


typedef struct Vector {
  int r;
  int c;
} Vector;

const Vector UP = { -1, 0 };
const Vector DOWN = { 1, 0 };
const Vector LEFT = { 0, -1 };
const Vector RIGHT = { 0, 1 };


char get_char(Vector pos) {
  return input[pos.r * SIZE + pos.c];
}

void set_char(Vector pos, char new_value) {
  input[pos.r * SIZE + pos.c] = new_value;
}

bool in_bounds(Vector pos) {
  return (
    0 <= pos.r &&
    pos.r < SIZE &&
    0 <= pos.c &&
    pos.c < SIZE
  );
}

Vector add(Vector v1, Vector v2) {
  return (Vector){
    .r = v1.r + v2.r,
    .c = v1.c + v2.c,
  };
}

Vector turn(Vector direction) {
  if (direction.r == UP.r && direction.c == UP.c) {
    return RIGHT;
  } else if (direction.r == RIGHT.r && direction.c == RIGHT.c) {
    return DOWN;
  } else if (direction.r == DOWN.r && direction.c == DOWN.c) {
    return LEFT;
  } else if (direction.r == LEFT.r && direction.c == LEFT.c) {
    return UP;
  } else {
    fprintf(stderr, "Unexpected direction\n");
    exit(EXIT_FAILURE);
  }
}

Vector find_start() {
  Vector result;
  for (int r = 0; r < SIZE; r++) {
    for (int c = 0; c < SIZE; c++) {
      Vector pos = { r, c };
      if (get_char(pos) == '^') {
        result = pos;
      }
    }
  }
  return result;
}

int main() {
  Vector pos = find_start();
  Vector direction = UP;

  // Simulate the guard's movement
  while (in_bounds(pos)) {
    set_char(pos, 'X');
    Vector next = add(pos, direction);
    if (in_bounds(next) && get_char(next) == '#') {
      direction = turn(direction);
    } else {
      pos = next;
    }
  }

  // Count visited positions
  int answer = 0;
  for (char* ch = input; *ch != 0; ch++) {
    if (*ch == 'X') {
      answer++;
    }
  }
  printf("%d\n", answer);
}
