#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"


Tree init_tree() {
  Tree tree;
  tree.root = NULL;
  return tree;
}
void load_from_file(Tree *tree, FILE *file) {
  char key[128];
  char info[128];
  // File End of File
  while (!feof(file)) {
    if (fscanf(file, "%s", key) != 1) {
      break;
    }
    if (fscanf(file, "%s", info) != 1) {
      break;
    }
    add_tree(tree, key, info);
  }
}
void close_tree(Tree *tree) {
  delete_all_nodes(tree->root);
}
void add_tree(Tree *tree, char *key, char const *info){
  if (tree->root == NULL) {
    tree->root = create_node(key, info);
    return;
  }
  adding(tree, key, info);
}
void proshivka_node(Node *new_node, Node *parent) {
  // this - parent
  // Прошивка
  if (parent->left == new_node) {
    if (parent->right == NULL) {
      new_node->next = parent;
    } 
    else { // parent->right != NULL
      // find next_
      // Поиск первого элемент у которого не будет двух указателей
      //    (в приоритете искать значение среди левых, потому что Л- первый по правилу обхода)
      Node *next_node = parent->right;
      while (next_node->left != NULL || next_node->right != NULL) {
        if (next_node->left != NULL) {
          next_node = next_node->left;
        }
        else {
          next_node = next_node->right;
        }
      }
      new_node->next = next_node;
    }
  }
  else /* parent->right == new_node */ {
    if (parent->left == NULL) {
      new_node->next = parent;
    }
    else {
      new_node->prev = parent->left;
      new_node->next = new_node->prev->next;

      new_node->prev->next = new_node; // если пойду назад, затем вперед, я окажусь на исходной точкт
      if (new_node->next != NULL) {
        new_node->next->prev = new_node; // и наоборот
      }
      return;
    }
  }
  // next - сущ
  new_node->prev = new_node->next->prev;
  new_node->next->prev = new_node;

  if (new_node->prev != NULL) {
    new_node->prev->next = new_node;
  }
}
void adding (Tree *tree, char *key, char const *info) {
  Node *this = tree->root;

  int going_left = 0;
  do {
    going_left = strcmp(this->key, key);

    if (going_left == 0) {
      add_element(&this->info, info);
      return;
    }
    if (going_left > 0) {
      if (this->left == NULL){
        break;
      }
      this = this->left;
    } else {
        if (this->right == NULL){
          break;
      }
        this = this->right;
    }
  } while (this != NULL);

  Node *new_node = create_node(key, info);
  if (going_left > 0) {
    this->left = new_node;
  } else {
    this->right = new_node;
  }
  new_node->parent = this;
  
  proshivka_node(new_node, this);
}
void delete_from_tree(Tree *tree, char *key) {
  Node *node = looking_for_key(tree->root, key);
  if (node == NULL) {
    return;
  }

  delete_old_box(&node->info);
  if (node->info.start != NULL) {
    return; // есть ещё значения в самом списке (поезд)
  }

  if (node->left != NULL && node->right != NULL) {
    Node *min_node = node->right;
    while (min_node->left != NULL) {
      min_node = min_node->left;
    }
    
    // swap content
    Node buf;
    buf.key  = node->key;
    buf.info = node->info;

    node->key = min_node->key;
    node->info = min_node->info;

    min_node->key = buf.key;
    min_node->info = buf.info;

    node = min_node;
  }
  
  Node *child = NULL; // ребенок для родителя (отн. удаляемого)
  if (node->left != NULL) {
    child = node->left;
  } else {
    child = node->right;
  }

  if (node->parent == NULL) { // это есть корень
    // поменять значение в tree root
    tree->root = child;
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
  
  // прошивка
  if (node->prev != NULL) {
    node->prev->next = node->next;
  }
  if (node->next != NULL) {
    node->next->prev = node->prev;
  }
  
  delete_node(node);
}
void search(Tree *tree, char *key, Box ***vector, int *size) {
  Node *res = looking_for_key(tree->root, key);
  if (res == NULL) {
    return;
  }

  Box *current = res->info.start;

  int filled = 0;
  *size = 10; // в голову что пришло
  *vector = (Box**) calloc(*size, sizeof(Box*));

  while (current != NULL) {
    (*vector)[filled] = current;
    filled += 1;
    current = current->next;

    if (filled == *size) {
      *size += 10;
      *vector = (Box**) realloc(*vector, sizeof(Box*) * (*size));
    }
  }
  *size = filled;
}
Node* special_search(Tree *tree, char *key) {
  if (tree->root == NULL) {
    return NULL;
  }

  Node *node = tree->root;
  while (node != NULL) {
    int going_left = strcmp(node->key, key);
    if (going_left == 0) {
      return near_node(node);     
    }

    if (going_left > 0) {
      if (node->left == NULL) {
        break;
      }
      node = node->left;
    } else {
      if (node->right == NULL) {
        break;
      }
      node = node->right;
    }
  }

  return node;
}
void display_tree_root(Tree *tree){
  if (tree->root == NULL) {
    return;
  }

  display_tree(tree->root, 0);
}
char* rand_str() {
  char *str = (char*) malloc(sizeof(char) * 10);
  for (int i = 0; i < 9; ++i) {
    str[i] = 'a' + (rand() % 28);
  }
  str[9] = '\0';
  return str;
}
void check_time(Tree *tree, int count_nodes) {
  char **keys = (char**)calloc(count_nodes, sizeof(char*));
  for (int i = 0; i < count_nodes; ++i) { 
    keys[i] = rand_str();
  }

  clock_t start = clock();
  for (int i = 0; i < count_nodes; ++i) { 
    add_tree(tree, keys[i], "a");
  }
  clock_t end   = clock();
  printf("INSERT TIME %10u elements: %fs\n", count_nodes, (float)(end - start) /CLOCKS_PER_SEC);

  int size = 0;
  Box **vector = NULL;
  start = clock();
  for (int i = 0; i < count_nodes; ++i) { 
    search(tree, keys[i], &vector, &size);
    free(vector);
    vector = NULL;
    size = 0;
  }
  end   = clock();
  printf("SEARCH TIME %10u elements: %fs\n", count_nodes, (float)(end - start) / CLOCKS_PER_SEC);

  start = clock();
  for (int i = count_nodes / 2; i < count_nodes / 100; ++i) { 
    int ran = rand() % count_nodes;
    delete_from_tree(tree, keys[ran]);
  }
  end   = clock();
  printf("DELETE TIME %10u elements: %fs\n", count_nodes, (float)(end - start) / CLOCKS_PER_SEC);

  for (int i = 0; i < count_nodes; ++i) { 
    free(keys[i]);
  }
  free(keys);
}
void travel_tree(Tree *tree) {
  // Пользуемся обшивкой (которая компенсирует использование рекурсии
  if (tree->root == NULL) {
    return;
  }

  Node *current = tree->root;
  while (current->prev != NULL) { // доведения до начала
    current = current->prev;
  }

  while (current != NULL) { // пока не дойду до конца
    display_node(current);
    current = current->next;
  }
}
