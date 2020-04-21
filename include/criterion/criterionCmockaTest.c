#include "criterion.h"

#define TODO 0
#define TODO_S ""
#define TODO_FP (FILE *)NULL

static void stdoutKoan(void **state)
{
    (void)state; /* unused */

    putchar('A');
    cr_assert_file_contents_eq_str(stdout, "A");

    puts("Foo\n");
    cr_assert_file_contents_eq_str(stdout, "Foo\n\n");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test_setup_teardown(stdoutKoan, captureStdOut, resetStdOut), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
