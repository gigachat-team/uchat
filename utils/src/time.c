#include "../utils.h"

struct tm str_to_tm(char *datetime_str, char *datetime_format) {
    struct tm datetime = {0};
    datetime.tm_isdst = -1;
    if (strptime(datetime_str, datetime_format, &datetime) == NULL) {
        fprintf(stderr, "strptime failed.\n");
        exit(EXIT_FAILURE);
    }
    return datetime;
}

struct tm utc_to_localtime(struct tm utc) {
    utc.tm_isdst = 0;
    time_t raw_utc = mktime(&utc);
    time_t raw_localtime = raw_utc - timezone + (daylight ? 3600 : 0);
    struct tm local_time = *localtime(&raw_localtime);

    return local_time;
}

struct tm utc_str_to_localtime_tm(char *utc_str, char *datetime_format) {
    struct tm utc = str_to_tm(utc_str, datetime_format);
    return utc_to_localtime(utc);
}

