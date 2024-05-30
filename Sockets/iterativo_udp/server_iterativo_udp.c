#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define PORT 12345
#define BUFLEN 512 // Tamaño del buffer
 
int main(){
    struct sockaddr_in sock_server, sock_client;
    int s, i, slen = sizeof(sock_client) , recv_len;
    char buf[BUFLEN];
    s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //Creó un socket UDP con IPPRTOT_UDP
    memset((char *) &sock_server, 0, sizeof(sock_server)); //Inicializa la estructura a 0 para evitar errores
    //Configuración de la estructura
    sock_server.sin_family = AF_INET;
    sock_server.sin_port = htons(PORT);
    sock_server.sin_addr.s_addr = htonl(INADDR_ANY);
     
    bind(s, (struct sockaddr*)&sock_server, sizeof(sock_server) );
    // Bucle infinito para recibir y enviar mensajes
    while(1){
        //recvfrom recibe un mensaje y lo almacena en buf
        recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &sock_client, &slen);
        printf("Recibido: %s\n" , buf);
        //sendto envía un mensaje a de vuelta al cliente
        sendto(s, buf, recv_len, 0, (struct sockaddr*) &sock_client, slen);
    }
 
    close(s);
    return 0;
}
