#pragma once

typedef struct Grid {
  int height;
  int width;
  char *data;
} Grid;

char get_item(Grid grid, int r, int c);

void set_item(Grid grid, int r, int c, char value);

bool in_bounds(Grid grid, int r, int c);
