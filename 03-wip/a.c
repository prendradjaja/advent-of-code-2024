#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

typedef struct state {
  int kind; // Should be one of EXPECT_*
  int left_operand;
  int right_operand;
} state;

const int EXPECT_M = 10;
const int EXPECT_U = 20;
const int EXPECT_L = 30;
const int EXPECT_OPEN_PAREN = 40;
const int EXPECT_LEFT_OPERAND = 50;
const int EXPECT_COMMA = 60;
const int EXPECT_RIGHT_OPERAND = 70;
const int EXPECT_CLOSE_PAREN = 80;

const state INITIAL_STATE = { .kind = EXPECT_M, .left_operand = 0, .right_operand = 0 };
const state SECOND_STATE = { .kind = EXPECT_U, .left_operand = 0, .right_operand = 0 };

state next_state(state current, int ch, int* answer);

int main() {
  FILE *file = fopen("in", "r");
  state my_state = INITIAL_STATE;
  int ch;
  int answer = 0;
  while ((ch = getc(file)) != EOF) {
    my_state = next_state(my_state, ch, &answer);
  }
  printf("%d\n", answer);
}

state advance_state(state current, int kind) {
  state result = current;
  result.kind = kind;
  return result;
}

int char_to_int(int ch) {
  return ch - '0';
}

state next_state(state current, int ch, int* answer) {
  switch (current.kind) {
    case EXPECT_M:
      if (ch == 'm') {
        return advance_state(current, EXPECT_U);
      } else {
        return current;
      }
    case EXPECT_U:
      if (ch == 'u') {
        return advance_state(current, EXPECT_L);
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case EXPECT_L:
      if (ch == 'l') {
        return advance_state(current, EXPECT_OPEN_PAREN);
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case EXPECT_OPEN_PAREN:
      if (ch == '(') {
        return advance_state(current, EXPECT_LEFT_OPERAND);
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case EXPECT_LEFT_OPERAND:
      if (isdigit(ch)) {
        state result = advance_state(current, EXPECT_COMMA);
        result.left_operand = char_to_int(ch);
        return result;
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case EXPECT_COMMA:
      if (isdigit(ch)) {
        state result = current;
        result.kind = EXPECT_COMMA;
        result.left_operand *= 10;
        result.left_operand += char_to_int(ch);
        return result;
      } else if (ch == ',') {
        return advance_state(current, EXPECT_RIGHT_OPERAND);
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case EXPECT_RIGHT_OPERAND:
      if (isdigit(ch)) {
        state result = advance_state(current, EXPECT_CLOSE_PAREN);
        result.right_operand = char_to_int(ch);
        return result;
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case EXPECT_CLOSE_PAREN:
      if (isdigit(ch)) {
        state result = current;
        result.kind = EXPECT_CLOSE_PAREN;
        result.right_operand *= 10;
        result.right_operand += char_to_int(ch);
        return result;
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else if (ch == ')') {
        *answer += current.left_operand * current.right_operand;
        return INITIAL_STATE;
      } else {
        return INITIAL_STATE;
      }
    default:
      fprintf(stderr, "Invalid input to next_state()\n");
      exit(EXIT_FAILURE);
  }
}
