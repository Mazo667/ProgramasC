#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Contiene la función fork

#define PORTNUMBER  12345

void service(int newSocket){
    char buf[10];
    int n;
    while ((n = recv(newSocket, buf, sizeof(buf), 0)) > 0){
        write(newSocket, buf, n);
    }
}

int main(void){
    int s, ns, len;
    struct sockaddr_in direcc;
   
    s = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *) &direcc, sizeof(direcc));
    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PORTNUMBER);
    direcc.sin_addr.s_addr = htonl(INADDR_ANY);

    len = sizeof(struct sockaddr_in);
    bind(s, (struct sockaddr *) &direcc, len);
    listen(s, 5);
    
    while(1){
        ns = accept(s, (struct sockaddr *) &direcc, &len);
        if(fork()==0){  // Creó un proceso hijo y lo identificó con 0
            close(s); // Cierro el socket heredado del padre ya que solo necesito el socket del hijo
            service(ns); // Llamó a la función service    
            close(ns); // Cierro el socket del hijo
            exit(0);
        }
        close(ns);
    } 
    
    close(s);
    exit(0);
}
