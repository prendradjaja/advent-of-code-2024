#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* fprintf(stderr, "Input too long\n"); */
/* exit(EXIT_FAILURE); */

const int PATTERN_SIZE = 4;
const char PATTERN[PATTERN_SIZE] = { 'X', 'M', 'A', 'S', };

typedef struct Vector {
  int r;
  int c;
} Vector;

// UDLR or NSEW?

const Vector UP = { -1, 0 };
const Vector DOWN = { 1, 0 };
const Vector LEFT = { 0, -1 };
const Vector RIGHT = { 0, 1 };

const Vector NORTHWEST = { -1, -1 };
const Vector NORTHEAST = { -1, 1 };
const Vector SOUTHWEST = { 1, -1 };
const Vector SOUTHEAST = { 1, 1 };

const int SIZE = 10;

const char INPUT[SIZE * SIZE] = {
  'M', 'M', 'M', 'S', 'X', 'X', 'M', 'A', 'S', 'M',
  'M', 'S', 'A', 'M', 'X', 'M', 'S', 'M', 'S', 'A',
  'A', 'M', 'X', 'S', 'X', 'M', 'A', 'A', 'M', 'M',
  'M', 'S', 'A', 'M', 'A', 'S', 'M', 'S', 'M', 'X',
  'X', 'M', 'A', 'S', 'A', 'M', 'X', 'A', 'M', 'M',
  'X', 'X', 'A', 'M', 'M', 'X', 'X', 'A', 'M', 'A',
  'S', 'M', 'S', 'M', 'S', 'A', 'S', 'X', 'S', 'S',
  'S', 'A', 'X', 'A', 'M', 'A', 'S', 'A', 'A', 'A',
  'M', 'A', 'M', 'M', 'M', 'X', 'M', 'M', 'M', 'M',
  'M', 'X', 'M', 'X', 'A', 'X', 'M', 'A', 'S', 'X',
};

/* const char INPUT[SIZE * SIZE] = { */
/*   'X', 'M', 'A', 'S', '.', '.', 'X', 'M', 'A', 'S', */
/*   '.', '.', '.', '.', '.', 'X', 'M', 'A', 'S', '.', */
/*   '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', */
/*   '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', */
/*   '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', */
/*   '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', */
/*   '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', */
/*   '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', */
/*   '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', */
/*   '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', */
/* }; */

/* const char INPUT[SIZE * SIZE] = { */
/*   '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', */
/*   't', '.', '.', '.', '.', '.', '.', '.', '.', 'b', */
/*   's', '.', '.', '.', '.', '.', '.', '.', '.', 'c', */
/*   'n', '.', '.', '.', '.', '.', '.', '.', '.', 'd', */
/*   'q', '.', '.', '.', '.', '.', '.', '.', '.', 'e', */
/*   'p', '.', '.', '.', '.', '.', '.', '.', '.', 'f', */
/*   'o', '.', '.', '.', '.', '.', '.', '.', '.', 'g', */
/*   'n', '.', '.', '.', '.', '.', '.', '.', '.', 'h', */
/*   'm', '.', '.', '.', '.', '.', '.', '.', '.', 'i', */
/*   'l', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A', */
/* }; */

void print_int(int n) {
  printf("%d\n", n);
}

// todo: Try using a macro maybe
char get_input_char(Vector v) {
  return INPUT[v.r * SIZE + v.c];
}

int in_bounds(Vector v) {
  return (
    0 <= v.r &&
    v.r < SIZE &&
    0 <= v.c &&
    v.c < SIZE
  );
}

Vector add(Vector v1, Vector v2) {
  return (Vector){
    v1.r + v2.r,
    v1.c + v2.c,
  };
}

Vector weighted_sum(int s1, Vector v1, int s2, Vector v2) {
  return (Vector){
    s1 * v1.r + s2 * v2.r,
    s1 * v1.c + s2 * v2.c,
  };
}

bool is_match(Vector pos, Vector direction) {
  for (int i = 0; i < PATTERN_SIZE; i++) {
    char expected = PATTERN[i];
    char actual = get_input_char(weighted_sum(1, pos, i, direction));
    if (expected != actual) {
      return false;
    }
  }
  return true;
}

int count_matches(Vector start, Vector direction) {
  int result = 0;
  for (
    Vector pos = start;
    in_bounds(weighted_sum(1, pos, PATTERN_SIZE - 1, direction));
    pos = add(pos, direction)
  ) {
    result += is_match(pos, direction);
  }
  return result;
}

int main() {
  int answer = 0;

  // Top
  for (Vector pos = { 0,        0,        }; pos.c < SIZE; pos.c++) answer += count_matches(pos, DOWN);

  for (Vector pos = { 0,        0,        }; pos.c < SIZE; pos.c++) answer += count_matches(pos, SOUTHWEST);
  for (Vector pos = { 1,        SIZE - 1, }; pos.r < SIZE; pos.r++) answer += count_matches(pos, SOUTHWEST);

  // Right side
  for (Vector pos = { 0,        SIZE - 1, }; pos.r < SIZE; pos.r++) answer += count_matches(pos, LEFT);

  for (Vector pos = { 0,        SIZE - 1, }; pos.r < SIZE; pos.r++) answer += count_matches(pos, NORTHWEST);
  for (Vector pos = { SIZE - 2, SIZE - 1, }; pos.c >= 0;   pos.c--) answer += count_matches(pos, NORTHWEST);

  // Bottom
  for (Vector pos = { SIZE - 1, SIZE - 1, }; pos.c >= 0;   pos.c--) answer += count_matches(pos, UP);

  for (Vector pos = { SIZE - 1, SIZE - 1, }; pos.c >= 0;   pos.c--) answer += count_matches(pos, NORTHEAST);
  for (Vector pos = { SIZE - 2, 0,        }; pos.r >= 0;   pos.r--) answer += count_matches(pos, NORTHEAST);

  // Left side
  for (Vector pos = { SIZE - 1, 0,        }; pos.r >= 0;   pos.r--) answer += count_matches(pos, RIGHT);

  for (Vector pos = { SIZE - 1, 0,        }; pos.r >= 0;   pos.r--) answer += count_matches(pos, SOUTHEAST);
  for (Vector pos = { 1,        0,        }; pos.c < SIZE; pos.c++) answer += count_matches(pos, SOUTHEAST);

  printf("%d\n", answer);
}
