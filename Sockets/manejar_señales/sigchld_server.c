#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h> // Contiene la función signal
#include <sys/wait.h> // Contiene la función waitpid

#define PORT 12345

void service(int newSocket){
    char buf[10];
    int n;
    while ((n = recv(newSocket, buf, sizeof(buf), 0)) > 0)
	write(newSocket, buf, n);
    return;
}

void sig_chld(int signo){ // Función para manejar señales
	pid_t	pid; // Identificador de proceso
	int	stat; // Estado del proceso
	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) // Espera por cualquier hijo
		printf("   Hijo %d ha terminado\n", pid);
	return; // Regresa
}

int main(void){
    int s, ns, len;
    struct sockaddr_in direcc;
   
    s = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *) &direcc, sizeof(direcc));
    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PORT);
    direcc.sin_addr.s_addr = htonl(INADDR_ANY);
    len = sizeof(struct sockaddr_in);
    bind(s, (struct sockaddr *) &direcc, len);
    listen(s, 5);
    signal(SIGCHLD, sig_chld); // Registra la señal SIGCHLD
     while(1){
        ns = accept(s, (struct sockaddr *) &direcc, &len);
        if(fork()==0){ 
            close(s);
            service(ns);      
            close(ns);
            exit(0);
        }
        close(ns);
    } 
    close(s);
    exit(0);
}
