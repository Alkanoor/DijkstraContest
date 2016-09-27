#include "path.h"
#include <stdio.h>

void concat_path(int* points, int pointsNb) {
  DIRECTION dir, curDir;
  int curX, curY, i;
  i = 0;
  curX = points[2 * i];
  curY = points[2 * i + 1];
  curDir = IMMOBILE;
  i++;
  while (i < pointsNb) {
    dir = ((points[2 * i + 1] - curY) * 4 + (points[2 * i] - curX) + 5);
    if (dir != curDir) {
      curDir = dir;
      printf("%i %i ", curX, curY);
    }
    curY = points[2 * i + 1];
    curX = points[2 * i];
    i++;
  }
  printf("%i %i\n", curX, curY);
}
