#pragma once

#include "utils.h"
#include <syslog.h>
#include <signal.h>

/**
 * @return nothing but turns server into the daemon state
*/
void daemon_server();
