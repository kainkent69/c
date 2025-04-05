#include "verbose.h"
#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../vector/vector.h"

#ifndef LIB_VERBOSE_C
#define LIB_VERBOSE_C

bool sys_verbose = false;



void trim_trailing_spaces(char *str) {
  if (str == NULL) {
    return;
  }

  size_t len = strlen(str);
  while (len > 0 && isspace((unsigned char)str[len - 1])) {

    str[len - 1] = '\0';
    len--;
  }
}



void set_verbosity_env(){
    sys_verbose = getenv("QUITE") != NULL;
}


bool is_filtered_with_pattern(char *filter, char *regex_pattern) {
  if (filter == NULL || regex_pattern == NULL) {
    return false; // Handle null input
  }
  trim_trailing_spaces(filter); // Trim trailing spaces

  regex_t regex;
  int ret;

  ret = regcomp(&regex, regex_pattern, REG_EXTENDED);

  if (ret != 0) {

    // Handle regex compilation error
    char error_message[100];
    regerror(ret, &regex, error_message, sizeof(error_message));
    regfree(&regex); // Free regex even on error

    return false;
  }

  ret = regexec(&regex, filter, 0, NULL, 0);
  regfree(&regex); // Free regex after use

  return (ret == 0); // Return true if match, false otherwise.
}




bool is_filtered_with(char *filter) {
  if (IS_VERBOSE  == false || (FILTERING_ENABLED )) return IS_VERBOSE;
    
  // TODO: filter it to separate contnte
  bool filtered = is_filtered_with_pattern(FILTER_CONTENTS, filter);
  return IS_VERBOSE && filtered;
};
/**
 * NOTE: DEVELOPERS, filter it using regix us e `|` as the separator 
 * NOTE: It is best used with the logger 
 **/
#endif
