#include "buffer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
buf_t *buf_new(size_t wide) {
  buf_t *buf = malloc(sizeof(buf_t) + wide);
  char *start = (char *)buf + sizeof(buf_t);
  *buf = (buf_t){.start = start, .next = start, .end = start + wide};
  return buf;
  
}

buf_t *buf_grow(buf_t *buf, size_t wide) {
  size_t size = buf_size((*buf)) + wide;
  printf("original [%zu] new [%zu]", buf_size((*buf)), size);
  buf_t *nbuf = realloc(buf, size);
  memset(buf->end, 0, wide);
  nbuf->end = buf->start + size;
  return nbuf;
}

void *buf_set_next(buf_t* buf,  void *src, size_t wide) {
       void* ret= memmove(buf->next, src, wide); 
       buf->next += wide;
       return ret;
}


void *buf_set(buf_t* buf, void* src, void* where,  size_t wide, bool incr){
       void* ret= memmove(where, src, wide); 
       if(incr) buf->next += wide;
       return ret;
}


void *buf_set_incr(buf_t* buf, void* src, void* where,  size_t wide);

// TODO: increasing data by using append
// TODO: allow make of auto growing buffers
void* buf_skip(buf_t* buf, size_t wide){
       if(buf_available((*buf)) < wide) return NULL;  
       void* ret = memmove(buf + wide, buf, buf_occupied((*buf)));
       buf->next += wide;
       return ret;
       
}


