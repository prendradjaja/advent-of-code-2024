#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* fprintf(stderr, "Input too long\n"); */
/* exit(EXIT_FAILURE); */

const int STATE_EXPECT_M = 10;
const int STATE_EXPECT_U = 20;
const int STATE_EXPECT_L = 30;
const int STATE_EXPECT_OPEN_PAREN = 40;
const int STATE_EXPECT_LEFT_OPERAND = 50;
const int STATE_EXPECT_COMMA = 60;
const int STATE_EXPECT_RIGHT_OPERAND = 70;
const int STATE_EXPECT_CLOSE_PAREN = 80;

void print_int(int n) {
  printf("%d\n", n);
}

int is_int(int ch) {
  switch (ch) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return TRUE;
    default:
      return FALSE;
  }
}

int next_state(int current, int ch) {
  switch (current) {
    case STATE_EXPECT_M:
      if (ch == 'm') {
        return STATE_EXPECT_U;
      } else {
        return current;
      }
    case STATE_EXPECT_U:
      if (ch == 'u') {
        return STATE_EXPECT_L;
      } else if (ch == 'm') {
        return STATE_EXPECT_U;
      } else {
        return STATE_EXPECT_M;
      }
    case STATE_EXPECT_L:
      if (ch == 'l') {
        return STATE_EXPECT_OPEN_PAREN;
      } else if (ch == 'm') {
        return STATE_EXPECT_U;
      } else {
        return STATE_EXPECT_M;
      }
    case STATE_EXPECT_OPEN_PAREN:
      if (ch == '(') {
        return STATE_EXPECT_LEFT_OPERAND;
      } else if (ch == 'm') {
        return STATE_EXPECT_U;
      } else {
        return STATE_EXPECT_M;
      }
    case STATE_EXPECT_LEFT_OPERAND:
      if (is_int(ch)) {
        return STATE_EXPECT_COMMA;
      } else if (ch == 'm') {
        return STATE_EXPECT_U;
      } else {
        return STATE_EXPECT_M;
      }
    case STATE_EXPECT_COMMA:
      if (is_int(ch)) {
        return STATE_EXPECT_COMMA;
      } else if (ch == ',') {
        return STATE_EXPECT_RIGHT_OPERAND;
      } else if (ch == 'm') {
        return STATE_EXPECT_U;
      } else {
        return STATE_EXPECT_M;
      }
    case STATE_EXPECT_RIGHT_OPERAND:
      if (is_int(ch)) {
        return STATE_EXPECT_CLOSE_PAREN;
      } else if (ch == 'm') {
        return STATE_EXPECT_U;
      } else {
        return STATE_EXPECT_M;
      }
    case STATE_EXPECT_CLOSE_PAREN:
      if (is_int(ch)) {
        return STATE_EXPECT_CLOSE_PAREN;
      } else if (ch == 'm') {
        return STATE_EXPECT_U;
      } else if (ch == ')') {
        print_int(99999);
        return STATE_EXPECT_M;
      } else {
        return STATE_EXPECT_M;
      }
    default:
      fprintf(stderr, "Invalid input to next_state()\n");
      exit(EXIT_FAILURE);
  }
}

// CONTINUE_HERE:
// - Collect the operands along the way (so that I can then use them)

int main() {
  FILE *file = fopen("ex", "r");
  int state = STATE_EXPECT_M;
  int ch;
  while ((ch = getc(file)) != EOF) {
    state = next_state(state, ch);
  }

  /* int answer = 0; */
  /* printf("%d\n", answer); */
}
