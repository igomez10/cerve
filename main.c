#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
// time
#include <time.h>
// Forward declaration of the struct Person
struct Person;

// Define the structure (class) Person
typedef struct Person
{
    char name[50];
    int age;
} Person;

// Function to set the name of the person
void set_name(Person *p, const char *name)
{
    // Copy the name to the person's name field
    strncpy(p->name, name, sizeof(p->name) - 1);
    // Ensure the name is null-terminated
    p->name[sizeof(p->name) - 1] = '\0';
}

// Function to set the age of the person
void set_age(Person *p, int age)
{
    // Set the age of the person
    p->age = age;
}

int get_age(Person *p)
{
    return p->age;
}

// Function to create a new person
Person *new_person(const char *name, int age)
{
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Initialize the person
    set_name(p, name);
    set_age(p, age);

    return p;
}

int testPerson()
{
    Person *john = new_person("John Doe", 30);
    if (john == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    if (john->age != 30)
    {
        printf("Error: John age is not 30 but %d\n", john->age);
        exit(EXIT_FAILURE);
    }

    if (strcmp(john->name, "John Doe") != 0)
    {
        printf("Error: John name is not John Doe\n");
        exit(EXIT_FAILURE);
    }

    set_name(john, "John Smith");
    if (strcmp(john->name, "John Smith") != 0)
    {
        printf("Error: John name is not John Smith\n");
        exit(EXIT_FAILURE);
    }

    set_age(john, 35);
    if (john->age != 35)
    {
        printf("Error: John age is not 35\n");
        exit(EXIT_FAILURE);
    }
    free(john);
    return 0;
}

int testArrays()
{
    // Declare an array of pointers to integers
    int numbers[3];

    // Assign values to the array elements
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;

    if (numbers[0] != 1)
    {
        printf("Error: numbers[0] is not 1\n");
        exit(EXIT_FAILURE);
    }

    // size of data type
    int datatype = sizeof(numbers[0]);
    // printf("Datatype: %d\n", datatype);

    // size of array
    int size = sizeof(numbers);
    // printf("Size: %d\n", size);

    // print length of array
    int length = size / datatype;
    // printf("Length: %d\n", length);
    if (length != 3)
    {
        printf("Error: length of numbers is not 3\n");
        exit(EXIT_FAILURE);
    }

    // append to array
    int new_numbers[4];
    for (int i = 0; i < length; i++)
    {
        new_numbers[i] = numbers[i];
    }
    new_numbers[3] = 4;

    return 0;
}

void initializeArrayWithMemoryLeak()
{
    // initializeArrayWithMemoryLeak(10000000);
    long *numbers = (long *)malloc(10000);
    if (numbers == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // set the values
    for (long j = 0; j < 1000; j++)
    {
        numbers[j] = j;
    }

    free(numbers);
}

int main()
{
    testPerson();
    testArrays();

    int sockfd;

    for (;;)
    {
        // Create socket
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1)
        {
            printf("Failed to create socket");
            exit(0);
        }
        else
        {
            printf("Socket created successfully\n");
        }

        struct sockaddr_in serv_addr;

        // Initialize serv_addr to zero
        bzero(&serv_addr, sizeof(serv_addr));

        // Set the necessary fields
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(8080);
        printf("Connecting to the server\n");
        // connect to the server
        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        {
            printf("Failed to connect to the server\n");
            usleep(500000);
            continue;
        }

        printf("Connected to the server\n");

        for (int i = 0;; i++)
        {
            // send current unix timestamp to the server
            char data[1024];
            sprintf(data, "%d\n", i);
            write(sockfd, data, strlen(data));

            // read data from the server
            char buffer[1024];
            read(sockfd, buffer, 1024);
            printf("Data received: %s\n", buffer);

            // sleep for 500ms
            usleep(500000);
        }
    }
    printf("Closing the connection\n");
    // Close the socket
    close(sockfd);

    return 0;
}
