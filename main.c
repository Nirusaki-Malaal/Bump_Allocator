#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>


// macros
#define MENU printf("====================================\n          NEUTRON ALLOCATOR\n====================================\n\n  1. Allocate Memory\n  2. View Memory Stats\n  3. Reset Allocator\n  4. Exit\n\n====================================\n  Select an option: ")

// constants
const size_t heap_size = 4096;

// global variable
size_t used_size = 0;


void reset(unsigned char* ptr) {
    // reset the allocator simple to implement
    memset(ptr, 0, heap_size); // set the whole space to zero
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
    if (mem_size == 0 || used_size > heap_size || mem_size > heap_size - used_size) {
        printf("Invalid Memory Size\n");
        return NULL;
    }
    unsigned char* ptr1 = mmap_ptr + used_size;
    used_size += mem_size;
    return ptr1;
}

int main(void) {
    // main function wrapped in a switch statement
    unsigned char *ptr = mmap(NULL, heap_size, PROT_READ | PROT_WRITE ,MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if(ptr == MAP_FAILED)  {
        printf("Unable to create mmap ");
        return -1;
    }
    // print the menu
    MENU;
     while(1) {
        size_t choice;
        int print = scanf("%zu", &choice);
        if (print == EOF) {
            goto exit_menu;
        }
        else if(print != 1) {
            int ch; // if the choice is invalid
            while ((ch = getchar()) != '\n' && ch != EOF) {
                // flushses the input buffer
            }
            printf("[ERROR] Invalid Unsupported Input\n");
            continue;
        }
        printf("%zu\n", choice);
        switch(choice) {
            case 1:
                printf("How Much Memory You Want To  (In bytes)\n");
                size_t mem_size;
                int result = scanf("%zu" , &mem_size);
                if (result == EOF) {
                    goto exit_menu;
                }

                if (result != 1) {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {
                        // flushes the input buffer
                    }
                    printf("[ERROR] Invalid Unsupported Input\n");
                    break;
                }

                unsigned char* allocated_ptr = allocate(ptr, mem_size);
                allocated_ptr != NULL ? printf("\n[*] Allocated Successfully\n%p\n", (void *)allocated_ptr) : printf("[ERROR] Invalid Unsupported Input\n");
                break;
            case 2:
                stats();
                break;
            case 3:
                reset(ptr);
                printf("\nReset Successful\n");
                break;
            case 4:
                printf("\n");
                goto exit_menu;
            default:
                printf("\nInvalid Input Try Again\n");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {
                    // flushses the input buffer
                }
                break;
        }
        MENU;
    }
    exit_menu: // better code
        if (munmap(ptr, heap_size) != 0){
            return EXIT_FAILURE;
        } else {
            return EXIT_SUCCESS;
        }

}
