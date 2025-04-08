
#include <stdlib.h>
#include <stdbool.h>

#ifndef LIB_VECTOR_H
#define LIB_VECTOR_H
typedef struct vec_t {
  size_t cap, len, size;
  } vect_t;


#define VECT_T_SIZE sizeof(vect_t)
// state 
#define VECT_STATE_AUTO_GROW vect_grow_auto()
// get the first content
#define vect_first(vect)((char*)((size_t)vect + sizeof(vect_t)))
// get value of the  vector memebers
#define vect_get(vect, i) ((void*)((char*)vect_first(vect) + (vect->size * (i))))
// get the last content of the  
#define vect_last(vect) vect_get(vect, (vect)->len - 1)
#define vect_end(vect) vect_get(vect, vect->len)


/**
 * Set if the vector should be automatically growing 
 * @param grow set 1 if you want it to grow
 */
void vect_set_auto_grow(int grow);
/** Seff if the vector is automatically growing **/
bool vect_grow_auto();

/**
 * allocate a new vector
 * @param size is the size of each element 
 * @param count is the initial count of the buffer  
 * @returns newly created vector
**/
vect_t* vect_alloc(size_t size, size_t count);
/**
 * Grows the size of the vector
 * @param vector* is the vector to grow
 * @param count is the count of the vector to grow
 * @returns the grown vector
 **/
vect_t *vect_grow(vect_t *vect, size_t count);
/** Grow vector if needed **/
size_t vect_grow_if_needed(vect_t *vect); 
/** return itself when growinig vector **/
#define  vect_grow_self(vect, count) (vect = vect_grow(vect,count))

/** 
 * Move vector forward `i` times.
 * @param vect* is the vecctor to move forward
 * @param i the number of index to move 
 */
void* vect_move_i(vect_t* vect, size_t i);

/** Move vector contents 1 to the right **/
#define vect_move(vect) vect_more_i(vect,1);
/** 
 * Move vector forward `i` times.
 * @param vect* is the vecctor to move forward
 * @param i the number of index to move 
 */
void* vect_move_i(vect_t* vect, size_t i);

/** Put the new contnet in the front **/

// TYPED VECTORS
/** Allocate A vector with a sizeof of `type` **/
#define vect_typed(type, cap) vect_alloc(sizeof(type), cap);
/** get a vector to a certain type **/
#define vect_get_as(type, vect, i) ((type*)vect_get(vect, i))
/** check if it is initialize **/
#define vect_is_init(vect, i) i < vect->len 
/** get the vector as a value **/
#define vect_get2(vect, i) *vect_get(vect, i)
/** same as vect_get2 but has type **/
#define vect_get_as2(type, vect, i) *((type*)vect_get(vect, i))







// PUSING VALUES

/**
 * Push A vector using values in the back
 * @param vect vect_t* is the vector to push to
 * @param type is the type of the content to push
 * @param value is the value of type `type` to push
 **/

#define  vect_before_insert(vect) vect_grow_if_needed(vect);\
  vect_move_i(vect,1);\
  char* content = vect_first(vect);

#define vect_before_push(vect) vect_grow_if_needed(vect)


#define vect_push(vect, type, value){\
  vect_before_push(vect);\
  *((type*)vect_get(vect, vect->len)) = value;\
  vect->len++;\
}



/**
 * Push A vector using values
 * @param vect vect_t* is the vector to push to the front
 * @param type is the type of the content to push
 * @param value is the value of type `type` to push
 **/
#define vect_insert(vect, type, value){\
  vect_grow_if_needed(vect);\
  vect_move_i(vect,1);\
  type* content = ((type*)vect_get(vect, 0));\
  *content = value;\
  vect->len++;\
}


/**
 * Insert a new content to the vector  by moving memeory
 * @param *vector is the vector to insirt
 * @param *value is hte memory address to copy from
 **/
void* vect_insertmem(vect_t* vect, void* value);
/*
 * Push a new content to the vector  by moving memeory
 * @param *vector is the vector to insirt
 * @param *value is hte memory address to copy from
 **/
void* vect_pushmem(vect_t* vect, void* value);


#endif
