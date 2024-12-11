//
// Created by mahdi on 11/12/2024.
//

#ifndef UTILS_H
#define UTILS_H

#include "constants.h"

void validate_arguments(int argc);
struct addrinfo* resolve_host(const char *host);
void print_resolved_ip(struct addrinfo *res);
int socket_init(struct addrinfo *res);
void send_rrq(int sockfd, struct sockaddr *server_addr, socklen_t addr_len, const char *file);
void receive_single_data(int sockfd, struct sockaddr *server_addr, socklen_t addr_len);
void receive_multiple_data(int sockfd, struct sockaddr *server_addr, socklen_t addr_len, const char *file);
#endif //UTILS_H
