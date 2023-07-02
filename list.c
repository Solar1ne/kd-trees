#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "list.h"



void add_element(List *list, char const *element){//допустим хочу
  if (list == NULL){
    printf("Nothing \n");
    return;
  }

  Box *new_element = malloc(sizeof(Box));
  new_element->data = malloc(sizeof(char) * strlen(element) + 1);
  strcpy(new_element->data, element);

  new_element->next = NULL;

  if(list->start == NULL ){
    list->start = new_element;
    return;// встаёт на первое число- 0
  }

  Box *end = list->start; //встаёт на первое число- 0
  while(end->next != NULL){// с 0 на 1
    end = end->next;
  }
  end->next = new_element;
}
void delete_box(Box *box) {
  if (box == NULL) {
    return;
  }

  free(box->data);
  free(box);
}
int delete_by_release(List *list, int release) {
  if (release <= 0)
    return 1;
  
  Box *trash = NULL;
  if (release == 1) {
    trash = list->start;
    list->start = list->start->next;
    delete_box(trash);
    return 0;
  }

  Box *current = list->start;
  while (current->next != NULL && release > 2) {
    current = current->next;
    release -= 1;
  }
  if (release > 2 || current->next == NULL)
    return 1; // НЕ НАЙДЕН

  trash = current->next;
  current->next = current->next->next;
  delete_box(trash);

  return 0;
}
void delete_list(List *list) {
  while (list->start != NULL) {
    Box *trash = list->start;
    list->start = list->start->next;
    delete_box(trash);
  }
}
void delete_old_box(List *list) {
  Box *trash = list->start;
  list->start = list->start->next;
  delete_box(trash);
}
void display_list(List *list) {
  Box *current = list->start;
  while (current != NULL) {
    printf("[%s] ", current->data);
    current = current->next;
  }
  printf("\n");
}
