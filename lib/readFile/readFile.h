#include <stdlib.h>
#include <stdint.h>
struct File {
  size_t size;
  char *buffer;
};

struct File *readFile(char *const path, char *const modes);


