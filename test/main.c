#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int square(int n)
{
    return n * n;
}

int test_square()
{
    // type testcase = {input, expected_output}
    int testcases[][2] = {
        {0, 0},
        {1, 1},
        {2, 4},
        {3, 9},
        {4, 16},
        {5, 25},
        {3546, 12574116},
        {10000, 100000000}};

    int n = sizeof(testcases) / sizeof(testcases[0]);
    for (int i = 0; i < n; i++)
    {
        int input = testcases[i][0];
        int expected_output = testcases[i][1];
        if (square(input) != expected_output)
        {
            printf("Testcase failed for input: %d\n", input);
            return 1;
        }
    }
    return 0;
}

void printer_pointer(int *p)
{
    printf("Value of a is %d\n", *p);
    printf("Address of a is %p\n", p);
}

int main()
{

        if (test_square() == 0)
    {
        printf("All testcases passed\n");
    }
    else
    {
        printf("Some testcases failed\n");
    }

    int a = 5;
    // allocate memory for a pointer
    int *p = malloc(sizeof(int));
    // dereference the pointer
    printf("Value of a is %d\n", *p);
    // the location of the pointer
    printf("Address of a is %p\n", p);

    // free the memory allocated for the pointer
    free(p);

    // allocate memory to the stack
    int *stackpointer = &a;

    printer_pointer(stackpointer);
    a = 10;
    printer_pointer(stackpointer);
    return 0;
}
