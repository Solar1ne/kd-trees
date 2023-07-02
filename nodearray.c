#include "node.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




Array init_array(int size) {
  Array array;
  array.filled = 0;
  array.size   = size;
  array.array  = calloc(sizeof(Node*), size);
  return array;
}
void close_array(Array *array) {
  if (array == NULL)
    return;

  for (int i = 0; i < array->filled; ++i)
    close_node(array->array[i]);

  free(array->array);
}
int binary_find(Array *array, char *find_key) {
  int left  = 0;
  int right = array->filled - 1;
  int middle;

  while (right >= left) {
    middle = (left + right) / 2;
//    if (array->array[middle]->point.coord[0] > find_key)
    if (strcmp(array->array[middle]->point.coord[0], find_key) > 0)
      right = middle - 1;
    else
      left = middle + 1;
  }

  return right + 1;
}
int find_median(Node **array, int left, int right, int deep) {
  printf("MEDIANA:\nLEFT: %d\nRIGHT: %d\n", left, right);
  if (left == right)
    return -1;

  if (left > right)
    return -1;

  if (right == left + 1)
    return left; 

  int middle = (left + right) / 2;
  while (1) {
    char *pivot = array[middle]->point.coord[deep];

    swap(array[middle], array[right - 1]);

    int store = left;
    int p     = left;
    while (p < right) {
      if (strcmp(array[p]->point.coord[deep], pivot) < 0) {
        if (p != store)
          swap(array[p], array[store]);
        store++;
      }
      p++;
    }
    swap(array[store], array[right - 1]);
    
    if (strcmp(array[store]->point.coord[deep], array[middle]->point.coord[deep]) == 0)
      return middle;

    if (store > middle)
      right = store;
    else
      left  = store;
  }
}
Node* rec_build_tree(Node **array, int left, int right, int deep) {
  if (left > right)
    return NULL;

  int pos = find_median(array, left, right, deep); // не удалось найти медиану
  if (pos == -1) 
    return NULL;

  printf("POS = %d\n", pos);
  Node *n = array[pos];

  n->left   = NULL; // В случае повторного вызова построения
  n->right  = NULL;
  n->parent = NULL;

  deep = (deep + 1) % 2;

  n->left  = rec_build_tree(array, left, pos, deep);
  if (n->left != NULL) // Если расмотреть дерево, которое построено на четном кол-ве эл-ов, не избежать провисания
                       //
                       //       (parent)
                       //          2 
                       // left-> 1   NULL <-right
                       //
                       // Так что, проверка имеет место быть, ведь важно настроить связь '1' с '2'
    n->left->parent = n;

  n->right = rec_build_tree(array, pos + 1, right, deep);
  if (n->right != NULL)
    n->right->parent = n;

  return n;
}
Node* build_tree(Array *array) {
  // Относительно готового массива формируем связь дерева
  return rec_build_tree(array->array, 0, array->filled, 0);
}
int find_pos(Array *array, char *x, char *y) {
  for (int i = 0; i < array->filled; ++i)
    if (equal_node(array->array[i], x, y))
      return i;

  return -1;
}
Node* insert_array(Array *array, char *x, char *y) {
/*  int pos_insert = binary_find(array, x);
  
  if (pos_insert > 0 && equal_node(array->array[pos_insert - 1], x, y)) {
    return array->array[pos_insert - 1];
  }
  */
  
  //shift_right(array, pos_insert);
//  int pos_insert = table->filled;
  int pos = find_pos(array, x, y);
  if (pos == -1) {
    array->array[array->filled] = init_node(x, y);
    pos = array->filled;
    ++array->filled;

    if (array->filled == array->size) { // увеличение массива, если не хватит место
      array->size  *= 2;
      array->array = realloc(array->array, sizeof(Node*) * array->size);
    }
  }

  return array->array[pos];
}
void shift_left(Array *array, int pos) {
  if (pos >= array->filled)
    return;

  for (int i = pos; i < array->filled - 1; ++i) {
//    array->array[i] = array->array[i + 1];
    
  }

  array->filled -= 1;
}
void shift_right(Array *array, int pos) {
  if (array->filled == array->size) { // увеличение массива, если не хватит место
    array->size  *= 2;
    array->array = realloc(array->array, sizeof(Node*) * array->size);
  }

  for (int i = array->filled; i > pos; --i)
    array->array[i] = array->array[i - 1];
}

