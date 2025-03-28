#include "../lib/arena/arena.h"
#include "./ctest/ctest.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

CTEST(arena, Initialization) {
  Arena *arena = create_arena(1024);
  ASSERT_EQUAL((size_t)arena, (size_t)arena->start - sizeof(Arena));
  ASSERT_EQUAL(arena->count, 0);
}


// allocation the tokens
CTEST(arena, Allocation) {
  Arena *arena = create_arena(1024);
  Region *region = region_alloc(100);
  // calculate
  ASSERT_EQUAL(arena->count, 1);
  ASSERT_NOT_NULL(arena->regions[0]);
  ASSERT_EQUAL(arena->regions[0]->start, region->start);
  ASSERT_EQUAL(arena->regions[0]->end, region->end);
  // get the occupied
  ASSERT_EQUAL(arena->occupied, 100);
  // freeing arena
  region_free(region);
  ASSERT_NOT_NULL(arena->freed_regions[0]);
  ASSERT_NULL(arena->regions[0]);

  ASSERT_EQUAL(arena->freed_regions[0]->start, region->start);
  ASSERT_EQUAL(arena->freed_regions[0]->end, region->end);
  // free
  arena_free(arena);
}

CTEST(arena, ReAllocate){
  Arena *arena = create_arena(1024);
  Region *region = region_alloc(100);
}
