#pragma once

#include "base_includes.h"
#include <pthread.h>

pthread_t create_default_thread(void *(*func)(void *), void *arg);
void create_detached_thread(void *(*func)(void *), void *arg);
void join_thread(pthread_t thread, void **thread_return);
void cancel_thread(pthread_t thread);

