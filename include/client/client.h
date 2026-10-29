#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "error_handler.h"

#define PORT 8080

void *client_send(void *sock);
void *client_receive(void *sock);
int run_client();