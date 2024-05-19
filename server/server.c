#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *handle_connection(void *socket_desc)
{
    int new_socket = *(int *)socket_desc;
    free(socket_desc); // Free the memory allocated for the socket descriptor

    char buffer[BUFFER_SIZE] = {0};
    int read_val;

    for (;;)
    {
        printf("Waiting for data\n");
        // Reading data from the client
        read_val = read(new_socket, buffer, BUFFER_SIZE);
        if (read_val <= 0)
        {
            printf("Failed to read data or connection closed\n");
            break;
        }

        printf("Received: %s\n", buffer);

        // Sending a response to the client
        const char *message = "Hello from server";
        if (write(new_socket, message, strlen(message) + 1) < 0)
        {
            printf("Failed to send message\n");
            break;
        }

        printf("Hello message sent\n");
    }

    // Closing the socket
    printf("Closing the socket\n");
    close(new_socket);
    printf("Connection closed\n");

    return NULL;
}

// start server
int main()
{
    int server_fd, *new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setting up the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the specified port with retrying if the port is already in use
    for (;;)
    {
        printf("Binding to port %d\n", PORT);
        if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0)
        {
            perror("bind failed");
            continue;
        }
        else
        {
            break;
        }
    }

    // Listening for incoming connections
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    // Accepting connections from clients
    for (;;)
    {
        printf("Waiting for a connection\n");

        new_socket = malloc(sizeof(int));
        if (new_socket == NULL)
        {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }

        *new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (*new_socket < 0)
        {
            perror("accept failed");
            free(new_socket);
            continue;
        }

        printf("Connection accepted\n");

        // Creating a thread for each new connection
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_connection, (void *)new_socket) < 0)
        {
            perror("could not create thread");
            free(new_socket);
            continue;
        }

        printf("Handler assigned\n");
        pthread_detach(thread_id); // Detach the thread so that it cleans up after itself
    }

    printf("Closing the server\n");
    close(server_fd);
    return 0;
}
