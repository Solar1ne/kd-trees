#include "tree.h"
#include <stdio.h>


int main() {
  Tree tree;
  init_tree(&tree);

  insert_array(&tree.array, 272, 59);
  insert_array(&tree.array, 481, 144);
  insert_array(&tree.array, 259, 189);
  insert_array(&tree.array, 139, 310);

  insert_array(&tree.array, 622, 410);

  insert_array(&tree.array, 281, 467);
  insert_array(&tree.array, 43, 480);
  insert_array(&tree.array, 445, 585);
  insert_array(&tree.array, 136, 615);

  insert_array(&tree.array, 260, 685);
  insert_array(&tree.array, 662, 798);
  insert_array(&tree.array, 438, 828);
  insert_array(&tree.array, 163, 826);
  insert_array(&tree.array, 571, 839);

  insert_array(&tree.array, 592, 715);

  insert_array(&tree.array, 915, 157);
  insert_array(&tree.array, 913, 276);
  insert_array(&tree.array, 821, 386);
  insert_array(&tree.array, 749, 683);
  insert_array(&tree.array, 879, 810);

  tree.root = build_tree(&tree.array);

  for (int i = 0; i < tree.array.filled; ++i) {
    printf("*****************************\n");
    printf("[%d] = \n", i + 1);

    /*
    printf("PARENT:"); 
    print_node(tree.array.array[i]->parent, 0);

    printf("RIGHT:"); 
    print_node(tree.array.array[i]->right, 0);
    */

    print_node(tree.array.array[i], 0);

 /*   printf("LEFT:");
    print_node(tree.array.array[i]->left, 0);
    printf("*****************************\n");
    */
  }

/*  insert_array(&tree.array, 10, 5);
  insert_array(&tree.array, 13, 5);
  insert_array(&tree.array, 1, 5);
  insert_array(&tree.array, 6, 5);
  insert_array(&tree.array, 6, 5);
  insert_array(&tree.array, 6, 5);
  insert_array(&tree.array, 6, 5);
  insert_array(&tree.array, 4, 5);
  */

  /*
  for (int i = 0; i < tree.array.filled; ++i) {
    printf("[%d] = ", i + 1);
    print_node(tree.array.array[i], 0);
  }
  */

  tree.root = build_tree(&tree.array);

  if (tree.root == NULL)
    printf("ПИШИ \"ПРОПАЛО\""); 
  else 
    like_tree_display(tree.root, 0);

  close_tree(&tree);
  return 0;
}
