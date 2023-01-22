#include "../inc/libmx.h"

void mx_print_unicode(wchar_t c) {
    char utf8_bytes[5];
    unsigned int unicode = c;

    if (unicode <= 0x7F) {
        utf8_bytes[0] = unicode & 0x7F;
        utf8_bytes[1] = '\0';
    } else if (unicode > 0x10FFFF) {
        utf8_bytes[0] = 0xEF;
        utf8_bytes[1] = 0xBF;
        utf8_bytes[2] = 0xBD;
        utf8_bytes[3] = '\0';
    } else {
        int count;
        if (unicode <= 0x7FF) {
            count = 1;
        } else if (unicode <= 0xFFFF) {
            count = 2;
        } else {
            count = 3;
        }
        for (int i = 0; i < count; ++i) {
            utf8_bytes[count-i] = 0x80 | (unicode & 0x3F);
            unicode >>= 6;
        }
        utf8_bytes[0] = (0x1E << (6 - count)) | (unicode & (0x3F >> count));
        utf8_bytes[1 + count] = '\0';
    }
    
    for (int i = 0; utf8_bytes[i] != '\0'; i++) {
        write(1, &utf8_bytes[i], 1);
    }
}

