#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffers.h"
#include "../verbose/verbose.h"

#define LOG_USE_COLOR
#define DLOG_USE_COLOR
#include "../loggers/src/log.h"
Buffer* buffCreate(size_t capacity, size_t elements_count) {
  Buffer* buff = malloc(sizeof(Buffer));
  buff->buffer_capacity = capacity;
  buff->elements_capacity = elements_count;
  buff->len = 0;
  buff->elements = malloc(sizeof(void*) * elements_count);
  return buff;
}

size_t buffSize(Buffer* buff) {
  size_t total = (size_t)buff->buffer + buff->buffer_capacity;
  size_t used = total - buff->next;
  return used;
};

Buffer* buffTrack(void* buffer, size_t capacity, size_t element_count) {
  Buffer* buff = buffCreate(capacity, element_count);
  buff->buffer = buffer;
  buff->next = (size_t)buffer;
  return buff;
}

void buffIncreaseCapacity(Buffer* buff, size_t size) {
  size_t newcapacity = buff->buffer_capacity + size;
  void* nbuff = realloc(buff->buffer, newcapacity);
  buff->buffer_capacity += size;
  buff->buffer = nbuff;
}

void buffElementIncreaseCapacity(Buffer* buff, size_t element_count) {
  buff->elements_capacity += element_count;
  void* nelements = realloc(buff->elements, sizeof(void*) * buff->elements_capacity);
  buff->elements = nelements;
};

void buffBeforeFill(Buffer* buff, size_t size) {
  if (((size_t)buff->buffer + buff->buffer_capacity) < (buff->next + size)) {
    buffIncreaseCapacity(buff, size);
  } else if (buff->elements_capacity <= buff->len) { //fixed bug, was < instead of <=.
    buffElementIncreaseCapacity(buff, 10);
  }
}

void buffFill(Buffer* buff, size_t size) {
  bool verbose =  is_filtered_verbose_of("buffer");
  void* nmem = (void*)buff->next;
  if(verbose) log_debug("len %zu \n mem %zu \n capacity %zu\n", (size_t)buff->len, (size_t)nmem, (size_t)buff->elements_capacity);
  buff->elements[buff->len] = nmem;
  buff->next += size;
  buff->len++;
};

void buffFreeAll(Buffer* buff) {
  free(buff->elements);
  free(buff->buffer);
  free(buff);
};

Buffer* buffInit(size_t capacity, size_t elements_count) {
  Buffer* buff = buffCreate(capacity, elements_count);
  void* buffer = malloc(capacity);
  return buffTrack(buffer, capacity, elements_count);
}
