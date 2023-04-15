#include "client.h"

t_user_messages_array allocate_user_messages_array(size_t size) {
    t_user_messages_array user_messages_array = {
        .size = size,
        .arr = malloc(size * sizeof(t_user_message))
    };
    return user_messages_array;
}
