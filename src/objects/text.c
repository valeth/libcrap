#include <check.h>
#include <debug.h>
#include "vec.h"
#include "text.h"


struct _Text {
    Vec inner;
};


Text text_new() {
    Text txt = malloc(sizeof(*txt));
    memcheck(txt);
    txt->inner = vec_new();
    check(txt->inner, "Failed to allocate inner vector.");
    return txt;
rescue:
    return nil;
}

Text text_from_cstring_unsafe(CString cstr) {
    Text tmp = text_new();
    check(tmp, "Failed to create text object.");
    for (Size i = 0; cstr[i] != '\0'; ++i) {
        vec_append(tmp->inner, &cstr[i]);
    }
    return tmp;
rescue:
    return nil;
}

CString text_as_cstring(Text txt) {
    Size size = text_size(txt);
    CString buf = malloc(sizeof(*buf) * (size + 1));
    for (Size i = 0; i < size; ++i) {
        buf[i] = text_get(txt, i);
    }
    buf[size + 1] = '\0';
    return buf;
}

void text_drop(Text txt) {
    check(txt, "Invalid text object");
    vec_drop(txt->inner);
    drop(txt);
rescue:
    return;
}

Char text_get(Text txt, Index idx) {
    return *(Char*)vec_get(txt->inner, idx);
}

bool text_is_empty(Text txt) {
    return 0 == text_size(txt);
}

Size text_size(Text txt) {
    check(txt, "Invalid text object");
    return vec_size(txt->inner);
rescue:
    return 0;
}

Text text_extend(Text dest, Text src) {
    check(dest, "Invalid destination");
    check(src, "Invalid source");
    vec_extend(dest->inner, src->inner);
rescue:
    return dest;
}
