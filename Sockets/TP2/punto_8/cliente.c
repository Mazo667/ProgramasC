#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define PORTNUMBER  12345

int main(void){
    char buf[10];
    int s, n;
    struct sockaddr_in server_addr;

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNUMBER);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    while (1){
        printf("Ingrese un mensaje: ");
        fgets(buf, sizeof(buf), stdin);
        sendto(s, buf, strlen(buf), 0, (struct sockaddr *) &server_addr, sizeof(server_addr));
        n = recvfrom(s, buf, sizeof(buf), 0, NULL, NULL);
        printf("Respuesta del servidor: %.*s\n", n, buf);
    }

    close(s);
    exit(0);
}
