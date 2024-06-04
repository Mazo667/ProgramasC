<h1>SERVER MULTICAST</h1>

Este es un servidor de multicast que permite la comunicación entre múltiples clientes de manera eficiente. A continuación, se detallan los pasos para ejecutar tanto el cliente como el servidor.

## Pasos para ejecutar el servidor

1. Abre una terminal.
2. Navega hasta el directorio donde se encuentra el archivo del servidor.
3. Compila el código fuente del servidor utilizando el siguiente comando:
    ```
    gcc server.c -o server
    ```
4. Ejecuta el servidor utilizando el siguiente comando:
    ```
    ./server <Listen IP> <Listen Port> <Group IP> <Group Port>
    ```

## Pasos para ejecutar el cliente

1. Abre una terminal.
2. Navega hasta el directorio donde se encuentra el archivo del cliente.
3. Compila el código fuente del cliente utilizando el siguiente comando:
    ```
    gcc client.c -o client
    ```
4. Ejecuta el cliente utilizando el siguiente comando:
    ```
    ./cliente <Server IP> <Server Port> <Group IP> <Group Port> <Name>
    ```

## ¿Qué son los servidores multicast?

Los servidores multicast son una forma eficiente de enviar datos a múltiples destinatarios en una red. En lugar de enviar copias individuales de los datos a cada destinatario, el servidor multicast envía un solo flujo de datos que es recibido por todos los clientes que se han unido al grupo multicast. Esto reduce la carga de la red y mejora la eficiencia en comparación con los servidores unicast, donde se envían copias separadas de los datos a cada cliente.

## Ejemplo
```
    ./server 127.0.0.1 12345 224.0.0.1 5432
```

```
    ./cliente 127.0.0.1 12345 224.0.0.1 5432 Pepe
```