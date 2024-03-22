#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 5000

int main(void)
{
    char buffer[80];
    struct sockaddr_in server_address;
    struct sockaddr_in connection_address;
    char *message = "Hello from server";

    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_descriptor < 0)
    {
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int status = bind(socket_descriptor, (struct sockaddr*)&server_address, sizeof(server_address));
    if (status != 0)
    {
        perror("Error in binding");
        exit(EXIT_FAILURE);
    }

    // listen to the incoming connections
    status = listen(socket_descriptor, 4);
    if (status < 0)
    {
        perror("Could'nt listen to the connection");
        exit(EXIT_FAILURE);
    }

    // Accept connections
    socklen_t length_of_addr = sizeof(connection_address);
    int client_socket = accept(socket_descriptor, (struct sockaddr*)&server_address, &length_of_addr);
    if (status < 0)
    {
        perror("Could'nt establish connection to the client");
        exit(EXIT_FAILURE);
    }

    int bytes_read = read(client_socket, buffer, 80);
    buffer[bytes_read] = '\0';
    printf("Message from client: %s", buffer);

    send(client_socket, message, strlen(message), 0);
    // Close all connections
    close(socket_descriptor);
    close(client_socket);

    return 0;
}