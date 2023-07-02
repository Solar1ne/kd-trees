#include "point.h"
#include <string.h>
#include <stdlib.h>



void init_point(Point *point, char *x, char *y) {
  point->coord[0] = malloc(sizeof(char) * (strlen(x) + 1));
  strcpy(point->coord[0], x);

  point->coord[1] = malloc(sizeof(char) * (strlen(y) + 1));
  strcpy(point->coord[1], y);
}
void close_point(Point *point) {
  if (point == NULL)
    return;

  free(point->coord[0]);
  free(point->coord[1]);
}
bool equal_point(Point *point, char *x, char *y) {
  return strcmp(point->coord[0], x) == 0 && 
         strcmp(point->coord[1], y) == 0;
}
