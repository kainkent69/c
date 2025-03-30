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
  ASSERT_NOT_NULL(arena);
  // calculate
  ASSERT_EQUAL(arena->count, 1);
  ASSERT_NOT_NULL(arena->regions[0]);
  ASSERT_EQUAL((size_t) arena->regions[0], (size_t)region);
  ASSERT_EQUAL(arena->regions[0]->end, region->end);
  // get the occupied
  ASSERT_EQUAL(arena->occupied, 100);
  // region
  ASSERT_EQUAL((size_t) region->start, (size_t) arena + sizeof(Arena) );
  ASSERT_EQUAL(region->end, (size_t) arena + sizeof(Arena)  + 100);
  // freeing arena
  region_free(region);
  ASSERT_TRUE(arena->regions[0]->free);
  // free
  arena_free(arena);
}

CTEST(arena, ReAllocate){
  Arena *arena = create_arena(1024);
  Region *region = region_alloc(512);
  size_t region_start_original = (size_t)region;
  Region copy =  *region;
  ASSERT_EQUAL(copy.end, region->end); 
  ASSERT_NOT_NULL(region);

  CTEST_LOG("region->start %zu and end %zu", region->start, (size_t)region->end);
  ASSERT_EQUAL(region->start + 512, region->end);
  ASSERT_EQUAL(region->end - region->start, 512);
  // allocate bigger  memory
  region_reallocate(region, 256);
  ASSERT_EQUAL(region->diff, 256);
  ASSERT_EQUAL(region_capacity(region), 256);
  ASSERT_EQUAL(region_capacity((&copy)), region_capacity(region) + 256 ); // it should be less
  ASSERT_EQUAL(region->ID ,copy.ID);
  // Try freeing a region
  region_free(region);
  ASSERT_TRUE(arena->regions[region->ID]->free);
  ASSERT_EQUAL((size_t)arena->regions[region->ID],  region->start);

  // try reallocation 
  arena_free(arena);

}


CTEST(arena, ReAllocate_higher_than_original){
  Arena *arena = create_arena(2048);
  Region *region = region_alloc(512);
  size_t region_start_original = (size_t)region;
  Region copy =  *region;
  ASSERT_EQUAL(copy.end, region->end); 
  ASSERT_NOT_NULL(region);

  CTEST_LOG("region->start %zu and end %zu", region->start, (size_t)region->end);
  ASSERT_EQUAL(region->start + 512, region->end);
  ASSERT_EQUAL(region->end - region->start, 512);
  // allocate bigger  memory
  region = region_reallocate(region, 1024);
  ASSERT_EQUAL(region_capacity(region), 1024);
  ASSERT_EQUAL(region->ID, 1);
  ASSERT_EQUAL(arena->count, 2);

  // Try freeing a region
  region_free(region);
  ASSERT_TRUE(arena->regions[region->ID]->free);
  ASSERT_EQUAL((size_t)arena->regions[region->ID],  region->start);

  // try reallocation 
  arena_free(arena);
}


CTEST(arena, reuse_a_free_region){
  Arena *arena = create_arena(1024);
  Region *region = region_alloc(512);

  size_t region_start_original = (size_t)region;
  Region copy =  *region;
  ASSERT_EQUAL(copy.end, region->end); 
  ASSERT_NOT_NULL(region);

  // free arena 
  region_free(region);
  ASSERT_TRUE(arena->regions[region->ID]->free);
  ASSERT_EQUAL((size_t)arena->regions[region->ID], (size_t) region);
  CTEST_LOG("before: %zu\n", (size_t)region);
  // allocate area with the same size
  region = region_alloc(500);
  CTEST_LOG("after:%zu ", (size_t)region);
  // check if the id is still the same
  ASSERT_EQUAL(region->ID, copy.ID);
  ASSERT_EQUAL(region->ID, arena->regions[region->ID]->ID);

  // check if original start and the new is still the same
  ASSERT_EQUAL((size_t)region, region_start_original);
  ASSERT_NOT_NULL(region);
  ASSERT_EQUAL((size_t)arena->regions[copy.ID]->ID, (size_t) region->ID);
  // test the size of the end of the arena 
  CTEST_LOG("both ends, %zu, %zu\n", region->end , arena->regions[region->ID]->end);
  ASSERT_TRUE(region_capacity(region) < region_capacity((&copy)));
  ASSERT_EQUAL(region->end - region_start_original, region_capacity(region) + 12);
}
