#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"

int main(int argc, const char *argv[]) {
  int                sock_fd;
  struct sockaddr_in server_addr;
  char               message[BUFFER_SIZE] = {0};
  strcat(message, "Hello, Server!");

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
	perror("socket failed");
	exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(PORT);

  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) < 0) {
	perror("Invalid address");
	exit(EXIT_FAILURE);
  }

  if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
	perror("connect failed");
	exit(EXIT_FAILURE);
  }

  send(sock_fd, message, strlen(message), 0);
  printf("Message sent to server: %s\n", message);

  memset(message, 0, BUFFER_SIZE);
  int valread = recv(sock_fd, message, BUFFER_SIZE, 0);
  if (valread > 0) printf("Received message: %s\n", message);

  close(sock_fd);

  return 0;
}
