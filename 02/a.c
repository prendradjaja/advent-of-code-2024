#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0


typedef struct SubarrayResult {
  int* arr;
  int is_safe;
} SubarrayResult;

// The example input (modified)
const int input[] = {
  7, 6, 4, 2, 1, 0, // Add a 0 to the end of each row
  1, 2, 7, 8, 9, 0,
  9, 7, 6, 2, 1, 0,
  1, 3, 2, 4, 5, 0,
  8, 6, 4, 4, 1, 0,
  1, 3, 6, 7, 9, 0,
  -1, // Add a -1 to the end of the input
};


SubarrayResult consume_one_subarray(int* arr);

int main() {
  int* arr = input;
  int answer = 0;
  while (*arr != -1) {
    SubarrayResult result = consume_one_subarray(arr);
    arr = result.arr;
    answer += result.is_safe;
  }
  printf("%d\n", answer);
}


int signum(int n) {
  if (n > 0) {
    return 1;
  } else if (n < 0) {
    return -1;
  } else {
    return 0;
  }
}

SubarrayResult consume_one_subarray(int* arr) {
  const int UNKNOWN_DIRECTION = 999;

  int deltas_all_ok = TRUE;
  int directions_all_same = TRUE;
  int first = TRUE;
  int prev = 0;
  int direction = UNKNOWN_DIRECTION; // Is the array increasing (1), decreasing (-1), or unknown (UNKNOWN_DIRECTION)?

  while (*arr != 0) {
    int curr = *arr;

    if (!first) {
      if (direction == UNKNOWN_DIRECTION) {
        direction = signum(curr - prev);
      } else {
        if (signum(curr - prev) != direction) {
          directions_all_same = FALSE;
        }
      }

      int delta = curr - prev;
      if (delta == 0 || delta > 3 || delta < -3) {
        deltas_all_ok = FALSE;
      }
    }

    prev = curr;
    first = FALSE;
    arr++;
  }

  arr++;

  int is_safe = (
    deltas_all_ok &&
    directions_all_same &&
    direction != 0
  );

  return (SubarrayResult) { .arr = arr, .is_safe = is_safe };
}
