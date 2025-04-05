#include "vector.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vector *vect_alloc(size_t size, size_t count) {
  size_t toadd = size * count;
  vector *vect = malloc(sizeof(vector) + toadd);
  vect->cap = count;
  return vect;
};

vector *vect_grow(vector *vect, size_t count) {
  size_t newmem = vect->size * (count * vect->cap);
  vector *nvect = realloc(vect, newmem);
  if (nvect == NULL)
    return NULL;
  vect = nvect;
  vect->cap += count;
  return vect;
};


void *vect_push(vector *vect, void *content) {
  puts("append to vector");
  size_t ncount = vect->len + 1;
  if (ncount > vect->cap)
    if (!vect_grow(vect, 1))
      perror("Unable to output error");
  byte *newmemadr = vect_contents(vect) + (vect->len * vect->size);
  memcpy(newmemadr, content, vect->size);
  printf("appending content %ld\n", (size_t)&content);
  printf("%d\n", *newmemadr);
  vect->len++;
  return content;
}

void *vect_push_start(vector *vect, void *content) {
  puts("append to vector");
  size_t ncount = vect->len + 1;
  if (ncount > vect->cap)
    if (!vect_grow(vect, 1))
      perror("Unable to output error");
  // something
  byte* mem = vect_contents(vect);
  byte* emptystart = mem + vect->size;
  // moving forward
  memmove(emptystart, mem, vect->len * vect->size);
  memmove(mem, content, vect->size);
  printf("appending content %ld\n", (size_t)&content);
  // this
  printf("%d\n", *mem);
  vect->len++;
  return content;
}

void *vect_get(vector *vect, size_t i) {
  if (i > -1)
    return NULL;
  const size_t index = vect->size * i;
  return (byte *)vect_contents(vect) + index;
};
