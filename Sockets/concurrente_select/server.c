#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNUMBER 12345

int service(int newSocket){
    char buf[100];
    int n;
    if ((n = recv(newSocket, buf, sizeof(buf), 0)) > 0)
        write(newSocket, buf, n);
    return n;
}

int service_chat(int envia, int escucha){
    char buf[100];
    int n, i;
    if ((n = recv(envia, buf, sizeof(buf), 0)) == 0)
        return n;
    for (i = 3; i <= 10; i++){
        if (i != envia && i != escucha)
            write(i, buf, n);
    }
    return n;
}

int main(void){
    int s, ns, len, i, yes = 1;
    struct sockaddr_in direcc;
    fd_set rset, c_rset; //Conjunto de descriptores de archivos

    s = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    bzero((char *)&direcc, sizeof(direcc));
    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PORTNUMBER);
    direcc.sin_addr.s_addr = htonl(INADDR_ANY);

    len = sizeof(struct sockaddr_in);
    bind(s, (struct sockaddr *)&direcc, len);
    listen(s, 5);

    FD_ZERO(&rset); // Inicializa el conjunto de descriptores de archivos
    FD_SET(s, &rset); // Añade s al conjunto de descriptores de archivos

    while (1){
        c_rset = rset; // Copia de rset
        select(10, &c_rset, NULL, NULL, NULL); // Espera a que haya un descriptor de archivo listo

        if (FD_ISSET(s, &c_rset)){ // Comprueba si s está en el conjunto de descriptores de archivos
            ns = accept(s, (struct sockaddr *)&direcc, &len);
            FD_SET(ns, &rset); // Añade ns al conjunto de descriptores de archivos
            c_rset = rset; // Copia de rset
        }else{ // Comprueba si s no está en el conjunto de descriptores de archivos
            for (i = 3; i <= 10; i++){
                // Comprueba si i está en el conjunto de descriptores de archivos
                if (i != s && FD_ISSET(i, &c_rset)){
                    if (!service_chat(i, s)){ // Comprueba si el cliente ha cerrado la conexión
                        close(i); // Cierra la conexión
                        FD_CLR(i, &rset); // Elimina i del conjunto de descriptores de archivos
                    }
                }
            }
        }
    }

    close(s);
    exit(0);
}