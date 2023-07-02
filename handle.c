#include "handle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




char* scanf_str() {
  // чтение строки произвольной длины
  size_t size = 16;
  char *str = malloc(sizeof(char) * size);
  size_t i = 0;
  while (1) {
    str[i] = getchar();
    if (str[i] == '\n') { // пользователь закончил ввод
      if (i == 0) {
        printf("Empty line: ");
        continue;
      }
      break;
    }
    if (i + 1 == size) {
      size *= 2;
      str = (char*) realloc(str, sizeof(char) * size);
    }
    ++i;
  }
  str[i] = '\0';
  str = (char*) realloc(str, sizeof(char) * (i + 1));

  return str;
}
bool str_to_int(char *str, int *res) {
  long temp = 0;
  for (int i = 0; str[i] != '\0'; ++i) {
    if (i > 12) { // максимальное кол-во цифр, которые 
                  //  можно сохранить в int (4 байта)
      return false;
    }
    if (str[i] < '0' || '9' < str[i]) {
      return false;
    }
    temp = (temp * 10) + (str[i] - '0');
  }

  *res = (int) temp;
  return true;
}
bool scanf_int(int *res) {
  char *str = scanf_str();

  bool negative = false;
  int i = 0;
  while (str[i] != '\0') {
    if ('0' <= str[i] && str[i] <= '9') {
      break;
    }
    if (str[i] == '-') {
      negative = !negative;
    } else if (str[i] != '+') {
      break;
    }
    ++i;
  }
  
  bool status_conversion = str_to_int(str + i, res);
  free(str);

  if (status_conversion == true && negative == true) {
    *res *= (-1);
  }
  
  return status_conversion;
}
