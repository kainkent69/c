#include "../lib/buffers/buffers.h"
#include "../lib/verbose/verbose.h"
#include "ctest/ctest.h"
#include <assert.h>

CTEST(buffer, creation_of_buffer) {
  Buffer *buffer = buffInit(10, 10);
  ASSERT_NOT_NULL(buffer);
  ASSERT_NOT_NULL(buffer->buffer);
  ASSERT_NOT_NULL(buffer->elements);
  // the memory addresses and data
  assert(buffer->next == (size_t)buffer->buffer);
  ASSERT_EQUAL(buffer->elements_capacity, 10);
  ASSERT_EQUAL(buffer->buffer_capacity, 10);
}

CTEST(buffer, reallocation_of_the_content) {
  Buffer *buffer = buffInit(10, 10);
  ASSERT_EQUAL(buffer->buffer_capacity, 10);
  buffIncreaseCapacity(buffer, 20);
  ASSERT_EQUAL(buffer->buffer_capacity, 30);
  // reallocation the element count
  ASSERT_EQUAL(buffer->elements_capacity, 10);
  buffElementIncreaseCapacity(buffer, 10);
  ASSERT_EQUAL(buffer->elements_capacity, 20);
}


CTEST(buffer, actual_value){
  char* hello_world = "Hello, World!";
  size_t len = strlen(hello_world) + 1;
  Buffer* buffer = buffInit(len, len);
  for(size_t i = 0; i < len -1; i++){
    buffAppend(buffer,sizeof(char), char*, hello_world[i]);
    ASSERT_EQUAL(hello_world[i], ((char*) buffer->buffer)[i]);
  }
  ASSERT_STR(buffer->buffer, hello_world);
  ASSERT_EQUAL_U(strlen(buffer->buffer), strlen(hello_world));
};


CTEST(buffer, append_string){
Buffer* buff = buffInit(1,1);
  char* str = "Hello World";
size_t size = (size_t) strlen(str) + 1;
buffBeforeFill(buff, size); 
memcpy((void*) buff->next, str, size -1);
buffFill(buff, size);         
}


CTEST(buffer, storing_strings){
  Buffer* buffer = buffInit(1000 * 10, 10);
  for(size_t i = 0; i < 10; i++){
    char words[100]; 
  size_t size = sprintf(words,  "Hello world! for [%zu] times", i);
  char* wordlist = malloc((size + 1) * sizeof(char));
  snprintf(wordlist, sizeof(words), "Hello world! for [%zu] times", i);
  stringBuffAppend(buffer, size, wordlist);
    free(wordlist);
  }

  for(size_t i = 0; i < buffer->len; i++){
    char* filter = filtered_verbose(); 
    bool verbose = is_filtered_verbose_of("test")  ;
    char* content = ((char*)buffer->elements[i]);
    char const *hello_world = "Hello world!";
    char* sample = malloc(strlen(hello_world) + 1);
    memcpy(sample, hello_world, strlen(hello_world) + 1);
    if(verbose) CTEST_LOG("buffer_tests: %s\n", content);
    free(sample);

  }
}





