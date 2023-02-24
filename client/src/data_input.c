#include "../client.h"

t_authentication_data get_authentication_data(GtkWidget *enter_login, GtkWidget *enter_password)
{
    t_authentication_data authentication_data;

    authentication_data.login = (char *)gtk_entry_get_text(GTK_ENTRY(enter_login));
    authentication_data.password = (char *)gtk_entry_get_text(GTK_ENTRY(enter_password));

    return authentication_data;
}

t_chat_creation_data get_chat_creation_data(int owner_id)
{
    printf("Enter the chat name: ");
    char chat_name[MAX_CHAT_NAME_LENGTH];
    scanf("%s", chat_name);

    t_chat_creation_data chat_creation_data = {strdup(chat_name), owner_id};
    return chat_creation_data;
}

t_new_chat_member_data get_new_chat_member_data()
{
    printf("Enter chat id: ");
    int chat_id;
    scanf("%d", &chat_id);

    printf("Enter new member login: ");
    char member_login[MAX_LOGIN_LENGTH];
    scanf("%s", member_login);

    t_new_chat_member_data new_chat_member_data = {chat_id, strdup(member_login)};
    return new_chat_member_data;
}

int get_chat_id()
{
    printf("Enter chat id: ");
    int chat_id;
    scanf("%d", &chat_id);
    return chat_id;
}

t_text_message_data get_text_message_data(uint32_t user_id, uint32_t chat_id)
{
    printf("Enter text message: ");
    char text_message[1000];
    scanf("%s", text_message);

    t_text_message_data text_message_data = {user_id, chat_id, strdup(text_message)};
    return text_message_data;
}
