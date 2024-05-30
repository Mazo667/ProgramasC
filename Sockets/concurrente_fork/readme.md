<h1>SERVIDOR CONCURRENTE CON FORK()</h1>

En este servidor concurrente, los procesos hijos van a atender a los clientes y el padre va a estar escuchando por nuevas conexiones. Cuando haiga una nueva conexión se va a crear un hijo para atender esa conexión.
<li>La función <b>fork()</b> irá dentro del while hasta que se ejecute <i>accept()</i> una vez ejecutado se crea un proceso hijo y este va a ejecutar nuestra función <i>service()</i> que brinda un servicio de eco.</li>
<li>La función <b>fork()</b> devuelve 0 cuando es el hijo y -1 cuando falla la creación del proceso hijo.</li>
<li>Un padre tiene un PID <i>(Process ID)</i> que normalmente es mayor a 0.</li>
<li>El primer socket se conoce como socket de escucha y el otro que devuelve el connect se lo conoce como socket de atención.</li> 
<li>El padre siempre presta atención al socket de escucha y el hijo al de atención.</li>
