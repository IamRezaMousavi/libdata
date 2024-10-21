#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, const char *argv[]) {
  int                server_fd, client_fd;
  struct sockaddr_in server_addr, client_addr;
  char               buffer[BUFFER_SIZE] = {0};
  socklen_t          addr_len            = sizeof(client_addr);

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
	perror("socket failed");
	exit(EXIT_FAILURE);
  }

  server_addr.sin_family      = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port        = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
	perror("bind failed");
	exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0) {
	perror("listen failed");
	exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", PORT);

  while (1) {
	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
	if (client_fd == -1) {
	  perror("accept failed");
	  exit(EXIT_FAILURE);
	}

	printf("Connected to a client.\n");

	memset(buffer, 0, BUFFER_SIZE);
	int valread = recv(client_fd, buffer, BUFFER_SIZE, 0);
	if (valread > 0) printf("Received message: %s\n", buffer);

	send(client_fd, "Hello Client!", 14, 0);

	close(client_fd);
	printf("Connection closed.\n");
  }

  close(server_fd);
  return EXIT_SUCCESS;
}
