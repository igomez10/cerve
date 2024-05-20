#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (head == NULL)
    {
        return 0;
    }

    int counter = 0;
    struct Node *current = head;
    for (; current != NULL; current = current->next)
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

void remove_last_element(struct Node *head)
{
    if (head == NULL)
    {
        return;
    }

    if (head->next == NULL)
    {
        head = NULL;
    }

    struct Node *current = head;

    // iterate until current.next.next == NULL
    for (; current->next->next != NULL; current = current->next)
    {
    }

    current->next = NULL;

    return;
}
int test_linked_list()
{
    struct Node node1 = {1, NULL};
    struct Node node2 = {2, NULL};
    struct Node node3 = {3, NULL};

    node1.next = &node2;
    node2.next = &node3;

    // print_linked_list(&node1);

    // get length of linked list
    {
        int length = get_length(&node1);
        // printf("Length of linked list is %d\n", length);
        if (length != 3)
        {
            printf("Testcase failed for get_length\n");
            return 1;
        }
    }

    {
        // printf("adding to end of node\n");
        struct Node new_node = {4, NULL};
        append_to_end(&node1, &new_node);
        // print_linked_list(node1.next);

        // get length of linked list
        int length = get_length(&node1);
        // printf("Length of linked list is %d\n", length);
        if (length != 4)
        {
            printf("Testcase failed for get_length\n");
            return 1;
        }
    }

    // linked list to string
    {
        char *str = linked_list_to_string(&node1);
        // printf("Linked list to string is %s\n", str);
        char *expected_str = "1 -> 2 -> 3 -> 4 -> NULL";
        if (strcmp(str, expected_str) != 0)
        {
            printf("Testcase failed for linked_list_to_string %s\n", str);
            return 1;
        }
    }

    {
        // remove last element
        remove_last_element(&node1);
        // check length is now 3
        int length = get_length(&node1);
        if (length != 3)
        {
            printf("unexpected length should be 3 but was %d\n", length);
            return 1;
        }

        char *str = linked_list_to_string(&node1);
        char *expectdstr = "1 -> 2 -> 3 -> NULL";
        if (strcmp(str, expectdstr) != 0)
        {
            printf("unexpected string format was %s\n", str);
            return 1;
        }
    }

    return 0;
}

int main()
{
    if (test_linked_list() == 0)
    {
        printf("All testcases passed\n");
    }
    else
    {
        printf("Some testcases failed\n");
    }

    return 0;
}
