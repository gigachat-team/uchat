#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * @return nothing but turns server into the daemon state
*/
void daemon_server();
