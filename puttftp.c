#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"


int main(int argc, char **argv) {
    validate_arguments(argc);

    const char *host = argv[1];
    const char *file = argv[2];

    struct addrinfo *res = resolve_host(host);
    // print_resolved_ip(res);

    int sockfd = socket_init(res);

    struct sockaddr_in server_addr;
    memcpy(&server_addr, res->ai_addr, sizeof(struct sockaddr_in));

    send_wrq(sockfd, &server_addr, file);

    send_multiple_data_packets(sockfd, &server_addr, file);

    close(sockfd);

    freeaddrinfo(res);
    // printf("File to process: %s\n", file);
    return 0;
}

