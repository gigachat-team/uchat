#include "../inc/threads.h"

pthread_t create_default_thread(void *(*func)(void *), void *arg) {
    pthread_t thread;
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    int result = pthread_create(&thread, &thread_attr, func, arg);
    if (result != 0) {
        fprintf(stderr, "pthread_create failed.\n");
        exit(EXIT_FAILURE);
    }
    return thread;
}

