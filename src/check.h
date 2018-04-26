//! @brief  Various check macros
//! @author Patrick Auernig
//! @date   2018-04-01
//! @file   check.h

#pragma once


#include <stdbool.h>

#include "misc.h"
#include "logger.h"


#define check(X, FMT, ...)\
    unless((X)) { raise(FMT, ##__VA_ARGS__); }\

#define memcheck(X)\
    if (is_nil((X))) {\
        raise("Failed to allocate memory.");\
    }

#define raise(FMT, ...)\
    do {\
        if (FMT) { error(FMT, ##__VA_ARGS__); }\
        goto rescue;\
    } while (0);
