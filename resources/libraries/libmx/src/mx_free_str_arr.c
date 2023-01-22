#include "../inc/libmx.h"

void mx_free_str_arr(char ***str_arr) {
    if (str_arr == NULL || *str_arr == NULL) {  
        return;
    }
    for (int i = 0; (*str_arr)[i] != NULL; i++) {
        free((*str_arr)[i]);
    }
    free(*str_arr);
    *str_arr = NULL;
}

