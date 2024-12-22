#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "grid.h"
#include "util.h"

char numeric_keypad_data[] = "789456123.0A";
Grid numeric_keypad = { 3, 4, numeric_keypad_data };

int main() {
  print_char(numeric_keypad_data[0]);
}
