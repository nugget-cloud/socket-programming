#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8000
#define BUFFER_SIZE 100

int main() {
    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Initialize server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }
    printf("Connected to server.\n");

    // Chat loop
    char buffer[BUFFER_SIZE];
    while (1) {
        // Send message to server
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sockfd, buffer, strlen(buffer), 0);

        // Receive message from server
        memset(buffer, 0, BUFFER_SIZE);  // Clear buffer
        ssize_t bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            printf("Server disconnected or error occurred.\n");
            break;
        }
        printf("Server: %s\n", buffer);
    }

    // Close socket
    close(sockfd);

    return 0;
}
