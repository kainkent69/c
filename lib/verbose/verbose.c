#include "verbose.h"
#include <string.h>
#ifndef LIB_VERBOSE_C
#define LIB_VERBOSE_C

bool is_verbose(){
  return getenv("VERBOSE") != NULL;
}

char* filtered_verbose(){
  if(is_verbose()){
    size_t size = strlen(getenv("FILTER_V"));
    char* content = malloc(size + 1 * sizeof(char));
    memcpy(content,  getenv("FILTER_V"), size);
    return content;
  }
  return NULL;
};
#endif
