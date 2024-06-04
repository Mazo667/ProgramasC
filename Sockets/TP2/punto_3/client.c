#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "MessagePacket.h"

#define MSGLEN (1024)
#define TIMEOUT (2)

// Función de procesamiento para ingresar cadenas de caracteres desde el teclado y enviarlas al servidor de eco
int SendEchoMessage(int sock, struct sockaddr_in *pServAddr);

// Función de procesamiento de visualización/recepción de mensajes desde el socket
int ReceiveEchoMessage(int sock, struct sockaddr_in *pServAddr);

// Varios datos para comunicación multicast/comunicación unicast
int sock_recv, sock;
char *mcastIP, *servIP;
unsigned int mcastPort, servPort;
struct sockaddr_in mcastAddr, servAddr;
struct ip_mreq mcastReq;

// Nombre de usuario  
char* userName;

// Variables para la configuración de opciones de socket
int optVal;                       
int maxDescriptor;
fd_set fdSet;
struct timeval tout;

/* プライベートチャット用 */
char privateChat[MSGLEN];
char* chatStringSplit[3];
char* privateSplit[2];

// Funcion de generacion de paquetes
int Packetize(short msgID, char *msgBuf, short msgLen, char *pktBuf, int pktBufSize){
  if(msgLen > MSGLEN - 4){
    return -1;
  }

  memcpy(&pktBuf[0], &msgID, 2);
  memcpy(&pktBuf[2], &msgLen, 2);
  memcpy(&pktBuf[4], msgBuf, msgLen);

  return msgLen + 4;
}

// Funcion de desempaquetado
int Depacketize(char *pktBuf, int pktLen, short *msgID, char *msgBuf, short msgBufSize){
  if(msgBufSize != MSGLEN){
    return -1;
  }

  memcpy(msgID, &pktBuf[0], 2);
  memcpy(&msgBufSize, &pktBuf[2], 2);
  memcpy(msgBuf, &pktBuf[4], msgBufSize);

  return msgBufSize;
}

// menu de uso
void usage(char *userName){
  printf("\n");
  printf("*****************************************************\n");
  printf("*** Multicast Chat ***\n");
  printf("*****************************************************\n");
  printf("\n");
  printf("[*] Hola %s.\n", userName);
  printf("\n");
  printf("[*] Usage\n");
  printf("[*] text             : Enviar un chat a otros miembros del grupo de chat.\n");
  printf("[*] /p-<name>-<body> : Enviar un chat privado。\n");
  printf("[*] /info            : Obtenga la información del grupo de chat.\n");
  printf("[*] /member          : Ver miembros de este grupo de chat.\n");
  printf("[*] /quit            : Deje de este grupo de chat.\n");
  printf("\n");
}

int isDelimiter(char p, char delim){
  return p == delim;
}

// Separe la cadena src con delim y guárdela en dst
int split(char *dst[], char *src, char delim){
  int count = 0;

  for(;;) {
    while (isDelimiter(*src, delim)){
      src++;
    }

    if (*src == '\0') break;
    dst[count++] = src;
    while (*src && !isDelimiter(*src, delim)) {
      src++;
    }
    if (*src == '\0') break;
    *src++ = '\0';
  }
  return count;
}

int main(int argc, char *argv[]){
  char pktBuf[MSGLEN];
  int pktLen;
  int sendMsgLen;

  // Comprobar argumentos
  if (argc != 6) {
    fprintf(stderr, "Usage: %s <Server IP> <Server Port> <Group IP> <Group Port> <Name>\n", argv[0]);
    exit(1);
  }
  
  // Obtenga la dirección IP del servidor de eco del primer argumento.
  servIP = argv[1];
  servPort = atoi(argv[2]);

  // Crear un socket para enviar mensajes al servidor de eco.
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  memset(&servAddr, 0, sizeof(servAddr));            /* 構造体をゼロで初期化 */
  servAddr.sin_family        = AF_INET;                /* インターネットアドレスファミリ */
  servAddr.sin_addr.s_addr    = inet_addr(servIP);    /* サーバのIPアドレス */
  servAddr.sin_port            = htons(servPort);        /* サーバのポート番号 */

  // Crear un socket para recibir mensajes 
  mcastIP = argv[3];
  mcastPort = atoi(argv[4]);
  sock_recv = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock_recv < 0) {
    fprintf(stderr, "socket() failed\n");
    exit(1);
  }

  // Asigno el nombre de usuario
  userName = argv[5];

  // Asigno valores a la estructura de dirección de grupo multicast
  memset(&mcastAddr, 0, sizeof(mcastAddr));          
  mcastAddr.sin_family = AF_INET;               
  mcastAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  mcastAddr.sin_port = htons(mcastPort);   

  // Establece opciones para que multiple procesos hagan bind() a la misma dirección y puerto
  optVal = 1;
  if (setsockopt(sock_recv, SOL_SOCKET, SO_REUSEADDR, (void*)&optVal, sizeof(optVal)) < 0) {
    fprintf(stderr, "setsockopt() failed\n");
    exit(1);
  }
  if (setsockopt(sock_recv, SOL_SOCKET, SO_REUSEPORT, (void*)&optVal, sizeof(optVal)) < 0) {
    fprintf(stderr, "setsockopt() failed\n");
    exit(1);
  }

  // Conecta el socket y la estructura de dirección de multicast
  if (bind(sock_recv, (struct sockaddr*)&mcastAddr, sizeof(mcastAddr)) < 0) {
    fprintf(stderr, "bind() failed\n");
    exit(1);
  }

  // Almacena los valores necesarios en la estructura para la solicitud de configuraciones de multicast
  mcastReq.imr_multiaddr.s_addr = inet_addr(mcastIP);  // Direccion IP multicast
  mcastReq.imr_interface.s_addr = htonl(INADDR_ANY);    // Direccion IP de la interfaz (comodin) 

  // Unirse a un grupo de multicast
  if (setsockopt(sock_recv, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&mcastReq, sizeof(mcastReq)) < 0) {
    fprintf(stderr, "setsockopt() failed\n");
    exit(1);
  }

  // Establecer el valor máximo de descriptores procesados por la funcion select()
  maxDescriptor = sock_recv;

  // Enviar solicitud de unirse al grupo
  pktLen = Packetize(MSG_ID_JOIN_REQUEST, 
    userName, strlen(userName), pktBuf, MSGLEN
  );

  // Enviar solicitud de unirse al grupo
  sendMsgLen = sendto(sock, pktBuf, pktLen, 0,
    (struct sockaddr *)&servAddr, sizeof(servAddr));

  // Verificar si se envió la cantidad correcta de bytes
  if (pktLen != sendMsgLen) {
    fprintf(stderr, "sendto() sent a different number of bytes than expected");
    return -1;
  }

  // Entrada de cadena, transmision de mensaje, recepcion del mensaje/bucle de procesamiento de visualizacion
  for (;;) {

    // Inicializa el conjunto de descriptores y configurar el teclado y el socket
    FD_ZERO(&fdSet);                // Inicializa en 0
    FD_SET(STDIN_FILENO, &fdSet);    // Establecer el descriptor para teclado (entrada estandar)
    FD_SET(sock_recv, &fdSet);            // Establecer el descriptor para el socket

    // Establecer el valor del tiempo de espera
    tout.tv_sec  = TIMEOUT; // Segundos
    tout.tv_usec = 0;       // Microsegundos

    // Espera la llegada de datos en el teclado o en el socket
    if (select(maxDescriptor + 1, &fdSet, NULL, NULL, &tout) == 0) {
      // Se agotó el tiempo de espera
      continue;
    }

    // Verificar si hay entrada de teclado
    if (FD_ISSET(STDIN_FILENO, &fdSet)) {
     // Si hay entrada de teclado, envía un mensaje al servidor de eco
      if (SendEchoMessage(sock, &servAddr) < 0) {
        break;
      }
    }
    
    // Comprobar la entrada del socket
    if (FD_ISSET(sock_recv, &fdSet)) {
      // Si hay entrada en el socket, recibe un mensaje del servidor de eco
      if (ReceiveEchoMessage(sock_recv, &servAddr) < 0) {
        break;
      }
    }
  }

  // Salir del grupo de multicast
  close(sock);
  close(sock_recv);
  exit(0);
}

// Función de procesamiento para ingresar cadenas de caracteres desde el teclado y enviarlas al servidor de eco
int SendEchoMessage(int sock, struct sockaddr_in *pServAddr){
  char chatString[MSGLEN];
  int chatStringLen;

  char msgString[MSGLEN];
  int msgStringLen;

  char pktBuf[MSGLEN];
  int pktLen;

  int sendMsgLen;

  // Leer la entrada del teclado y incluye los espacios en blanco
  if (fgets(chatString, MSGLEN, stdin) == NULL) {
    // Error de entrada o Ctrl + D
    return -1;
  }

  // CHAT PRIVADO
  if(strncmp(chatString, "/p", 2) == 0){
    chatString[strlen(chatString)-1] = '\0';
    split(chatStringSplit, chatString, '-');

    // COnfiguracion de formato
    snprintf(msgString, MSGLEN, "[%s] %s", userName, chatStringSplit[2]);
    snprintf(msgString, MSGLEN, "%s$%s\n", msgString, chatStringSplit[1]);

    // Comprobar la longitud de la cadena de entrada
    msgStringLen = strlen(msgString);
    if (msgStringLen < 1) {
      fprintf(stderr,"No input string.\n");
      return -1;
    }

    // Empaquetar
    pktLen = Packetize(MSG_ID_PRIVATE_CHAT_TEXT, 
      msgString, msgStringLen, pktBuf, MSGLEN
    );
    
    // Enviar
    sendMsgLen = sendto(sock, pktBuf, pktLen, 0,
      (struct sockaddr*)pServAddr, sizeof(*pServAddr));

    // Error de envío
    if (pktLen != sendMsgLen) {
      fprintf(stderr, "sendto() sent a different number of bytes than expected");
      return -1;
    }
  }

  // Obtener informacion del grupo
  else if(strcmp(chatString, "/info\n") == 0){
    pktLen = Packetize(MSG_ID_GROUP_INFO_REQUEST,
      userName, strlen(userName), pktBuf, MSGLEN
    );

    sendMsgLen = sendto(sock, pktBuf, pktLen, 0,
      (struct sockaddr*)pServAddr, sizeof(*pServAddr));
  }

  // Obtener informacion de los miembros del grupo 
  else if(strcmp(chatString, "/member\n") == 0){
    pktLen = Packetize(MSG_ID_USER_LIST_REQUEST,
      userName, strlen(userName), pktBuf, MSGLEN
    );

    sendMsgLen = sendto(sock, pktBuf, pktLen, 0,
      (struct sockaddr*)pServAddr, sizeof(*pServAddr));
  }

  // Salida del grupo
  else if(strcmp(chatString, "/quit\n") == 0){
    pktLen = Packetize(MSG_ID_LEAVE_REQUEST,
      userName, strlen(userName), pktBuf, MSGLEN
    );

    sendMsgLen = sendto(sock, pktBuf, pktLen, 0,
      (struct sockaddr*)pServAddr, sizeof(*pServAddr));
  }

  // Enviar CHAT
  else{
    // Configuracion de formato
    snprintf(msgString, MSGLEN, "[%s] %s", userName, chatString);

    // Comprobar la longitud de la cadena de entrada
    msgStringLen = strlen(msgString);
    if (msgStringLen < 1) {
      fprintf(stderr,"No input string.\n");
      return -1;
    }

    pktLen = Packetize(MSG_ID_CHAT_TEXT, 
      msgString, msgStringLen, pktBuf, MSGLEN
    );

    sendMsgLen = sendto(sock, pktBuf, pktLen, 0,
      (struct sockaddr*)pServAddr, sizeof(*pServAddr));

    if (pktLen != sendMsgLen) {
      fprintf(stderr, "sendto() sent a different number of bytes than expected");
      return -1;
    }
  }
  
  return 0;
}

// Función de procesamiento de visualización/recepción de mensajes desde el socket
int ReceiveEchoMessage(int sock, struct sockaddr_in *pServAddr){
  struct sockaddr_in fromAddr;
  unsigned int fromAddrLen;
  char pktBuffer[MSGLEN];
  int recvPktLen;
  int msgLen;
  short msgID;
  char msgBuf[MSGLEN];
  char msg[MSGLEN];

  // Inicializa la longitud de la estructura de la direccion de origen del mensaje eco
  fromAddrLen = sizeof(fromAddr);

  // Recibe un mensaje del servidor de eco
  recvPktLen = recvfrom(sock, pktBuffer, MSGLEN, 0,
    (struct sockaddr*)&fromAddr, &fromAddrLen);

  if (recvPktLen < 0) {
    fprintf(stderr, "recvfrom() failed");
    return -1;
  }

  msgLen = Depacketize(
    pktBuffer, recvPktLen, &msgID, msgBuf, MSGLEN
  );
  msgBuf[msgLen] = '\0';

  // Recibir mensaje de chat privado
  if(msgID == (short)MSG_ID_PRIVATE_CHAT_TEXT){
    split(privateSplit, msgBuf, '$');

    privateSplit[0][strlen(privateSplit[0])] = '\0';
    privateSplit[1][strlen(privateSplit[1])-1] = '\0';

    // Muestra si esta digirido a mi
    if(strcmp(privateSplit[1], userName) == 0){
      printf("(privado) %s\n", privateSplit[0]);
      return 0;
    }
  }

  // Texto de chat recibido
  else if(msgID == MSG_ID_CHAT_TEXT){
    printf("%s", msgBuf);
    return 0;
  }

  // Recibir respuesta de informacion del grupo
  else if(msgID == (short)MSG_ID_GROUP_INFO_RESPONSE){
    printf("\n[*] La dirección de multidifusión del grupo de chat es %s\n\n", mcastIP);
    return 0;
  }

  // Recibir respuesta de unirse al grupo
  else if(msgID == MSG_ID_JOIN_RESPONSE){
    if(strcmp(msgBuf, userName) == 0){
      usage(userName);
    }else{
      printf("[*] %s se unio al grupo.\n", msgBuf);
    }
    return 0;
  }

  // Recibir respuesta de informacion de miembros del grupo
  else if(msgID == (short)MSG_ID_USER_LIST_RESPONSE){
    printf("%s\n", msgBuf);
    return 0;
  }

  // Recibir respuesta de salida del grupo
  else if(msgID == MSG_ID_LEAVE_RESPONSE){
    printf("[*] %s ha salido del grupo\n", msgBuf);

    // Finaliza si se acpeta la solicitud de salida
    if(strcmp(msgBuf, userName) == 0){
      exit(0);
    }

    return 0;
  }

  return 0;
}