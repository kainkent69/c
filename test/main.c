#include "../lib/buffers/buffers.h"
#include "ctest/ctest.h"
#include <assert.h>
#define CTEST_COLOR_OK

CTEST(buffer, creation_of_buffer) {
  Buffer *buffer = buffinit(10, 10);
  ASSERT_NOT_NULL(buffer);
  ASSERT_NOT_NULL(buffer->buffer);
  ASSERT_NOT_NULL(buffer->elements);
  // the memory addresses and data
  assert(buffer->next == (size_t)buffer->buffer);
  ASSERT_EQUAL(buffer->elements_capacity, 10);
  ASSERT_EQUAL(buffer->buffer_capacity, 10);
}

CTEST(buffer, reallocation_of_the_content) {
  Buffer *buffer = buffinit(10, 10);
  ASSERT_EQUAL(buffer->buffer_capacity, 10);
  buffincrese_capacitiy(buffer, 20);
  ASSERT_EQUAL(buffer->buffer_capacity, 30);
  // reallocation the element count
  ASSERT_EQUAL(buffer->elements_capacity, 10);
  buffelement_increase_capacity(buffer, 10);
  ASSERT_EQUAL(buffer->elements_capacity, 20);
}


CTEST(buffer, actual_value){
  char* hello_world = "Hello, World!";
  size_t len = strlen(hello_world) + 1;
  Buffer* buffer = buffinit(len, len);
  for(size_t i = 0; i < len -1; i++){
    buff_append(buffer,sizeof(char), char*, hello_world[i]);
    ASSERT_EQUAL(hello_world[i], ((char*) buffer->buffer)[i]);
  }
  ASSERT_STR(buffer->buffer, hello_world);
  ASSERT_EQUAL_U(strlen(buffer->buffer), strlen(hello_world));
  CTEST_LOG("the new buffer: %s\n", (char*)buffer->buffer);
};


CTEST(buffer, append_string){
Buffer* buff = buffinit(1,1);
  char* str = "Hello World";
size_t size = (size_t) strlen(str) + 1;
buffbefore_fill(buff, size); 
memcpy((void*) buff->next, str, size -1);
buffill(buff, size);         
}


CTEST(buffer, storing_strings){
    CTEST_LOG("Before All");
  Buffer* buffer = buffinit(1000 * 10, 10);
  for(size_t i = 0; i < 10; i++){
    char words[100]; 
  size_t size = sprintf(words,  "Hello world! for [%zu] times", i);
  char* wordlist = malloc((size + 1) * sizeof(char));
  CTEST_LOG("created a worklist\n");
  snprintf(wordlist, sizeof(words), "Hello world! for [%zu] times", i);
  CTEST_LOG("providing value for worklinst\n");
  buff_append_str(buffer, size, wordlist);
    free(wordlist);
  }

  CTEST_LOG("%s", (char*)buffer->elements[0] );
  for(size_t i = 0; i < buffer->len; i++){
    CTEST_LOG("%s\n", ((char*)buffer->elements[i]));

  }
}





