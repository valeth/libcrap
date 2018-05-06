#include <test_helpers.h>
#include <objects/list.h>


example(create_and_drop)
    List list = list_new();

    assert_neq(nil, list);
    assert_eq(0, list_size(list));
    assert_true(list_is_empty(list));

after:
    list_drop(list);
example_end


example(insert_and_delete)
    List list = list_new();
    int values[4] = { 9, 7, 3, 5 };

    list_insert(list, 0, &values[0]);   // insert into empty
    list_insert(list, 0, &values[1]);   // prepend
    list_insert(list, 6, &values[2]);   // append
    list_insert(list, 2, &values[3]);   // at index

    assert_false(list_is_empty(list));
    assert_eq(4, list_size(list));
    assert_eq(7, *(int*)list_get(list, 0));
    assert_eq(9, *(int*)list_get(list, 1));
    assert_eq(5, *(int*)list_get(list, 2));
    assert_eq(3, *(int*)list_get(list, 3));

    assert_eq(9, *(int*)list_delete(list, 1));
    assert_eq(7, *(int*)list_delete(list, 0));
    assert_eq(5, *(int*)list_delete(list, 0));
    assert_eq(3, *(int*)list_delete(list, 6));
    assert_true(list_is_empty(list));
    assert_eq(0, list_size(list));

after:
    list_drop(list);
example_end


example(prepend_and_shift)
    List list = list_new();
    int values[4] = { 9, 7, 3, 2 };

    list_prepend(list, &values[0]);
    list_prepend(list, &values[1]);
    list_prepend(list, &values[2]);

    assert_eq(3, list_size(list));
    assert_eq(3, *(int*)list_get(list, 0));
    assert_eq(7, *(int*)list_get(list, 1));
    assert_eq(9, *(int*)list_get(list, 2));

    assert_eq(3, *(int*)list_shift(list));
    assert_eq(7, *(int*)list_shift(list));
    assert_eq(9, *(int*)list_shift(list));
    assert_eq(nil, list_shift(list));
    assert_true(list_is_empty(list));
    assert_eq(0, list_size(list));

after:
    list_drop(list);
example_end

example(append_and_pop)
    List list = list_new();
    int values[4] = { 9, 7, 3, 2 };

    list_append(list, &values[0]);
    list_append(list, &values[1]);
    list_append(list, &values[2]);

    assert_false(list_is_empty(list));
    assert_eq(3, list_size(list));
    assert_eq(9, *(int*)list_get(list, 0));
    assert_eq(7, *(int*)list_get(list, 1));
    assert_eq(3, *(int*)list_get(list, 2));

    assert_eq(3, *(int*)list_pop(list));
    assert_eq(7, *(int*)list_pop(list));
    assert_eq(9, *(int*)list_pop(list));
    assert_eq(nil, list_pop(list));
    assert_true(list_is_empty(list));
    assert_eq(0, list_size(list));

after:
    list_drop(list);
example_end

example(extend)
    List list = list_new();
    List list2 = list_new();

    int values[8] = { 9, 7, 3, 2, 5, 1, 10, 8 };

    list_append(list, &values[0]);
    list_append(list, &values[1]);
    list_append(list, &values[2]);
    list_append(list2, &values[3]);
    list_append(list2, &values[4]);
    list_append(list2, &values[5]);
    list_append(list2, &values[6]);
    list_append(list2, &values[7]);
    assert_eq(3, list_size(list));
    assert_eq(5, list_size(list2));

    list_extend(list, list2);
    assert_eq(8, list_size(list));
    assert_eq(5, list_size(list2));

after:
    list_drop(list);
    list_drop(list2);
example_end

describe(List)
    test(create_and_drop);
    test(insert_and_delete);
    test(prepend_and_shift);
    test(append_and_pop);
    test(extend);
describe_end
