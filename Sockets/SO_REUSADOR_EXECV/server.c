#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define PORT 8080

void sig_chld(int signo){
    pid_t	pid;
    int	stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("   Hijo %d ha terminado\n", pid);
    return;
}

int main(void){
    int s, ns, len;
    struct sockaddr_in direcc;
    int optval = 1; // Variable para habilitar la reutilización del puerto
    s = socket(AF_INET, SOCK_STREAM, 0);
    //Cambio a setsockopt para habilitar la reutilización del puerto
    //Usando la variable optval y SO_REUSEADDR
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    bzero((char *) &direcc, sizeof(direcc));
    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PORT);
    direcc.sin_addr.s_addr = htonl(INADDR_ANY);
    len = sizeof(struct sockaddr_in);
    bind(s, (struct sockaddr *) &direcc, len);
    listen(s, 5);
    signal(SIGCHLD, sig_chld);
    while(1){
        ns = accept(s, (struct sockaddr *) &direcc, &len);
        if(fork()==0){ 
            close(s);
            char str[12]; // Buffer para almacenar la representación de cadena del entero.
            sprintf(str, "%d", ns); // Convierte el entero a una cadena.
            char *arr[] = { "./service", str, NULL }; // Array de argumentos.
            //service(ns); en vez de llamar a service, se llama a execv
            printf("Voy a llamar a sevice\n");
            execv("./service",arr);
            close(ns);
            exit(0);
        }
        close(ns);
    } 
    close(s);
    exit(0);
}