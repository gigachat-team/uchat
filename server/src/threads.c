#include "../server.h"

void *handle_request_thread(void *client_socket_void) {
    int client_socket = *(int *)client_socket_void;
    free(client_socket_void);

    t_request client_request = recieve_unsigned_char(client_socket);
    send_unsigned_char(client_socket, SUCCESSFULLY_READ);

    if (client_request == LOGIN) {
        handle_login(client_socket);
    } else if (client_request == REGISTER) {
        handle_registration(client_socket);
    } else if (client_request == CREATE_CHAT) {
        handle_chat_creation(client_socket);
    } else if (client_request == GET_CHATS_I_AM_IN) {
        handle_getting_chats(client_socket);
    }

    pthread_exit(NULL);
}

void *accept_requests_thread(void *listening_socket_void) {
    int listening_socket = *(int *)listening_socket_void;

    while (true)
    {
        int client_socket = accept_socket(listening_socket);
        pthread_testcancel();
        int *mallocated_client_socket = malloc(sizeof(int));
        *mallocated_client_socket = client_socket;
        create_detached_thread(handle_request_thread, mallocated_client_socket);
    }
}

