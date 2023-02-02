#include "../server.h"

/** most likely won't work in macos (aka shitos). Needed to track daemon in syslog file **/
void log_daemon_into_syslog() {
    int count = 0;

    openlog("Logs", LOG_PID, LOG_USER);

    while (true) {
        sleep(2);
        syslog(LOG_INFO, "logging: %d\n", count++);
    }

    closelog();
}

void daemon_server() {
    pid_t process_id = fork();
    pid_t sid = 0;

    if (process_id < 0) {
        perror("Creation of child process failed");
    }

    if (process_id > 0) {
        printf("Successfully created a proccess with the id of %d\n", process_id);
        exit(EXIT_SUCCESS);
    }

    umask(0);
    sid = setsid();

    if (sid < 0) {
        perror("Creation of session falied");
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    //log_daemon_into_syslog();
}
