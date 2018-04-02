#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include <misc.h>
#include <logger.h>


#define LOG_TEST(FMT, ...)\
    logger(stdout, LVL_TEST, __FILE__, __LINE__, __func__, FMT, ##__VA_ARGS__)

#define TEST_STATE(RET) (RET ? true : (++fail_count && false))

#define TEST_MSG(MSG, NAME, RET)\
    sprintf(MSG, "%s %s", (TEST_STATE(RET) ? (CO_GRN "[ OK ] " CO_NON) : (CO_RED "[FAIL] " CO_NON)), NAME)


#define describe(NAME)\
    int main(void) {\
        LOG_TEST("Testing %s...", #NAME);

#define describe_end\
        return (fail_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;\
    }

#define test(NAME)\
    unused_test_##NAME();

#define example(NAME)\
        static void UNUSED_FUNC(test_##NAME()) {\
            const char* example_name = #NAME;\
            char* msg = (char*)malloc(sizeof(*msg) * 256);\
            bool failed = false;

#define example_end\
        TEST_MSG(msg, example_name, !failed);\
        if (msg) { LOG_TEST("%s", msg); }\
        free(msg);\
        return;\
    failed:\
        failed = true;\
        ++fail_count;\
        goto after;\
    }

#define assert(EXPECT)\
    if (!(EXPECT)) { goto failed; }

#define assert_true(A)\
    assert((A) == true)

#define assert_false(A)\
    assert((A) == false)

#define assert_eq(E, A)\
    assert((A) == (E))

#define assert_neq(E, A) assert((A) != (E))


typedef void (*testfunc)(char *msg);

unsigned int fail_count = 0;
