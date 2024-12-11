//
// Created by mahdi on 11/12/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "utils.h"
#include "constants.h"

void validate_arguments(int argc) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./program <host> <file>\n");
        exit(EXIT_FAILURE);
    }
}


struct addrinfo *resolve_host(const char *host) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;

    int status = getaddrinfo(host, PORT, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    return res;
}


void print_resolved_ip(struct addrinfo *res) {
    char ipstr[INET_ADDRSTRLEN];
    struct sockaddr_in *ipv4 = (struct sockaddr_in *) res->ai_addr;

    if (inet_ntop(AF_INET, &(ipv4->sin_addr), ipstr, sizeof(ipstr)) == NULL) {
        perror("inet_ntop error");
        exit(EXIT_FAILURE);
    }

    printf("Resolved IP: %s\n", ipstr);
}


int socket_init(struct addrinfo *res) {
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        perror("socket error");
        freeaddrinfo(res);
        return -1;
    }
    return sockfd;
}
