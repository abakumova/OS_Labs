#ifndef TASK_2_1_TASK_2_1_ARRAYLIST_H_
#define TASK_2_1_TASK_2_1_ARRAYLIST_H_
#define INITIAL_ARRAY_SIZE 15

typedef struct {
  int *arr;
  int size;
  int capacity;
} ArrayList;

ArrayList create(ArrayList *list);
int *get(ArrayList *list, int i);
void destruct(ArrayList *list);
int add(ArrayList *list, int value);
int removeAt(ArrayList *list, int index);
int* getAll(ArrayList *list);
int contains(ArrayList *list, int value);
int getIndexOf(ArrayList *list, int value);
int insert(ArrayList *list, int index, int value);
int getSize(ArrayList *list);

#endif //TASK_2_1_TASK_2_1_ARRAYLIST_H_
