#include "error_handler.h"

int check_sock_error(int value, SOCKET_ERRORS err){
    if(value > 0) return 0;

    switch(err){
        case SOCKET_ERR:
            if (value < 0){
                perror("Failed socket");
                puts(strerror(errno));
                return -1;
            }

            break;
            
        case BIND_ERR:
            if (value < 0){
                perror("Failed Bind");
                puts(strerror(errno));
                return -1;
            }
        
            break;

        case LISTEN_ERR:
            if (value < 0){
                perror("Failed Listen");
                puts(strerror(errno));
                return -1;
            }

            break;

        case ACCEPT_ERR:
            if (value < 0){
                perror("Failed Accept");
                puts(strerror(errno));
                return -1;
            }

            break;

        case CONNECT_ERR:
            if (value < 0){
                perror("Failed Connect");
                puts(strerror(errno));
                return -1;
            }

            break;
    }

    return 0;
}