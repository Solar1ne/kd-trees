#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "handle.h"




void init_tree(Tree *tree) {
  tree->root  = NULL;
  tree->needRebuild = false;
  tree->array = init_array(10);
}
void close_tree(Tree *tree) {
  if (tree == NULL)
    return;

  close_array(&tree->array);
}
int load_file(Tree *tree) {
  printf("Filename: ");
  char *filename = scanf_str();
  FILE *file = fopen(filename, "r");
  free(filename);

  if (file == NULL)
    return EMPTY;

  char x[128], y[128], info[128];
  while (!feof(file)) {
//    int x, y;
    if (fscanf(file, "%s", x) != 1)
      break;

    if (fscanf(file, "%s", y) != 1)
      break;

    if (fscanf(file, "%s", info) != 1)
      break;
    
    Node *node = insert_array(&tree->array, x, y);
    push_info_node(node, info);
  }

  fclose(file);

  build_tree(&tree->array);
  return SUCCESS;
}
int insert_tree(Tree *tree) {
  printf("X: ");
  char *x = scanf_str();

  printf("Y: ");
  char *y = scanf_str();

  printf("Info: ");
  char *info = scanf_str();

  Node *node = insert_array(&tree->array, x, y);
  push_info_node(node, info);

  free(x);
  free(y);
  free(info);

  return SUCCESS; 
}
int remove_tree(Tree *tree) {
  printf("X: ");
  char *x = scanf_str();

  printf("Y: ");
  char *y = scanf_str();

  int release = 0;
  printf("Release: ");
  scanf_int(&release);

  int pos = find_pos(&tree->array, x, y);
  int status = NOT_FOUND;

  for (int i = 0; i < tree->array.filled; ++i) {
    printf("*****************************\n");
    printf("[%d] = \n", i + 1);

    /*
    printf("PARENT:"); 
    print_node(tree.array.array[i]->parent, 0);

    printf("RIGHT:"); 
    print_node(tree.array.array[i]->right, 0);
    */

    print_node(tree->array.array[i], 0);

 /*   printf("LEFT:");
    print_node(tree.array.array[i]->left, 0);
    printf("*****************************\n");
    */
  }
  if (pos != -1) {
    status = delete_node(&tree->root, x, y, release);

    if (status == SUCCESS)
      shift_left(&tree->array, pos);
  }

  free(x);
  free(y);
 
  return status;
}
int search_tree(Tree *tree) {
  printf("X: ");
  char *x = scanf_str();

  printf("Y: ");
  char *y = scanf_str();
  
  Node *node = search_node(tree->root, x, y);
  int status;
  if (node == NULL) {
    status = NOT_FOUND;
  }
  else {
    display_list(&node->info);
    status = SUCCESS;
  }

  free(x);
  free(y);

  return status;
}
int display_tree(Tree *tree) {
  if (tree->array.filled == 0)
    return EMPTY;

  tree->root = build_tree(&tree->array);
  like_tree_display(tree->root, 0);

  return SUCCESS;
}
int travel_tree(Tree *tree) {
  if (tree->array.filled == 0)
    return EMPTY;

  inorder(tree->root);
  return SUCCESS;
}
int special_tree(Tree *tree) {
  return SUCCESS;
}
