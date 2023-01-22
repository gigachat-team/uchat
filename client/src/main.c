#include "../inc/main.h"

t_state_code register_user(char *ip, int port, char *login, char *password) {
    int client_socket = create_socket();
    connect_socket(client_socket, ip, port);

    send_unsigned_char(client_socket, REGISTER);
    recieve_unsigned_char(client_socket);

    send(client_socket, login, strlen(login) + 1, 0);
    recieve_unsigned_char(client_socket);

    send(client_socket, password, strlen(password) + 1, 0);

    t_state_code registration_result = recieve_unsigned_char(client_socket);

    close(client_socket);

    return registration_result;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: ./uchat [ip] [port]");
        return 0;
    }

    while (true)
    {
        printf("Enter a command (login, register, exit): ");
        char user_command_str[1024];
        scanf("%s", user_command_str);

        if (strcmp(user_command_str, "login") == 0) {

        } else if (strcmp(user_command_str, "register") == 0) {
            printf("Enter new login: ");
            char login[MAX_LOGIN_LENGTH];
            scanf("%s", login);

            printf("Enter new password: ");
            char password[MAX_PASSWORD_LENGTH];
            scanf("%s", password);

            t_state_code registration_result = register_user(argv[1], atoi(argv[2]), login, password);
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

