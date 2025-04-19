// client.c
// A simple TCP client that connects to server and sends a message

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // for close()
#include <arpa/inet.h>   // for sockaddr_in, inet_pton()

#define PORT 12345 // Must match the server's port
#define SERVER_IP "192.168.56.101" // Replace with Server VM's IP address

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "Hello Sockets";

    // Step 1: Create socket (IPv4, TCP)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Step 2: Define server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Step 3: Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Step 4: Send the message
    send(sock, hello, strlen(hello), 0);
    printf("Message sent to server: %s\n", hello);

    // Step 5: Close the socket
    close(sock);
    return 0;
}
