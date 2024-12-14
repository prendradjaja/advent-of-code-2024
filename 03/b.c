#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

char* DO = "do()";
char* DONT = "don't()";

const int DO_LENGTH = 4;
const int DONT_LENGTH = 7;

bool is_substring_match(char* haystack, char* needle, int index) {
  if (index < 0) {
    return false;
  }
  int i = 0;
  while (needle[i] != '\0') {
    if (haystack[index + i] != needle[i]) {
      return false;
    }
    i++;
  }
  return true;
}

bool is_do(char* haystack, int end_index) {
  return is_substring_match(haystack, DO, end_index - (DO_LENGTH - 1));
}

bool is_dont(char* haystack, int end_index) {
  return is_substring_match(haystack, DONT, end_index - (DONT_LENGTH - 1));
}

// In production code, this function would be dangerous (allows buffer overflow attacks), needs a
// max length argument.
void read_input_file(char* buffer, char* filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Could not open input file\n");
    exit(EXIT_FAILURE);
  }

  char ch;
  int i = 0;
  while ((ch = getc(file)) != EOF) {
    buffer[i] = ch;
    i++;
  }
  buffer[i] = '\0';

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

State next_state(State current, int ch, int* answer, bool mul_enabled) {
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
        if (mul_enabled) {
          *answer += current.left_operand * current.right_operand;
        }
        return INITIAL_STATE;
      } else {
        return INITIAL_STATE;
      }
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a ex\n");
    fprintf(stderr, " ./a in\n");
    exit(EXIT_FAILURE);
  }

  char* filename = argv[1];

  char* input = malloc(50000 * sizeof(char));
  read_input_file(input, filename);

  FILE *file = fopen(filename, "r");
  State state = INITIAL_STATE;
  int ch;
  int answer = 0;
  int i = 0;
  bool mul_enabled = true;
  while ((ch = getc(file)) != EOF) {
    state = next_state(state, ch, &answer, mul_enabled);
    if (is_do(input, i)) {
      mul_enabled = true;
    } else if (is_dont(input, i)) {
      mul_enabled = false;
    }
    i++;
  }
  printf("%d\n", answer);
  fclose(file);
}
