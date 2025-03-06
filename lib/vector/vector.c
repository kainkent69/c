#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "vector.h"

vector* vcreate(size_t size, size_t count){
  vector* vect = malloc(sizeof(vector));
  size_t toadd = size * count;
  vect->contents = malloc(toadd);
  vect->cap = count;
  return vect;
};


bool vincrcap(vector* vect, size_t size,  size_t count){
  size_t newmem = size * (count * vect->cap);
  vector* nvect = realloc(vect, newmem);
  if(nvect == NULL) return  false;
  vect = nvect;
  vect->cap+= count;
  return true;
};


bool vappend(vector* vect, size_t size, void* content){
  puts("append to vector");
  size_t ncount = vect->len + 1;
  if(ncount > vect->cap) if(!vincrcap(vect,size, 1)) perror("Unable to output error");
  byte* newmemadr =   vect->contents + (vect->len * size);
  memcpy(newmemadr, content, size);
  printf("appending content %ld\n", (size_t)&content);
  printf("%d\n", *newmemadr);
  vect->len++;
  return true;
}



void* vget(vector* vect, size_t size, size_t i) {
  const size_t index = size * i;
  return  (byte*) vect->contents + index;
};





