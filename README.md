# NEUTRON ALLOCATOR

A tiny bump (arena) allocator written in C. It reserves one fixed heap with
`mmap`, then hands out memory by simply moving a pointer forward. Freeing is
instant: you reset the whole allocator and start over.

## Layout

```
include/allocator.h   allocator API
include/menu.h        menu API
src/allocator.c       mmap setup, allocate / reset / stats
src/menu.c            interactive menu loop
src/main.c            entry point
```

## Build

```sh
make        # produces ./neutron
make run    # build and start
make clean  # remove build artifacts
```

## Usage

```
====================================
          NEUTRON ALLOCATOR
====================================

  1. Allocate Memory
  2. View Memory Stats
  3. Reset Allocator
  4. Exit

====================================
  Select an option:
```

1. **Allocate Memory** — asks for a size in bytes and returns a pointer into
   the heap. Fails if the request is `0` or larger than the free space.
2. **View Memory Stats** — prints heap size, used and free bytes.
3. **Reset Allocator** — sets the bump pointer back to the start.
4. **Exit** — unmaps the heap and quits.

## Notes

- Heap size is fixed at `4096` bytes (`heap_size` in `src/allocator.c`).
- Memory is never individually freed; use reset to reclaim it all.
- Requests are bump-only: no reuse of previously allocated blocks.
