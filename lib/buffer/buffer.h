#ifndef LIB_BUFFER_H
#define LIB_BUFFER_H
// auto growing buffers
#if defined(BUFFER_AUTO_GROW)
#define BUFFER_GROW_AUTO true
#else
#define BUFFER_GROW_AUTO false
#endif

#ifndef BUFF_T
#define BUFF_T
#include <stddef.h>
#include <stdbool.h>

typedef struct buf_t {
    char *end;
    char *next;
    char *start;
} buf_t;

#endif

// define the  helpers for the buffers
#ifdef BUFF_T
#define buf_occupied(buf) ((size_t)(buf.next - buf.start))
#define buf_available(buf) ((size_t)(buf.end - buf.next))
#define buf_size(buf)((size_t)(buf.end - buf.start))
// functions
buf_t *buf_new(size_t wide);
buf_t *buf_grow(buf_t* buf, size_t wide);
void *buf_set_next(buf_t* buf, void* src,  size_t wide);
void *buf_set(buf_t* buf, void* src, void* where,  size_t wide, bool incr);
void *buf_set_incr(buf_t* buf, void* src, void* where,  size_t wide);
void* buf_skip(buf_t* buf, size_t fwd);


#endif

#endif
