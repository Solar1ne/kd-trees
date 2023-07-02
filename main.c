#include "tree.h"
#include "handle.h"
#include <stdio.h>




int menu() {
  printf("----------\n");
  printf("What do u whant to do:\n");
  printf("1- Add node\n");
  printf("2- Delete node\n");
  printf("3- Search element\n");
  printf("4- Show tree\n");
  printf("5- Travel tree\n");
  printf("6- Special search\n");
  printf("7 - Load file\n");
  printf("----------\n");

  int user_choice = 0;
  while (scanf_int(&user_choice) == false) {
    printf("Enter again: ");
  }
  return user_choice;
}


int main() {
  Tree tree;
  init_tree(&tree);

  char const *msg[] = {"Success", "Empty", "Not found"};

  int (*func[])(Tree*) = {NULL, insert_tree, remove_tree,
                          search_tree, display_tree,
                          travel_tree, special_tree,
                          load_file};

  while (1) {
    int user_choice = menu();
    if (user_choice == 0) {
      break;
    } else if (user_choice < 0 || user_choice > 7) {
      printf("Out of menu\n");
      continue;
    }

    int status = func[user_choice](&tree);
    printf("Status exit: %s\n", msg[status]);
  }

  close_tree(&tree);

  return 0;
}
