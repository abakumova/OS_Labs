#include <stdio.h>
#include "ArrayList.h"

int main(void) {
  ArrayList list = create(&list);
  for (int i = 0; i < 100; i++) {
    add(&list, i);
  }
  printf("The current size is %d\n", list.size);
  printf("The current capacity is %d\n", list.capacity);

  for (int i = 0; i < 29; i++) {
    removeAt(&list, i);
  }

  printf("The current size is %d\n", list.size);
  printf("The current capacity is %d\n", list.capacity);
  insert(&list, 5, 555);
  insert(&list, 0, 111);

  insert(&list, 6, 666);
  printf("%d\n", *get(&list, 5));
  printf("%d\n", *get(&list, 0));
  printf("%d\n", *get(&list, 6));
  return 0;
}
