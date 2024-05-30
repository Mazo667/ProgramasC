<h1>TCP PREFORKED SERVERS</h1>
Una mejora que se le puede realizar a los servidores TCP concurrentes, es utilizar una técnica llamada <b>Prefrorking.</b>
En lugar de llamar a <i>fork()</i> por cada conexión de un cliente, el servidor realiza  un número de prefork para crear algunos hijos cuando se inicia, y luego de los hijos están listos para atender a los clientes a medida que llegan las conexiones.


La ventaja de esta técnica es que los padres pueden manejar nuevos clientes sin el costo de realizar un <i>fork()</i>.
La desventaja es que el padre debe “adivinar” cuántos hijos debe preforkear cuando se inicializa. Si el número de clientes en cualquier momento es igual al número de hijos, se “ignoran” clientes adicionales hasta que haya un hijo disponible.

Pero los clientes no son completamente ignorados. El kernel completará el <i>three-way handshake</i> para cualquier cliente adicional, hasta el número configurado con la llamada <i>listen()</i> para este socket, y luego pasará las conexiones completadas al servidor cuando se llame a <i>accept()</i>.
Sin embargo, la aplicación del cliente puede notar una degradación en el tiempo de respuesta porque, aunque la llamada a <i>connect()</i> que realizó, puede volver de inmediato, es posible que el servidor no gestione su primera solicitud durante algún tiempo.

Con algo de codificación adicional, el servidor siempre puede manejar la carga del cliente. Lo que el padre debe hacer es monitorear continuamente el número de hijos disponibles, y si este valor cae por debajo de algún umbral, debe preforkear hijos adicionales.
Además, si el número de hijos disponibles excede otro umbral, el padre puede terminar algunos de los hijos en exceso, porque tener demasiados hijos disponibles también puede degradar el rendimiento.
