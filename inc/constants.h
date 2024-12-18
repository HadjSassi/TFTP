//
// Created by mahdi on 11/12/2024.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PORT "1069"
#define RRQ_OPCODE 1
#define BUFFER_SIZE 512
#define MODE "octet"
#define BUFFER_SIZE 512
#define TFTP_OP_WRQ 2
#define TFTP_OP_DATA 3
#define TFTP_OP_ACK 4
#define READ_BINARY "rb"
#define WRITE_BINARY "wb"
#define SUCCESS_WRQ "WRQ sent for file: %s\n"
#define SUCCESS_ACK "Received ACK for block %d\n"
#define SUCCESS_RCV "Received block %d, data: "
#define RCV_MSG_OVERVIEW "Expected block: %d, Received block: %d\n"
#define RCV_OVERVIEW "Data received (up to %zd bytes): %.*s\n"
#define SUCCESS_RCV_PACKET "Received packet of size %zd\n"
#define SUCCESS_ACK_1 "Single DATA packet sent (block 1)\n"
#define FINALIZATION_MSG "File transfer completed.\n"
#define WRONG_PARAMETER_ERROR "Usage: ./program <host> <file>\n"
#define RESOLVED_IP "Resolved IP: %s\n"


#endif //CONSTANTS_H
