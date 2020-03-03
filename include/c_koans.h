#include <setjmp.h> /* jmp_buf for cmocka */
#include <stdarg.h> /* va_start for cmocka */
#include <stddef.h> /* size_t for cmocka */
#include <cmocka.h>
#include <stdio.h> /* puts for asserts */
#include <stdlib.h> /* abs for asserts */

#ifndef CKOANS_H
#define CKOANS_H

#define TODO 0
#define TODO_NZ 1
#define TODO_S ""
#define TODO_FP (FILE *)NULL

typedef struct {
    int month;
    int day;
    int year;
} birthday;

struct person {
    char *name;
    birthday bday;
};

extern int global_var;

int string_compare(const void *p1, const void *p2);

void double_an_int(int *i);

int modify_global();
int modify_local();
int modify_local_static();

struct person make_person(const char *, int, int, int);
int make_person_better(struct person *, const char *, int, int, int);

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

#define cr_assert_not_eq(expected, actual, message) \
    if ((expected) == (actual)) { \
        puts((message)); \
        assert_int_equal((expected), (actual)); \
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

#endif
