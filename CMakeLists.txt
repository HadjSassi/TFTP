cmake_minimum_required(VERSION 3.22)
project(TFTP C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

add_executable(TFTP1 main.c
        utils.c)
add_executable(TFTP2 gettftp.c
        utils.c)
add_executable(TFTP3 puttftp.c
        utils.c)
