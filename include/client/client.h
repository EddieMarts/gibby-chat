#pragma once

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "error_handler.h"

#define PORT 8081

int run_client();