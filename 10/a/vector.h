#pragma once

typedef struct Vector {
  int r;
  int c;
} Vector;
typedef Vector Position;
typedef Vector PositionDelta;

Vector add(Vector v1, Vector v2);
