#include <check.h>
#include <debug.h>
#include "vec.h"


static const Size GROW_FACTOR = 2;


struct _Vec {
    Size size;
    Size capacity;
    Value* content;
};


static bool grow(Vec vec) {
    Size new_cap = ((vec->capacity == 0) ? 2 : vec->capacity) * GROW_FACTOR;
    Value* new_content = realloc(vec->content, sizeof(*vec->content) * new_cap);
    memcheck(new_content);
    vec->content = new_content;
    vec->capacity = new_cap;
    return true;
rescue:
    return false;
}

static void shift_right(Vec vec, Index idx, Value val) {
    for (Size i = vec_size(vec); i > idx; --i) {
        vec->content[i] = vec->content[i - 1];
    }
    vec->content[idx] = val;
}

static Value shift_left(Vec vec, Index idx) {
    Value val = vec->content[idx];
    for (Size i = idx; i < vec_size(vec) - 1; ++i) {
        vec->content[i] = vec->content[i + 1];
    }
    return val;
}


Vec vec_new() {
    return vec_with_capacity(0);
}

Vec vec_with_capacity(Size initial) {
    Vec vec = malloc(sizeof(*vec));
    memcheck(vec);
    vec->size = 0;
    vec->capacity = initial;
    vec->content = malloc(sizeof(*vec->content) * initial);
    return vec;
rescue:
    return nil;
}

void vec_drop(Vec vec) {
    check(vec, nil);
    drop(vec->content);
    drop(vec);
rescue:
    return;
}

void vec_insert(Vec vec, Index idx, Value val) {
    check(vec, "Invalid vector");

    if (vec->size == vec->capacity) {
        check(grow(vec), "Failed to grow vector");
    }

    if (vec_is_empty(vec)) {
        vec->content[0] = val;
    } else if (idx >= vec_size(vec)) {
        vec->content[vec_size(vec)] = val;
    } else {
        shift_right(vec, idx, val);
    }

    ++vec->size;
rescue:
    return;
}

void vec_append(Vec vec, Value val) {
    vec_insert(vec, vec->size, val);
}

void vec_prepend(Vec vec, Value val) {
    vec_insert(vec, 0, val);
}

Value vec_delete(Vec vec, Index idx) {
    check(vec, "Invalid vector");
    check(!vec_is_empty(vec), nil);

    Value val = nil;

    if (idx >= vec_size(vec)) {
        val = vec->content[vec_size(vec) - 1];
        vec->content[vec_size(vec) - 1] = nil;
    } else {
        val = shift_left(vec, idx);
    }

    --vec->size;

    return val;
rescue:
    return nil;
}

Value vec_shift(Vec vec) {
    return vec_delete(vec, 0);
}

Value vec_pop(Vec vec) {
    return vec_delete(vec, vec->size);
}

Value vec_get(Vec vec, Index idx) {
    check(vec, "Invalid vector");
    check(vec->size > idx, "Index out of range");
    return vec->content[idx];
rescue:
    return nil;
}

Value vec_first(Vec vec) {
    check(vec, "Invalid vector");
    check(vec->size > 0, nil);
    return vec_get(vec, 0);
rescue:
    return nil;
}

Value vec_last(Vec vec) {
    check(vec, "Invalid vector");
    check(vec->size > 0, nil);
    return vec_get(vec, vec->size - 1);
rescue:
    return nil;
}

bool vec_is_empty(Vec vec) {
    return vec_size(vec) == 0;
}

Size vec_size(Vec vec) {
    check(vec, nil);
    return vec->size;
rescue:
    return 0;
}

Size vec_capacity(Vec vec) {
    check(vec, nil);
    return vec->capacity;
rescue:
    return 0;
}

Vec vec_extend(Vec vec, Vec other) {
    check(vec, "Invalid vector");
    check(other, "Invalid other vector");
    for (Size i = 0; i < vec_size(other); ++i) {
        vec_append(vec, vec_get(other, i));
    }
    return vec;
rescue:
    return nil;
}
