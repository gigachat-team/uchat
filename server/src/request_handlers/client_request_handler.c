#include "request_handlers.h"

void *handle_client_request_thread(void *allocated_client_socket) {
    int client_socket = *(int *)allocated_client_socket;
    free(allocated_client_socket);

    t_request client_request = receive_byte(client_socket);

    switch (client_request) {
    case LOGIN:
        handle_login(client_socket); break;
    case REGISTER:
        handle_registration(client_socket); break;
    case CREATE_CHAT:
        handle_chat_creation(client_socket); break;
    case ADD_MEMBER_TO_CHAT:
        handle_adding_new_member_to_chat(client_socket); break;
    case GET_CHATS_I_AM_IN:
        handle_getting_chats(client_socket); break;
    case SEND_TEXT_MESSAGE:
        handle_text_message_sending(client_socket); break;
    case GET_MESSAGES_IN_CHAT:
        handle_messages_in_chat_getting(client_socket); break;
    case SEND_MESSAGE_AND_GET_MESSAGE_UPDATES:
        handle_message_sending_and_messages_updates_getting(client_socket); break;
    case DELETE_MESSAGE_AND_GET_MESSAGE_UPDATES:
        handle_message_deleting_and_messages_updates_getting(client_socket); break;
    case CHANGE_MESSAGE_AND_GET_MESSAGE_UPDATES:
        handle_message_changing_and_message_updates_getting(client_socket); break;
    case REPLY_TO_MESSAGE_AND_GET_MESSAGE_UPDATES:
        handle_message_replying_and_message_updates_getting(client_socket); break;
    case GET_MESSAGE_UPDATES:
        handle_message_updates_getting(client_socket); break;
    case REMOVE_USER_FROM_CHAT:
        handle_removing_user_from_chat(client_socket); break;
    case GET_CHAT_MEMBERS:
        handle_getting_chat_members(client_socket); break;
    case CHANGE_LOGIN:
        handle_login_changing(client_socket); break;
    case DELETE_ACCOUNT:
        handle_account_deleting(client_socket); break;
    }

    close(client_socket);

    pthread_exit(NULL);
}
