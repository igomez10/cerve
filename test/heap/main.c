#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int *values;
    int length;
    int capacity;
} Array;

Array new_array(int length, int capacity)
{

    if (length > capacity)
    {
        printf("invalid length cannot be smaller than capacity");
        exit(1);
    }

    Array res;
    res.values = (int *)malloc(sizeof(int) * capacity);
    if (res.values == NULL)
    {
        printf("failed to allocate memory");
        exit(1);
    }
    res.length = length;
    res.capacity = capacity;

    return res;
}

void append(Array *array, int new_element)
{
    // if length < capacity, add element at index size
    if (array->length < array->capacity)
    {
        array->values[array->length] = new_element;
        array->length += 1;
        return;
    }

    // create a new array with a new capacity of 2x + 1
    int new_capacity = array->capacity * 2 + 1;
    Array bigger_array = new_array(array->length, new_capacity);
    for (int i = 0; i < array->length; i++)
    {
        bigger_array.values[i] = array->values[i];
    }

    // add new element
    bigger_array.values[array->length] = new_element;
    bigger_array.length += 1;

    free(array->values);
    *array = bigger_array;
}

// pop will remove the first element of the array, move the last element to the first and
// bubble down the element to the correct position
int pop(Array *given_heap)
{
    if (given_heap->length == 0)
    {
        printf("cannot pop from an empty heap\n");
        exit(1);
    }

    // printf("popping\n");
    // switch the first and last element
    int temp = given_heap->values[0];
    given_heap->values[0] = given_heap->values[given_heap->length - 1];
    given_heap->values[given_heap->length - 1] = temp;
    given_heap->length -= 1;

    // bubble down the element to the correct position
    // if current element is on index i, the left child is on index 2i + 1
    // if the left child is smaller than the current element, swap the left child with the current element
    // if the right child is smaller than the current element, swap the right child with the current element
    int current_index = 0;
    for (; current_index < given_heap->length;)
    {
        // printf("current index %d\n", current_index);
        // check left child
        int left_child = current_index * 2 + 1;
        int right_child = current_index * 2 + 2;

        if (left_child < given_heap->length && given_heap->values[left_child] < given_heap->values[current_index])
        {
            // swap current with left child
            int tmp = given_heap->values[current_index];
            given_heap->values[current_index] = given_heap->values[left_child];
            given_heap->values[left_child] = tmp;
            current_index = left_child;
            continue;
        }
        // check right child
        if (right_child < given_heap->length && given_heap->values[right_child] < given_heap->values[current_index])
        {
            // swap current with right child
            int tmp = given_heap->values[current_index];
            given_heap->values[current_index] = given_heap->values[right_child];
            given_heap->values[right_child] = tmp;
            current_index = right_child;
            continue;
        }

        break;
    }

    // printf("popped\n");
    return temp;
}
// push
void push(Array *given_heap, int new_element)
{
    // place the element at the end of the array and bubble up the element to the correct position
    append(given_heap, new_element);

    int current_index = given_heap->length - 1;

    for (; given_heap->values[current_index] < given_heap->values[current_index / 2];)
    {
        int parent_index = current_index / 2;
        {
            int tmp = given_heap->values[parent_index];
            given_heap->values[parent_index] = given_heap->values[current_index];
            given_heap->values[current_index] = tmp;
            current_index = current_index / 2;
        }
    }
}

// top
int top(Array given_head)
{
    // return the top element
    if (given_head.length == 0)
    {
        printf("cannot get top of an empty heap\n");
        exit(1);
    }

    return given_head.values[0];
}

void print_array(Array given_array)
{
    for (int i = 0; i < given_array.length; i++)
    {
        printf("element at index %d is %d\n", i, given_array.values[i]);
    }
}

char *to_string(Array given_array)
{
    char *res = (char *)malloc(sizeof(char) * 100);
    if (res == NULL)
    {
        printf("failed to allocate memory\n");
        exit(1);
    }

    for (int i = 0; i < given_array.length; i++)
    {
        char *tmp = (char *)malloc(sizeof(char) * 100);
        if (tmp == NULL)
        {
            printf("failed to allocate memory\n");
            exit(1);
        }
        sprintf(tmp, "%d ", given_array.values[i]);
        strcat(res, tmp);
        free(tmp);
    }

    return res;
}

int test_heap()
{
    printf("starting heap tests\n");
    // array of integers
    Array arr = new_array(3, 10);
    arr.values[0] = 0;
    arr.values[1] = 1;
    arr.values[2] = 2;

    printf("testing pop\n");
    int popped = pop(&arr);
    if (popped != 0)
    {
        printf("Testcase 1 failed pop, expected 0, got %d\n", popped);
        return 1;
    }

    printf("tested pop\n");
    if (arr.values[0] != 1)
    {
        printf("Testcase 2 failed pop, expected 1, got %d\n", arr.values[0]);
        return 1;
    }

    if (arr.length != 2)
    {
        printf("Testcase 3 failed pop, expected 2, got %d\n", arr.length);
        return 1;
    }

    popped = pop(&arr);
    // print_array(arr);
    if (popped != 1)
    {
        printf("Testcase 4 failed pop, expected 1, got %d\n", popped);
        print_array(arr);
        return 1;
    }
    if (arr.length != 1)
    {
        printf("Testcase 5 failed pop, expected 1, got %d\n", arr.length);
        return 1;
    }
    if (arr.values[0] != 2)
    {
        printf("Testcase 6 failed pop, expected 2 as first element, got %d\n", arr.values[0]);
        return 1;
    }

    pop(&arr);

    // validate length is 0
    if (arr.length != 0)
    {
        printf("Testcase 7 failed pop, expected 0, got %d\n", arr.length);
        return 1;
    }

    push(&arr, 9);
    if (arr.length != 1)
    {
        printf("Testcase 8 failed push, expected 1, got %d\n", arr.length);
        return 1;
    }

    if (top(arr) != 9)
    {
        printf("Testcase 1 failed top, expected 5, got %d\n", top(arr));
        return 1;
    }

    push(&arr, 5);
    push(&arr, 3);
    push(&arr, 1);
    push(&arr, 7);
    push(&arr, 2);
    push(&arr, 99);
    push(&arr, 120);

    if (arr.length != 8)
    {
        printf("Testcase 9 failed push, expected 8, got %d\n", arr.length);
        return 1;
    }

    print_array(arr);

    if (arr.values[0] != 1)
    {
        printf("Testcase 10 failed push, expected 1, got %d\n", arr.values[0]);
        return 1;
    }

    printf("heap tests passed\n");
    return 0;
}

int test_array()
{
    // array of integers
    int length = 3;
    int capacity = 4;
    Array arr = new_array(length, capacity);
    arr.values[0] = 0;
    arr.values[1] = 100;
    arr.values[2] = 255;

    if (arr.capacity != capacity)
    {
        printf("unexpected capacity %d %d\n", arr.capacity, capacity);
        return 1;
    }

    if (arr.length != length)
    {
        printf("unexpected length %d %d\n", arr.length, length);
        return 1;
    }

    // traverse array
    for (int i = 0; i < arr.length; i++)
    {
        // printf("Element at index %d\n", arr.values[i]);
    }

    if (arr.values[0] != 0)
    {
        printf("Testcase 1 failed, expected 0, got %d\n", arr.values[0]);
        return 1;
    }

    if (arr.values[1] != 100)
    {
        printf("Testcase 1 failed, expected 100, got %d\n", arr.values[0]);
        return 1;
    }

    arr.values[2] = 255;
    if (arr.values[2] != 255)
    {
        printf("Testcase 2 failed, expected 255, got %d\n", arr.values[5]);
        return 1;
    }

    int old_length = arr.length;
    int new_value = 19;
    append(&arr, new_value);
    if (arr.length != old_length + 1)
    {
        printf("unexpected length %d %d", old_length + 1, arr.length);
        return 1;
    }

    if (arr.values[arr.length - 1] != new_value)
    {
        printf("unexpected value %d %d", new_value, arr.values[arr.length - 1]);
        return 1;
    }

    // trigger array resizing
    old_length = arr.length;
    new_value = 300;
    append(&arr, new_value);
    if (arr.length != old_length + 1)
    {
        printf("unexpected length %d %d\n", arr.length, old_length + 1);
        return 1;
    }

    if (arr.values[arr.length - 1] != new_value)
    {
        printf("unexpected value %d %d\n", arr.values[arr.length - 1], new_value);
        return 1;
    }

    // validate capacity is now 2x + 1
    if (arr.capacity != capacity * 2 + 1)
    {
        printf("unexpected capacity %d %d\n", capacity * 2 + 1, arr.capacity);
        return 1;
    }

    printf("Array tests passed\n");
    return 0;
}

int main()
{
    test_array();
    int test_array_res = test_array();
    printf("finished testing array %d", test_array_res);
    if (test_array_res != 0)
    {
        printf("array tests failed");
    }
    else
    {
        printf("array tests successful");
    }
    printf("starting\n");
    printf("testing heap\n");
    int test_heap_res = test_heap();
    if (test_heap_res != 0)
    {
        printf("heap tests failed\n");
    }

    printf("finished testing\n");
    return 0;
}
