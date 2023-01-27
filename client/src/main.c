#include "../client.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: ./uchat [ip] [port]");
        return 0;
    }

    init_authentication(argv[1], atoi(argv[2]));

    while (true)
    {
        printf("\nEnter a command (login, register, exit): ");
        char user_command_str[1024];
        scanf("%s", user_command_str);

        if (strcmp(user_command_str, "login") == 0) {
            t_authentication_data authentication_data = get_authentication_data();

            t_state_code login_result = authenticate_user(authentication_data, LOGIN_MODE);
            if (login_result == SUCCESSFUL_LOGIN) {
                printf("Successful login.\n");
            } else if (login_result == SUCH_LOGIN_DOES_NOT_EXIST) {
                printf("Such login does not exist.\n");
            } else if (login_result == WRONG_PASSWORD) {
                printf("Wrong password.\n");
            }
        } else if (strcmp(user_command_str, "register") == 0) {
            t_authentication_data authentication_data = get_authentication_data();

            t_state_code registration_result = authenticate_user(authentication_data, REGISTER_MODE);
            if (registration_result == SUCCESSFUL_REGISTRATION) {
                printf("Successful registration.\n");
            } else if (registration_result == SUCH_LOGIN_ALREADY_EXISTS) {
                printf("Such login already exists.\n");
            }
        } else if (strcmp(user_command_str, "exit") == 0) {
            return 0;
        }
    }

    return 0;
}

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

void free_authentication_data(t_authentication_data authentication_data) {
    free(authentication_data.login);
    free(authentication_data.password);
}

