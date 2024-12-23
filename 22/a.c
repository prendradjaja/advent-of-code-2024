#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


const unsigned long MODULUS = 16777216;
const int MAX_LINE_LENGTH = 100000;


unsigned long next_secret(unsigned long secret) {
  secret = (secret ^ (secret * 64)) % MODULUS;
  secret = (secret ^ (secret / 32)) % MODULUS;
  secret = (secret ^ (secret * 2048)) % MODULUS;
  return secret;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a ex\n");
    fprintf(stderr, " ./a in\n");
    exit(EXIT_FAILURE);
  }

  char* filename = argv[1];
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Could not open input file\n");
    exit(EXIT_FAILURE);
  }

  unsigned long answer = 0;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\r\n")] = '\0';

    unsigned long secret;
    sscanf(line, "%lu", &secret);

    for (int i = 0; i < 2000; i++) {
      secret = next_secret(secret);
    }
    answer += secret;
  }

  if (ferror(file)) {
    fprintf(stderr, "Error reading input file\n");
    exit(EXIT_FAILURE);
  }

  printf("%lu\n", answer);
}
