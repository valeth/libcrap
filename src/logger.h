#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h> // va_* functions

#ifdef NCOLOR
    #define CO_RED ""
    #define CO_YLW ""
    #define CO_GRN ""
    #define CO_DEF ""
    #define CO_NON ""
    #define CO_STR(S, C) S
#else
    #define CO_RED "\e[0;31m"  /**< @brief  Red */
    #define CO_YLW "\e[0;33m"  /**< @brief  Dark Yellow */
    #define CO_GRN "\e[0;32m"  /**< @brief  Green */
    #define CO_DEF "\e[1;39m"  /**< @brief  Default Foreground */
    #define CO_NON "\e[0m"     /**< @brief  Reset color */
    #define CO_STR(S, C) C S CO_NON
#endif

#define log(FMT, ...) \
    logger(stderr, LVL_NORMAL, __FILE__, __LINE__, __func__, FMT, ##__VA_ARGS__)

#define info(FMT, ...) \
    logger(stderr, LVL_INFO, __FILE__, __LINE__, __func__, FMT, ##__VA_ARGS__)

#define warn(FMT, ...) \
    logger(stderr, LVL_WARNING, __FILE__, __LINE__, __func__, FMT, ##__VA_ARGS__)

#define error(FMT, ...) \
    logger(stderr, LVL_ERROR, __FILE__, __LINE__, __func__, FMT, ##__VA_ARGS__)

#define fatal(FMT, ...) \
    logger(stderr, LVL_FATAL, __FILE__, __LINE__, __func__, FMT, ##__VA_ARGS__)


enum Severity {
    LVL_NORMAL = 0,
    LVL_INFO,
    LVL_TEST,
    LVL_WARNING,
    LVL_DEBUG,
    LVL_ERROR,
    LVL_FATAL
};


void logger(
    FILE *stream,
    int level,
    const char* file,
    const int line,
    const char* function_name,
    const char* fmt,
    ...
);
