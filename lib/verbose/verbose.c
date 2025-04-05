#include "verbose.h"
#include <string.h>
#include <regex.h>
#include <ctype.h>
#ifndef LIB_VERBOSE_C
#define LIB_VERBOSE_C

bool is_verbose(){
  return getenv("VERBOSE") != NULL;
}


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

bool is_filtered(char *filter, char *regex_pattern) {

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

char* filtered_verbose(){
  if(is_verbose()){
    return getenv("FILTER_V");
  }
  return NULL;
};


bool is_filtered_verbose(){
  return getenv("FILTER_V") != NULL;
}



bool is_filtered_verbose_of(char* filter){
  if(!is_filtered_verbose()){
    return is_verbose();
  }
  bool filtered = is_filtered(filtered_verbose(), filter);
  return is_verbose() && filtered; 
};



#endif
