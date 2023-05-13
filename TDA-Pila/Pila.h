#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR -1



typedef struct dato{
  int numero;
}Dato;

typedef struct nodo{
   Dato midato;
   struct nodo *siguiente;
}Nodo;
typedef struct pila{
   int tamanio;
   Nodo *cima;
}Pila;

Pila inicializarPila();
int PilaVacia(Pila *miPila);
Nodo *CrearNodo(Dato miDato);
int Apilar(Pila *miPila, Nodo *miNodo);
void imprimir(Pila *miPila);
int CantidadElementos(Pila miPila);
