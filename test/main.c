#include <stdio.h>

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
        {3546, 12567116},
        {10000, 100000000}};

    int n = sizeof(testcases) / sizeof(testcases[0]);
    for (int i = 0; i < n; i++)
    {
        int input = testcases[i][0];
        int expected_output = testcases[i][1];
        if (square(input) != expected_output)
        {
            return 1;
        }
    }
    return 0;
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
    return 0;
}
