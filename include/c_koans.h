#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */
#include <cmocka.h>

#ifndef CKOANS_H
#define CKOANS_H

#define TODO 0
#define TODO_NZ 1
#define TODO_S ""
#define TODO_FP (FILE*) NULL

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

void cr_assert(int state, ...); /* char *message and opts */
void cr_assert_eq(int expected, int actual, ...); /* char *message */
void cr_assert_gt(long expected, long actual, char *message);
void cr_assert_float_eq(double expected, double actual, double eps, char *message);
void cr_assert_null(void* expected, ...); /* char *message and opts */
void cr_assert_str_eq(char expected[], char actual[], char *message);
/*
void cr_assert_file_contents_eq();
void cr_assert_arr_eq_cmp();
*/

#endif
