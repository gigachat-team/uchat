#include "../server.h"

void *handle_request_thread(void *client_socket_void) {
    int client_socket = *(int *)client_socket_void;
    free(client_socket_void);

    t_request client_request = receive_byte(client_socket);

    if (client_request == LOGIN) {
        handle_login(client_socket);
    } else if (client_request == REGISTER) {
        handle_registration(client_socket);
    } else if (client_request == CREATE_CHAT) {
        handle_chat_creation(client_socket);
    } else if (client_request == GET_CHATS_I_AM_IN) {
        handle_getting_chats(client_socket);
    } else if (client_request == ADD_MEMBER_TO_CHAT) {
        handle_adding_new_member_to_chat(client_socket);
    } else if (client_request == SEND_TEXT_MESSAGE) {
        handle_text_message_sending(client_socket);
    } else if (client_request == GET_LAST_MESSAGES) {
        handle_last_messages_getting(client_socket);
    } else if (client_request == REMOVE_USER_FROM_CHAT) {
        handle_removing_user_from_chat(client_socket);
    } else if (client_request == GET_CHAT_MEMBERS) {
        handle_getting_chat_members(client_socket);
    }

    close(client_socket);

    pthread_exit(NULL);
}

