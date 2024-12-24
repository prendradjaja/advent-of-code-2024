#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE = 2000;

void read_input_file(char* filename, int* arr1, int* arr2, int* size) {
  FILE *file = fopen(filename, "r");
  int elem1, elem2;
  int i = 0;
  while (fscanf(file, "%d %d", &elem1, &elem2) != EOF) {
    arr1[i] = elem1;
    arr2[i] = elem2;
    i++;
  }
  if (i > MAX_SIZE) {
    fprintf(stderr, "Input too long\n");
    exit(EXIT_FAILURE);
  }
  *size = i;
}

int count_occurrences(int n, int* arr, int size) {
  int result = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] == n) {
      result++;
    }
  }
  return result;
}

// TODO Maybe do the faster (linear time?) solution
int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a ex\n");
    fprintf(stderr, " ./a in\n");
    exit(EXIT_FAILURE);
  }
  int left[MAX_SIZE];
  int right[MAX_SIZE];
  int size;
  read_input_file(argv[1], left, right, &size);

  int answer = 0;
  for (int i = 0; i < size; i++) {
    int n = left[i];
    answer += n * count_occurrences(n, right, size);
  }
  printf("%d\n", answer);
}
