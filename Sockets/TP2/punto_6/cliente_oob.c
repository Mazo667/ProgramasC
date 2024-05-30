#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#define PORTNUMBER 9000
#define MSJMAX 100

 void bail(const char *err_msg) {
    if ( errno != 0 ) {
       fputs(strerror(errno),stderr);
          fputs(": ",stderr);
   }
     fputs(err_msg,stderr);
      fputc('\n',stderr);
      exit(1);
  }

static void iband(int socket,char *msg){
    int n;
    // Envía los datos dentro de banda
    n = send(socket, msg, strlen(msg), 0);
    printf("Mensaje enviado dentro de banda: %s\n", msg);
}

static void oband(int socket, char *msg) {
    int n;
    // Envía los datos fuera de banda
	n = send(socket, msg, strlen(msg), MSG_OOB);
    printf("Mensaje enviado fuera de banda: %s\n", msg);
}

int main(void) {
    int s, n, len;
    struct sockaddr_in server_addr;
    char msj[MSJMAX];
    char answer;

    s = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNUMBER);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al conectar con el servidor\n");
        exit(EXIT_FAILURE);
    }
    answer = 'y';
    while (answer == 'y' || answer == 'Y'){
        printf("Ingrese el mensaje que quiere enviar: \n");
        scanf("%s",msj);
        iband(s, msj);
        memset(msj, 0, MSJMAX);

        printf("Ingrese el mensaje fuera de banda que quiere enviar: \n");
        scanf("%s",msj);
        oband(s, msj);
        memset(msj, 0, MSJMAX);

        printf("Desea enviar otro mensaje? (y/n)\n");
        scanf(" %c", &answer);
    }
        
    close(s);
    exit(EXIT_SUCCESS);
}
