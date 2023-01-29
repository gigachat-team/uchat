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

