#include <stdio.h>
#include <netdb.h>
#include "utils.h"


int main(int argc, char **argv) {
    validate_arguments(argc);

    const char *host = argv[1];
    const char *file = argv[2];

    struct addrinfo *res = resolve_host(host);
    // print_resolved_ip(res);

    int sockfd = socket_init(res);

    freeaddrinfo(res);
    // printf("File to process: %s\n", file);
    return 0;
}

