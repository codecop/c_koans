#include "c_koans.h"
#include <stdlib.h>
#include <string.h>

static int static_function(int);

int global_var = 0;

int string_compare(const void *s1, const void *s2)
{
    /*
        The comparison function must match the declaration in the prototype
        exactly. This is why, even though we are comparing 2 strings, the
        arguments must be void pointers.

        The actual arguments passed into this function is the address of each
        element in the array, which in this case is a char **, this is why we
        must cast the argument to a char ** and dereference it once for strcmp
        to work.
    */
    return strcmp(*(char **)s1, *(char **)s2);
}

void double_an_int(int *i)
{
    /*
        The '*' operator for dereference has a higher precedence than the other
        arithmetic operators, therefore it will be multiplying and assigning the
        int that is pointer to by i.
    */
    *i *= 2;
}

int modify_global()
{
    /*
        We modify the global variable, located in the .data section,
        visible to the entire program.
    */
    global_var++;
    return global_var;
}

int modify_local()
{
    /*
        We modify the local variable, located and initialized on the stack.
        every call, it will be initialized and modified in the same fashion.
    */
    int i = 0;
    i++;
    return i;
}

int modify_local_static()
{
    /*
        Local static variables will be initialized only once and be located
        in the .data section. Local static variables can only be referenced
        inside the function because the name will be known inside the function.
        This causes the value of the variable to be preserved across function
        calls.

        The static qualifier has a double meaning depending on the scope it
        appears in; the next function will show this
    */
    static int i = 0;
    i++;
    static_function(0); /* we are calling this to avoid a compiler warning */
    return i;
}

/*
    Static when used in a top-level scope will cause the variable or function
    to be visible only within the file. This is similar to the 'private' keyword
    in Java.
 */
static int static_int = 0;

static int static_function(int n)
{
    static_int++;
    if (n == 0)
        return 0;
    else
        return static_int + static_function(n - 1);
}

struct person make_person(const char *name, int month, int day, int year)
{
    struct person ret;

    /* is this a problem? What is the lifetime of this heap allocated memory? */
    ret.name = calloc(strlen(name), sizeof(char));
    strcpy(ret.name, name);

    ret.bday.month = month;
    ret.bday.day = day;
    ret.bday.year = year;

    return ret;
}

int make_person_better(
    struct person *person, const char *name, int month, int day, int year)
{

    /*
        The access operator for a pointer to a struct is different that usual
        Instead of having to type (*person).bday.month for accessing a pointer
        to a struct's fields, the '->' operator is sugar for the last expression
    */
    person->bday.month = month;
    person->bday.day = day;
    person->bday.year = year;

    /*
        Errno is a global variable that is set
        by library functions to indicate an
        an error occurred in that function. When we call calloc, an error might
        occur, such as the machine being out of memory.
    */
    errno = 0; /* we set it to zero because all error numbers are non zero. */

    /* When is this freed? */
    person->name = calloc(strlen(name), sizeof(char));

    /* We check if an error occurred */
    if (errno)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
    /*
        EXIT_SUCCESS and EXIT_FAILURE are predefined macros for typical success
        or failure. On our VM they are 0 and 1 respectively.
    */
}

// void cr_assert(int state, char *message)  {
//     if (state) {
//         /* ok */
//     } else {
//         puts(message);
//         assert_true(state);
//     }
// }

// void cr_assert_eq(int expected, int actual, char *message) {
//     if (expected == actual) {
//         /* ok */
//     } else {
//         puts(message);
//         assert_int_equal(expected, actual);
//     }
// }

// void cr_assert_not_eq(int expected, int actual, char *message) {
//     if (expected != actual) {
//         /* ok */
//     } else {
//         puts(message);
//         assert_int_not_equal(expected, actual);
//     }
// }

// void cr_assert_gt(long larger, long smaller, char *message) {
//     if (larger > smaller) {
//         /* ok */
//     } else {
//         puts(message);
//         assert_true(larger > smaller);
//     }
// }

// void cr_assert_float_eq(
//     double expected, double actual, double eps, char *message)
// {
//     if (abs(expected - actual) > eps) {
//         puts(message);
//         assert_float_equal(expected, actual, eps);
//     }
// }

// void cr_assert_null(void *actual, char *message) {
//     if (actual == NULL) {
//         /* ok */
//     } else {
//         puts(message);
//         assert_null(actual);
//     }
// }

// void cr_assert_not_null(void *actual, char *message) {
//     if (actual != NULL) {
//         /* ok */
//     } else {
//         puts(message);
//         assert_non_null(actual);
//     }
// }

// void cr_assert_str_eq(char expected[], char actual[], char *message) {
//     if (strcmp(expected, actual) == 0) {
//         /* ok */
//     } else {
//         puts(message);
//         assert_string_equal(expected, actual);
//     }
// }

void cr_assert_arr_eq_cmp(char *expected[], char *actual[], size_t array_size,
    int (*string_compare)(const void *, const void *), char *message)
{
    for (unsigned int i = 0; i < array_size; i++) {
        if (string_compare(&expected[i], &actual[i]) != 0) {
            puts(message);
            fail();
            break;
        }
    }
}

void cr_assert_file_contents_eq_str(FILE *f, char *expected)
{
    // // https://stackoverflow.com/a/35249468/104143
    // int stdout_bk; // is fd for stdout backup
    // stdout_bk = dup(fileno(f));

    // int pipefd[2];
    // pipe2(pipefd, 0); // O_NONBLOCK);

    // // What used to be stdout will now go to the pipe.
    // dup2(pipefd[1], fileno(f));

    // fflush(f); // flushall();
    // write(pipefd[1], "", 1); // null-terminated string!
    // close(pipefd[1]);

    // dup2(stdout_bk, fileno(f)); // restore

    // char actual[101];
    // read(pipefd[0], actual, 100);
    // cr_assert_str_eq(expected, actual, "Read content different.");

    // char actual[1024];
    // if (fgets(actual, 1024, f) != NULL) {
    //     cr_assert_str_eq(expected, actual, "Read content different.");
    // } else {
    //     perror("Error printed by perror");
    //     puts("Reading from file did not return anything");
    // fail();
    // }
}
