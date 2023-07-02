#include "node.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define YELLOW "\033[1;33m"
#define RESET  "\033[0m"


Node* init_node(char *x, char *y) {
  Node *n   = malloc(sizeof(Node));
  init_point(&n->point, x, y);
  n->info.start = NULL;
  n->parent = NULL;
  n->left   = NULL;
  n->right  = NULL;

  return n;
}
void close_node(Node *node) {
  if (node == NULL)
    return;

  close_point(&node->point);
  delete_list(&node->info);
  free(node);
}
void push_info_node(Node *node, char *info) {
  add_element(&node->info, info);
}
void print_node(Node *node, int deep) {
  if (node == NULL) {
    printf("NULL\n");
    return;
  }

  if (deep % 2 == 0)
    printf("(%s%s%s; %s)\n", YELLOW, node->point.coord[0], RESET, node->point.coord[1]);
  else
    printf("(%s; %s%s%s)\n", node->point.coord[0], YELLOW, node->point.coord[1], RESET);
}
void like_tree_display(Node *root, int deep) {
  if (root == NULL)
    return;
  
  like_tree_display(root->right, deep + 1);

  for (int i = 0; i < deep; ++i)
    printf(" ~~~ ");
  print_node(root, deep);

  like_tree_display(root->left, deep + 1);
}
void swap(Node *left, Node *right) {
  Node buf;

  buf.point = left->point;
  left->point  = right->point;
  right->point = buf.point;

  buf.info.start    = left->info.start;
  left->info.start  = right->info.start;
  right->info.start = buf.info.start;
}
bool equal_node(Node *node, char *x, char *y) {
  return equal_point(&node->point, x, y);
}
void inorder(Node *node) {
  if (node == NULL) {
    return;
  }

  inorder(node->left);

  print_node(node, 0);
  display_list(&node->info);

  inorder(node->right);
}
int delete_node(Node **root, char *x, char *y, int release) {
  Node *node = search_node(*root, x, y);
  if (node == NULL)
    return NOT_FOUND;

  if (delete_by_release(&node->info, release) == 1)
    return NOT_FOUND;

  if (node->info.start != NULL)
    return MORE_INFO;

  if (node->left != NULL && node->right != NULL) {
    Node *min_node = node->right;
    while (min_node->left != NULL) {
      min_node = min_node->left;
    }
    
    // swap content
    swap(node, min_node);

    Node buf;

    buf.parent = node->parent;
    buf.left   = node->left;
    buf.right  = node->right;
    
    if (min_node->right != NULL) {
      min_node->right->parent = node;
      node->right             = min_node->right;
    }

    //node = min_node;
  }
  
  Node *child = NULL; // ребенок для родителя (отн. удаляемого)
  if (node->left != NULL) {
    child = node->left;
  } else {
    child = node->right;
  }

  if (node->parent == NULL) { // это есть корень
    // поменять значение в tree root
    *root = child;
  } else {
    if (node->parent->left == node) {  // node == root)
      node->parent->left = child; // пересвязываем ребенка к родителю
    } else {
      node->parent->right = child; // пересвязываем ребенка к родителю
    }
  }

  if (child != NULL) {
    child->parent = node->parent;
  }
   
  close_node(node);

  return SUCCESS;
}
Node* search_node(Node *root, char *x, char *y) {
  int deep = 0;
  char *current = x;
  while (root != NULL) {
    int res = strcmp(root->point.coord[deep], current);
    if (res == 0) {
      if (equal_node(root, x, y)) {
        return root; // FOUND
      }
    }

    if (res > 0)
      root = root->left;
    else
      root = root->right;

    deep = (deep + 1) % 2;
    if (deep == 0)
      current = x;
    else
      current = y;
  }


  return NULL;
}
