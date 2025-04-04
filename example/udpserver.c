#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <libdata/datastruct/queue.h>

#define BUFFER_SIZE (1024 * 1024)
#define NUM_WORKERS 8
#define PORT        8080

pthread_t workers[NUM_WORKERS];
Queue     worker_queues[NUM_WORKERS];
int       running = 1;
int       sockfd;

void *worker_function(void *arg) {
    int worker_id = *(int *)arg;
    free(arg);
    printf("[INFO] Worker id %d\n", worker_id);

    while (running) {
        char *data = (char *)queue_pop(&worker_queues[worker_id]);
        if (data == NULL)
            continue;
        printf("[INFO] Get Data\n");
        printf("[INFO] Data is %s\n", data);

        free(data);
    }

    return NULL;
}

void cleanup() {
    printf("\n[INFO] Cleaning up resources...\n");
    running = 0;

    for (int i = 0; i < NUM_WORKERS; i++) {
        pthread_join(workers[i], NULL);
        queue_destroy(&worker_queues[i], free);
    }

    close(sockfd);
    printf("[INFO] Resources cleaned up. Exiting.\n");
}

void signal_handler(int signum) {
    if (signum == SIGINT) {
        cleanup();
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char **argv) {
    struct sockaddr_in server_addr, client_addr;
    char               buffer[BUFFER_SIZE];
    socklen_t          addr_len = sizeof(client_addr);

    // Set up signal handler
    signal(SIGINT, signal_handler);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("[ERROR] Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(PORT);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("[ERROR] Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("[INFO] UDP server is running on port %d...\n", PORT);

    // Initialize worker queues
    for (int i = 0; i < NUM_WORKERS; i++) {
        queue_init(&worker_queues[i]);
    }

    // Create worker threads
    for (int i = 0; i < NUM_WORKERS; i++) {
        int *id = malloc(sizeof(int));
        *id     = i;
        if (pthread_create(&workers[i], NULL, worker_function, id) != 0) {
            perror("[ERROR] Worker thread creation failed");
            cleanup();
            exit(EXIT_FAILURE);
        }
    }

    // Main loop to receive data and distribute it
    uint8_t round_robin_index = 0;
    while (running) {
        ssize_t received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (received < 0) {
            if (errno == EINTR)
                continue; // Interrupted by signal
            perror("[ERROR] Receive failed");
            break;
        }

        char *data = malloc(sizeof(char) * received);
        memcpy(data, buffer, received);

        queue_push(&worker_queues[round_robin_index], data);

        round_robin_index = (round_robin_index + 1) % NUM_WORKERS;
    }

    cleanup();
    return EXIT_SUCCESS;
}
