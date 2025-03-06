#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "readFile.h"

extern struct File *readFile(char *const path, char *const modes) {
  struct File* file = malloc(sizeof(struct File));
  char buffer[1024];
  FILE *fp = fopen(path, modes);
  file->buffer = malloc(100 * sizeof(char));
  while ((fgets(buffer, 1023, fp)) != NULL) {
    size_t len = strlen(buffer);
    char* nbuff= realloc(file->buffer, (file->size + len + 1) * sizeof(char)); 
    if(nbuff == NULL){
    }
    if(file->size <= 0){
      memcpy(nbuff, file->buffer, file->size + len );
    } else {
      strcat(nbuff, buffer);
    }
    file->buffer = nbuff;
    file->size += len;
  }
  return file;
}



