#ifndef NODE_H
#define NODE_H

#include "point.h"
#include "list.h"

enum { // 
  SUCCESS, 
  EMPTY,
  NOT_FOUND,
  MORE_INFO
};

typedef struct Node Node;
struct Node {
  Point point;
  List info;
  Node  *parent;
  Node  *left;
  Node  *right;
};

typedef struct Array Array;
struct Array {
  int filled;
  int size;
  Node **array; // массив
};


// TREE PART
Node* init_node(char *x, char *y);
void close_node(Node *node);
void push_info_node(Node *node, char *info);
void inorder(Node *node);

int delete_node(Node **node, char *x, char *y, int release);
Node* search_node(Node *root, char *x, char *y);
void like_tree_display(Node *root, int deep);
void swap(Node *left, Node *right);
void print_node(Node *node, int deep);
bool equal_node(Node *node, char *x, char *y);

// ARRAY PART
Array init_array(int size);
void  close_array(Array *array);

Node* build_tree(Array *array);
Node* insert_array(Array *array, char *x, char *y);
int find_pos(Array *array, char *x, char *y);

// display && search <- ни в коем случае не делать для массива (нарушает принцип)

void  shift_left(Array *array, int pos);
void shift_right(Array *array, int pos);

#endif // NODE_H
