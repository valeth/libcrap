#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "logger.h"


#define CLEAN_ERRNO (errno == 0 ? "None" : strerror(errno))


const char* loglevel_str[] = {
    CO_STR("NORM", CO_DEF),
    CO_STR("INFO", CO_DEF),
    CO_STR("TEST", CO_YLW),
    CO_STR("WARN", CO_YLW),
    CO_STR("DEBUG", CO_GRN),
    CO_STR("ERROR", CO_RED),
    CO_STR("FATAL", CO_RED)
};


void logger(
    FILE *stream,
    int level,
    const char* file,
    const int line,
    const char* function_name,
    const char* fmt,
    ...
) {
    va_list args;
    va_start(args, fmt);
    const int buffer_size = 1024;
    char *buffer = calloc(buffer_size, sizeof(*buffer));

    vsnprintf(buffer, buffer_size, fmt, args);

    if (level == LVL_TEST) {
        const char* log_format = "%s\n";
        fprintf(stream, log_format, buffer);
    } else if (level > LVL_TEST) {
        const char* log_format = "[%5s]  (%s:%-2d %s <errno: %s>)  %s\n";
        fprintf(stream, log_format, loglevel_str[level], file, line, function_name, CLEAN_ERRNO, buffer);
    } else {
        const char* log_format = "[%5s]  %s\n";
        fprintf(stream, log_format, loglevel_str[level], buffer);
    }

    free(buffer);
    va_end(args);
}
