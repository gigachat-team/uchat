#pragma once

#include "base_includes.h"
#include <pthread.h>

pthread_t create_default_thread(void *(*func)(void *), void *arg);

