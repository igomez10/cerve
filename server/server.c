#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define BACKLOG 3

void *handle_connection(void *socket_desc)
{
    int new_socket = *(int *)socket_desc;
    free(socket_desc);

    char buffer[BUFFER_SIZE] = {0};
    int read_val;

    for (;;)
    {
        printf("Waiting for data\n");
        read_val = read(new_socket, buffer, BUFFER_SIZE);
        if (read_val <= 0)
        {
            if (read_val == 0)
            {
                printf("Client disconnected\n");
            }
            else
            {
                perror("Failed to read data");
            }
            break;
        }

        printf("Received: %s\n", buffer);

        const char *message = "Hello from server";
        if (write(new_socket, message, strlen(message)) < 0)
        {
            perror("Failed to send message");
            break;
        }

        printf("Hello message sent\n");
    }

    printf("Closing the socket\n");
    close(new_socket);
    printf("Connection closed\n");

    return NULL;
}

void start_server()
{
    int server_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    while (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0)
    {
        perror("Bind failed, retrying");
        sleep(1); // wait before retrying
    }

    if (listen(server_fd, BACKLOG) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1)
    {
        printf("Waiting for a connection\n");

        int *new_socket = malloc(sizeof(int));
        if (new_socket == NULL)
        {
            perror("Malloc failed");
            exit(EXIT_FAILURE);
        }

        *new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (*new_socket < 0)
        {
            perror("Accept failed");
            free(new_socket);
            continue;
        }

        printf("Connection accepted\n");

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_connection, (void *)new_socket) < 0)
        {
            perror("Could not create thread");
            free(new_socket);
            continue;
        }

        pthread_detach(thread_id);
        printf("Handler assigned\n");
    }

    close(server_fd);
}

int main()
{
    start_server();
    return 0;
}
