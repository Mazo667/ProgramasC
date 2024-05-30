#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define PORTNUMBER  12345

int main(void){
    char buf[10]; //Buffer de caracteres especiales para almacenar temporalmente los datos
    int s, n, ns, len; //Se utilizan para manejar las conexiones de red y los datos a través de sockets TCP
    struct sockaddr_in direcc; //Estructura para definir la familia de protocolo, puerto y dirección 
s = socket(AF_INET, SOCK_STREAM,0); //Crea un socket y devuelve un valor para acceder al descriptor de archivo

    bzero((char *) &direcc, sizeof(direcc)); //Pone en 0 a la estructura para asegurar que no haya basura
    direcc.sin_family = AF_INET; //Asignó a la estructura que sea de la familia TCP/IP
    direcc.sin_port = htons(PORTNUMBER); //Asignó el puerto que va a utilizar el servidor
    direcc.sin_addr.s_addr = htonl(INADDR_ANY); //Asigno la dirección IP

    len = sizeof(struct sockaddr_in); //Obtener el tamaño de la estructura
    bind(s, (struct sockaddr *) &direcc, len); //Asigna la estructura definida al socket
    listen(s, 5); //Establece una cola de conexión hasta 5 peticiones
    
    //El servidor se bloquea hasta que se establece una conexión con cliente
    ns = accept(s, (struct sockaddr *) &direcc, &len);

    while ((n = recv(ns, buf, sizeof(buf), 0)) > 0) //Recibo datos del cliente mientras haya datos
        write(1, buf, n); //Los datos recibidos son devueltos al cliente con write
         
    close(ns); close(s); //Cierro el socket del cliente y finalmente del servidor
    exit(0);
}
