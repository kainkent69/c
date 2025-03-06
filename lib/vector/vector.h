
#include <stdlib.h>
#include <stdbool.h>
typedef char byte;
typedef struct {
  size_t cap,  len;
  byte* contents; 
  } vector;

#define vassign(type, vector, size, index)  *((type) veget(vector, size, index)) 


vector* vcreate(size_t size, size_t count);

bool vincrcap(vector* vect, size_t size,  size_t count);

bool vappend(vector* vect, size_t size, void* content);

void* vget(vector* vect, size_t size, size_t i);








