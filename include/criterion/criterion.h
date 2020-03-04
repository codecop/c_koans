#include <setjmp.h> /* jmp_buf for cmocka */
#include <stdarg.h> /* va_start for cmocka */
#include <stddef.h> /* size_t for cmocka */

#include <cmocka.h>

#include <stdio.h> /* puts in asserts */
#include <stdlib.h> /* abs in asserts */

#define cr_assert(state, message) \
    if (!(state)) { \
        puts((message)); \
        assert_true((state)); \
    }

#define cr_assert_eq(expected, actual, message) \
    if ((expected) != (actual)) { \
        puts((message)); \
        assert_int_equal((expected), (actual)); \
    }
// also ptr_equal

#define cr_assert_not_eq(expected, actual, message) \
    if ((expected) == (actual)) { \
        puts((message)); \
        assert_int_not_equal((expected), (actual)); \
    }

#define cr_assert_gt(larger, smaller, message) \
    if ((larger) <= (smaller)) { \
        puts((message)); \
        assert_true((larger) > (smaller)); \
    }

#define cr_assert_float_eq(expected, actual, eps, message) \
    if (abs((expected) - (actual)) > (eps)) { \
        puts((message)); \
        assert_float_equal((expected), (actual), (eps)); \
    }

#define cr_assert_null(actual, message) \
    if ((actual) != NULL) { \
        puts((message)); \
        assert_null((actual)); \
    }

#define cr_assert_not_null(actual, message) \
    if ((actual) == NULL) { \
        puts((message)); \
        assert_non_null((actual)); \
    }

#define cr_assert_str_eq(expected, actual, message) \
    if (strcmp((expected), (actual)) != 0) { \
        puts((message)); \
        assert_string_equal((expected), (actual)); \
    }

void cr_assert_arr_eq_cmp(char *sorted_names[], char *names[], size_t array_size,
    int (*string_compare)(const void *, const void *), char *message);

void cr_assert_file_contents_eq_str(FILE *_File, char *expected);

/*
void cr_assert_arr_eq_cmp();
*/
