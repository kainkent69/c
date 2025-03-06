#include "buffers.h"

int main() {
  void *bufferc = malloc(10 * sizeof(int));
  Buffer *buffer = bufftrack(bufferc, sizeof(int), 10);
  int *newmem = (int *)buffer->next;
  printf("the newmeme %d\n", (int *)newmem == NULL);
  printf("the next %zu\n", (size_t)buffer->next);
  buffbefore_fill(buffer, sizeof(int));
  *newmem = 2;
  buffill(buffer, sizeof(int));
  int *content = buffer->buffer;
  buff_append(buffer, sizeof(int), int *, 16000);
  printf("this is the first content %d\n", content[0]);
  printf("this is the second content %d\n", content[1]);
  for (int i = 0; i < buffer->len; i++) {
    printf("the element mem %zu, the value %d, dont forget the size of %zu\n",
           (size_t)buffer->elements[i], *((int *)buffer->elements[i]),
           sizeof(int));
  }
  buffreeall(buffer);
  return 0;
}
