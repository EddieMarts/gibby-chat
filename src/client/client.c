#include "client/client.h"

bool connect_status = 0;

void *client_send(void *sock){
    int s_sock = *(int*)sock;

    char send_buff[256];
    
    connect_status = 1;
    
    while(1){
        memset(send_buff, 0, sizeof(send_buff));

        if (!fgets(send_buff, sizeof(send_buff), stdin))
            break;
        
        if (!strcmp(send_buff, "exit\n")){
            connect_status = 1;
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

void *client_receive(void *sock){
    int r_sock = *(int*)sock;

    char rec_buff[256];
    
    while(1){
        if(!connect_status){
            break;
        }

        memset(rec_buff, 0, sizeof(rec_buff));
        int bytes = recv(r_sock, rec_buff, sizeof(rec_buff), 0);
        
        if (rec_buff[0]) {
            rec_buff[bytes-1] = '\0';
            puts(rec_buff);
        }
        
        sched_yield();
    }
    
    return NULL;
}

int run_client(){
    char buff[256];
    char msg[] = "Client accepted the connection";
    
    struct sockaddr_in client_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT)
    };

    int client_sock = socket(AF_INET, SOCK_STREAM, 0);
    check_sock_error(client_sock, SOCKET_ERR);

    int connect_code = connect(client_sock, (struct sockaddr*)&client_addr, sizeof(client_addr));
    check_sock_error(connect_code, CONNECT_ERR);

    pthread_t send_thread;
    pthread_t receive_thread;

    send(client_sock, msg, sizeof(msg), 0);
    recv(client_sock, buff, sizeof(buff), 0);

    puts(buff);
    
    pthread_create(&send_thread, NULL, client_send, &client_sock);
    pthread_create(&receive_thread, NULL, client_receive, &client_sock);
    
    pthread_join(send_thread, NULL);
    pthread_join(receive_thread, NULL);

    pthread_detach(send_thread);
    pthread_detach(receive_thread);
    
    close(client_sock);
    return 0;
}