#include <setjmp.h> /* jmp_buf for cmocka */
#include <stdarg.h> /* va_start for cmocka */
#include <stddef.h> /* size_t for cmocka */

#include <cmocka.h>

#include <stdio.h> /* printf in asserts */
#include <stdlib.h> /* abs in asserts */
#include <string.h> /* strcmp in asserts */
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

#define cr_assert_arr_eq_cmp(                                                  \
    expected, actual, array_size, string_compare, ...)                         \
    for (unsigned int _i_xyz = 0; _i_xyz < (array_size); _i_xyz++) {           \
        if ((string_compare)(&(expected)[_i_xyz], &(actual)[_i_xyz]) != 0) {   \
            printf(__VA_ARGS__);                                               \
            printf("\n");                                                      \
            fail();                                                            \
            break;                                                             \
        }                                                                      \
    }

static FILE __original;
static char *__fileName;
static FILE *__captured;
static long __startPos;

#define READ_BUFFER 1000
static char __readBuffer[READ_BUFFER];

static int captureStdOut(void **state)
{
    (void)state; /* unused */

    __original = *stdout;
    __fileName = tmpnam(NULL);
    __captured = freopen(__fileName, "wb+", stdout);
    __startPos = 0;

    return 0;
}

static void getStdOut(FILE *file)
{
    if (file == stdout) {
        fflush(__captured);

        long next = ftell(__captured);
        fseek(__captured, __startPos, SEEK_SET);
        /* fprintf(stderr, "current startpos %d\n", __startPos); */

        memset(__readBuffer, 0, READ_BUFFER);
        fread(__readBuffer, sizeof(char), READ_BUFFER, __captured);
        /* fprintf(stderr, "read %s\n", __readBuffer); */

        __startPos = next;
        fseek(__captured, __startPos, SEEK_SET);
        /* fprintf(stderr, "next startpos %d\n", __startPos); */

    } else if (file == stderr) {
    }
}

static int resetStdOut(void **state)
{
    (void)state; /* unused */

    fclose(__captured);
    remove(__fileName);

    return 0;
}

#define cr_assert_file_contents_eq_str(file, expected)                         \
    getStdOut(file);                                                           \
    cr_assert_str_eq(expected, __readBuffer, " File contents");
