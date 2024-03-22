#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 5000

int main(void) {
  struct sockaddr_in server_address;
  char *message = "Hello from client";
  char buffer[1024] = {0};

  int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Initialize addr struct for binding addr and port
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  int lengthOfAddr = sizeof(server_address);
  int client_connection = connect(
      socketDescriptor, (struct sockaddr *)&server_address, lengthOfAddr);
  if (client_connection != 0) {
    perror("Failed to connect to server");
    exit(EXIT_FAILURE);
  }

  // Send to server
  send(socketDescriptor, message, strlen(message), 0);

  // Read from server
  read(socketDescriptor, buffer, 1024);
  printf("Message from server: %s", buffer);
  // Close socket
  close(socketDescriptor);
  return 0;
}