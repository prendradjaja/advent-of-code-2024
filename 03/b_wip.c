#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

// Find up to MAX occurrences of string NEEDLE in HAYSTACK. Return a (-1)-terminated array of string
// indices.
int* find_occurrences(char* haystack, char* needle, int max) {
  char* start = haystack;
  int* result = malloc((max + 1) * sizeof(int*));
  int* result_start = result;
  char* ptr;
  while ((ptr = strstr(haystack, needle))) {
    *result = ptr - start;
    result++;
    haystack = ptr + 1;
  }
  *result = -1;
  return result_start;
}

char* input = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
char* filename = "ex";

int main(int argc, char** argv) {
  /* if (argc < 2) { */
  /*   fprintf(stderr, "Usage:\n"); */
  /*   fprintf(stderr, " ./a ex\n"); */
  /*   fprintf(stderr, " ./a in\n"); */
  /*   exit(EXIT_FAILURE); */
  /* } */

  int* do_indices = find_occurrences(input, "do()", 50);
  int* dont_indices = find_occurrences(input, "don't()", 50);

  // CONTINUE HERE:
  // - Check whether do_indices[0] or dont_indices[0] is larger (i.e. do we start with a dont or a
  // do)
  //   - Answer: For both example and puzzle input, we start with a dont. That makes sense, since
  //   the prompt says we start 'on'
  // - Merge do_indices and dont_indices into one array (see Discord)
  // - Sort it

  FILE *file = fopen(filename, "r");
  State state = INITIAL_STATE;
  int ch;
  int answer = 0;
  int i = 0;
  while ((ch = getc(file)) != EOF) {
    state = next_state(state, ch, &answer);
    /* printf("%d %c\n", i, ch); */
    i++;
  }
  printf("%d\n", answer);
  fclose(file);
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
  }
}
