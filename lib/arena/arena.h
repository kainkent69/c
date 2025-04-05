
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef LIB_ARENA_H
#define LIB_ARENA_H

#define set_arena_default_region_count(count) _arena_default_region_count = (size_t) count;


typedef struct Region {
   void*  parent;                      // The Arena address
   size_t    end,                      // The end of the memory  to get the capacity 
              ID,                      // The  ID of the region should be base 0
           start,                      // The start or the memory of the array
            diff;                      // The allownce of storage when used
   bool     free;                      // If the region is freed
} Region;



typedef struct Arena {
    size_t     start,                  // the start of the memroy 
                 end,                  // the end of the memory to make easy calculation 
            occupied,                  // The number of bytes being filled 
               count;                  // The number of regions made
    Region** regions;                  // the regions an multi-deminsional array
} Arena;


// for making linked list
/** get the next region **/
#define region_next(region) (arena->regions[region->ID + 1])
/** get the previews region **/
#define region_prev(region) (region->ID > 0 ? arena->regions[region->ID + 1] : NULL;)
/** get the start of the region **/
/** The capacity of a region **/ 
#define region_capacity(region) (region->end - region->start - region->diff)
/** See if the region is the first child **/
#define region_first_child(region ) (region->ID == 0)
/** Realloc allocate region from arena **/
#define region_alloc(size) region_allocate(arena, size)

/**
 * Initialize a new arena
 * @param capacity is the size of the :w:w
 * @return a new arena
 **/
Arena* create_arena(size_t capacity);

/**
 * allocate a region for the arena
 * @param *arena is the source arena
 * @param size is the number of bytes to save
 * @return a newly created reagion
 **/
Region* region_allocate(Arena* arena, size_t size); 


/**
 * allocate a region for the arena
 * @param *arena is the source arena
 * @param size is the number of bytes to save
 * @return a newly created reagion
 **/
Region* region_reallocate( Region* region, size_t size);
/**
 * allocate a region for the arena
 * @param *arena is the source arena
 * @param size is the number of bytes to save
 * @return a newly created reagion
 **/
Region* region_allocate(Arena* arena, size_t size); 
/**
 * free a region meaning see the freed region
 * @param *region is the region to be freed
 * @return  true if there is nothing wrong
 **/
void region_free(Region* region);

/**
 * frees up an arane
 * @param *arena is the arena to be freed
 **/
void arena_free(Arena* arena);



#endif
