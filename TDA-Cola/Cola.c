#include "Cola.h"

Nodo *crearNodo(Dato elDato){
    Nodo *miNodo = NULL;
    miNodo = (Nodo*)malloc(sizeof(Nodo));
    miNodo->siguiente=NULL;
    miNodo->elDato=elDato;
    return (miNodo);
}
//Precondicion: Debe existir espacio en memoria
//Entrada: Un dato
//Salida: Un nodo que contiene un dato
//Poscondcion: Se crea un nodo

Cola inicializarCola() {
    Cola laCola;
    laCola.Frente = NULL;
    laCola.Final = NULL;
    laCola.tamanio = 0;
    return laCola;
}
//Precondicion: debe existir espacio en memoria
//Entrada:
//Salida: una lista creada e inicializada
//Poscondicion: se crea una lista

int colaVacia(Cola *laCola){
    if(laCola->Frente==NULL && laCola->tamanio==0){
        return(OK);
    }else{
        return(ERROR);
    }
}
//Precondicion: la cola debe ser valida
//Entrada: una Cola
//Salida: valor de verdad que indica si la cola esta vacia o no
//Poscondicion: se determino si la Cola esta vacia o no

int cantidadElementos(Cola *laCola){
    if(colaVacia(laCola) == OK){
        return(ERROR);
    }else{
        return(laCola->tamanio);
    }
}
//Precondicion: Que exista una Cola con elementos
//Entrada: Una Cola
//Salida: La cantidad de nodos que tenga la Cola
//Poscondcion: La cantidad de nodos que tenga la Cola

void Imprimir(Cola *laCola){
    if(colaVacia(laCola) == OK){
        printf("La Cola esta vacia");
    }else{
    Nodo *nodoAux = laCola->Frente;
    while(nodoAux != NULL){
        printf("Elemento: %d\t",nodoAux->elDato);
        nodoAux = nodoAux->siguiente;
        }
    }
}
//Precondicion: Exista una Cola que tenga elementos
//Entrada: Una Cola
//Salida: El dato de los nodos
//Poscondcion: Se imprime todos los valores de la Cola

int eliminarCola(Cola *laCola){
    if(colaVacia(laCola) == OK){
        return (ERROR);
    }else{
        Nodo *nodoAux;
        Nodo *NodoParaEliminar;
        nodoAux = laCola->Frente;
        while(nodoAux != NULL){
            NodoParaEliminar = nodoAux;
            nodoAux = nodoAux->siguiente;
            free(NodoParaEliminar);
            }
        laCola->Frente = NULL;
        laCola->Final = NULL;
        laCola->tamanio = 0;
        return(OK);
    }
}
//Precondicion: Exista una Cola
//Entrada: Una Cola
//Salida: Un entero
//Poscondcion: Se elimina una Cola

int encolar(Cola *laCola, Nodo *miNodo){
    if(miNodo == NULL){
        return (ERROR); //El nodo no se guardo correctamente
    }else{
        if(colaVacia(laCola) == OK){
        laCola->Final = miNodo;
        laCola->Frente = miNodo;
        laCola->tamanio++;
        return (OK);
    }else{
        Nodo *nodoAux;
        nodoAux = laCola->Final;
        nodoAux->siguiente = miNodo;
        laCola->Final = miNodo;
        laCola->tamanio++;
        return (OK);
        }
    }
}
//Precondicion: Exista una Cola y un dato que encolar
//Entrada: Una Cola y un nodo
//Salida: Un entero
//Poscondcion: Se agrega un nodo al final de la cola


int Desencolar(Cola *laCola){
    if(colaVacia(laCola) == OK){
        return (ERROR);
    }else{
        if(laCola->tamanio == 1){
            eliminarCola(laCola);
            return (OK);
        }else{
        Nodo *nodoAux;
        Nodo *nodoParaEliminar = laCola->Frente;
        nodoAux = nodoParaEliminar->siguiente;
        free(nodoParaEliminar);
        laCola->tamanio--;
        laCola->Frente = nodoAux;
        return (OK);
        }
    }
}
//Precondicion: Exista una cola con nodos
//Entrada: Una cola
//Salida: Un entero
//Poscondcion: Desencolaremos el elemento que se encuentra en la cabeza

Dato obtenerElementoCabeza(Cola *laCola){
        Dato error;
        error.numero = ERROR;
    if(colaVacia(laCola) == OK){
        return error;
    }else{
    Dato unDato;
    Nodo *nodoAux;
    nodoAux = laCola->Frente;
    unDato = nodoAux->elDato;
    return unDato;
    }
}
//Precondicion: Exista una cola con nodos
//Entrada: Una cola
//Salida: Un dato
//Poscondcion: Obtenemos el elemento que esta en la cabeza de la cola si lo hay
