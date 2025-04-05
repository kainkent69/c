#include <stdlib.h>
#include <stdbool.h>
#ifndef LIB_VERBOSE_H
#define LIB_VERBOSE_H
/** 
  * is_verbose checks if it is verbose (looks for "VERBOSE" env)
  * @return is weather it is verbose or not 
*/
bool is_verbose();

/** checks the filtered verbose
  * @return the string or NULL if it is not filtered
  **/
char* filtered_verbose();

/** cheks if it is filted 
  * @return if there are filtered
**/

bool is_filtered_verbose();
/**
* check if vervose is filted something 
* @param filter is the filter text
**/
bool is_filtered_verbose_of(char* filter);
#endif
