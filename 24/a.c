#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>


const int NO_VALUE = -1;

typedef enum Operator {
  AND,
  OR,
  XOR
} Operator;

int wire_id_as_int(char* wire_id) {
  char a = wire_id[0];
  char b = wire_id[1];
  char c = wire_id[2];
  return 128 * 128 * a + 128 * b + c;
}

void read_initial_wire_values(FILE* file, int* wire_values) {
  const int MAX_LINE_LENGTH = 100000;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\r\n")] = '\0';

    if (line[0] == '\0') {
      return;
    }

    line[3] = '\0';
    int wire_id = wire_id_as_int(line);
    int wire_value = *(line + 5) - '0';
    wire_values[wire_id] = wire_value;
  }
}

void read_gates(FILE* file, char** lines, int* count_lines) {
  const int LINE_BUFFER_SIZE = 100;
  *count_lines = 0;
  while (true) {
    char* line = malloc(LINE_BUFFER_SIZE * sizeof(char));
    line = fgets(line, LINE_BUFFER_SIZE, file);
    if (line == NULL) {
      return;
    }
    line[strcspn(line, "\r\n")] = '\0';
    lines[*count_lines] = line;
    (*count_lines)++;
  }

  if (ferror(file)) {
    fprintf(stderr, "Error reading input file\n");
    exit(EXIT_FAILURE);
  }
}

char* consume(char* s, char* expected) {
  while (*expected != '\0') {
    assert(*s == *expected);
    s++;
    expected++;
  }
  return s;
}

char* consume_wire_id(char* s, int* result) {
  *result = wire_id_as_int(s);
  return s + 3;
}

// Return true if wire_values was changed
bool handle_line(char* line, int* wire_values) {
  // Parse
  int w1, w2, w3;
  Operator op;
  line = consume_wire_id(line, &w1);
  line = consume(line, " ");
  switch (line[0]) {
    case 'A':
      op = AND;
      line += 3;
      break;
    case 'O':
      op = OR;
      line += 2;
      break;
    case 'X':
      op = XOR;
      line += 3;
      break;
    default:
      fprintf(stderr, "Unexpected operator character\n");
      exit(EXIT_FAILURE);
  }
  line = consume(line, " ");
  line = consume_wire_id(line, &w2);
  line = consume(line, " -> ");
  line = consume_wire_id(line, &w3);

  // Process
  if (wire_values[w1] == NO_VALUE || wire_values[w2] == NO_VALUE || wire_values[w3] != NO_VALUE) {
    return false;
  }
  switch (op) {
    case AND:
      wire_values[w3] = wire_values[w1] && wire_values[w2];
      break;
    case OR:
      wire_values[w3] = wire_values[w1] || wire_values[w2];
      break;
    case XOR:
      wire_values[w3] = wire_values[w1] ^ wire_values[w2];
      break;
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


  // Parse
  int count_wire_values = 128 * 128 * 128;
  int wire_values[count_wire_values];
  for (int i = 0; i < count_wire_values; i++) {
    wire_values[i] = NO_VALUE;
  }
  read_initial_wire_values(file, wire_values);

  int MAX_GATE_COUNT = 1000;
  char** lines = malloc(MAX_GATE_COUNT * sizeof(char*));
  int gate_count;
  read_gates(file, lines, &gate_count);


  // Simulate
  bool changed;
  do {
    changed = false;
    for (int i = 0; i < gate_count; i++) {
      changed = changed || handle_line(lines[i], wire_values);
    }
  } while (changed);


  // Read answer
  uint64_t answer = 0;
  int i = 0;
  for (int i = 0; i < 100; i++) {
    int tens = i / 10;
    int ones = i % 10;
    char wire_id_str[4] = { 'z', tens + '0', ones + '0', '\0' };
    int wire_id = wire_id_as_int(wire_id_str);
    int wire_value = wire_values[wire_id];
    if (wire_value != NO_VALUE) {
      answer += (uint64_t) wire_value << i;
    }
  }
  printf("%" PRIu64 "\n", answer);
}
