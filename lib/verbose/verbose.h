#include <stdlib.h>
#include <stdbool.h>
#ifndef LIB_VERBOSE_H
#define LIB_VERBOSE_H

/** It Needs Verbosity **/
#define IS_VERBOSE sys_verbose
#define FILTERING_ENABLED getenv("FILTER") != NULL
#define FILTER_CONTENTS FILTERING_ENABLED ? getenv("FILTER"): NULL

/** 
  * is_verbose checks if it is verbose (looks for "VERBOSE" env)
  * @return is weather it is verbose or not 
*/
#endif
