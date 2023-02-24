#include "../client.h"

void handle_chatting(t_address server_address, uint32_t user_id, uint32_t chat_id)
{
    while (true)
    {
        printf("\nEnter a command (send, last_messages, exit): ");
        char command[100];
        scanf("%s", command);

        if (strcmp(command, "send") == 0)
        {
            t_text_message_data text_message_data = get_text_message_data(user_id, chat_id);
            t_state_code responce = rq_send_text_message(server_address, text_message_data);
            if (responce == TEXT_MESSAGE_SENT_SUCCESSFULLY)
            {
                printf("Sent successfully.\n");
            }
            free_text_message_data(text_message_data);
        }
        else if (strcmp(command, "last_messages") == 0)
        {
            uint32_t messages_count = 0;
            t_user_message *messages = rq_get_last_messages(server_address, LAST_LOADING_MESSAGES_COUNT, chat_id, &messages_count);
            for (size_t i = 0; i < messages_count; i++)
            {
                printf("user_login: %s, message: %s\n", messages[i].user_login, messages[i].bytes);
            }
            free_user_messages_array(messages, messages_count);
        }
        else if (strcmp(command, "exit") == 0)
        {
            return;
        }
    }
}

void handle_authenticated_user_commands(t_address server_address, int user_id)
{
    while (true)
    {
        printf("\nEnter a command (newchat, chats, add_member, enter_chat, exit): ");
        char user_command[100];
        scanf("%s", user_command);

        if (strcmp(user_command, "newchat") == 0)
        {
            t_chat_creation_data chat_creation_data = get_chat_creation_data(user_id);
            t_state_code creating_chat_result = rq_create_chat(server_address, chat_creation_data);
            if (creating_chat_result == CHAT_CREATED_SUCCESSFULLY)
            {
                printf("Chat \"%s\" created successfully.", chat_creation_data.chat_name);
            }
            free_chat_creation_data(chat_creation_data);
        }
        else if (strcmp(user_command, "add_member") == 0)
        {
            t_new_chat_member_data new_chat_member_data = get_new_chat_member_data();
            t_state_code adding_new_member_result = rq_add_new_member(server_address, new_chat_member_data);
            if (adding_new_member_result == USER_SUCCESSFULLY_ADDED_TO_CHAT)
            {
                printf("The user %s successfully added to the chat.\n", new_chat_member_data.member_login);
            }
            else if (adding_new_member_result == SUCH_USER_IS_ALREADY_IN_CHAT)
            {
                printf("The user %s is already in the chat.\n", new_chat_member_data.member_login);
            }
            free_new_chat_member_data(new_chat_member_data);
        }
        else if (strcmp(user_command, "chats") == 0)
        {
            t_chat *chats_i_am_in = NULL;
            size_t chats_i_am_in_length = 0;
            if (rq_get_chats_i_am_in(server_address, user_id, &chats_i_am_in, &chats_i_am_in_length) == CHATS_ARRAY_TRENSFERRED_SUCCESSFULLY)
            {
                printf("Chats you're in:\n");
                for (size_t i = 0; i < chats_i_am_in_length; i++)
                {
                    printf("id: %i, name: %s\n", chats_i_am_in[i].id, chats_i_am_in[i].name);
                }
            }
            free_chats(chats_i_am_in, chats_i_am_in_length);
        }
        else if (strcmp(user_command, "enter_chat") == 0)
        {
            int chat_id = get_chat_id();
            handle_chatting(server_address, user_id, chat_id);
        }
        else if (strcmp(user_command, "exit") == 0)
        {
            return;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("usage: ./uchat [ip] [port]");
        return 0;
    }

    gui_init(argc, argv);

    return 0;
}

