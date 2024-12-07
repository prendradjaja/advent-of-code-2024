#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


const long END_OF_SUBARRAY = 0;
const long END_OF_INPUT = -1;

// The example input
const long INPUT[] = {
  190, 10, 19, END_OF_SUBARRAY,
  3267, 81, 40, 27, END_OF_SUBARRAY,
  83, 17, 5, END_OF_SUBARRAY,
  156, 15, 6, END_OF_SUBARRAY,
  7290, 6, 8, 6, 15, END_OF_SUBARRAY,
  161011, 16, 10, 13, END_OF_SUBARRAY,
  192, 17, 8, 14, END_OF_SUBARRAY,
  21037, 9, 7, 18, 13, END_OF_SUBARRAY,
  292, 11, 6, 16, 20, END_OF_SUBARRAY,
  END_OF_INPUT,
};


typedef struct SubarrayResult {
  long* next_subarray;
  bool is_solvable;
} SubarrayResult;


long* copy_reversed(long* null_terminated_array) {
  // Find size of array
  long* ptr1 = null_terminated_array;
  long size = 0;
  while (*ptr1 != END_OF_SUBARRAY) {
    size++;
    ptr1++;
  }

  // Reverse
  long* result = malloc((size + 1) * sizeof(long));
  long* ptr2 = result;
  ptr1--;
  for (long i = 0; i < size; i++) {
    *ptr2 = *ptr1;
    ptr2++;
    ptr1--;
  }
  *ptr2 = END_OF_SUBARRAY;
  return result;
}

bool ends_with(long n, long suffix) {
  int power_of_ten = 1;
  while (power_of_ten <= suffix) {
    power_of_ten *= 10;
  }
  return (n % power_of_ten) == suffix;
}

long unconcat(long n, long suffix) {
  int power_of_ten = 1;
  while (power_of_ten <= suffix) {
    power_of_ten *= 10;
  }
  return n / power_of_ten;
}

bool solvable(long total, long* null_terminated_array) {
  long* array = null_terminated_array;
  if (*(array + 1) == END_OF_SUBARRAY) {
    return *array == total;
  }

  bool solvable_with_mul;
  if (total % *array != 0) {
    solvable_with_mul = false;
  } else {
    // Recurse with *
    solvable_with_mul = solvable(total / *array, array + 1);
  }

  bool solvable_with_concat;
  if (!ends_with(total, *array)) {
    solvable_with_concat = false;
  } else {
    // Recurse with concatenation
    solvable_with_concat = solvable(unconcat(total, *array), array + 1);
  }

  return (
    // Recurse with +
    solvable(total - *array, array + 1)
    ||
    solvable_with_mul
    ||
    solvable_with_concat
  );
}

SubarrayResult consume_one_subarray(long* arr) {
  long total = *arr;
  arr++;

  long* subarray = arr;
  long* reversed = copy_reversed(subarray);
  bool is_solvable = solvable(total, reversed);

  while (*arr != END_OF_SUBARRAY) {
    arr++;
  }
  arr++;

  return (SubarrayResult) { arr, is_solvable };
}

int main() {
  long* ptr = INPUT;
  long answer = 0;
  while (*ptr != END_OF_INPUT) {
    long total = *ptr;
    SubarrayResult result = consume_one_subarray(ptr);
    ptr = result.next_subarray;
    answer += result.is_solvable * total;
  }
  printf("%ld\n", answer);
}
