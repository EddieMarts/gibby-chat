#include "server/server.h"

bool connect_status = 0;

void *server_send(void *sock){
    int s_sock = *(int *)sock;

    char send_buff[256];
    
    connect_status = 1;

    while(1){
        memset(send_buff, 0, sizeof(send_buff));

        if (!fgets(send_buff, sizeof(send_buff), stdin))
            break;
        
        if (!strcmp(send_buff, "exit\n")){
            connect_status = 0;
            break;
        }
        
        if (send_buff[0]){
            int send_code = send(s_sock, send_buff, strlen(send_buff), 0);
            if(send_code < 0) break;
        }

        sched_yield();
    }
    puts("Quitting");
    
    return NULL;
}

void *server_receive(void *sock){
    int r_sock = *(int *)sock;

    char rec_buff[256];
    
    while(1){
        if (!connect_status){
            break;
        }
        
        memset(rec_buff, 0, sizeof(rec_buff));
        int bytes = recv(r_sock, rec_buff, sizeof(rec_buff), 0);

        if (bytes == 0){
            puts("Client socket was closed");
            break;
        }

        if (bytes < 0){
            perror("Socket: ");
            break;
        }

        if (rec_buff[0]) {
            rec_buff[bytes-1] = '\0';
            puts(rec_buff);
        }
        sched_yield(); 
    }
    
    return NULL;
}

int run_server(){
    char msg[] = "Connected to server";
    char buff[256] = {0};
    
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT),
    };

    socklen_t addr_len = sizeof(addr);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    check_sock_error(sock, SOCKET_ERR);
    
    int bind_code = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    check_sock_error(bind_code, BIND_ERR);

    int list_code = listen(sock, 23);
    check_sock_error(list_code, LISTEN_ERR);

    int new_sock = accept(sock, (struct sockaddr*)&addr, &addr_len);
    check_sock_error(new_sock, ACCEPT_ERR);

    pthread_t send_thread;
    pthread_t receive_thread;
    
    recv(sock, buff, sizeof(buff), 0);
    send(new_sock, msg, sizeof(msg), 0);
    
    pthread_create(&send_thread, NULL, server_send, &new_sock);
    pthread_create(&receive_thread, NULL, server_receive, &new_sock);

    pthread_join(send_thread, NULL);
    pthread_join(receive_thread, NULL);

    pthread_detach(send_thread);
    pthread_detach(receive_thread);

    close(new_sock);
    close(sock);

    return 0;
}