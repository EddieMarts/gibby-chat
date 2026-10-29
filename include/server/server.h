#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "error_handler.h"

#define PORT 8080

void *server_send(void *sock);
void *server_receive(void *sock);
int run_server();