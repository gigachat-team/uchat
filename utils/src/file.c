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

t_string read_three_files(char *filename1, char *filename2, char *filename3) {
    FILE *file1 = fopen(filename1, "a+");
    FILE *file2 = fopen(filename2, "a+");
    FILE *file3 = fopen(filename3, "a+");

    fseek(file1, 0L, SEEK_END);
    size_t file1_size = ftell(file1);
    fseek(file1, 0L, SEEK_SET);
    fseek(file2, 0L, SEEK_END);
    size_t file2_size = ftell(file2);
    fseek(file2, 0L, SEEK_SET);
    fseek(file3, 0L, SEEK_END);
    size_t file3_size = ftell(file3);
    fseek(file3, 0L, SEEK_SET);

    t_string files_content = string_new(file1_size + file2_size + file3_size);

    fread(files_content.val, sizeof(char), file1_size, file1);
    fread(files_content.val + file1_size, sizeof(char), file2_size, file2);
    fread(files_content.val + file1_size + file2_size, sizeof(char), file3_size, file3);
    fclose(file1);
    fclose(file2);
    fclose(file3);

    return files_content;
}
