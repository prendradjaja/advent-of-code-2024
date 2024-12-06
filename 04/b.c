#include <stdio.h>
#include <stdbool.h>


// INPUT = The example input with newlines removed
const int N = 10;
const char INPUT[N * N] = "MMMSXXMASMMSAMXMSMSAAMXSXMAAMMMSAMASMSMXXMASAMXAMMXXAMMXXAMASMSMSASXSSSAXAMASAAAMAMMMXMMMMMXMXAXMASX";
char matches[N * N] =     "....................................................................................................";

const int PATTERN_SIZE = 3;
const char PATTERN[PATTERN_SIZE] = "MAS";

typedef struct Vector {
  int r;
  int c;
} Vector;

const Vector UP = { -1, 0 };
const Vector DOWN = { 1, 0 };
const Vector LEFT = { 0, -1 };
const Vector RIGHT = { 0, 1 };
const Vector DIAG_UL = { -1, -1 };
const Vector DIAG_UR = { -1, 1 };
const Vector DIAG_DL = { 1, -1 };
const Vector DIAG_DR = { 1, 1 };


int count_matches(Vector start, Vector direction);

int main() {
  int answer = 0;

  for (Vector pos = { 0,     0,     }; pos.c < N;    pos.c++) { answer += count_matches(pos, DIAG_DL); }
  for (Vector pos = { 1,     N - 1, }; pos.r < N;    pos.r++) { answer += count_matches(pos, DIAG_DL); }

  for (Vector pos = { 0,     N - 1, }; pos.r < N;    pos.r++) { answer += count_matches(pos, DIAG_UL); }
  for (Vector pos = { N - 1, N - 2, }; pos.c >= 0;   pos.c--) { answer += count_matches(pos, DIAG_UL); }

  for (Vector pos = { N - 1, N - 1, }; pos.c >= 0;   pos.c--) { answer += count_matches(pos, DIAG_UR); }
  for (Vector pos = { N - 2, 0,     }; pos.r >= 0;   pos.r--) { answer += count_matches(pos, DIAG_UR); }

  for (Vector pos = { N - 1, 0,     }; pos.r >= 0;   pos.r--) { answer += count_matches(pos, DIAG_DR); }
  for (Vector pos = { 0,     1,     }; pos.c < N;    pos.c++) { answer += count_matches(pos, DIAG_DR); }

  /* printf("%d\n", answer); */
}


char get_input_char(Vector v) {
  return INPUT[v.r * N + v.c];
}

void add_match(Vector v) {
  matches[v.r * N + v.c] = '#';
}

bool has_match(Vector v) {
  return matches[v.r * N + v.c] == '#';
}

int in_bounds(Vector v) {
  return (
    0 <= v.r &&
    v.r < N &&
    0 <= v.c &&
    v.c < N
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
  Vector center = add(pos, direction);
  if (has_match(center)) {
    puts("X found");
  } else {
    add_match(center);
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
