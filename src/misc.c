#include "check.h"
#include "misc.h"


void drop(Value object) {
    check(object, nil);
    free(object);
    object = nil;
rescue:
    return;
}
