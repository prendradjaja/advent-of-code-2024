#include <stdio.h>
#include <stdbool.h>


// Input
const int N = 10;
const char INPUT[N * N] =
  // The example input with newlines removed
  "MMMSXXMASMMSAMXMSMSAAMXSXMAAMMMSAMASMSMXXMASAMXAMMXXAMMXXAMASMSMSASXSSSAXAMASAAAMAMMMXMMMMMXMXAXMASX";


// Constants and types
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


// Globals
bool MAS_centers[N * N] = { 0 };
int answer = 0;


void find_MASes(Vector start, Vector direction);

int main() {
  // Explanation:
  // - Look for "MAS" pattern (like in part 1, but only diagonally)
  // - If two different MASes share the same "A" center, they are an X

  for (Vector pos = { 0,     0,     }; pos.c < N;    pos.c++) { find_MASes(pos, DIAG_DL); }
  for (Vector pos = { 1,     N - 1, }; pos.r < N;    pos.r++) { find_MASes(pos, DIAG_DL); }

  for (Vector pos = { 0,     N - 1, }; pos.r < N;    pos.r++) { find_MASes(pos, DIAG_UL); }
  for (Vector pos = { N - 1, N - 2, }; pos.c >= 0;   pos.c--) { find_MASes(pos, DIAG_UL); }

  for (Vector pos = { N - 1, N - 1, }; pos.c >= 0;   pos.c--) { find_MASes(pos, DIAG_UR); }
  for (Vector pos = { N - 2, 0,     }; pos.r >= 0;   pos.r--) { find_MASes(pos, DIAG_UR); }

  for (Vector pos = { N - 1, 0,     }; pos.r >= 0;   pos.r--) { find_MASes(pos, DIAG_DR); }
  for (Vector pos = { 0,     1,     }; pos.c < N;    pos.c++) { find_MASes(pos, DIAG_DR); }

  printf("%d\n", answer);
}


char get_input_char(Vector v) {
  return INPUT[v.r * N + v.c];
}

void add_MAS_center(Vector v) {
  MAS_centers[v.r * N + v.c] = true;
}

bool has_MAS_center(Vector v) {
  return MAS_centers[v.r * N + v.c];
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

Vector add_weighted(Vector v1, int v2_weight, Vector v2) {
  return (Vector){
    v1.r + v2_weight * v2.r,
    v1.c + v2_weight * v2.c,
  };
}

void check_for_MAS(Vector pos, Vector direction) {
  for (int i = 0; i < PATTERN_SIZE; i++) {
    char expected = PATTERN[i];
    char actual = get_input_char(add_weighted(pos, i, direction));
    if (expected != actual) {
      return;
    }
  }

  // MAS found
  Vector center = add(pos, direction);
  if (has_MAS_center(center)) {
    answer++;
  } else {
    add_MAS_center(center);
  }
}

void find_MASes(Vector start, Vector direction) {
  for (
    Vector pos = start;
    in_bounds(add_weighted(pos, PATTERN_SIZE - 1, direction));
    pos = add(pos, direction)
  ) {
    check_for_MAS(pos, direction);
  }
}
