#include <setjmp.h> /* jmp_buf for cmocka */
#include <stdarg.h> /* va_start for cmocka */
#include <stddef.h> /* size_t for cmocka */

#include <cmocka.h>

#include <stdio.h> /* printf in asserts */
#include <stdlib.h> /* abs in asserts */

/*
 * Adapter macros to use cmocka instead of Criterion.
 */

#define cr_assert(state, ...)                                                  \
    if (!(state)) {                                                            \
        printf(__VA_ARGS__);                                                   \
        printf("\n");                                                          \
        assert_true((state));                                                  \
    }

#define cr_assert_eq(expected, actual, ...)                                    \
    if ((expected) != (actual)) {                                              \
        printf(__VA_ARGS__);                                                   \
        printf("\n");                                                          \
        assert_int_equal((expected), (actual));                                \
    }
// this is also used ptr_equal, gives warnings

#define cr_assert_not_eq(expected, actual, ...)                                \
    if ((expected) == (actual)) {                                              \
        printf(__VA_ARGS__);                                                   \
        printf("\n");                                                          \
        assert_int_not_equal((expected), (actual));                            \
    }

#define cr_assert_gt(larger, smaller, ...)                                     \
    if ((larger) <= (smaller)) {                                               \
        printf(__VA_ARGS__);                                                   \
        printf("\n");                                                          \
        assert_true((larger) > (smaller));                                     \
    }

#define cr_assert_float_eq(expected, actual, eps, ...)                         \
    if (abs((expected) - (actual)) > (eps)) {                                  \
        printf(__VA_ARGS__);                                                   \
        printf("\n");                                                          \
        assert_float_equal((expected), (actual), (eps));                       \
    }

#define cr_assert_null(actual, ...)                                            \
    if ((actual) != NULL) {                                                    \
        printf(__VA_ARGS__);                                                   \
        printf("\n");                                                          \
        assert_null((actual));                                                 \
    }

#define cr_assert_not_null(actual, ...)                                        \
    if ((actual) == NULL) {                                                    \
        printf(__VA_ARGS__);                                                   \
        printf("\n");                                                          \
        assert_non_null((actual));                                             \
    }

#define cr_assert_str_eq(expected, actual, ...)                                \
    if (strcmp((expected), (actual)) != 0) {                                   \
        printf(__VA_ARGS__);                                                   \
        printf("\n");                                                          \
        assert_string_equal((expected), (actual));                             \
    }

void cr_assert_arr_eq_cmp(char *sorted_names[], char *names[],
    size_t array_size, int (*string_compare)(const void *, const void *),
    char *message);

// void cr_assert_arr_eq_cmp(char *expected[], char *actual[], size_t array_size,
//     int (*string_compare)(const void *, const void *), char *message)
// {
//     for (unsigned int i = 0; i < array_size; i++) {
//         if (string_compare(&expected[i], &actual[i]) != 0) {
//             puts(message);
//             fail();
//             break;
//         }
//     }
// }

void cr_assert_file_contents_eq_str(FILE *_File, char *expected);
