#include "../inc/libmx.h"

char *mx_trim_front(char *str, int count) {
    char *new_str = mx_strdup(str + count);
    free(str);
    return new_str;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (lineptr == NULL || buf_size <= 0 || fd < 0) {
        return -2;
    }

    static char *buffer = NULL;
    int read_symbols_count = 0;
    int read_file_state;

    if (buffer != NULL) {
        *lineptr = buffer;
        buffer = NULL;
        read_symbols_count += mx_strlen(*lineptr);
    }
    buffer = mx_strnew(buf_size);

    while (true) {
        read_file_state = read(fd, buffer, buf_size);
        if (read_file_state == -1) {
            return -2;
        }
        for ( ; buffer[0] != '\0'; ) {
            if (*buffer == delim) {
                buffer = mx_trim_front(buffer, 1);
                return read_symbols_count;
            }
           *lineptr = mx_realloc(*lineptr, read_symbols_count + 1);
            (*lineptr)[read_symbols_count++] = *buffer;

            buffer = mx_trim_front(buffer, 1);
        }
    }
}

