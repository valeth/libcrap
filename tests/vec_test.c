#include <test_helpers.h>
#include <objects/vec.h>

example(create_and_drop)
    Vec vec = vec_new();
    Vec vec2 = vec_with_capacity(2);

    assert_neq(nil, vec);
    assert_eq(0, vec_size(vec));
    assert_eq(0, vec_capacity(vec));
    assert_true(vec_is_empty(vec));

    assert_neq(nil, vec2);
    assert_eq(0, vec_size(vec2));
    assert_eq(2, vec_capacity(vec2));
    assert_true(vec_is_empty(vec2));

after:
    vec_drop(vec);
    vec_drop(vec2);
example_end


example(insert_and_delete)
    Vec vec = vec_new();
    int values[4] = { 9, 7, 3, 5 };

    vec_insert(vec, 0, &values[0]);     // insert into empty
    vec_insert(vec, 0, &values[1]);     // prepend
    vec_insert(vec, 6, &values[2]);     // append
    vec_insert(vec, 2, &values[3]);     // at index

    assert_false(vec_is_empty(vec));
    assert_eq(4, vec_size(vec));
    assert_eq(4, vec_capacity(vec));
    assert_eq(7, *(int*)vec_get(vec, 0));
    assert_eq(9, *(int*)vec_get(vec, 1));
    assert_eq(5, *(int*)vec_get(vec, 2));
    assert_eq(3, *(int*)vec_get(vec, 3));

    assert_eq(9, *(int*)vec_delete(vec, 1));
    assert_eq(7, *(int*)vec_delete(vec, 0));
    assert_eq(5, *(int*)vec_delete(vec, 0));
    assert_eq(3, *(int*)vec_delete(vec, 6));
    assert_true(vec_is_empty(vec));
    assert_eq(0, vec_size(vec));
    assert_eq(4, vec_capacity(vec));

after:
    vec_drop(vec);
example_end


example(prepend_and_shift)
    Vec vec = vec_new();
    int values[4] = { 10, 82, 12, 42 };

    for (int i = 0; i < 4; ++i) {
        vec_prepend(vec, &values[i]);
    }

    assert_false(vec_is_empty(vec));
    assert_eq(4, vec_size(vec));
    assert_eq(4, vec_capacity(vec));
    assert_eq(42, *(int*)vec_get(vec, 0));
    assert_eq(12, *(int*)vec_get(vec, 1));
    assert_eq(82, *(int*)vec_get(vec, 2));
    assert_eq(10, *(int*)vec_get(vec, 3));

    assert_eq(42, *(int*)vec_shift(vec));
    assert_eq(12, *(int*)vec_shift(vec));
    assert_eq(82, *(int*)vec_shift(vec));
    assert_eq(10, *(int*)vec_shift(vec));
    assert_eq(nil, vec_shift(vec));
    assert_true(vec_is_empty(vec));
    assert_eq(0, vec_size(vec));
    assert_eq(4, vec_capacity(vec));

after:
    vec_drop(vec);
example_end


example(append_and_pop)
    Vec vec = vec_new();
    int values[5] = { 9, 7, 3, 5, 2 };

    for (int i = 0; i < 5; ++i) {
        vec_append(vec, &values[i]);
    }

    assert_false(vec_is_empty(vec));
    assert_eq(5, vec_size(vec));
    assert_eq(8, vec_capacity(vec));
    assert_eq(9, *(int*)vec_get(vec, 0));
    assert_eq(7, *(int*)vec_get(vec, 1));
    assert_eq(3, *(int*)vec_get(vec, 2));
    assert_eq(5, *(int*)vec_get(vec, 3));
    assert_eq(2, *(int*)vec_get(vec, 4));

    assert_eq(2, *(int*)vec_pop(vec));
    assert_eq(5, *(int*)vec_pop(vec));
    assert_eq(3, *(int*)vec_pop(vec));
    assert_eq(7, *(int*)vec_pop(vec));
    assert_eq(9, *(int*)vec_pop(vec));
    assert_eq(nil, vec_pop(vec));
    assert_true(vec_is_empty(vec));
    assert_eq(0, vec_size(vec));
    assert_eq(8, vec_capacity(vec));

after:
    vec_drop(vec);
example_end


describe(Vec)
    test(create_and_drop);
    test(insert_and_delete);
    test(prepend_and_shift);
    test(append_and_pop);
    // test(extend)
describe_end
