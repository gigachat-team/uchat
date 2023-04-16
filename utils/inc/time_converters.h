#pragma once

#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct tm str_to_tm(char *datetime_str, char *datetime_format);
struct tm utc_to_localtime(struct tm utc);
struct tm utc_str_to_localtime_tm(char *utc_str, char *datetime_format);
