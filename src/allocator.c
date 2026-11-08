#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>

#include "allocator.h"

// constants
const size_t heap_size = 4096;

// global variable
size_t used_size = 0;


unsigned char* bump_create(void) {
    // sets up the mmap region the bump pointer walks over
    unsigned char *ptr = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (ptr == MAP_FAILED) {
        return NULL;
    }
    return ptr;
}

int bump_destroy(unsigned char* ptr) {
    // gives the whole region back to the OS
    if (munmap(ptr, heap_size) != 0) {
        return -1;
    }
    return 0;
}

void reset(unsigned char* ptr) {
    // reset the allocator simple to implement
    used_size = 0;
}

void stats(void) {
    // shows the stats of the allocator
    printf("\nHeap Size   :  %zu\n", heap_size);
    printf("Used Memory   :  %zu\n" , used_size);
    printf("Free Memory   :  %zu\n", heap_size-used_size);
}

unsigned char* allocate(unsigned char* mmap_ptr,size_t mem_size) {
    // allocate the memory with bound safety checks
    if (mem_size == 0 || mem_size > heap_size - used_size) {
        printf("Invalid Memory Size\n");
        return NULL;
    }
    unsigned char* ptr1 = mmap_ptr + used_size;
    used_size += mem_size;
    return ptr1;
}
