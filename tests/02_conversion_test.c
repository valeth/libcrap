#include <test_helpers.h>
#include <objects/conversions.h>


example(vec_to_list)
    Vec vec = vec_new();
    int values[4] = { 9, 7, 3, 2 };
    vec_append(vec, &values[0]);
    vec_append(vec, &values[1]);
    vec_append(vec, &values[2]);
    vec_append(vec, &values[3]);

    List converted = vec_to_list(vec);
    assert_eq(9, *(int*)list_get(converted, 0));
    assert_eq(7, *(int*)list_get(converted, 1));
    assert_eq(3, *(int*)list_get(converted, 2));
    assert_eq(2, *(int*)list_get(converted, 3));

after:
    vec_drop(vec);
    list_drop(converted);
example_end


example(list_to_vec)
    List list = list_new();
    int values[4] = { 9, 7, 3, 2 };
    list_append(list, &values[0]);
    list_append(list, &values[1]);
    list_append(list, &values[2]);
    list_append(list, &values[3]);

    Vec converted = list_to_vec(list);
    assert_eq(9, *(int*)vec_get(converted, 0));
    assert_eq(7, *(int*)vec_get(converted, 1));
    assert_eq(3, *(int*)vec_get(converted, 2));
    assert_eq(2, *(int*)vec_get(converted, 3));

after:
    list_drop(list);
    vec_drop(converted);
example_end


describe(Conversion)
    test(vec_to_list);
    test(list_to_vec);
describe_end
