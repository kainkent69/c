
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// append bufferes.
#define buffAppend(buff, size, type, value){\
   buffBeforeFill(buff, size);*((type) buff->next) = value;buffFill(buff, size);\
}


// append buffers as strings 

#define stringBuffAppend(buff, size, str){\
buffBeforeFill(buff, size); \
memcpy((void*) buff->next, str, size -1);\
buffFill(buff, size);         \
}

// the stuct type for the buffer types 
typedef struct _Buffer {
  size_t buffer_capacity,     // the size of the buffers 
         next,                // the count of the bufers 
         len,                 // the current length of the buffers 
         elements_capacity;   //  the elements capacity 
  void* buffer;               // the current bufefrs 
  void** elements;            //  elements array 
} Buffer;           

/**
 * buffcreate ceate buffer 
 * @param capacity is the count of the buffers 
 * @param elements_count is the count of the elements
 * */
Buffer* buffCreate( size_t capacity, size_t elements_count );


/**
 * usedbuf is the size of the buffer in bytes 
 * @param *buff is the buffer 
 **/
size_t buffSize(Buffer *buff);

/** bufftrack is the to create a new buffers 
 * @param *buffer is the buffer to be tracked
 * @param capacity is the is the byte size 
 * @param element_count is the count of the elementes for the buffers
 * @return a new Buffer
 * */
 Buffer* buffTrack(void* buffer,  size_t capacity, size_t element_count);


/**
 * buffIncreaseCapacity is a funtion to increase the buffers
 * @param *buff is the Buffer
 * @param size is the number of bytes to be added
 * */
void buffIncreaseCapacity(Buffer* buff, size_t size);

/** 
 * buffElement_increase_increase_capacity
 * @param *buff is the Buffer ot 
 * @param element_count is the element count   
 * */
void buffElementIncreaseCapacity(Buffer* buff, size_t element_count);

/** 
 * buffBeforeFill is the way to do before adding or removing element to a buffer
 * @param *buff is the Buffer
 * @param is the size of the elenents
 **/
void buffBeforeFill(Buffer* buff, size_t size );

/** 
 * buffFill is to add a new elemnt to a bufer
 * @param *buff is the buffer to fill
 * @param size is the size to be fill to the buffer
 **/
void buffFill(Buffer* buff, size_t size );

/** buffFreeAll is the way to free all of the buffers
 * @param *buff is the buffer to be freed 
 **/
void buffFreeAll(Buffer *buff);

/** 
 * buffInit to initialize a buffer
 * @param capacity is the size in bytes to make a buffer capacity 
 * @param elements_count is the initial count of the elements
 */
Buffer* buffInit(size_t capacity, size_t elements_count);







