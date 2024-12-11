//
// Created by mahdi on 11/12/2024.
//

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv) {
    if(argc != 3) {
        printf("Missing arguments! \n");
        exit(0);
    }
    printf("Host: %s\t",argv[1]);
    printf("File: %s\n",argv[2]);
}
