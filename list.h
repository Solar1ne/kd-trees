#ifndef LIST_H
#define LIST_H


typedef struct Box Box;
struct Box{//Вагон
  char *data; //char *
  Box *next;
};

typedef struct List List;
struct List{
  Box *start;
};

void add_element(List *list, char const *element);
void delete_box(Box *box);
void delete_list(List *list);
int delete_by_release(List *list, int release);
void delete_old_box(List *list);
void display_list(List *list);

#endif // LIST_H
