#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;

    // size of address structure
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

    // Binding the socket to the specified port with
    // retrying if the port is already in use
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

    // Accepting a connection from a client
    for (;;)
    {
        printf("Waiting for a connection\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0)
        {
            continue;
        }

        printf("Connection accepted\n");
        for (;;)
        {
            printf("Waiting for data\n");
            // Reading data from the client
            char buffer[BUFFER_SIZE] = {0};
            int read_val = read(new_socket, buffer, BUFFER_SIZE);
            printf("Data received\n");
            if (read_val < 0)
            {
                printf("failed to read data");
                break;
            }

            printf("Received: %s\n", buffer);

            // Sending a response to the client
            printf("Sending response\n");
            const char *message = "Hello from server";
            int sentres = write(new_socket, message, strlen(message) + 1);
            if (sentres < 0)
            {
                printf("failed to send message");
                break;
            }

            printf("Hello message sent\n");
        }

        // Closing the socket
        printf("Closing the socket\n");
        close(new_socket);
        printf("Connection closed\n");
    }

    printf("Closing the server\n");
    close(server_fd);
    return 0;
}
