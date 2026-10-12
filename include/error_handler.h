#pragma once

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef enum{
    SOCKET_ERR,
    BIND_ERR,
    LISTEN_ERR,
    ACCEPT_ERR,
    CONNECT_ERR
} SOCKET_ERRORS;

int check_sock_error(int value, SOCKET_ERRORS err);