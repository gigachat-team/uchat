#pragma once

#include <stdio.h>

void write_to_file(char *filename, char *text);
void read_from_file(char *filename, size_t max_len, char *buffer);
