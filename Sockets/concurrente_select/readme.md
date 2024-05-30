<h1>MULTIPLEXACIÓN (I/O)</h1>
La multiplexación es una forma de enviar múltiples señales o flujos de información a través de un medio de comunicación compartido al mismo tiempo. Para ello se envía una única señal compleja que el receptor recupera y separa en un proceso llamado demultiplexación.
Por ejemplo cuando un cliente TCP maneja dos entradas al mismo tiempo (la entrada estándar y un socket TCP) o otro caso en un servidor de dos o más socket TCP nos encontramos con el problema que cuando se encuentran bloqueados en una llamada para dar atención a alguna de esas entradas y recibir una notificación en la otra, si queremos recibir una notificación si una o más condiciones de E/S están listas, para eso el servidor debe estar en un estado latente hasta que le llega algún estímulo, atenderlo y luego volver a esa latencia a esa capacidad se la denomina multiplexación de E/S y es proporcionado por las funciones <b>select()</b> y <b>poll().</b>
La multiplexación de E/S se usa generalmente cuando:
<li>Un cliente maneja múltiples descriptores (entrada interactiva y un socket de red).</li>
<li>Un servidor TCP maneja un socket de escucha y los de atención.</li>
<li>Un servidor maneja tanto TCP como UDP (multiprotocolo).</li>
<li>Un servidor maneja múltiples servicios y tal vez múltiples protocolos.</li>
