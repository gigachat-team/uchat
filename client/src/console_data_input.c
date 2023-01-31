#include "../client.h"

t_authentication_data get_authentication_data() {
    t_authentication_data authentication_data;

    printf("Enter login: ");
    char login[MAX_LOGIN_LENGTH];
    scanf("%s", login);

    printf("Enter password: ");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    authentication_data.login = mx_strdup(login);
    authentication_data.password = mx_strdup(password);

    return authentication_data;
}

t_chat_creation_data get_chat_creation_data(char *owner_login) {
    printf("Enter the chat name: ");
    char chat_name[MAX_CHAT_NAME_LENGTH];
    scanf("%s", chat_name);

    t_chat_creation_data chat_creation_data = {strdup(chat_name), strdup(owner_login)};
    return chat_creation_data;
}

t_new_chat_member_data get_new_chat_member_data() {
    printf("Enter chat id: ");
    int chat_id;
    scanf("%d", &chat_id);

    printf("Enter new member login: ");
    char member_login[MAX_LOGIN_LENGTH];
    scanf("%s", member_login);

    t_new_chat_member_data new_chat_member_data = {chat_id, strdup(member_login)};
    return new_chat_member_data;
}

