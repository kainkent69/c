#include "vector.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vect_auto_grow = 0;

/**
 * State to automatically grow vectors
 **/
void vect_set_auto_grow(int grow) { vect_auto_grow = grow; }

vect_t *vect_alloc(size_t size, size_t cap) {
  vect_t *vect = malloc(VECT_T_SIZE + size * cap);
  *vect = (vect_t){.cap = cap, .size = size, .len = 0}; // Initialize vector
  return vect;
};

vect_t *vect_grow(vect_t *vect, size_t count) {
  vect_t *nvect =
      realloc(vect, +VECT_T_SIZE + (vect->size * (vect->cap + count)));
  if (nvect == NULL)
    return NULL;
  nvect->cap += count;
  return nvect;
};

size_t vect_grow_if_needed(vect_t *vect) {
  if (vect_auto_grow == 1 && vect->len + 1 > vect->cap) {
    puts("GROW IS NEEDED");
    if (!vect_grow(vect, 1))
      return -1;
  }
  return 0;
}



// TODO:  Make a vecor to be pushed or append per value
// TODO: allow arrays to be used as the vector contents

void printIntArray(vect_t *vec, int len) {
  printf("[ ");
  for (int i = 0; i < len; i++) {
    printf("%d ", ((int *)vect_first(vec))[i]);
  }
  printf("]\n");
};

void *vect_move_i(vect_t *vect, size_t i) {
  void *moved =
      memmove(vect_get(vect, i), vect_first(vect), vect->len * vect->size);
  vect->len++;
  return moved;
}

#include <stdio.h>
int main() {
  vect_t *int_vector = vect_typed(int, 10);
  assert(int_vector->cap == 10 && int_vector->size == 4);
  assert((size_t)vect_first(int_vector) == (size_t)int_vector + sizeof(vect_t));
  // push contents
  int *contents = (int *)vect_first(int_vector);
  for (int i = 0; i < 10; i++) {
    contents[i] = i;
    int_vector->len++;
  }
  // printing
  printf("\n Initial contents ");
  printIntArray(int_vector, 10);
  // grow
  vect_grow_self(int_vector, 10);

  assert(int_vector->cap == 20);
  vect_move_i(int_vector, 1);

  printf("Lenght: %zu\n", int_vector->len);
  printf("Last: %p\n", vect_last(int_vector));
  printf("Index 10: %p\n", vect_get(int_vector, 10));
  printf("Index len-1: %p\n", vect_get(int_vector, int_vector->len - 1));

  assert(int_vector->len == 11);
  *((int *)vect_first(int_vector)) = (int)11;
  *((int *)vect_last(int_vector)) = (int)100;

  int_vector->len = 20;
  assert(int_vector->len == 20);

  vect_set_auto_grow(1);
  if (vect_auto_grow == 1 && int_vector->len + 1 > int_vector->cap)
    puts("needs growing");
  // print
  printf("\n Grown Vector");
  printIntArray(int_vector, 20);
  printf("capacity %zu\n", int_vector->cap);
  // pushing 
  vect_push(int_vector, int, 21);
  printf("capacity after %zu\n", int_vector->cap);
  printf("After pushing");
  printIntArray(int_vector, 21);

  // insert
  vect_insert(int_vector, int, 55);
  printf("capacity after %zu\n", int_vector->cap);
  printf("After pushing");
  printIntArray(int_vector, 22);

  assert(*vect_get_as(int, int_vector,0) == 55);
  // push a content but
}
