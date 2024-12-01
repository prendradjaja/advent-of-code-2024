#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE = 2000;

void read_input_file(int* arr1, int* arr2, int* size) {
  FILE *file = fopen("in", "r");
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

// selection_sort implemented by generative AI -- TODO Implement it myself
void selection_sort(int* arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    // Find the index of the smallest element in the remaining array
    int min_index = i;
    for (int j = i + 1; j < size; j++) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }

    // Swap the smallest element with the first unsorted element
    if (min_index != i) {
      int temp = arr[i];
      arr[i] = arr[min_index];
      arr[min_index] = temp;
    }
  }
}

int main() {
  int left[MAX_SIZE];
  int right[MAX_SIZE];
  int size;
  read_input_file(left, right, &size);

  selection_sort(left, size);
  selection_sort(right, size);

  int answer = 0;
  for (int i = 0; i < size; i++) {
    answer += abs(left[i] - right[i]);
  }
  printf("%d\n", answer);
}
