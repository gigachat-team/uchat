#pragma once

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TIME_FORMAT "%2m-%2d %2H:%2M"
#define DEFAULT_TIME_FORMAT_LEN 12

struct tm str_to_tm(char *datetime_str, char *datetime_format);
struct tm utc_to_localtime(struct tm utc);
struct tm utc_str_to_localtime_tm(char *utc_str, char *datetime_format);
