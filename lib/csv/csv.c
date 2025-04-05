#include "readFile.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

struct csv {
  size_t rows, columns;
};

void csv_read(vector* tokens, char* str) {
  char* next_token;
  char*  token = strtok_r(str, "\n", &next_token);
  printf("token:\n %s\n\n", token);
  printf("next_token:\n %s\n", next_token);
  size_t token_len = strlen(token);
  if(token_len){
    puts("new token");
    puts(token);
  } else {
    puts("no new token");
  }
  if(strlen(next_token)){
    csv_read(tokens, next_token );
  }
}

void csv_load(char *const path) {
  const struct File* file = readFile(path, "r");
  vector* tokens =  vcreate(sizeof(char*), 100);  
  csv_read(tokens, file->buffer);
}

int main() { csv_load("./test.html"); }
