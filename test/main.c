
// test square function defined in ../main.c

#include <stdio.h>
#include "../square.c"
#include "../person/person.c"

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

// test person functions defined in person/person.c
int test_person()
{
    Person p = Person_create();
    p.set_name(&p, "Alice");
    p.set_age(&p, 30);
    p.print_info(&p);

    if (p.age != 30)
    {
        printf("Age is not set correctly\n");
        return 1;
    }

    if (strcmp(p.name, "Alice") != 0)
    {
        printf("Name is not set correctly\n");
        return 1;
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

    if (test_person() == 0)
    {
        printf("All testcases passed\n");
    }
    else
    {
        printf("Some testcases failed\n");
    }

    return 0;
}
