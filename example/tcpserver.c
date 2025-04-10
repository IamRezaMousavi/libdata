#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT        8080
#define BUFFER_SIZE 1024

void *handle_client(void *client_socket) {
    int *client_fd = (int *)client_socket;
    printf("[%d] Connected a client.\n", *client_fd);

    char buffer[BUFFER_SIZE] = {0};
    int  recbytes            = recv(*client_fd, buffer, BUFFER_SIZE, 0);
    if (recbytes > 0)
        printf("[%d] Received message [%d bytes]: %s\n", *client_fd, recbytes, buffer);

    send(*client_fd, "Hello Client!", 14, 0);

    close(*client_fd);
    printf("[%d] Connection closed.\n", *client_fd);
    free(client_fd);

    return NULL;
}

int main(int argc, const char *argv[]) {
    int                server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char               buffer[BUFFER_SIZE] = {0};
    socklen_t          addr_len            = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("[server] socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("[server] bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("[server] listen failed");
        exit(EXIT_FAILURE);
    }

    printf("[server] listening on port %d...\n", PORT);

    while (1) {
        int *client_fd = malloc(sizeof(int));
        *client_fd     = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (*client_fd < 0) {
            perror("[server] accept failed");
            exit(EXIT_FAILURE);
        }

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void *)client_fd) != 0) {
            perror("pthread_create failed");
            close(*client_fd);
            free(client_fd);
        }
        pthread_detach(thread_id);
    }

    close(server_fd);
    return EXIT_SUCCESS;
}
