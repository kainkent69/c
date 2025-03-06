#include "./buffers.h"
#include <stdio.h>
int main() {
  printf("Before All");
  Buffer *buffer = buffinit(1000 * 10, 10);
  for (size_t i = 0; i < 10; i++) {
    char words[100];
    size_t size = sprintf(words, "Hello world! for [%zu] times", i);
    char *wordlist = malloc((size + 1) * sizeof(char));
    printf("created a worklist\n");
    snprintf(wordlist, sizeof(words), "Hello world! for [%zu] times", i);
    printf("providing value for worklinst\n");
    buff_append_str(buffer, size, wordlist);
    free(wordlist);
  }
}
