#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>

#define PORTNUMBER 12345

void sig_chld(int signo){
	pid_t	pid;
	int	stat;
	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("   Hijo %d ha terminado\n", pid);
	return;
}


main(){
    int s, x, ns, len, yes=1;
    struct sockaddr_in direcc;
    pid_t pid;
   
    s = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(s,SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    bzero((char *) &direcc, sizeof(direcc));
    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PORTNUMBER);
    direcc.sin_addr.s_addr = htonl(INADDR_ANY);
    len = sizeof(struct sockaddr_in);
    bind(s, (struct sockaddr *) &direcc, len);
    listen(s, 5);

    signal(SIGCHLD, sig_chld);
    for (x = 0; x < 5; x++) { // Creo 5 hijos que estarán a la escucha de peticiones
        if ((pid = fork()) == 0) { 
		    ns = accept(s, (struct sockaddr *) &direcc, &len);
		    close(s);
            service(ns);      
            close(ns);
            exit(0);
        }
    }
  wait(NULL); 
  close(s);
  exit(0);
}
