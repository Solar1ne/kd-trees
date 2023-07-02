#ifndef TREE_H
#define TREE_H

#include "node.h"



typedef struct Tree Tree;
struct Tree {
  Node *root; // дерево

  Array array;
  bool  needRebuild;
};



void  init_tree(Tree *tree);
void close_tree(Tree *tree);
int load_file(Tree *tree);

int insert_tree(Tree *tree);
int remove_tree(Tree *tree);
int search_tree(Tree *tree);
int display_tree(Tree *tree);
int  travel_tree(Tree *tree);
int special_tree(Tree *tree);
int timing(Tree *tree);

#endif // TREE_H
