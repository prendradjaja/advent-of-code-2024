#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

const int STATE_EXPECT_M = 10;
const int STATE_EXPECT_U = 20;
const int STATE_EXPECT_L = 30;
const int STATE_EXPECT_OPEN_PAREN = 40;
const int STATE_EXPECT_LEFT_OPERAND = 50;
const int STATE_EXPECT_COMMA = 60;
const int STATE_EXPECT_RIGHT_OPERAND = 70;
const int STATE_EXPECT_CLOSE_PAREN = 80;

typedef struct state {
  int kind;
  int left_operand;
  int right_operand;
} state;

const state INITIAL_STATE = { .kind = STATE_EXPECT_M, .left_operand = 0, .right_operand = 0 };
const state SECOND_STATE = { .kind = STATE_EXPECT_U, .left_operand = 0, .right_operand = 0 };

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

state advance_state(state current, int kind) {
  state result = current;
  result.kind = kind;
  return result;
}

int ctoi(int ch) {
  return ch - '0';
}

state next_state(state current, int ch, int* answer) {
  switch (current.kind) {
    case STATE_EXPECT_M:
      if (ch == 'm') {
        return advance_state(current, STATE_EXPECT_U);
      } else {
        return current;
      }
    case STATE_EXPECT_U:
      if (ch == 'u') {
        return advance_state(current, STATE_EXPECT_L);
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case STATE_EXPECT_L:
      if (ch == 'l') {
        return advance_state(current, STATE_EXPECT_OPEN_PAREN);
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case STATE_EXPECT_OPEN_PAREN:
      if (ch == '(') {
        return advance_state(current, STATE_EXPECT_LEFT_OPERAND);
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case STATE_EXPECT_LEFT_OPERAND:
      if (is_int(ch)) {
        state result = advance_state(current, STATE_EXPECT_COMMA);
        result.left_operand = ctoi(ch);
        return result;
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case STATE_EXPECT_COMMA:
      if (is_int(ch)) {
        state result = current;
        result.kind = STATE_EXPECT_COMMA;
        result.left_operand *= 10;
        result.left_operand += ctoi(ch);
        return result;
      } else if (ch == ',') {
        return advance_state(current, STATE_EXPECT_RIGHT_OPERAND);
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case STATE_EXPECT_RIGHT_OPERAND:
      if (is_int(ch)) {
        state result = advance_state(current, STATE_EXPECT_CLOSE_PAREN);
        result.right_operand = ctoi(ch);
        return result;
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case STATE_EXPECT_CLOSE_PAREN:
      if (is_int(ch)) {
        state result = current;
        result.kind = STATE_EXPECT_CLOSE_PAREN;
        result.right_operand *= 10;
        result.right_operand += ctoi(ch);
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
