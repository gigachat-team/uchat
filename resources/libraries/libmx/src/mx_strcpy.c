char *mx_strcpy(char *dst, const char *src) {
    int i = 0;
    for (; src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return dst;
}

