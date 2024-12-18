//
// Created by mahdi on 11/12/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "utils.h"

void validate_arguments(int argc) {
    if (argc != 3) {
        fprintf(stderr, WRONG_PARAMETER_ERROR);
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
        exit(EXIT_FAILURE);
    }
    return res;
}

void print_resolved_ip(struct addrinfo *res) {
    char ipstr[INET_ADDRSTRLEN];
    struct sockaddr_in *ipv4 = (struct sockaddr_in *) res->ai_addr;

    if (inet_ntop(AF_INET, &(ipv4->sin_addr), ipstr, sizeof(ipstr)) == NULL) {
        exit(EXIT_FAILURE);
    }

    printf(RESOLVED_IP, ipstr);
}

void send_rrq(int sockfd, struct sockaddr *server_addr, socklen_t addr_len, const char *file) {
    char buffer[BUFFER_SIZE];
    int offset = 0;

    buffer[offset++] = 0;
    buffer[offset++] = RRQ_OPCODE;

    strcpy(&buffer[offset], file);
    offset += strlen(file) + 1;

    strcpy(&buffer[offset], MODE);
    offset += strlen(MODE) + 1;

    ssize_t sent = sendto(sockfd, buffer, offset, 0, server_addr, addr_len);
    if (sent < 0) {
        exit(EXIT_FAILURE);
    }
}

int socket_init(struct addrinfo *res) {
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        freeaddrinfo(res);
        return -1;
    }
    return sockfd;
}

void receive_single_data(int sockfd, struct sockaddr *server_addr, socklen_t addr_len) {
    char buffer[BUFFER_SIZE];
    ssize_t received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, server_addr, &addr_len);
    if (received < 0) {
        exit(EXIT_FAILURE);
    }

    if (buffer[1] != 3) {
        exit(EXIT_FAILURE);
    }

    uint16_t block_number = ntohs(*(uint16_t *) &buffer[2]);
    printf(SUCCESS_RCV, block_number);

    for (int i = 4; i < 16 && i < received; i++) {
        printf("%02x ", (unsigned char) buffer[i]);
    }
    printf("\n");

    char ack[4];
    ack[0] = 0;
    ack[1] = 4;
    *(uint16_t *) &ack[2] = htons(block_number);
    if (sendto(sockfd, ack, sizeof(ack), 0, server_addr, addr_len) < 0) {
        exit(EXIT_FAILURE);
    }
}

void receive_multiple_data(int sockfd, struct sockaddr *server_addr, socklen_t addr_len, const char *file) {
    FILE *output = fopen(file, WRITE_BINARY);
    if (!output) {
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    uint16_t expected_block = 1;

    while (1) {
        ssize_t received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, server_addr, &addr_len);
        if (received < 0) {
            exit(EXIT_FAILURE);
        }

        printf(SUCCESS_RCV_PACKET, received);

        for (int i = 0; i < received; i++) {
            printf("%02X ", (unsigned char) buffer[i]);
        }
        printf("\n");

        if (buffer[1] != 3) {
            exit(EXIT_FAILURE);
        }

        uint16_t block_number = ntohs(*(uint16_t *) &buffer[2]);

        printf(RCV_MSG_OVERVIEW, expected_block, block_number);

        if (block_number != expected_block) {
            exit(EXIT_FAILURE);
        }

        printf(RCV_OVERVIEW, received - 4, (int) (received - 4), &buffer[4]);

        fwrite(&buffer[4], 1, received - 4, output);

        char ack[4];
        ack[0] = 0;
        ack[1] = 4;
        *(uint16_t *) &ack[2] = htons(block_number);
        if (sendto(sockfd, ack, sizeof(ack), 0, server_addr, addr_len) < 0) {
            exit(EXIT_FAILURE);
        }

        if (received < BUFFER_SIZE) {
            break;
        }

        expected_block++;
    }

    fclose(output);
}

void send_wrq(int sockfd, struct sockaddr_in *server_addr, const char *filename) {
    char buffer[BUFFER_SIZE];
    int offset = 0;

    buffer[offset++] = 0;
    buffer[offset++] = TFTP_OP_WRQ;

    strcpy(&buffer[offset], filename);
    offset += strlen(filename) + 1;

    strcpy(&buffer[offset], MODE);
    offset += strlen(MODE) + 1;

    ssize_t sent = sendto(sockfd, buffer, offset, 0, (struct sockaddr *)server_addr, sizeof(*server_addr));
    if (sent < 0) {
        exit(EXIT_FAILURE);
    }

    printf(SUCCESS_WRQ, filename);

    char ack[4];
    socklen_t addr_len = sizeof(*server_addr);
    ssize_t received = recvfrom(sockfd, ack, sizeof(ack), 0, (struct sockaddr *)server_addr, &addr_len);
    if (received < 0) {
        exit(EXIT_FAILURE);
    }

    if (ack[1] != 4 || ntohs(*(uint16_t *) &ack[2]) != 0) {
        fprintf(stderr, "Error: Expected ACK block 0, got block %d\n", ntohs(*(uint16_t *) &ack[2]));
        exit(EXIT_FAILURE);
    }

    printf("Received ACK for block 0\n");
}

void send_single_data_packet(int sockfd, struct sockaddr_in *server_addr, const char *file) {
    char buffer[BUFFER_SIZE];
    FILE *input = fopen(file, READ_BINARY);
    if (!input) {
        exit(EXIT_FAILURE);
    }

    size_t data_len = fread(&buffer[4], 1, BUFFER_SIZE - 4, input);
    fclose(input);

    buffer[0] = 0;
    buffer[1] = TFTP_OP_DATA;
    buffer[2] = 0;
    buffer[3] = 1;

    ssize_t sent = sendto(sockfd, buffer, data_len + 4, 0, (struct sockaddr *)server_addr, sizeof(*server_addr));
    if (sent < 0) {
        exit(EXIT_FAILURE);
    }

    printf(SUCCESS_ACK_1);
}

void send_multiple_data_packets(int sockfd, struct sockaddr_in *server_addr, const char *file) {
    char buffer[BUFFER_SIZE];
    FILE *input = fopen(file, READ_BINARY);
    if (!input) {
        exit(EXIT_FAILURE);
    }

    uint16_t block_number = 1;
    ssize_t data_len;
    socklen_t addr_len = sizeof(*server_addr);


    while ((data_len = fread(&buffer[4], 1, BUFFER_SIZE - 4, input)) > 0) {
        buffer[0] = 0;
        buffer[1] = TFTP_OP_DATA;
        buffer[2] = (block_number >> 8) & 0xFF;
        buffer[3] = block_number & 0xFF;

        ssize_t sent = sendto(sockfd, buffer, data_len + 4, 0, (struct sockaddr *)server_addr, addr_len);
        if (sent < 0) {
            exit(EXIT_FAILURE);
        }

        printf("Data packet %d sent\n", block_number);

        char ack[4];
        ssize_t received = recvfrom(sockfd, ack, sizeof(ack), 0, (struct sockaddr *)server_addr, &addr_len);
        if (received < 0) {
            exit(EXIT_FAILURE);
        }

        if (ack[1] != 4) {
            exit(EXIT_FAILURE);
        }

        uint16_t ack_block_number = ntohs(*(uint16_t *) &ack[2]);
        if (ack_block_number != block_number) {
            exit(EXIT_FAILURE);
        }

        printf(SUCCESS_ACK, block_number);

        if (data_len < BUFFER_SIZE - 4) {
            break;
        }

        block_number++;
    }

    fclose(input);
    printf(FINALIZATION_MSG);
}