//
// Created by mahdi on 11/12/2024.
//

#ifndef UTILS_H
#define UTILS_H

void validate_arguments(int argc);
struct addrinfo* resolve_host(const char *host);
void print_resolved_ip(struct addrinfo *res);
int socket_init(struct addrinfo *res);
#endif //UTILS_H
