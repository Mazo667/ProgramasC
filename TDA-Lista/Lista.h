#include <stdio.h>
#include <stdlib.h>

#ifndef TP3_H_
#define TP3_H_
#endif


#define OK 1
#define ERROR -1

typedef struct dato{
   int NUMERO;
} Dato;

//Estructura del nodo
typedef struct nodo{
        Dato elDato;//Dato contenido en el nodo
        struct nodo* siguiente;//Puntero  al siguiente nodo de la lista
        struct nodo* anterior;//Puntero al siguiente nodo de la lista
} Nodo;//Nombre para hacer referencia al tipo de dato de esta estructura.

typedef struct lista{
    int tamanio;    //Longitud de la lista
    Nodo *primero;  //Salida de la lista
} Lista;

//Inicializacion de funciones y variables
Lista inicializarLista();
int listaVacia(Lista *miLista);
int agregarAlPrincipio(Lista *miLista, Nodo *miNodo);
int agregarAlFinal(Lista *miLista, Nodo *miNodo);
int agregarEnPosicion(Lista *miLista, Nodo *miNodo, int posicion);
void Imprimir(Lista *miLista);
int cantidadElementos(Lista *miLista);
int eliminarPrimerElemento(Lista *miLista);
int eliminarUltimoElemento(Lista *miLista);
int eliminarElementoEnPosicion(Lista *miLista, int posicion);
int eliminarLista(Lista *miLista);
//Dato obtenerPrimerElemento(Lista *miLista);
//Dato obtenerUltimoElemento(Lista *miLista);
//Dato obtenerElementoDeterminado(Lista *miLista, int posicion);
Lista crearLista();
