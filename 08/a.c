#include <stdio.h>
#include <stdbool.h>


// Input and constants
const int END_OF_SUBARRAY = -2;
const int END_OF_INPUT = -1;

const int SIZE = 12;
int input[] = {
  // Example input
  '0', 1, 8,
  2, 5,
  3, 7,
  4, 4,
  END_OF_SUBARRAY,
  'A', 5, 6,
  8, 8,
  9, 9,
  END_OF_SUBARRAY,
  END_OF_INPUT,
};


// Types
typedef struct Vector {
  int r;
  int c;
} Vector;
typedef Vector Position;
typedef Vector PositionDelta;


// Functions
Vector add(Vector v1, Vector v2) {
  return (Vector){
    v1.r + v2.r,
    v1.c + v2.c,
  };
}

Vector subtract(Vector v1, Vector v2) {
  return (Vector){
    v1.r - v2.r,
    v1.c - v2.c,
  };
}

bool in_bounds(Position v) {
  return (
    0 <= v.r && v.r < SIZE &&
    0 <= v.c && v.c < SIZE
  );
}

void find_antinodes(Position pos1, Position pos2, bool* is_antinode) {
  PositionDelta delta = subtract(pos2, pos1);

  Position antinode1 = subtract(pos1, delta);
  if (in_bounds(antinode1)) {
    is_antinode[antinode1.r * SIZE + antinode1.c] = true;
  }

  Position antinode2 = add(pos2, delta);
  if (in_bounds(antinode2)) {
    is_antinode[antinode2.r * SIZE + antinode2.c] = true;
  }
}

int* consume_one_subarray(int* arr, bool* is_antinode) {
  // Discard frequency
  arr++;

  // Count antennas
  int* start = arr;
  int count_antennas = 0;
  while (*arr != END_OF_SUBARRAY) {
    count_antennas++;
    arr += 2;
  }
  arr++;

  // Find antinodes
  for (int i = 0; i < count_antennas; i++) {
    for (int j = i + 1; j < count_antennas; j++) {
      Position pos1 = { start[i * 2], start[i * 2 + 1] };
      Position pos2 = { start[j * 2], start[j * 2 + 1] };
      find_antinodes(pos1, pos2, is_antinode);
    }
  }
  return arr;
}

int main() {
  // Find antinodes
  bool is_antinode[SIZE * SIZE] = { 0 };
  int* ptr = input;
  while (*ptr != END_OF_INPUT) {
    ptr = consume_one_subarray(ptr, is_antinode);
  }

  // Count antinodes
  int answer = 0;
  for (int i = 0; i < SIZE * SIZE; i++) {
    answer += is_antinode[i];
  }
  printf("%d\n", answer);
}
