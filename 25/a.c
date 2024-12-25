#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct Schematic {
  bool is_lock;
  int heights[5];
} Schematic;


// Reads one schematic from FILE into RESULT. Returns a bool indicating whether or not there is at
// least one more schematic left to read next.
bool read_one_schematic(FILE* file, Schematic* result) {
  const int MAX_LINE_LENGTH = 10;

  char line[MAX_LINE_LENGTH];
  char body[5][MAX_LINE_LENGTH];
  bool is_lock;
  bool has_next;

  // Read the schematic
  fgets(line, MAX_LINE_LENGTH, file);
  is_lock = line[0] == '#';
  for (int r = 0; r < 5; r++) {
    fgets(body[r], MAX_LINE_LENGTH, file);
  }
  fgets(line, MAX_LINE_LENGTH, file);

  // Check if there is a next schematic. (This might be harder to implement if the input file is
  // allowed to have an extra blank line at the end!)
  has_next = fgets(line, MAX_LINE_LENGTH, file) != NULL;

  // Determine the heights
  *result = (Schematic) { is_lock, { 0 } };
  for (int c = 0; c < 5; c++) {
    for (int r = 0; r < 5; r++) {
      if (body[r][c] == '#') {
        result->heights[c]++;
      }
    }
  }

  return has_next;
}

bool can_fit(Schematic lock, Schematic key) {
  for (int i = 0; i < 5; i++) {
    if (lock.heights[i] + key.heights[i] > 5) {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a ex\n");
    fprintf(stderr, " ./a in\n");
    exit(EXIT_FAILURE);
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
    fprintf(stderr, "Could not open input file\n");
    exit(EXIT_FAILURE);
  }

  Schematic locks[1000];
  Schematic keys[1000];
  int count_locks = 0;
  int count_keys = 0;

  bool has_next = true;
  while (has_next) {
    Schematic schematic;
    has_next = read_one_schematic(file, &schematic);
    if (schematic.is_lock) {
      locks[count_locks] = schematic;
      count_locks++;
    } else {
      keys[count_keys] = schematic;
      count_keys++;
    }
  }

  int answer = 0;
  for (int i = 0; i < count_locks; i++) {
    for (int j = 0; j < count_keys; j++) {
      answer += can_fit(locks[i], keys[j]);
    }
  }
  printf("%d\n", answer);
}
