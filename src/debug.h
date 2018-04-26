//! @brief  Debug Macros
//! @author Patrick Auernig
//! @date   2018-04-01
//! @file   debug.h

#pragma once


#include "logger.h"


#ifdef __GNUC__
    #define UNUSED(X) unused_ ## X __attribute__((__unused__))
    #define UNUSED_FUNC(X) __attribute__((__unused__)) unused_ ## X
#else
    #define UNUSED(X) unused_ ## X
    #define UNUSED_FUNC(X) unused_ ## X
#endif

#ifdef NDEBUG
    #define debug(FMT, ...)
#else
    #define debug(FMT, ...) \
        logger(stderr, LVL_DEBUG, __FILE__, __LINE__, __func__, FMT, ##__VA_ARGS__)
#endif
