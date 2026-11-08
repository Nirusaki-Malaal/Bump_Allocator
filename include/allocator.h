#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

// constants
extern const size_t heap_size;

// sets up the backing heap
unsigned char* bump_create(void);

// allocate the memory with bound safety checks
unsigned char* allocate(unsigned char* mmap_ptr, size_t mem_size);

// reset the allocator simple to implement
void reset(unsigned char* ptr);

// shows the stats of the allocator
void stats(void);

// releases the backing heap
int bump_destroy(unsigned char* ptr);

#endif
