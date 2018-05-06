#include <check.h>
#include "conversions.h"


List vec_to_list(Vec vec) {
    List tmp = list_new();
    check(tmp, nil);

    for (Size i = 0; i < vec_size(vec); ++i) {
        list_append(tmp, vec_get(vec, i));
    }

    return tmp;
rescue:
    return nil;
}

Vec list_to_vec(List list) {
    Vec tmp = vec_with_capacity(list_size(list));
    check(tmp, nil);

    for (Size i = 0; i < list_size(list); ++i) {
        vec_append(tmp, list_get(list, i));
    }

    return tmp;
rescue:
    return nil;
}
