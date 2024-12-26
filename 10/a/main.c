#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "grid.h"
#include "vector.h"


PositionDelta directions[] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
int count_directions = sizeof(directions) / sizeof(directions[0]);

Grid read_input_file(char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  int ch;
  char *data = malloc(10000 * sizeof(char));
  int width = 0;
  int size = 0;
  bool is_first_line = true;

  while ((ch = getc(file)) != EOF) {
    if (ch == '\n' || ch == '\r') {
      is_first_line = false;
      continue;
    }

    if (is_first_line) {
      width++;
    }

    data[size] = ch;
    size++;
  }

  if (ferror(file)) {
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  assert(width * width == size);

  return (Grid) { width, width, data };
}

void _count_reachable_summits(Grid topo_map, Position position, Grid *results) {
  if (get_item(topo_map, position.r, position.c) == '9') {
    set_item(*results, position.r, position.c, true);
    return;
  }

  char elevation = get_item(topo_map, position.r, position.c);
  int result = 0;
  for (int i = 0; i < count_directions; i++) {
    PositionDelta direction = directions[i];
    Position neighbor = add(position, direction);
    if (
      in_bounds(topo_map, neighbor.r, neighbor.c) &&
      get_item(topo_map, neighbor.r, neighbor.c) == elevation + 1
    ) {
      _count_reachable_summits(topo_map, neighbor, results);
    }
  }
}

int count_reachable_summits(Grid topo_map, Position position) {
  char data[topo_map.height * topo_map.width];
  for (int i = 0; i < sizeof(data); i++) {
    data[i] = false;
  }
  Grid results = { topo_map.height, topo_map.width, data };

  _count_reachable_summits(topo_map, position, &results);

  int total = 0;
  for (int i = 0; i < sizeof(data); i++) {
    total += data[i];
  }
  return total;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, " ./a ex\n");
    fprintf(stderr, " ./a in\n");
    exit(EXIT_FAILURE);
  }
  Grid topo_map = read_input_file(argv[1]);

  // Find trailheads
  Position trailheads[topo_map.width * topo_map.height];
  int count_trailheads = 0;
  for (int r = 0; r < topo_map.height; r++) {
    for (int c = 0; c < topo_map.width; c++) {
      if (get_item(topo_map, r, c) == '0') {
        trailheads[count_trailheads] = (Position) { r, c };
        count_trailheads++;
      }
    }
  }

  // Count reachable summits
  int answer = 0;
  for (int i = 0; i < count_trailheads; i++) {
    Position trailhead = trailheads[i];
    answer += count_reachable_summits(topo_map, trailhead);
  }
  printf("%d\n", answer);
}
