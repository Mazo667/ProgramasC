<h1>THREADS EN LINUX</h1>
Un programa es un conjunto de datos y funciones, los datos son accedidos mediante variables. Una variable a su vez puede ser global o local.
Un <b>thread</b> o <b>hilo de ejecución</b> puede considerarse un punto concreto de ejecución de un programa en un momento dado. 
En una aplicación multi thread, por su parte tiene más de un punto de ejecución en un momento dado. Si ejecutamos una aplicación multi thread en una máquina con un procesador de más de un núcleo <i>(core)</i>; cada núcleo puede ejecutar un thread, por lo que podrá ejecutar más de una tarea a la vez.
El principal inconveniente de las aplicaciones con múltiples threads, es mantener el orden en el acceso a los recursos compartidos (tales como las variables globales).
