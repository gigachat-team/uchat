#include "../inc/threads.h"

pthread_t create_default_thread(void *(*func)(void *), void *arg) {
    pthread_t thread;
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    int result = pthread_create(&thread, &thread_attr, func, arg);
    if (result != 0) {
        fprintf(stderr, "Failed to create a thread.\n");
        exit(EXIT_FAILURE);
    }
    return thread;
}

void create_detached_thread(void *(*func)(void *), void *arg) {
    pthread_t thread = create_default_thread(func, arg);
    pthread_detach(thread);
}

void join_thread(pthread_t thread, void **thread_return) {
    if (pthread_join(thread, thread_return) != 0) {
        fprintf(stderr, "Failed to join the thread.\n");
        exit(EXIT_FAILURE);
    }
}

void cancel_thread(pthread_t thread) {
    if (pthread_cancel(thread) != 0) {
        fprintf(stderr, "Failed to cancel the thread.\n");
        exit(EXIT_FAILURE);
    }
}

