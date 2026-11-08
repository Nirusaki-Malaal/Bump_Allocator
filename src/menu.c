#include <stdlib.h>
#include <stdio.h>

#include "allocator.h"
#include "menu.h"

// macros
#define MENU "====================================\n          NEUTRON ALLOCATOR\n====================================\n\n  1. Allocate Memory\n  2. View Memory Stats\n  3. Reset Allocator\n  4. Exit\n\n====================================\n  Select an option: "

int run_menu(void) {
    // main function wrapped in a switch statement
    unsigned char *ptr = bump_create();

    if (ptr == NULL) {
        printf("Unable to create mmap ");
        return -1;
    }
    // print the menu
    printf("%s", MENU);
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
        printf("%s", MENU);
    }
    exit_menu: // better code
        if (bump_destroy(ptr) != 0){
            return EXIT_FAILURE;
        } else {
            return EXIT_SUCCESS;
        }

}
