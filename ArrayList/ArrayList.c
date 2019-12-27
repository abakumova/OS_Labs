#include <stdlib.h>
#include "ArrayList.h"

int shift(ArrayList *list);
int wide(ArrayList *list);

/**
 * Creates a new ArrayList.
 * @param list
 * @return
 */
ArrayList create(ArrayList *list) {
  list->size = 0;
  list->arr = (int *) calloc(INITIAL_ARRAY_SIZE, sizeof(int));
  list->capacity = INITIAL_ARRAY_SIZE;
  return *list;
}

/**
 * Removes an ArrayList by freeing memory.
 * @param list
 */
void destruct(ArrayList *list) {
  free(list->arr);
  free(&(list->capacity));
  free(&(list->size));
  free(list);
}

/**
 * adds a value to an ArrayList, expands the ArrayList if needed
 * @param list
 * @param value
 * @return
 */
int add(ArrayList *list, int value) {
  if (list == NULL || list->arr == NULL) {
    return 1;
  }

  if (list->size + 1 <= list->capacity) {
    list->arr[list->size] = value;
  } else {
    //check if we have memory to expand ArrayList
    if (wide(list) != 1) {
      list->arr[list->size] = value;
    } else {
      return 1;
    }
  }
  list->size++;
  return 0;
}

/**
 * increases size of the ArrayList.
 * @param list
 * @return 1 if the system don't have enough memory, and 0 if success.
 */
int wide(ArrayList *list) {
  int newCapacity = list->capacity * 2;
  int *newArr = (int *) calloc(newCapacity, sizeof(int));

  if (newArr == NULL) {
    return 1;
  }

  for (int i = 0; i < list->size; i++) {
    newArr[i] = list->arr[i];
  }
  free(list->arr);
  list->arr = newArr;
  list->capacity = newCapacity;
  return 0;
}

/**
 * The method decrease ArrayList size.
 * @param list
 * @return returns 1 if a system don't have enough memory.
 * And 0 if success.
 */
int shift(ArrayList *list) {
  int newCapacity = list->capacity / 2;
  int *newArr = (int *) calloc(newCapacity, sizeof(int));
  if (newArr == NULL) {
    return 1;
  }
  for (int i = 0; i < list->size; i++) {
    newArr[i] = list->arr[i];
  }
  free(list->arr);
  list->arr = newArr;
  list->capacity = newCapacity;
  return 0;
}

/**
 * The method removes a value stored at the passed index
 * @param list
 * @param index
 * @return
 */
int removeAt(ArrayList *list, int index) {
  if (list->arr == NULL || index > list->size) {
    return 1;
  }

  for (int i = index; i < list->size - 1; i++) {
    list->arr[i] = list->arr[i + 1];
  }
  if (list->size * 2 <= list->capacity && list->capacity > 15) {
    shift(list);
  }
  list->size--;
  return 0;
}

/**
 * returns a pointer to a value stored by passed index.
 * Returns NULL if the passed index is bigger than ArrayList size
 * @param list
 * @param i
 * @return a value with index i, or NULL if the i is more than array size
 */
int *get(ArrayList *list, int i) {
  if (i < list->size) {
    return &list->arr[i];
  }
  return NULL;
}

/**
 * The method returns an array of all containing values of the ArrayList.
 * @param list
 * @return
 */
int *getAll(ArrayList *list) {
  if (list == NULL) {
    return NULL;
  }

  int *newArr = (int *) calloc(list->size, sizeof(int));
  for (int i = 0; i < list->size; i++) {
    newArr[i] = list->arr[i];
  }
  return newArr;
}

/**
 * The method returns 1 if the ArrayList contains a value,
 * or 0 if not.
 * @param list
 * @param value
 * @return
 */
int contains(ArrayList *list, int value) {
  if (list == NULL || list->arr == NULL) {
    return 0;
  }

  for (int i = 0; i < list->size; i++) {
    if (list->arr[i] == value) {
      return 1;
    }
  }
  return 0;
}

/**
 * Returns an index of a value, or -1 if the ArrayList doesn't contain the value.
 * @param list
 * @param value
 * @return
 */
int getIndexOf(ArrayList *list, int value) {
  if (list == NULL || list->arr == NULL) {
    return -1;
  }

  for (int i = 0; i < list->size; i++) {
    if (list->arr[i] == value) {
      return i;
    }
  }
  return -1;
}

int insert(ArrayList *list, int index, int value) {
  if (list == NULL || list->arr == NULL || index >= list->size - 1) {
    return 1;
  }

  if (list->size + 1 <= list->capacity) {
    for (int i = list->size; i > index; i--) {
      list->arr[i] = list->arr[i - 1];
    }
    list->arr[index] = value;
  } else {
    //check if we have memory to expand ArrayList
    if (wide(list) != 1) {
      for (int i = list->size; i > index; i--) {
        list->arr[i] = list->arr[i - 1];
      }
      list->arr[index] = value;
    } else {
      return 1;
    }
  }
  list->size++;
  return 0;
}

int getSize(ArrayList *list) {
  return list->size;
}

int setAt(ArrayList *list, int index, int value) {
  if (list == NULL || list->arr == NULL || index >= list->size - 1) {
    return 1;
  }

  list->arr[index] = value;
  return 0;
}