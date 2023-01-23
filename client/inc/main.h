#pragma once

#include "../../utils/inc/base_includes.h"
#include "../../utils/inc/socket.h"
#include "../../utils/inc/requests.h"
#include "../../utils/inc/state_codes.h"
#include "../../utils/inc/recievers.h"
#include "../../utils/inc/senders.h"
#include "authentication.h"

t_authentication_data get_authentication_data();
void free_authentication_data(t_authentication_data authentication_data);

