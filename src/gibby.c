#include <stdio.h>
#include <string.h>

#include "server/server.h"
#include "client/client.h"

#define VERSION "0.1.0-alpha"

/*
    Gibby chat - Writted by Eduardo M. Gomes

    It's a simples chat tool (for now).
    Very early stage
*/

static inline void show_help(){
    puts("use: gib [-v | --version] [-h | --help] <command> [args]\n");
    
    puts("commands:");
    puts("\t client \t initiate a client socket");
    puts("\t server \t initiate a server socket");
    
    puts("options:");
    puts("\t -h, --help \t display help");
    puts("\t -v, --version \t display version");
}

int main(int argc, char **argv){
    if(argc < 2){
        show_help();
    }
    else if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")){
        show_help();
    }
    else if(!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")){
        printf("gibby version: %s \n", VERSION);
    }
    else if(!strcmp(argv[1], "client")){
        run_client();
    }
    else if(!strcmp(argv[1], "server")){
        run_server();
    }

    return 0;
}