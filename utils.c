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
        perror("sendto error");
        exit(EXIT_FAILURE);
    }
    /*printf("Sending RRQ to %s:%d\n",
           inet_ntoa(((struct sockaddr_in *) server_addr)->sin_addr),
           ntohs(((struct sockaddr_in *) server_addr)->sin_port));*/
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

void receive_single_data(int sockfd, struct sockaddr *server_addr, socklen_t addr_len) {
    char buffer[BUFFER_SIZE];
    ssize_t received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, server_addr, &addr_len);
    if (received < 0) {
        perror("recvfrom error");
        exit(EXIT_FAILURE);
    }

    if (buffer[1] != 3) {
        fprintf(stderr, "Unexpected packet received\n");
        exit(EXIT_FAILURE);
    }

    uint16_t block_number = ntohs(*(uint16_t *) &buffer[2]);
    printf("Received block %d, data: ", block_number);

    for (int i = 4; i < 16 && i < received; i++) {
        printf("%02x ", (unsigned char) buffer[i]);
    }
    printf("\n");

    char ack[4];
    ack[0] = 0;
    ack[1] = 4;
    *(uint16_t *) &ack[2] = htons(block_number);
    if (sendto(sockfd, ack, sizeof(ack), 0, server_addr, addr_len) < 0) {
        perror("sendto error");
        exit(EXIT_FAILURE);
    }
}

void receive_multiple_data(int sockfd, struct sockaddr *server_addr, socklen_t addr_len, const char *file) {
    FILE *output = fopen(file, "wb");
    if (!output) {
        perror("fopen error");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    uint16_t expected_block = 1;

    while (1) {
        ssize_t received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, server_addr, &addr_len);
        if (received < 0) {
            perror("recvfrom error");
            exit(EXIT_FAILURE);
        }

        printf("Received packet of size %zd\n", received);

        printf("Packet contents: ");
        for (int i = 0; i < received; i++) {
            printf("%02X ", (unsigned char) buffer[i]);
        }
        printf("\n");

        if (buffer[1] != 3) {
            fprintf(stderr, "Unexpected packet received\n");
            exit(EXIT_FAILURE);
        }

        uint16_t block_number = ntohs(*(uint16_t *) &buffer[2]);

        printf("Expected block: %d, Received block: %d\n", expected_block, block_number);

        if (block_number != expected_block) {
            fprintf(stderr, "Unexpected block number\n");
            exit(EXIT_FAILURE);
        }

        printf("Data received (up to %zd bytes): %.*s\n", received - 4, (int) (received - 4), &buffer[4]);

        fwrite(&buffer[4], 1, received - 4, output);

        char ack[4];
        ack[0] = 0;
        ack[1] = 4;
        *(uint16_t *) &ack[2] = htons(block_number);
        if (sendto(sockfd, ack, sizeof(ack), 0, server_addr, addr_len) < 0) {
            perror("sendto error");
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
    int filename_len = strlen(filename);
    int mode_len = 6;

    buffer[0] = 0;
    buffer[1] = TFTP_OP_WRQ;

    memcpy(&buffer[2], filename, filename_len + 1);

    memcpy(&buffer[2 + filename_len + 1], "octet", mode_len);

    ssize_t sent = sendto(sockfd, buffer, 2 + filename_len + 1 + mode_len, 0, (struct sockaddr *)server_addr, sizeof(*server_addr));
    if (sent < 0) {
        perror("sendto error in WRQ");
        exit(EXIT_FAILURE);
    }
    printf("Sent WRQ to server for file: %s\n", filename);
}

void send_single_data_packet(int sockfd, struct sockaddr_in *server_addr, const char *file) {
    FILE *fp = fopen(file, "rb");
    if (!fp) {
        perror("File open error");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read = fread(buffer + 4, 1, BUFFER_SIZE - 4, fp);
    if (bytes_read < 0) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }
    buffer[0] = 0;
    buffer[1] = TFTP_OP_DATA;
    uint16_t block_number = 1;
    *(uint16_t *)(buffer + 2) = htons(block_number);

    ssize_t sent = sendto(sockfd, buffer, bytes_read + 4, 0, (struct sockaddr *)server_addr, sizeof(*server_addr));
    if (sent < 0) {
        perror("sendto error in data packet");
        exit(EXIT_FAILURE);
    }

    printf("Sent single data packet with block number 1\n");

    fclose(fp);
}

void send_multiple_data_packets(int sockfd, struct sockaddr_in *server_addr, const char *file) {
    FILE *fp = fopen(file, "rb");
    if (!fp) {
        perror("File open error");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    uint16_t block_number = 1;

    while (1) {
        size_t bytes_read = fread(buffer + 4, 1, BUFFER_SIZE - 4, fp);
        if (bytes_read < 0) {
            perror("Error reading file");
            exit(EXIT_FAILURE);
        }

        buffer[0] = 0;
        buffer[1] = TFTP_OP_DATA;
        *(uint16_t *)(buffer + 2) = htons(block_number);

        ssize_t sent = sendto(sockfd, buffer, bytes_read + 4, 0, (struct sockaddr *)server_addr, sizeof(*server_addr));
        if (sent < 0) {
            perror("sendto error in data packet");
            exit(EXIT_FAILURE);
        }

        printf("Sent data packet with block number %d\n", block_number);

        char ack[4];
        ssize_t ack_received = recvfrom(sockfd, ack, sizeof(ack), 0, NULL, NULL);
        if (ack_received < 0) {
            perror("recvfrom error in ACK");
            exit(EXIT_FAILURE);
        }

        uint16_t ack_block_number = ntohs(*(uint16_t *)(ack + 2));
        if (ack_block_number != block_number) {
            fprintf(stderr, "Unexpected ACK block number. Expected %d, got %d\n", block_number, ack_block_number);
            exit(EXIT_FAILURE);
        }

        printf("Received ACK for block number %d\n", block_number);

        if (bytes_read < BUFFER_SIZE - 4) {
            break;
        }

        block_number++;
    }

    fclose(fp);
}