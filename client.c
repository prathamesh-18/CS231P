

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      
#include <arpa/inet.h>   

#define PORT 12345 
#define SERVER_IP "192.168.56.101" 

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "Hello Sockets";

    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }


    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }


    send(sock, hello, strlen(hello), 0);
    printf("Message sent to server: %s\n", hello);


    close(sock);
    return 0;
}
