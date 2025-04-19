// server.c
// A simple TCP server that listens for a connection and prints received message

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // for close()
#include <arpa/inet.h>   // for sockaddr_in, inet_ntoa()

#define PORT 12345       // Port number for server
#define BUFFER_SIZE 1024 // Buffer to hold received data

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    // Step 1: Create socket (IPv4, TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Define the server address
    address.sin_family = AF_INET;         // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Accept any IP
    address.sin_port = htons(PORT);       // Convert to network byte order

    // Step 3: Bind the socket to the IP/port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Step 4: Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Step 5: Accept a connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Step 6: Read message from client
    int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
    buffer[bytes_read] = '\0'; // Null-terminate the received message
    printf("Received message: %s\n", buffer);

    // Step 7: Close sockets
    close(new_socket);
    close(server_fd);
    return 0;
}
