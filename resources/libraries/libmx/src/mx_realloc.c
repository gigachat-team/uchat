#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    void *new;

    if (!ptr) {
        new = malloc(size);
    } else {
        if (malloc_size(ptr) < size) {
            new = malloc(size);
            mx_memcpy(new, ptr, malloc_size(ptr));
            free(ptr);
        } else {
            new = ptr;
        }
    }

    return new;
}

