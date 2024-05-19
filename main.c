#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

// start client
int main()
{
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
