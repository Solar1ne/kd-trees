#ifndef POINT_H
#define POINT_H

#include <stdbool.h>

typedef struct Point Point;
struct Point {
  char *coord[2];
};

void init_point(Point *point, char *x, char *y);
void close_point(Point *point);
bool equal_point(Point *point, char *x, char *y);

#endif // POINT_H
