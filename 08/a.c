#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// Types and constants =============================================================================
typedef struct Vector {
  int r;
  int c;
} Vector;
typedef Vector Position;
typedef Vector PositionDelta;

const int MAX_ANTENNAS_PER_FREQUENCY = 10;


// Globals =========================================================================================

// e.g. count_antennas['A'] = 5 means there are 5 antennas of frequency 'A'
int count_antennas[128] = { 0 };

// e.g. antennas['A'] is an array containing the positions of those 5 antennas
Vector antennas[128][MAX_ANTENNAS_PER_FREQUENCY];
// We can probably improve this (remove the need for count_antennas separate from antennas) by
// changing each antennas[freq] from an array of Vectors to an array of Vector*s, so that i can just
// use null-terminated arrays

int input_size;


// Functions =======================================================================================
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
    0 <= v.r && v.r < input_size &&
    0 <= v.c && v.c < input_size
  );
}

/*
 * Read the input file and transform its contents into position vectors, storing the results in
 * `input_size`, `antennas` and `count_antennas`.
 */
void read_input_file(char* filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Could not open input file\n");
    exit(EXIT_FAILURE);
  }

  const int MAX_LINE_LENGTH = 100;
  char line[MAX_LINE_LENGTH];
  int r = 0;
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\r\n")] = '\0';

    for (int c = 0; line[c] != '\0'; c++) {
      Vector pos = { r, c };
      unsigned char ch = line[c];
      if (ch == '.') {
        continue; // '.' is not a frequency, it is just the "background" -- ignore it
      }

      int idx = count_antennas[ch];
      antennas[ch][idx] = pos;
      count_antennas[ch]++;
    }
    r++;
  }

  input_size = r;

  if (ferror(file)) {
    fprintf(stderr, "Error reading input file\n");
    exit(EXIT_FAILURE);
  }
}

void find_antinodes_for_two_antennas(Position pos1, Position pos2, bool* is_antinode) {
  PositionDelta delta = subtract(pos2, pos1);

  Position antinode1 = subtract(pos1, delta);
  if (in_bounds(antinode1)) {
    is_antinode[antinode1.r * input_size + antinode1.c] = true;
  }

  Position antinode2 = add(pos2, delta);
  if (in_bounds(antinode2)) {
    is_antinode[antinode2.r * input_size + antinode2.c] = true;
  }
}

void find_antinodes_for_frequency(unsigned char freq, bool* is_antinode) {
  for (int i = 0; i < count_antennas[freq]; i++) {
    for (int j = i + 1; j < count_antennas[freq]; j++) {
      Position pos1 = antennas[freq][i];
      Position pos2 = antennas[freq][j];
      find_antinodes_for_two_antennas(pos1, pos2, is_antinode);
    }
  }
}

int main(int argc, char** argv) {
  // Read args and input file
  if (argc < 2) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a ex\n");
    fprintf(stderr, " ./a in\n");
    exit(EXIT_FAILURE);
  }
  read_input_file(argv[1]);

  // Find antinodes
  bool* is_antinode = malloc(input_size * input_size * sizeof(bool));
  for (unsigned char i = 0; i < 128; i++) {
    find_antinodes_for_frequency(i, is_antinode);
  }

  // Count antinodes
  int answer = 0;
  for (int i = 0; i < input_size * input_size; i++) {
    answer += is_antinode[i];
  }
  printf("%d\n", answer);
}
