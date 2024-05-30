#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

#include <signal.h>
#include <netinet/in.h>
#include <fcntl.h>

#define BUFF_SIZE 1024
#define PORT 9000

int sock_serv, sock_client;

static void sig_urg(int sig){
    int str_len; 
    char buffer[BUFF_SIZE];
    str_len = recv(sock_client, buffer, sizeof(buffer), MSG_OOB);
    buffer[str_len] = '\0';
    printf("Mensaje URGENTE: %s (%d) \n", buffer, str_len);
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}

int main(){
    struct sockaddr_in addr_serv;
    socklen_t sz_addr_serv;
    char buff[BUFF_SIZE];
    ssize_t str_len;
    int state;

    // Inicializar socket
    sock_serv = socket(AF_INET, SOCK_STREAM, 0);
    // Inicializar en 0 la estructura
    memset(&addr_serv, 0, sizeof(addr_serv));
    // Configuracion de la estructura
    addr_serv.sin_family = PF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(PORT);

    if(-1 == bind(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv))) error_handling("Error bind()");

    if(-1 == listen(sock_serv, 5)) error_handling("Error listen()");

    sz_addr_serv = sizeof(addr_serv);
    sock_client = accept(sock_serv, (struct sockaddr*)&addr_serv, &sz_addr_serv);

    //Cambie el propietario del socket (F_SETOWN) al que apunta el descriptor de archivo sock_client al proceso cuyo ID es el valor de retorno de getpid()
    fcntl(sock_client, F_SETOWN, getpid());
    
    signal(SIGURG, sig_urg);

    while (1){
        str_len = recv(sock_client, buff, sizeof(buff), 0);
        if (str_len == -1){
            error_handling("Error recv()");
        } else if (str_len > 0){
            buff[str_len] = '\0';
            printf("Mensaje recibido: %s (%ld)\n", buff, str_len);
        } else {
            break;
        }
    }
    close(sock_client);
    close(sock_serv);
    return 0;
}
