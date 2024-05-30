#include <sys/socket.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Bienvenido al service\n");
    int n;
    char buf[10];
    int newSocket = atoi(argv[1]); // Convierto la cadena recibida a un número entero del socket cliente

    while ((n = recv(newSocket, buf, sizeof(buf), 0)) > 0)
        write(newSocket, buf, n);
    return 0;
}
