#include "../../client.h"

t_authentication_data get_authentication_data(GtkWidget *enter_login, GtkWidget *enter_password) {
    t_authentication_data authentication_data;

    authentication_data.login = (char *)gtk_entry_get_text(GTK_ENTRY(enter_login));
    authentication_data.password = (char *)gtk_entry_get_text(GTK_ENTRY(enter_password));

    return authentication_data;
}

t_chat_creation_data get_chat_creation_data(id_t owner_id, char *chat_name) {

    t_chat_creation_data chat_creation_data = {strdup(chat_name), owner_id};
    return chat_creation_data;
}

t_new_chat_member_data get_new_chat_member_data(id_t chat_id) {
    printf("Enter new member login: ");
    char member_login[MAX_LOGIN_LENGTH];
    scanf("%s", member_login);

    t_new_chat_member_data new_chat_member_data = {chat_id, strdup(member_login)};
    return new_chat_member_data;
}

int console_input_int(char *message) {
    printf("%s", message);
    int number;
    scanf("%d", &number);
    return number;
}

t_text_message_data get_text_message_data(id_t user_id, id_t chat_id) {
    printf("Enter text message: ");
    char text_message[1000];
    scanf("%s", text_message);

    t_text_message_data text_message_data = {user_id, chat_id, strdup(text_message)};
    return text_message_data;
}
