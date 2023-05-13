#include "Lista.h"

Nodo *crearNodo(Dato elDato){
    Nodo *miNodo = NULL;
    miNodo = (Nodo*)malloc(sizeof(Nodo));
    miNodo->anterior=NULL;
    miNodo->siguiente=NULL;
    miNodo->elDato=elDato;
    return (miNodo);
}
//Precondicion: debe existir espacion en memoria
//Entrada:
//Salida: Un nodo que contiene un dato
//Poscondcion: Se crea un nodo

Lista inicializarLista() {
    Lista miLista;
    miLista.primero = NULL;
    miLista.tamanio = 0;
    return miLista;
}
//Precondicion: debe existir espacio en memoria
//Entrada:
//Salida: una lista creada e inicializada
//Poscondicion: se crea una lista


int listaVacia(Lista *miLista){
    if(miLista->primero==NULL && miLista->tamanio==0){
        return(OK);
    }else{
        return(ERROR);
    }
}
//Precondicion: la lista debe ser valida
//Entrada: una Lista
//Salida: valor de verdad que indica si a lista esta vacia o no
//Poscondicion: se determino si la lista esta vacia o no


int agregarAlPrincipio(Lista *miLista, Nodo *miNodo){
    if(miNodo == NULL){
        return (ERROR); //El nodo no se guardo correctamente
    }else{
        Nodo *nodoAux;
        if(miLista->primero == NULL){
        miLista->primero = miNodo;
        miLista->tamanio++;
        return (OK);
    }else{
        nodoAux = miLista->primero;
        miLista->primero = miNodo;
        miNodo->siguiente = nodoAux;
        nodoAux->anterior = miNodo;
        miLista->tamanio++;
        return (OK);
        }
    }
}
//Precondicion: que exista una lista
//Entrada: Una lista y un nodo
//Salida: un entero
//Poscondcion: Se crea un nuevo nodo en la lista

int agregarAlFinal(Lista *miLista, Nodo *miNodo){
    if(miNodo == NULL){
        return (ERROR); //El nodo no se guardo correctamente
    }else{
            Nodo *nodoAux;
            nodoAux = miLista->primero;
        if(listaVacia(miLista) == OK){ //La lista esta vacia
            miLista->primero = miNodo; //El elemento va a hace el primero en la lista
            miLista->tamanio++;
            return (OK);
        }else{
            while(nodoAux->siguiente != NULL){
            nodoAux = nodoAux->siguiente;
            }
            nodoAux->siguiente = miNodo;
            miNodo->anterior = nodoAux;
            miLista->tamanio++;
            return (OK);
        }
    }
}
//Precondicion: que exista una lista
//Entrada: Una lista y un nodo
//Salida: un entero
//Poscondcion: Se crea un nuevo nodo al final de la lista

int agregarEnPosicion(Lista *miLista, Nodo *miNodo, int posicion){
    if(miNodo == NULL){
        return (ERROR); //El nodo no se guardo correctamente
    }else{
    if(listaVacia(miLista) == OK){
        agregarAlPrincipio(miLista,miNodo);
        return (OK);
    }else if(posicion == 1){
        agregarAlPrincipio(miLista,miNodo);
        return (OK);
    }else if(posicion >= cantidadElementos(miLista)){
        agregarAlFinal(miLista,miNodo);
        return (OK);
    }else{
        Nodo *nodoAux;
        nodoAux = miLista->primero;
        int i = 1;
        Nodo *nodoAux2;
            while(i != posicion){
                nodoAux2 = nodoAux; //Guarda el nodo anterior
                nodoAux = nodoAux->siguiente; //Guarda el nodo en la posicion
                i++;
                }
            nodoAux2->siguiente = miNodo;
            miNodo->anterior = nodoAux2;
            miNodo->siguiente = nodoAux;
            nodoAux->anterior = miNodo;
            miLista->tamanio++;
            return(OK);
        }
    }
}

//Precondicion: Que exista una lista
//Entrada: Una lista y un nodo
//Salida: Un entero
//Poscondcion: Se crea un nuevo nodo en la lista

void Imprimir(Lista *miLista){
    if(listaVacia(miLista) == OK){
        printf("La lista esta vacia");
    }else{
    Nodo *nodoAux = miLista->primero;
    while(nodoAux != NULL){
        printf("Elemento: %d\t",nodoAux->elDato);
        nodoAux = nodoAux->siguiente;
        }
    }
}
//Precondicion: exista una lista que contenga nodos
//Entrada: Una lista
//Salida: El dato de los nodos
//Poscondcion: Se imprime todos los valores de la lista

int cantidadElementos(Lista *miLista){
    if(listaVacia(miLista) == OK){
        return(ERROR);
    }else{
        return(miLista->tamanio);
    }
}
//Precondicion: exista una lista que contenga nodos
//Entrada: Una lista
//Salida: La cantidad de nodos que tenga la lista
//Poscondcion: La cantidad de nodos que tenga la lista

int eliminarPrimerElemento(Lista *miLista) {
    if (miLista->primero == NULL) {
        // La lista está vacía
        return ERROR;
    }

    Nodo *nodoParaEliminar = miLista->primero;

    if (nodoParaEliminar->siguiente == NULL) {
        // La lista tiene un solo elemento
        miLista->primero = NULL;
        free(nodoParaEliminar);
    } else {
        miLista->primero = nodoParaEliminar->siguiente;
        miLista->primero->anterior = NULL;
        free(nodoParaEliminar);
    }

    miLista->tamanio--;
    return OK;
}
//Precondicion: exista una lista que contenga nodos
//Entrada: Una lista
//Salida: Un entero
//Poscondcion: Se elimina el primer nodo de la lista si lo hay
int eliminarUltimoElemento(Lista *miLista) {
    Nodo *nodoParaEliminar = miLista->primero;
    Nodo *nodoAux = NULL;

    if (nodoParaEliminar == NULL) {
        // La lista está vacía
        return ERROR;
    }

    if (nodoParaEliminar->siguiente == NULL) {
        // La lista tiene un solo elemento
        miLista->primero = NULL;
        free(nodoParaEliminar);
    } else {
        // Recorrer hasta el último elemento
        while (nodoParaEliminar->siguiente != NULL) {
            nodoAux = nodoParaEliminar;
            nodoParaEliminar = nodoParaEliminar->siguiente;
        }
}
}
//Precondicion: exista una lista que contenga nodos
//Entrada: Una lista
//Salida: Un entero
//Poscondcion: Se elimina el ultimo nodo de la lista si lo hay

int eliminarElementoEnPosicion(Lista *miLista, int posicion){
    if(listaVacia(miLista) == OK){
        return (ERROR);
    }else{
        int i = 1;
        Nodo *nodoParaEliminar;
        Nodo *nodoAux;
        nodoParaEliminar = miLista->primero;
    while(i != posicion){
        nodoAux = nodoParaEliminar; //Guarda el nodo anterior
        nodoParaEliminar = nodoParaEliminar -> siguiente; //Guarda el nodo en la posicion
        i++;
    }
        nodoAux->siguiente = nodoParaEliminar->siguiente;
        nodoParaEliminar->siguiente->anterior = nodoAux->siguiente;
        free(nodoParaEliminar);
        miLista->tamanio--;
        return (OK);
    }
}

//Precondicion: exista una lista que contenga nodos
//Entrada: Una lista y un indice
//Salida: Un entero
//Poscondcion: Se elimina un nodo en cualquier posicion de la lista si lo hay

int eliminarLista(Lista *miLista){
    if(listaVacia(miLista) == OK){
        return (ERROR);
    }else{
        Nodo *nodoAux;
        Nodo *NodoParaEliminar;
        nodoAux = miLista->primero;
        while(nodoAux != NULL){
            NodoParaEliminar = nodoAux;
            nodoAux = nodoAux->siguiente;
            free(NodoParaEliminar);
            }
        miLista->primero = NULL;
        miLista->tamanio = 0;
        return(OK);
    }
}
//Precondicion: exista una lista
//Entrada: Una lista
//Salida: Un entero
//Poscondcion: Se elimina una lista

Dato obtenerPrimerElemento(Lista *miLista){
        Dato error;
        error.NUMERO = ERROR;
    if(listaVacia(miLista) == OK){
        return error;
    }else{
    Dato unDato;
    Nodo *nodoAux;
    nodoAux = miLista->primero;
    unDato = nodoAux->elDato;
    return unDato;
    }
}
//Precondicion: exista una lista con nodos
//Entrada: Una lista
//Salida: Un dato
//Poscondcion: Obtenemos el primer dato de una lista si lo hay

Dato obtenerUltimoElemento(Lista *miLista){
        Dato error;
        error.NUMERO = ERROR;
    if(listaVacia(miLista) == OK){
        return error;
    }else{
    Dato undato;
    Nodo *nodoAux;
    nodoAux = miLista->primero;
    while(nodoAux->siguiente != NULL){
        nodoAux = nodoAux->siguiente;
    }
    undato = nodoAux->elDato;
    return undato;
    }
}
//Precondicion: exista una lista con nodos
//Entrada: Una lista
//Salida: Un dato
//Poscondcion: Obtenemos el ultimo dato de una lista si lo hay

Dato obtenerElementoDeterminado(Lista *miLista, int posicion){
        Dato error; //Declaro una variable error
        error.NUMERO = ERROR;   //Le asigno el valor de error
   if(listaVacia(miLista) == OK){
        return error;
    }else if(cantidadElementos(miLista) < posicion ){
        return error;
    }else{
        int i = 0;
        Dato undato;
        Nodo *nodoAux;
        Nodo *nodoAux2;
        nodoAux = miLista->primero;
         while(i < posicion){
            nodoAux2 = nodoAux;
            nodoAux = nodoAux -> siguiente;
            i++;
            }
            undato = nodoAux2->elDato;
            return undato;
        }
}
//Precondicion: exista una lista con nodos
//Entrada: Una lista y un indice
//Salida: Un dato
//Poscondcion: Obtenemos el dato de una determinada posicion de la lista si lo hay
