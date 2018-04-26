/// @brief  Dynamic Array
/// @author Patrick Auernig
/// @date   2018-04-25
/// @file   vec.h

#pragma once


#include <stdlib.h>
#include <stdbool.h>

#include <misc.h>


struct _Vec;

typedef struct _Vec* Vec;


Vec vec_new();

Vec vec_with_capacity(Size);

void vec_drop(Vec);

void vec_insert(Vec, Index, Value);

void vec_append(Vec, Value);

void vec_prepend(Vec, Value);

Value vec_delete(Vec, Index);

Value vec_shift(Vec);

Value vec_pop(Vec);

Value vec_get(Vec, Index);

Value vec_first(Vec);

Value vec_last(Vec);

bool vec_is_empty(Vec);

Size vec_size(Vec);

Size vec_capacity(Vec);
