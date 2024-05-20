#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include "main.h"
#include <pthread.h>

// start client
int main()
{
    for (int client_id = 0;; client_id++)
    {
        pthread_t thread;
        int *arg = malloc(sizeof(int));
        if (arg == NULL)
        {
            printf("Failed to allocate memory\n");
            exit(1);
        }
        *arg = client_id;
        if (pthread_create(&thread, NULL, connect_to_server, arg) != 0)
        {
            printf("Failed to create thread\n");
            free(arg);
            exit(1);
        }
        // Optionally detach the thread if you don't want to join later
        pthread_detach(thread);

        usleep(5000); // Sleep for 50ms before creating the next client
    }

    return 0;
}

void *connect_to_server(void *arg_client_id)
{
    int client_id = *(int *)arg_client_id;
    free(arg_client_id);

    // Set thread name
    char thread_name[16];
    snprintf(thread_name, sizeof(thread_name), "client_%d", client_id);
    pthread_setname_np(thread_name);

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
            close(sockfd); // Close the socket on failure to connect
            continue;
        }

        printf("Connected to the server\n");

        for (int i = 0;; i++)
        {
            // send current unix timestamp to the server
            char data[1024];
            sprintf(data, "client_id %d %d\n", client_id, i);
            write(sockfd, data, strlen(data));

            // read data from the server
            char buffer[1024];
            read(sockfd, buffer, 1024);
            printf("cleint_id %d Data received: %s\n", client_id, buffer);

            // sleep for 500ms
            usleep(500000);
        }
    }
    printf("Closing the connection\n");
    // Close the socket
    close(sockfd);
    return NULL; // Return NULL to match the pthread function signature
}
