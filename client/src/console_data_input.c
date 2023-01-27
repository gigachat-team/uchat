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

t_chat_data get_chat_data() {
    t_chat_data chat_data;
    
    printf("Enter chat name (Empty for no chat name): ");
    char chat_name[MAX_CHAT_NAME_LENGTH];
    scanf("%s", chat_name);

    printf("Enter the members' login through the space: ");
    char members_login_through_space[1000];
    scanf("%s", members_login_through_space);
    char **member_logins = mx_strsplit(members_login_through_space, ' ');

    chat_data.name = mx_strdup(chat_name);
    chat_data.member_logins = member_logins;

    return chat_data;
}

void free_authentication_data(t_authentication_data authentication_data) {
    free(authentication_data.login);
    free(authentication_data.password);
}

void free_chat_data(t_chat_data chat_data) {
    free(chat_data.name);
    mx_free_str_arr(&chat_data.member_logins);
}

