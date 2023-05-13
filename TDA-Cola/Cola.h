#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR -1

typedef struct dato{
    int numero;
}Dato;

typedef struct nodo{
    Dato elDato;
    struct nodo* siguiente;
}Nodo;

typedef struct cola{
    int tamanio;
    Nodo *Frente;
    Nodo *Final;
}Cola;


Cola inicializarCola();
Nodo *crearNodo(Dato elDato);
int colaVacia(Cola *laCola);
int cantidadElementos(Cola *laCola);
void Imprimir(Cola *laCola);
int agregarAlFinal(Cola *laCola, Nodo *miNodo);
int Desencolar(Cola *laCola);
int encolar(Cola *laCola, Nodo *miNodo);
int eliminarCola(Cola *laCola);
