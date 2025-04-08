#include "vector.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../loggers/src/log.h"
#include "../verbose/verbose.h"

#define VV_NAME "vector|vec"
#define VV_GET FILTERING_ENABLED ? is_filtered_with(VV_NAME) : true
#define VV_ IS_VERBOSE ? VV_GET : false;
bool is_verbose_local(){return VV_}
#define VV if (is_verbose_local())

/**
int vect_auto_grow = 0;
 * State to automatically grow vectors
 **/

vect_t *vect_alloc(size_t size, size_t cap) {
  VV log_info("vector: allocating vector size[%zu] cap[%zu]", size, cap);
  size_t newsize = sizeof(vect_t) + (size * cap);
  VV log_info("vector: allocating [%zu]", newsize);
  assert(newsize > 0);
  vect_t *vect = malloc(newsize);
  *vect = (vect_t){.cap = cap, .size = size, .len = 0}; // Initialize vector
  VV log_info("vector: finished allocating vector[%p]", vect);
  return vect;
};

vect_t *vect_grow(vect_t *vect, size_t count) {
  VV log_debug("vect: growing %zu count", count);
  size_t new_capacity = vect->cap + count;
  size_t new_storage = VECT_T_SIZE + (vect->size * new_capacity);
  assert(new_storage > vect->cap * vect->size);
  vect_t *nvect = realloc(vect, new_storage);

  if (nvect == NULL)
    return NULL;
  VV log_debug("vect: grown %zu count sucessful", count);

  VV log_debug("vect: cleaning up the memory");
  char *mem = vect_end(nvect);
  size_t diff = count * vect->size;
  // memset
  memset(mem, '\0', diff);
  printf("\nDo something like this\n");

  for (int i = 0; i < nvect->cap; i++) {
    printf("%d ", *vect_get_as(int, vect, i));
  }
  nvect->cap = new_capacity;
  return nvect;
};

size_t vect_grow_if_needed(vect_t *vect) {
  if ( vect->len + 1 > vect->cap) {
    VV log_info("vector: Needs to grow");
    if (!vect_grow_self(vect, 1))
      return -1;
  }
  return 0;
}

// TODO:  Make a vecor to be pushed or append per value
// TODO: allow arrays to be used as the vector contents
// TODO move
void *vect_move_i(vect_t *vect, size_t i) {
  VV log_info("vector: Moving vector for %zu back", i);
  VV log_debug("vector: Moving vector(%p)", vect);
  void *moved =
      memmove(vect_get(vect, i), vect_first(vect), vect->len * vect->size);
  vect->len++;
  return moved;
}

void *vect_pushmem(vect_t *vect, void *value) {
  vect_before_push(vect);
  memmove(vect_end(vect), value, vect->size);
  vect->len++;
  return value;
}

void *vect_insertmem(vect_t *vect, void *value) {
  vect_before_insert(vect);
  memmove(vect_first(vect), value, vect->size);
  vect->len++;
  return value;
}

void *vec_append(vect_t *vec0, vect_t *vec1) {
  if (vec0->cap <= vec0->len + vec1->len) {
  }
  return vec0;
}

#include <stdio.h>
