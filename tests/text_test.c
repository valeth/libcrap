#include <test_helpers.h>
#include <objects/text.h>


example(create_and_drop)
    Text txt = text_new();

    assert_neq(nil, txt);
    assert_true(text_is_empty(txt));
    assert_eq(0, text_size(txt));

after:
    text_drop(txt);
example_end


example(from_cstring)
    Text txt = text_from_cstring_unsafe("some string");

    assert_neq(nil, txt);
    assert_false(text_is_empty(txt));
    assert_eq(11, text_size(txt));

after:
    text_drop(txt);
example_end


example(extend)
    Text txt = text_from_cstring_unsafe("first ");
    Text txt2 = text_from_cstring_unsafe("second");

    text_extend(txt, txt2);

    assert_eq('f', text_get(txt, 0));
    assert_eq('t', text_get(txt, 4));
    assert_eq('s', text_get(txt, 6));
    assert_eq('d', text_get(txt, 11));

after:
    text_drop(txt);
    text_drop(txt2);
example_end


describe(Text)
    test(create_and_drop);
    test(from_cstring);
    test(extend);
describe_end
