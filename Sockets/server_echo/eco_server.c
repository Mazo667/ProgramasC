#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 8080

void sig_chld(int signo) {
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("Child %d terminated\n", pid);
    return;
}

void service(int newSocket) {
    static char *argv[] = {"eco", NULL};
    execv("./eco", argv);
}

int main(void) {
    int s, ns, len, pid, yes = 1;
    struct sockaddr_in direcc;

    s = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)); // Reutilizar el puerto de escucha

    bzero((char *)&direcc, sizeof(direcc));
    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PORT);
    direcc.sin_addr.s_addr = htonl(INADDR_ANY);

    len = sizeof(struct sockaddr_in);
    bind(s, (struct sockaddr *)&direcc, len);
    listen(s, 5);
    signal(SIGCHLD, sig_chld);

    while (1) {
        ns = accept(s, (struct sockaddr *)&direcc, &len);
        if ((pid = fork()) == 0) {
            close(s);
            dup2(ns, 0); // Redirigir la entrada estándar al socket
            dup2(ns, 1); // Redirigir la salida estándar al socket
            service(ns);
            close(ns);
            exit(0);
        } else {
            close(ns);
        }
    }

    close(s);
    exit(0);
}