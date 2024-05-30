#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define PORT 12345
#define BUFLEN 512 // Tamaño del buffer

int main() {
    struct sockaddr_in sock_server;
    int s, slen = sizeof(struct sockaddr_in);
    char buf[BUFLEN];
    int broadcast = 1;
    int yes = 1;

    //Creó un socket UDP
    s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    //Permitir reutilizar el puerto
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    //Permitir broadcasting
    setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    
    //Inicializa la estructura a 0 para evitar errores
    memset((char *) &sock_server, 0, sizeof(sock_server));
    
    //Configuración de la estructura
    sock_server.sin_family = AF_INET;
    sock_server.sin_port = htons(PORT);
    sock_server.sin_addr.s_addr = htonl(INADDR_BROADCAST);
     
    bind(s, (struct sockaddr*)&sock_server, sizeof(sock_server) );

    while(1){
        time_t t = time(NULL);
        char *time_str = ctime(&t);
        strncpy(buf, time_str, BUFLEN);
        //sendto envía un mensaje a través de un socket
        printf("Enviando: %s\n", buf);
        sendto(s, buf, strlen(buf), 0, (struct sockaddr*)&sock_server, slen);
        sleep(1); //Esperar un segundo antes de enviar el próximo mensaje
    }

    close(s);
    return 0;
}