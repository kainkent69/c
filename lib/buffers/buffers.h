#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buff_append(buff, size, type, value){\
   buffbefore_fill(buff, size);*((type) buff->next) = value;buffill(buff, size);\
}



#define buff_append_str(buff, size, str){\
buffbefore_fill(buff, size); \
memcpy((void*) buff->next, str, size -1);\
buffill(buff, size);         \
}

typedef struct _Buffer {
  size_t buffer_capacity,  next, len, elements_capacity;
  void* buffer;
  void** elements;
} Buffer;


Buffer* buffcreate( size_t capacity, size_t elements_count );

size_t usedbuff(Buffer *buff);


 Buffer* bufftrack(void* buffer,  size_t capacity, size_t element_count);


void buffincrese_capacitiy(Buffer* buff, size_t size);


void buffelement_increase_capacity(Buffer* buff, size_t element_count);

void buffbefore_fill(Buffer* buff, size_t size );

void buffill(Buffer* buff, size_t size );

void buffreeall(Buffer *buff);

Buffer* buffinit(size_t capacity, size_t elements_count);








