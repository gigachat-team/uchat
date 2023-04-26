#include "server_receivers.h"

t_id_and_changes_count_array receive_id_and_changes_count_array(int client_socket) {
    t_id_and_changes_count_array id_and_changes_count_array = create_id_and_changes_count(receive_uint32(client_socket));
    for (size_t i = 0; i < id_and_changes_count_array.len; i++) {
        id_and_changes_count_array.arr[i].id = receive_uint32(client_socket);
        id_and_changes_count_array.arr[i].changes_count = receive_byte(client_socket);
    }
    return id_and_changes_count_array;
}
