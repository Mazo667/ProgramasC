#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <netinet/in.h>


#define BUFF_SIZE 1024
#define PORT 9000

int sock_serv, sock_client;

// Check if file descriptor is valid
int isValidFd(int fd) {
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF; // EBADF: Bad file descriptor
}

static void sig_urg(int sig){
    int str_len; 
    char buffer[BUFF_SIZE];
    str_len = recv(sock_client, buffer, sizeof(buffer), MSG_OOB); // Recibe datos fuera de banda
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

    if (bind(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv)) == -1) {
        error_handling("Error bind()");
    }
    
    if (listen(sock_serv, 5) == -1) {
        error_handling("Error listen()");
    }

    sz_addr_serv = sizeof(addr_serv);
    sock_client = accept(sock_serv, (struct sockaddr*)&addr_serv, &sz_addr_serv);

    
    if (isValidFd(sock_client)) {
        fcntl(sock_client, F_SETOWN, getpid());
    } else {
        error_handling("Error fcntl()");
    }
    
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
