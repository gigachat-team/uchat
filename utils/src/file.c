#include "file.h"

void write_to_file(char *filename, char *text) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fputs(text, file);
        fclose(file);
    } else {
        fprintf(stderr, "Failed to open file file \"%s\" for writing\n", filename);

    }
}

void read_from_file(char *filename, size_t max_len, char *buffer) {
    FILE *file = fopen(filename, "a+");
    if (file) {
        fgets(buffer, max_len, file);
        fclose(file);
    } else {
        fprintf(stderr, "Failed to open file file \"%s\" for reading\n", filename);
    }
}
