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

bool _is_safe(int* report, int count_levels, int skip_index);

bool is_safe(char* line) {
  // Parse
  int report[100];
  int count_levels = 0;
  int n;
  int count_chars;
  while (sscanf(line, "%d%n", &n, &count_chars) == 1) {
    report[count_levels] = n;
    count_levels++;
    line += count_chars;
  }

  // Check safety without the Problem Dampener
  if (_is_safe(report, count_levels, -1)) {
    return true;
  }

  // Check safety with the Problem Dampener
  for (int skip_index = 0; skip_index < count_levels; skip_index++) {
    if (_is_safe(report, count_levels, skip_index)) {
      return true;
    }
  }
  return false;
}

bool _is_safe(
  int* report,
  int count_levels,
  int skip_index // Use -1 to check for safety without removing any level
) {
  const int UNKNOWN_DIRECTION = 999;

  int deltas_all_ok = true;
  int directions_all_same = true;
  bool first = true;
  int prev;
  int direction = UNKNOWN_DIRECTION; // Is the array increasing (1), decreasing (-1), or unknown?

  int i = skip_index != 0 ? 0 : 1;
  while (i < count_levels) {
    int curr = report[i];
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
    if (i + 1 != skip_index) {
      i++;
    } else {
      i += 2;
    }
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
