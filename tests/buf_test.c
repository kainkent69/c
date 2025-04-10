#include "../ctest/ctest.h"
#include "../lib/buffer/buffer.h"
#include <assert.h>
#include <stdio.h>

#define EQ ASSERT_EQUAL
#define EQZU(a, b) ASSERT_EQUAL((size_t)a, (size_t)b)
#define EQU ASSERT_EQUAL_U
#define NUL ASSERT_NULL
#define NNUL ASSERT_NOT_NULL

void loop(void *mem, size_t size, size_t start, size_t len,
          void func(void *mem)) {
  for (int i = start; i < len; i++) {
    void *imem = mem + (i * size);
    func(imem);
  }
}
void printnums(void *number) { printf(" %d", *((int *)number)); }

CTEST(buf_test, test) {
  puts("TESTING: BUFFERS");
  puts("Creating Buffers");
  buf_t *buf = buf_new(4 * 10); // 10
  int *nums = (int *)buf->start;
  printf("buf_test: new buffer created [%p]\n", buf);
  assert(buf != NULL);
  EQ((size_t)buf->end, (size_t)buf->start + 40);
  EQ((size_t)buf->next, (size_t)buf->start);
  EQ(buf_available((*buf)), 40);
  EQ(buf_size((*buf)), 40);
  EQ(buf_occupied((*buf)), 0);
  puts("buf_test: initializing the memory");
  // just printing
  printf("buf_test: before the init [");
  loop(buf->start, 4, 0, 10, printnums);
  printf(" ]\n");
  loop(buf->start, 4, 0, 10, printnums);
  for (int i = 0; i < 10; i++) {
    int num = i + 1;
    buf_set_next(buf, &num, 4);
    printf("occupied %zu\n", buf_occupied((*buf)));
    EQ((size_t)buf->next, (size_t)(buf->start + ((i + 1) * 4)));
    EQ(buf_occupied((*buf)), (size_t)((i + 1) * 4));
  }

  // assume that the initialization is done
  EQ(buf_occupied((*buf)), 40);
  printf("\nbuf_test: after the init [");
  loop(buf->start, 4, 0, 10, printnums);
  printf(" ]\n");

  // no need but just for visual
  for (int i = 0; i < 10; i++) {
    int *imem = (int *)buf->start + i;
    EQ(*imem, nums[i]);
    EQ(*imem, i + 1);
  }

  puts("buf_test:growing the buf");
  buf_grow(buf, 20);

  NNUL(buf);
  EQZU(buf->next, buf->start + 40);
  EQZU(buf->end, buf->start + 60);
  EQZU(buf_available((*buf)), 20);
  EQZU(buf_size((*buf)), 60);
  EQZU(buf_occupied((*buf)), 40);

  // initializing the buf
  for (int i = 15; i > 10; i--) {
    int value = 1000 + i;
    buf_set(buf, &value, (buf->start + ((i - 1) * 4 )), 4, true);
  }


  // getting the new thing of it
  for (size_t i = 0; i < 15; i++) {
    if (i < 10) {
      EQ(nums[i], i + 1);
    } else {
      EQ(nums[i], i + 1000 + 1);
    }

  }
}
