<h1>SERVIDOR CONCURRENTE CON MANEJADOR DE SEÑALES</h1>
En este servidor concurrente, pero con un manejador de señales <b>(sig_chld)</b>, esta función es un manejador para la señal <i>SIGCHLD</i> es enviada cuando un proceso hijo termina. Esta función <b>espera a que todos los procesos hijos terminados no permanezcan como procesos zombies</b>.
Un proceso zombie es un proceso que ha terminado, pero su entrada aún permanece en la tabla de procesos.
