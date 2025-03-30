#include "arena.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#ifndef LIB_ARENA_C
#define LIB_ARENA_C

size_t _arena_default_region_count = 100;

Arena *create_arena(size_t capacity) {
  Arena *arena = malloc(capacity + sizeof(Arena));
  void *address = (void *)((size_t)arena + sizeof(Arena));
  *arena = (Arena){.start = (size_t)address,
                   .end = (size_t)address + capacity,
                   .count = 0,
                   .occupied = 0};
  arena->regions = malloc(sizeof(Arena *) * _arena_default_region_count);
  return arena;
};

Region *region_reuse(Arena *arena, size_t size) {
  puts("reuse");
  for (size_t i = 0; i < arena->count; i++) {
    puts("reusing");
    Region *region = arena->regions[i];
    if (region->free && region->end - region->start > size) {
      if (region != NULL)
        puts("reused: region is not null");
      region->free = false;
      if (region_capacity(region) > size) {
            puts("reusing with different size");
        size_t diff = region_capacity(region) - size;
        printf("the end %zu, size %zu and diff %zu\n", region->end, size, diff);
        region->diff = diff;
        printf("new end %zu", region->end);
      };
      return region;
    }
  }
  return NULL;
}

Region *region_allocate(Arena *arena, size_t size) {
  assert(arena != NULL || arena->end - arena->start > arena->occupied + size);
  Region *reuse = region_reuse(arena, size);
  if (reuse != NULL)
    return reuse;

  // create the region
  Region *region;
  region = (Region *)(arena->start + arena->occupied);
  printf("region: %zu\n", (size_t)region);
  *region = (Region){.ID=arena->count,.diff=0, .start=(size_t)region, .end = (size_t)region+ size};
  region->parent = arena;
  // add what is occupied
  arena->occupied += size;
  arena->regions[arena->count] = region;
  // setup if hte is next child
  arena->count++;
  return region;
};


Region *region_reallocate(Region *_region, size_t size) {
  putchar('\n');
  Arena *arena = (Arena *)_region->parent;
  Region *region = region_reuse(arena, size);
  if (region != NULL)
    return region;
  ;
  size_t capacity = region_capacity(_region);
  // if it is the last memory

  if (_region->ID == arena->count || capacity > size) {
    puts("capacity is less than  size");
    // create a new region to avoid conflict
    Region *region = arena->regions[_region->ID];
    // if the region memory is higher than needed
    if (capacity >= size) {
      size_t diff = capacity - size;
      region->diff = diff;
      return region;
    }

    // continue to process if the_region->ID
    region->end = region->start + size;
    arena->occupied += size - capacity;
    return region;
  }

  puts("normal region reallocation");
  // contineu then it means that new allocation is goig to be used
  region_free(_region);
  region = region_allocate(arena, size);
    printf("The new allocated rgion id %zu couont %zu\n", region->ID, arena->count );
  assert(region != NULL);
  return region;
}

void arena_free(Arena *arena) {
  free(arena->regions);
  free(arena);
}

void region_free(Region *region) {
  Arena *arena = region->parent;
  assert(region != NULL && arena != NULL);
  Region* _region = arena->regions[region->ID];
   _region->free = true;
    _region->diff = 0;
}

#endif
