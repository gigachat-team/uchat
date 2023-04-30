#pragma once

#include "str.h"
#include <stdio.h>

void write_to_file(char *filename, char *text);
void read_from_file(char *filename, size_t max_len, char *buffer);
t_string read_three_files(char *filename1, char *filename2, char *filename3);
