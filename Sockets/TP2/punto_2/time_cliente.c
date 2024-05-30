#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT 12345
#define BUFLEN 1024 // Tamaño del buffer

int main() {
    struct sockaddr_in sock_client;
    int s, recv_len;
    int yes = 1;
    char buf[BUFLEN];
    socklen_t slen = sizeof(sock_client);

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Create a UDP socket

    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    memset((char *) &sock_client, 0, sizeof(sock_client));
    sock_client.sin_family = AF_INET;
    sock_client.sin_port = htons(PORT);
    sock_client.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr *)&sock_client, sizeof(sock_client)) == -1) {
        perror("Bind error");
        exit(1);
    }

    while(1) {
        // Recibe un mensaje a través de un socket
        recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&sock_client, &slen);
        buf[recv_len] = '\0';

        // Imprime el mensaje recibido
        printf("Respuesta del servidor: %s\n", buf);

        sleep(1); // Wait a second before the next request
    }

    close(s);
    return 0;
}