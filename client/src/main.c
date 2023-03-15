#include "../client.h"

void handle_chatting(t_address server_address, id_t user_id, id_t chat_id) {
    while (true) {
        printf("\nEnter a command (send, last_messages, members, add_member, remove_member, exit): ");
        char command[100];
        scanf("%s", command);

        if (strcmp(command, "send") == 0) {
            t_text_message_data text_message_data = get_text_message_data(user_id, chat_id);
            t_state_code response = rq_send_text_message(server_address, text_message_data);
            if (response == TEXT_MESSAGE_SENT_SUCCESSFULLY) {
                printf("Sent successfully.\n");
            }
            free_text_message_data(text_message_data);
        } else if (strcmp(command, "last_messages") == 0) {
            uint16_t messages_count = 0;
            t_user_message *messages = rq_get_last_messages(server_address, UINT32_MAX, LAST_LOADING_MESSAGES_COUNT, chat_id, &messages_count);
            for (size_t i = 0; i < messages_count; i++) {
                char datetime[DEFAULT_TIME_FORMAT_LEN];
                strftime(datetime, DEFAULT_TIME_FORMAT_LEN, DEFAULT_TIME_FORMAT, &messages[i].creation_date);
                printf("%s, login: %s, message: %s\n", datetime, messages[i].user_login, messages[i].bytes);
            }
            free_user_messages(messages, messages_count);
        } else if (strcmp(command, "members") == 0) {
            uint32_t members_count = 0;
            t_user *members = rq_get_chat_members(server_address, chat_id, &members_count);
            for (size_t i = 0; i < members_count; i++)
            {
                printf("Id: %d; Login: %s\n", members[i].id, members[i].login);
            }
            free_users(members, members_count);
        } else if (strcmp(command, "add_member") == 0) {
            t_new_chat_member_data new_chat_member_data = get_new_chat_member_data(chat_id);
            t_state_code adding_new_member_result = rq_add_new_member(server_address, new_chat_member_data);
            if (adding_new_member_result == USER_SUCCESSFULLY_ADDED_TO_CHAT) {
                printf("The user %s successfully added to the chat.\n", new_chat_member_data.member_login);
            }
            else if (adding_new_member_result == SUCH_USER_IS_ALREADY_IN_CHAT) {
                printf("The user %s is already in the chat.\n", new_chat_member_data.member_login);
            }
            free_new_chat_member_data(new_chat_member_data);
        } else if (strcmp(command, "remove_member") == 0) {
            id_t user_id = console_input_int("Enter user id: ");
            t_state_code response = rq_remove_member_from_chat(server_address, user_id, chat_id);
            if (response == USER_REMOVED_FROM_CHAT_SUCCESSFULLY) {
                printf("The user removed from the chat.\n");
            }
        } else if (strcmp(command, "exit") == 0) {
            return;
        }
    }
}

void handle_authenticated_user_commands(t_address server_address, id_t user_id) {
    while (true) {
        printf("\nEnter a command (newchat, chats, enter_chat, exit): ");
        char user_command[100];
        scanf("%s", user_command);

        if (strcmp(user_command, "newchat") == 0) {
            // t_chat_creation_data chat_creation_data = get_chat_creation_data(user_id);
            // id_t created_chat_id = rq_create_chat(server_address, chat_creation_data);
            // printf("Chat \"%s\" with id %u created successfully.", chat_creation_data.chat_name, created_chat_id);
            // free_chat_creation_data(chat_creation_data);
        } else if (strcmp(user_command, "chats") == 0) {
            size_t chats_count = 0;
            t_chat *chats = rq_get_chats_i_am_in(server_address, user_id, &chats_count);
            if (chats_count != 0) {
                printf("Chats you're in:\n");
                for (size_t i = 0; i < chats_count; i++) {
                    printf("id: %i, name: %s\n", chats[i].id, chats[i].name);
                }
            }
            else {
                printf("You aren't in any chats.\n");
            }
            free_chats(chats, chats_count);
        } else if (strcmp(user_command, "enter_chat") == 0) {
            id_t chat_id = console_input_int("Enter chat id: ");
            handle_chatting(server_address, user_id, chat_id);
        } else if (strcmp(user_command, "exit") == 0) {
            return;
        }
    }
}

void create_new_chat_in_server(t_address server_address, id_t user_id, char *chat_name) {
    t_chat_creation_data chat_creation_data = get_chat_creation_data(user_id, chat_name);
    id_t created_chat_id = rq_create_chat(server_address, chat_creation_data);
    printf("Chat \"%s\" with id %u created successfully.", chat_creation_data.chat_name, created_chat_id);
    free_chat_creation_data(chat_creation_data);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: ./uchat [ip] [port]");
        return 0;
    }

    gui_init(argc, argv);

    return 0;
}

