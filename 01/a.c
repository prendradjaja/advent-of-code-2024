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

int compare(const void* item1, const void* item2) {
  int n1 = *((int*) item1);
  int n2 = *((int*) item2);
  return n1 - n2;
}

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

  qsort(left, size, sizeof(int), compare);
  qsort(right, size, sizeof(int), compare);

  int answer = 0;
  for (int i = 0; i < size; i++) {
    answer += abs(left[i] - right[i]);
  }
  printf("%d\n", answer);
}
