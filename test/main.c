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

// linked list node
struct Node
{
    int data;
    struct Node *next;
};

void print_linked_list(struct Node *head)
{
    if (head == NULL)
    {
        return;
    }

    struct Node *current = head;
    int counter = 0;
    for (; current != NULL; current = current->next)
    {

        printf("Node %d: %d\n", counter, current->data);
        counter++;
    }

    printf("End of linked list\n");
    return;
}

void append_to_end(struct Node *head, struct Node *new_node)
{
    // reach end of linked list and
    struct Node *current = head;
    for (; current->next != NULL; current = current->next)
    {
    }

    current->next = new_node;
    return;
}

int get_length(struct Node *head)
{
    int counter = 0;
    struct Node *current = head;
    for (; current->next != NULL; current = current->next)
    {
        counter++;
    }

    return counter;
}

// linked list to string
char *linked_list_to_string(struct Node *head)
{
    char *str = malloc(100 * sizeof(char));
    struct Node *current = head;
    int counter = 0;
    for (; current != NULL; current = current->next)
    {
        counter += sprintf(str + counter, "%d -> ", current->data);
    }

    sprintf(str + counter, "NULL");
    return str;
}

int test_linked_list()
{

    struct Node head = {0, NULL};
    // struct Node tail = {0, NULL};

    // set head next is tail
    // head.next = &tail;

    struct Node node1 = {1, NULL};
    struct Node node2 = {2, NULL};
    struct Node node3 = {3, NULL};

    node1.next = &node2;
    node2.next = &node3;

    head.next = &node1;
    // node3.next = &tail;

    print_linked_list(head.next);
    printf("adding to end of node\n");
    struct Node new_node = {4, NULL};
    append_to_end(&head, &new_node);
    print_linked_list(head.next);

    // get length of linked list
    int length = get_length(&head);
    printf("Length of linked list is %d\n", length);
    if (length != 4)
    {
        printf("Testcase failed for get_length\n");
        return 1;
    }

    // linked list to string
    char *str = linked_list_to_string(&head);
    printf("Linked list to string is %s\n", str);
    char *expected_str = "1 -> 2 -> 3 -> 4 -> NULL";
    if (strcmp(str, expected_str) != 0)
    {
        printf("Testcase failed for linked_list_to_string\n");
        return 1;
    }

    return 0;
}

int main()
{

    if (test_linked_list() != 0)
    {
        printf("Linked list testcases failed\n");
    }

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
