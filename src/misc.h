#pragma once


#include <stdlib.h>


#ifdef __GNUC__
    #define UNUSED(X) unused_ ## X __attribute__((__unused__))
    #define UNUSED_FUNC(X) __attribute__((__unused__)) unused_ ## X
#else
    #define UNUSED(X) unused_ ## X
    #define UNUSED_FUNC(X) unused_ ## X
#endif

#define nil NULL

#define unless(X)\
    if (!(X))

#define is_nil(X)\
    ((X) == nil)


typedef void* Value;
typedef size_t Index;
typedef size_t Size;


void drop(Value object);
