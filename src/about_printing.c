#include "c_koans.h"
#include <stdio.h>

#include "x86_x64.h"

/*
    This series of koans will go over topics not entirely specific to the C
    language itself, but is an essential topic for writing more-than-trivial
    C programs: printing.

    The topic of this koan is a subset of the general topic of IO.
    A more in-depth IO koan will be presented in about_io.
*/

static void about_printing_basic_printing(void** state)
{
    (void)state; /* unused */

    /*
        The most basic printing mechanisms are provided by the functions
	putchar and puts.

        putchar will output the single character to the standard output stream.
	The argument for putchar in type integer. The standard notes that it
	will be cast to an unsigned char before being output to the stream.
    */

    // For this koan, output 'A'
    putchar('A');

    cr_assert_file_contents_eq_str(stdout, "A");

    /*
       The next function is puts. This function will output the input string
       to the standard output stream with a newline character appended.
    */

    // For this koan, output "Foo" and two newline characters.
    // Remember that puts will output a newline character, too!
    puts("Foo\n");

    cr_assert_file_contents_eq_str(stdout, "Foo\n\n");
}

static void about_io_printf(void** state)
{
    (void)state; /* unused */

    /*
        This koan will go over the most common function used for output in C:
	printf.

	printf will print a format string to the standard output stream. Format
	strings are strings with special sequences of characters following a %
	character. Format specifiers will be filled out with the variables

	Unlike puts, printf will not output anything besides the string.
    */

    // For this koan, output "Hello World" and a newline.
    char *string = "World";
    printf("Hello %s\n", string);

    cr_assert_file_contents_eq_str(stdout, "Hello World\n");

    /*
        There are many modifiers present in C. You can access a list of them at:
        http://www.cplusplus.com/reference/cstdio/printf/
        Complete the following:
    */

    /*
        Use the references to determine which format specifier will give the
        proper output. When you complete this koan, change the literal on line
        76 to a nonzero value. This is to avoid compilation errors.
    */

#if 1
    char c = 'J';
    int i = -1;
    double d = 3.14;
    long l = 0xDEADBEEF;
    void* p = (void*)0x400;

    printf("char: %c\n", c);
    printf("int: %d\n", i);
    printf("unsigned int: %u\n", i);
    printf("hexadecimal unsigned int: %x\n", i);
    printf("float: %f\n", d);
    /* printf("long: %I64d\n", l); = long long int */
    /* https://stackoverflow.com/a/13590809/104143 */
    /* printf("long: %lld\n", l); = long long int */
    printf("long: %lu\n", l); /* fixed - no %ld! */
    printf("pointer: %p\n", p);
#endif
    cr_assert_file_contents_eq_str(stdout,
        "char: J\nint: -1\nunsigned int: 4294967295\nhexadecimal unsigned int: "
        "ffffffff\nfloat: 3.140000\nlong: 3735928559\npointer: " UPTR_STRING "\n");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test_setup_teardown(about_printing_basic_printing, captureStdOut, resetStdOut), /* */
        cmocka_unit_test_setup_teardown(about_io_printf, captureStdOut, resetStdOut), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
