#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 8080          // Server listening port
#define MAX_CLIENTS 10     // Maximum number of clients
#define BUFFER_SIZE 1024   // Buffer size for messages

int main() {
    int server_fd, new_socket, client_sockets[MAX_CLIENTS];
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    fd_set readfds; // Set of socket descriptors

    // Initialize all client sockets to 0 (not connected)
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
    }

    // Create a socket (IPv4, TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the server address structure
    address.sin_family = AF_INET;         // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Bind to any IP
    address.sin_port = htons(PORT);       // Convert port to network byte order

    // Bind the socket to the specified address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Listening on port %d...\n", PORT);

    while (1) {
        FD_ZERO(&readfds);      // Clear the socket set
        FD_SET(server_fd, &readfds); // Add server socket to the set
        int max_sd = server_fd;

        // Add active client sockets to the set
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_sockets[i];
            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_sd) max_sd = sd;
        }

        // Monitor sockets for activity (blocking until an event occurs)
        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0) {
            perror("Select error");
            continue;
        }

        // New connection request
        if (FD_ISSET(server_fd, &readfds)) {
            int addrlen = sizeof(address);
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                perror("Accept failed");
                continue;
            }

            printf("New client connected: %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            // Store new socket in client list
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = new_socket;
                    break;
                }
            }
        }

        // Handle client messages
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_sockets[i];

            if (FD_ISSET(sd, &readfds)) {
                int valread = read(sd, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    // Client disconnected
                    close(sd);
                    client_sockets[i] = 0;
                    printf("Client disconnected\n");
                } else {
                    buffer[valread] = '\0';
                    printf("Client: %s\n", buffer);
                }
            }
        }
    }

    return 0;
}
