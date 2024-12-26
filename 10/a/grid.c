#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "grid.h"

char get_item(Grid grid, int r, int c) {
  return grid.data[r * grid.width + c];
}

void set_item(Grid grid, int r, int c, char value) {
  grid.data[r * grid.width + c] = value;
}

bool in_bounds(Grid grid, int r, int c) {
  return (
    0 <= r && r < grid.height &&
    0 <= c && c < grid.width
  );
}
