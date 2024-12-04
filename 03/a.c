#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

typedef enum {
  EXPECT_M,
  EXPECT_U,
  EXPECT_L,
  EXPECT_OPEN_PAREN,
  EXPECT_LEFT_OPERAND,
  EXPECT_COMMA,
  EXPECT_RIGHT_OPERAND,
  EXPECT_CLOSE_PAREN
} StateType;

typedef struct State {
  StateType type;
  int left_operand;
  int right_operand;
} State;

const State INITIAL_STATE = { .type = EXPECT_M, .left_operand = 0, .right_operand = 0 };
const State SECOND_STATE = { .type = EXPECT_U, .left_operand = 0, .right_operand = 0 };

State next_state(State current, int ch, int* answer);

int main() {
  FILE *file = fopen("in", "r");
  State state = INITIAL_STATE;
  int ch;
  int answer = 0;
  while ((ch = getc(file)) != EOF) {
    state = next_state(state, ch, &answer);
  }
  printf("%d\n", answer);
}

State advance_state(State current, int type) {
  State result = current;
  result.type = type;
  return result;
}

int char_to_int(int ch) {
  return ch - '0';
}

State next_state(State current, int ch, int* answer) {
  switch (current.type) {
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
        State result = advance_state(current, EXPECT_COMMA);
        result.left_operand = char_to_int(ch);
        return result;
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case EXPECT_COMMA:
      if (isdigit(ch)) {
        State result = current;
        result.type = EXPECT_COMMA;
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
        State result = advance_state(current, EXPECT_CLOSE_PAREN);
        result.right_operand = char_to_int(ch);
        return result;
      } else if (ch == 'm') {
        return SECOND_STATE;
      } else {
        return INITIAL_STATE;
      }
    case EXPECT_CLOSE_PAREN:
      if (isdigit(ch)) {
        State result = current;
        result.type = EXPECT_CLOSE_PAREN;
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
