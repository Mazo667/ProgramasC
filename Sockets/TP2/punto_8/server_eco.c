#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define PORTNUMBER  12345

void servicio(int s){
    int n;
    char buf[10];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    char ip[INET_ADDRSTRLEN];


    //En UDP se utiliza sendto() y recvfrom() en lugar de send() y recv()
    while ((n = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &client_addr, &client_len)) > 0){
        // inet_ntop convierte la direccion binaria a una cadena de texto
        inet_ntop(AF_INET, &(client_addr.sin_addr), ip, INET_ADDRSTRLEN);
        // Set the null terminator at the end of the buf array to indicate the end of the string.
        buf[n] = '\0';
        printf("Socket IP: %s\n", ip);
        printf("Socket Numero de Puerto: %d\n", ntohs(client_addr.sin_port));
        printf("Tamaño del mensaje: %d\n", n );
        printf("Retransmitiendo mensaje: %s\n",buf);
        sendto(s, buf, n, 0, (struct sockaddr *) &client_addr, client_len);
        memset(buf,0,sizeof(buf));
    }

    return;
}

int main(void){
    char buf[10];
    int s, n, len;
    struct sockaddr_in server_addr;
    //Familia TCP
    //    s = socket(AF_INET, SOCK_STREAM, 0);
    //Familia UDP
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memset((char *) &server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNUMBER);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(s, (struct sockaddr *) &server_addr, sizeof(server_addr));
    //Saco el listen porque no es necesario en UDP
    //listen(s, 5);
    while (1){
        //Saco el accept porque no es necesario en UDP
        //ns = accept(s, (struct sockaddr *) &direcc, &len);
        servicio(s);
        //No es necesario cerrar el socket en UDP
    }

    close(s);
    exit(0);
}