#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffers.h"
#define LOG_USE_COLOR
#define DLOG_USE_COLOR
#include "../loggers/src/log.h"

Buffer* buffcreate( size_t capacity, size_t elements_count ){
  Buffer *buff = malloc(sizeof(Buffer));
  buff->buffer_capacity = capacity;
  buff->elements_capacity =  elements_count;
  buff->len = 0;
  buff->elements = malloc(sizeof(void*) * elements_count);
  return buff;
}


size_t usedbuff(Buffer *buff){
  size_t total = (size_t) buff->buffer + buff->buffer_capacity;
  size_t used = total - buff->next;
  return used;
};


 Buffer* bufftrack(void* buffer,  size_t capacity, size_t element_count){
  Buffer *buff =  buffcreate(capacity, element_count);
  buff->buffer = buffer;
   buff->next =  (size_t) buffer;
  return buff;
}


void buffincrese_capacitiy(Buffer* buff, size_t size){
  size_t newcapacity = buff->buffer_capacity + size;
  void* nbuff = realloc(buff->buffer, newcapacity);
  buff->buffer_capacity+=size;
  buff->buffer = nbuff;
}


void buffelement_increase_capacity(Buffer* buff, size_t element_count){
  buff->elements_capacity += element_count;
  void* nelements = realloc(buff->elements, sizeof(void*) * buff->elements_capacity);
  buff->elements = nelements;
};

void buffbefore_fill(Buffer* buff, size_t size ){
  if(((size_t) buff->buffer + buff->buffer_capacity) < (buff->next + size)){
    buffincrese_capacitiy(buff,size);
  } else if (buff->elements_capacity < buff->len){
    buffelement_increase_capacity(buff, 10);
  }
}

void buffill(Buffer* buff, size_t size ){
  void* nmem = (void*) buff->next;
  log_debug("len %zu and mem %zu", (size_t)buff->len, (size_t) nmem);
  log_debug(" capacity %zu\n",  (size_t) buff->elements_capacity);
  buff->elements[buff->len] = nmem;
  buff->next += size;
  buff->len++;
};


void buffreeall(Buffer *buff){
  free(buff->elements);
  free(buff->buffer);
  free(buff);
};


Buffer* buffinit(size_t capacity, size_t elements_count){
  Buffer* buff = buffcreate(capacity, elements_count);
  void* buffer = malloc(capacity);
  return bufftrack(buffer, capacity, elements_count);
}









