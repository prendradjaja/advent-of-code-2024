#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



typedef struct Robot {
  int px;
  int py;
  int vx;
  int vy;
} Robot;

void print_int(int n) {
  printf("%d\n", n);
}

char* consume(char* s, char* expected) {
  while (*expected != '\0') {
    assert(*s == *expected);
    s++;
    expected++;
  }
  return s;
}

char* consume_int(char* s, int* result) {
  int chars_consumed;
  sscanf(s, "%d%n", result, &chars_consumed);
  return s + chars_consumed;
}

void print_robot(Robot* r) {
  printf("%d\t%d\t/\t%d\t%d\n", r->px, r->py, r->vx, r->vy);
}

Robot* read_line(char* line) {
  int px, py, vx, vy, chars_consumed;

  line = consume(line, "p=");
  line = consume_int(line, &px);
  line = consume(line, ",");
  line = consume_int(line, &py);
  line = consume(line, " v=");
  line = consume_int(line, &vx);
  line = consume(line, ",");
  line = consume_int(line, &vy);

  Robot* result = malloc(sizeof(Robot));
  *result = (Robot) { px, py, vx, vy };
  return result;
}

Robot** read_input_file(FILE* file) {
  const int MAX_LINE_LENGTH = 100;
  const int MAX_ROBOTS = 1000;

  Robot** result = malloc((MAX_ROBOTS + 1) * sizeof(Robot*));

  char line[MAX_LINE_LENGTH];
  int i = 0;
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\r\n")] = '\0';

    result[i] = read_line(line);

    // for (int c = 0; line[c] != '\0'; c++) {
    //   unsigned char ch = line[c];
    // }

    i++;
  }
  result[i] = NULL;

  if (ferror(file)) {
    fprintf(stderr, "Error reading input file\n");
    exit(EXIT_FAILURE);
  }

  return result;
}

int modulo(int a, int b){
  return (a % b + b) % b;
}

void move(Robot* robot, int height, int width) {
  robot->px = modulo(robot->px + robot->vx, width);
  robot->py = modulo(robot->py + robot->vy, height);
}

int to_quadrant(int x, int y, int height, int width) {
  int mid_x = width / 2;
  int mid_y = height / 2;
  if        (x < mid_x && y < mid_y) {
    return 0;
  } else if (x > mid_x && y < mid_y) {
    return 1;
  } else if (x < mid_x && y > mid_y) {
    return 2;
  } else if (x > mid_x && y > mid_y) {
    return 3;
  } else {
    assert(x == mid_x || y == mid_y);
    return 4; // Not a quadrant
  }
}

int main(int argc, char** argv) {
  if (argc < 4) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a INPUT_FILE WIDTH HEIGHT\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Examples:\n");
    fprintf(stderr, " ./a ex 11 7\n");
    fprintf(stderr, " ./a in 101 103\n");
    exit(EXIT_FAILURE);
  }

  FILE *file = fopen(argv[1], "r");
  int width = atoi(argv[2]);
  int height = atoi(argv[3]);

  if (!file) {
    fprintf(stderr, "Could not open input file\n");
    exit(EXIT_FAILURE);
  }

  Robot** robots = read_input_file(file);
  int SIMULATION_LENGTH = 100;
  for (int i = 0; i < SIMULATION_LENGTH; i++) {
    /* printf("%d\n", i); */
    /* printf("    "); */
    /* print_robot(robots[10]); */
    for (int j = 0; robots[j] != NULL; j++) {
      move(robots[j], height, width);
    }
  }

  int quadrant_counts[5] = { 0 };

  for (int i = 0; robots[i] != NULL; i++) {
    Robot* r = robots[i];
    int quadrant = to_quadrant(r->px, r->py, height, width);
    quadrant_counts[quadrant]++;
  }

  int answer = 1;
  for (int i = 0; i < 4; i++) {
    answer *= quadrant_counts[i];
  }
  printf("%d\n", answer);
}
