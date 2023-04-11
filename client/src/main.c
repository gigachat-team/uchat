#include "../client.h"
#include <stdlib.h>

// void handle_chatting(t_address server_address, id_t user_id, id_t chat_id)
// {
//     while (true)
//     {
//         printf("\nEnter a command (send, last_messages, members, add_member, remove_member, exit): ");
//         char command[100];
//         scanf("%s", command);

//         if (strcmp(command, "send") == 0)
//         {
//             // t_text_message_data text_message_data = get_text_message_data(user_id, chat_id);
//             // t_state_code response = rq_send_text_message(server_address, text_message_data);
//             // if (response == TEXT_MESSAGE_SENT_SUCCESSFULLY)
//             // {
//             //     printf("Sent successfully.\n");
//             // }
//             // free_text_message_data(text_message_data);
//         }
//         else if (strcmp(command, "last_messages") == 0)
//         {
//             uint16_t messages_count = 0;
//             t_user_message *messages = rq_get_last_messages(server_address, UINT32_MAX, LAST_LOADING_MESSAGES_COUNT, chat_id, &messages_count);
//             for (size_t i = 0; i < messages_count; i++)
//             {
//                 char datetime[DEFAULT_TIME_FORMAT_LEN];
//                 strftime(datetime, DEFAULT_TIME_FORMAT_LEN, DEFAULT_TIME_FORMAT, &messages[i].creation_date);
//                 printf("%s, login: %s, message: %s\n", datetime, messages[i].user_login, messages[i].bytes);
//             }
//             free_user_messages(messages, messages_count);
//         }
//         else if (strcmp(command, "members") == 0)
//         {
//             uint32_t members_count = 0;
//             t_user *members = rq_get_chat_members(server_address, chat_id, &members_count);
//             for (size_t i = 0; i < members_count; i++)
//             {
//                 printf("Id: %d; Login: %s\n", members[i].id, members[i].login);
//             }
//             free_users(members, members_count);
//         }
//         else if (strcmp(command, "add_member") == 0)
//         {
//             t_new_chat_member_data new_chat_member_data = get_new_chat_member_data(chat_id);
//             t_state_code adding_new_member_result = rq_add_new_member(server_address, new_chat_member_data);
//             if (adding_new_member_result == USER_SUCCESSFULLY_ADDED_TO_CHAT)
//             {
//                 printf("The user %s successfully added to the chat.\n", new_chat_member_data.member_login);
//             }
//             else if (adding_new_member_result == SUCH_USER_IS_ALREADY_IN_CHAT)
//             {
//                 printf("The user %s is already in the chat.\n", new_chat_member_data.member_login);
//             }
//             free_new_chat_member_data(new_chat_member_data);
//         }
//         else if (strcmp(command, "remove_member") == 0)
//         {
//             id_t user_id = console_input_int("Enter user id: ");
//             t_state_code response = rq_remove_member_from_chat(server_address, user_id, chat_id);
//             if (response == USER_REMOVED_FROM_CHAT_SUCCESSFULLY)
//             {
//                 printf("The user removed from the chat.\n");
//             }
//         }
//         else if (strcmp(command, "exit") == 0)
//         {
//             return;
//         }
//     }
// }

void create_new_chat_in_server(t_address server_address, id_t user_id, char *chat_name) {
    t_chat_creation_data chat_creation_data = get_chat_creation_data(user_id, chat_name);
    id_t created_chat_id = rq_create_chat(server_address, chat_creation_data);
    printf("Chat \"%s\" with id %u created successfully.\n", chat_creation_data.chat_name, created_chat_id);
    free_chat_creation_data(chat_creation_data);
}

void send_message_in_server(t_address server_address, id_t user_id, id_t chat_id, char *text_message) {
    t_text_message_data text_message_data = { user_id, chat_id, strdup(text_message) };
    t_state_code response = rq_send_text_message(server_address, text_message_data);
    if (response == TEXT_MESSAGE_SENT_SUCCESSFULLY) {
        printf("Sent successfully.\n");
    }
    free_text_message_data(text_message_data);
}

static GtkBuilder *create_gtk_builder() {
    GError *err = NULL;
    GtkBuilder *builder = gtk_builder_new();

    if (gtk_builder_add_from_file(builder, GLADE_FILE_PATH, &err) == 0) {
        fprintf(stderr, "Error adding build from file. Error: %s\n", err->message);
        exit(EXIT_FAILURE);
    }

    return builder;
}

static t_gui_data create_gui_data(char *ip, in_port_t port) {
    t_gui_data gui_data = {
        .builder = create_gtk_builder(),
        .server_address = {ip, port},
        .user_id = 0
    };
    return gui_data;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(USAGE_MESSAGE);
        return EXIT_FAILURE;
    }

    gtk_init(&argc, &argv);
    load_css(DEFAULT_CSS_FILE_PATH);
    t_gui_data gui_data = create_gui_data(argv[1], atoi(argv[2]));
    gtk_builder_connect_signals(gui_data.builder, &gui_data);
    open_window(gui_data.builder, "Authorization");
    gtk_main();
    g_object_unref(gui_data.builder);

    return EXIT_SUCCESS;
}
