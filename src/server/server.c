#include "server/server.h"

int run_server(){
    char buff[256] = {0};
    char msg[] = "Server Initiated";
    
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT),
    };

    socklen_t addr_len = sizeof(addr);

    socklen_t sock = socket(AF_INET, SOCK_STREAM, 0);
    check_sock_error(sock, SOCKET_ERR);
    
    int bind_code = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    check_sock_error(bind_code, BIND_ERR);

    int list_code = listen(sock, 23);
    check_sock_error(list_code, LISTEN_ERR);

    int new_sock = accept(sock, (struct sockaddr*)&addr, &addr_len);
    check_sock_error(new_sock, ACCEPT_ERR);

    puts(msg);

    recv(new_sock, buff, sizeof(buff)-1, 0);
    puts(buff);

    while(1){
        int recv_code = recv(new_sock, buff, sizeof(buff)-1, 0);
        puts(buff);

        if(recv == 0){
            puts("Client ended connection");
            break;
        }
    }

    close(new_sock);
    close(sock);
    return 0;
}