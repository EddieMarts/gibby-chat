#include "client/client.h"

int run_client(){
    char buff[256] = {0};
    char msg[] = "Client accepted the connection";
    
    struct sockaddr_in client_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT)
    };

    socklen_t client_sock = socket(AF_INET, SOCK_STREAM, 0);
    check_sock_error(client_sock, SOCKET_ERR);

    int connect_code = connect(client_sock, (struct sockaddr*)&client_addr, sizeof(client_addr));
    check_sock_error(connect_code, CONNECT_ERR);

    send(client_sock, msg, sizeof(msg)-1, 0);

    while(1){
        fgets(buff, sizeof(buff),stdin);
        send(client_sock, buff, sizeof(buff)-1, 0);
    }

    close(client_sock);
    return 0;
}