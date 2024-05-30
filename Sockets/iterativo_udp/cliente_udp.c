#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVER "127.0.0.1" //IP del servidor
#define BUFLEN 512
#define PORT 12345 

int main(){
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
 
    s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    inet_aton(SERVER , &si_other.sin_addr); //inet_aton() convierte la dirección IP de formato texto a binario
 
    while(1){
        printf("Mensaje a enviar : ");
        fgets(message, sizeof message, stdin);  //fgets lee una cadena de texto de tamaño BUFLEN
        sendto(s, message, strlen(message),0,(struct sockaddr *) &si_other, slen);
        memset(buf,'\0', BUFLEN);
        recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t *)&slen);
        puts(buf); //imprime el mensaje recibido
    }
    close(s);
    return 0;
}
