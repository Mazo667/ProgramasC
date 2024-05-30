#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define PORTNUMBER  12345

void* service(void *arg){
      int sock;
      char buf[100];
      int n;
      printf("thread hijo %i con pid %i... creado.\n", pthread_self(), getpid());
      sock = (int) arg; // Convertir el argumento a un entero representando el cliente socket
      while ((n = recv(sock, buf, sizeof(buf), 0)) > 0){
   	    write(sock, buf, n);
      }
      close(sock);
      printf("thread hijo %i con pid %i... finalizado.\n", pthread_self(), getpid());
}

int main(void) {
	int s, n, ns, len, pid;
	struct sockaddr_in direcc;
        pthread_t thread_id; // Identificador del thread
	s = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &direcc, sizeof(direcc));
	direcc.sin_family = AF_INET;
	direcc.sin_port = htons(PORTNUMBER);
	direcc.sin_addr.s_addr = htonl(INADDR_ANY);
	len = sizeof(struct sockaddr_in);
	if( bind(s, (struct sockaddr *) &direcc, len))
   	   printf("bind error");
	if( listen(s, 5))
   	   printf("listen error");
        while(1){
   	      ns = accept(s, (struct sockaddr *) &direcc, &len);    
   	      n = pthread_create(&thread_id, NULL, service, (void *) ns); // Creó un nuevo thread
   	      if (n != 0) {
     		   printf("No se pudo crear el thread.\n");
     		   return 0;
   	      }
	 // Para evitar que los threads se queden en estado zombie
   	 pthread_detach(thread_id); // Liberó los recursos del thread cuando termina
   	 sched_yield(); // Liberó el procesador
    }
    
   close(s);
   exit(0);
}
