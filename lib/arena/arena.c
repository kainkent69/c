#include "arena.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#ifndef LIB_ARENA_C
#define LIB_ARENA_C


size_t  _arena_default_region_count = 100;

Arena* create_arena(size_t capacity){
  Arena* arena = malloc(capacity + sizeof(Arena));
  void* address = (void*)((size_t) arena + sizeof(Arena));
  *arena = (Arena){.start=(size_t) address, .end = (size_t) address + capacity, .count=0, .occupied=0 };
  arena->regions = malloc(sizeof(Arena*) * _arena_default_region_count);
  arena->freed_regions = malloc(sizeof(Arena*) * _arena_default_region_count);
  return arena;
};


Region* region_allocate(Arena* arena, size_t size){
  assert(arena != NULL || arena->end - arena->start > arena->occupied + size);
  Region* region;
  region = (Region*)(arena->start + arena->occupied);
  *region=(Region){.start=(size_t)region, .parent=arena, .end = (size_t) region + size, .ID=arena->count, .prev=NULL, .next=NULL};
  arena->occupied += size;
  arena->regions[arena->count] = region;
  // setup if hte is next child
  if(!region_first_child(region)){
    region->prev = arena->regions[arena->count];
    if(arena->count >= 3) region->next = arena->regions[1];
  } 
  arena->count++;
  return region;
};

void arena_free(Arena *arena){
  free(arena->regions);
  free(arena->freed_regions);
  free(arena);
}


void region_free(Region *region){
  Arena* arena = region->parent;
  arena->freed_regions[region->ID] = arena->regions[region->ID];
  arena->regions[region->ID] = NULL;
}

#endif
