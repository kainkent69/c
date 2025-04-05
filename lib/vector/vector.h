
#include <stdlib.h>
#include <stdbool.h>
typedef char byte;
typedef struct vector {
  size_t cap, len, size;
  } vector;


#define vect_contents(vect)((char*)((size_t)vect + sizeof(vector)))

/**
 * allocate a new vector
 * @param size is the size of each element 
 * @param count is the initial count of the buffer  
 * @returns newly created vector
**/
vector* vect_alloc(size_t size, size_t count);

/**
 * pushes the new content to grow the size of a vector
 * @param *vect vector to add a content
 * @param  content is the content to be pushed
 * @returns returns the newly pushed content 
**/
void* vect_push(vector* vect,  void* content);


 /* pushes the new content to the start 
 * @param *vect vector to add a content
 * @param  content is the content to be pushed
 * @returns returns the newly pushed content 
**/
void* vect_push_start(vector* vect,  void* content);

/**
 * get a single elements of a vector
 * @param vect* the vector to inspect
 * @param i is the index
 **/
void* vect_get(vector* vect,   size_t i);









