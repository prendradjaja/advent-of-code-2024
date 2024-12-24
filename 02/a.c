#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int signum(int n) {
  if (n > 0) {
    return 1;
  } else if (n < 0) {
    return -1;
  } else {
    return 0;
  }
}

bool is_safe(char* line) {
  const int UNKNOWN_DIRECTION = 999;

  int deltas_all_ok = true;
  int directions_all_same = true;
  bool first = true;
  int prev;
  int direction = UNKNOWN_DIRECTION; // Is the array increasing (1), decreasing (-1), or unknown?

  // For each int `curr` in `line`
  int curr;
  int count_chars;
  while (sscanf(line, "%d%n", &curr, &count_chars) == 1) {
    if (!first) {
      if (direction == UNKNOWN_DIRECTION) {
        direction = signum(curr - prev);
      } else {
        if (signum(curr - prev) != direction) {
          directions_all_same = false;
        }
      }

      int delta = curr - prev;
      if (delta == 0 || delta > 3 || delta < -3) {
        deltas_all_ok = false;
      }
    }

    prev = curr;
    first = false;

    line += count_chars;
  }

  return (
    deltas_all_ok &&
    directions_all_same &&
    direction != 0
  );
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

  const int MAX_LINE_LENGTH = 100000;
  char line[MAX_LINE_LENGTH];
  int answer = 0;
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\r\n")] = '\0';
    answer += is_safe(line);
  }

  if (ferror(file)) {
    fprintf(stderr, "Error reading input file\n");
    exit(EXIT_FAILURE);
  }

  printf("%d\n", answer);
}
