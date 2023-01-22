#include "../inc/libmx.h"

char *mx_file_to_str(const char *file) {
	if (file == NULL) {
		return NULL;
	}
	int fd = open(file, O_RDONLY);
	if (fd == - 1) return NULL;
	int file_size = 0;
	int read_state = 1;
	char buf[1];
	while (read_state != 0) {
		read_state = read(fd, buf, 1);
		if (read_state != 0)
			file_size++;
	}
	if (file_size <= 0) {
		return NULL;
	}
	char *str = mx_strnew(file_size);
	int str_len = 0;
	close(fd);
	fd = open(file, O_RDONLY);
	read_state = 1;
	while (read_state != 0) {
		read_state = read(fd, buf, 1);
		if (read_state != 0) {
			str[str_len] = buf[0];
			str_len++;
		}
	}
	close(fd);
	return str;
}

