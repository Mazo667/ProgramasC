#include "Pila.h"
Pila inicializarPila(){
  Pila miPila;
  miPila.cima = NULL;
  miPila.tamanio = 0;
  return miPila;
  }
//PRECONDICION: Que exista un espacio en memoria.
//ENTRADA:
//SALIDA: Una Pila inicializada.
//POSCONDICION: se Crea una Pila.

int PilaVacia(Pila *miPila){
    if (miPila->tamanio == 0 && miPila->cima == NULL){
      return OK;
    }else
      return ERROR;
}
//PRECONDICION: La Pila debe ser valida.
//ENTRADA: Una Pila.
//SALIDA: Un valor que nos indique que la Pila esta vacia.
//POSCONDICION: Se determino si la Pila esta o no vacia.

Nodo *CrearNodo(Dato miDato){
     Nodo *miNodo;
     miNodo = (Nodo*)malloc(sizeof(Nodo));
     miNodo->midato = miDato;
     miNodo->siguiente = NULL;
     return miNodo;
 }
//PRECONDICION: Que exista un espacio en memoria.
//ENTRADA:
//SALIDA: Un nodo.
//POSCONDICION: Se crea un nodo.
int Apilar(Pila *miPila, Nodo *miNodo){
    if (miNodo == NULL){
        return ERROR;
    }else{
        if (PilaVacia == OK){
          miPila->cima = miNodo;
          miNodo->siguiente = NULL;
          miPila->tamanio++;
            return OK;
         }else{
              Nodo *nodoAux;
              nodoAux = miPila->cima;
              miPila->cima = miNodo;
              miNodo->siguiente = nodoAux;
              miPila->tamanio++;
                return OK;
            }
    }
}
//PRECONDICION: Que exista una pila.
//ENTRADA: Una Pila y un nodo.
//SALIDA: Un entero.
//POSTCONDICION: Se crea un nuevo nodo en la Pila.
void imprimir(Pila *miPila){
    if (PilaVacia(miPila) == OK){
      printf("La Pila esta vacia");
      }else{
         Nodo *nodoAux = miPila->cima;
         while (nodoAux != NULL){
           printf("Elemento %d \t", nodoAux);
           nodoAux = nodoAux->siguiente;
         }
      }
}
//PRECONDICION: Que exista una pila que contenga nodos.
//ENTRADA: Una Pila.
//SALIDA: El dato de los nodos.
//POSCONDICION: Se imprime todos los datos que contenga la Pila.

int CantidadElementos(Pila miPila){
    if (PilaVacia == OK){
        return ERROR;
    }else{
        return miPila.tamanio;
    }
}
//PRECONDICION: Que exista una Pila que contengsa nodos.
//ENTRADA: Una Pila.
//SALIDA: La cantidad de nodos que tiene la Pila.
//POSCONDICION: La cantidad de nodos que tiene la Pila.
int EliminarElemento(Pila *miPila){
    if (PilaVacia(miPila) == OK){
        return ERROR;
    }else{
        Nodo *nodoAux = miPila->cima;
        Nodo *nodoParaEliminar;
        nodoParaEliminar = miPila->cima;
          if (nodoAux->siguiente == NULL){
            eliminarPila(miPila);
            free(nodoAux);
            return (OK);
            }else{
               nodoAux = nodoAux->siguiente;
               miPila->cima = nodoAux;
               miPila->tamanio--;
               free(nodoParaEliminar);
               return (OK);
            }
          }
   }
//PRECONDICION: Que exista una Pila que contenga nodos.
//ENTRADA: Una Pila.
//SALIDA: Un entero.
//POSCONDICION: Se elimina el primer nodo de la Pila, si lo hay.

int eliminarPila(Pila *miPila){
    if (PilaVacia(miPila) == OK){
       return (ERROR);
       }else{
          Nodo *nodoAux;
          Nodo *NodoParaEliminar;
          nodoAux = miPila->cima;
          while (nodoAux != NULL){
             NodoParaEliminar = nodoAux;
             nodoAux = nodoAux->siguiente;
             free(NodoParaEliminar);
          }
          miPila->cima = NULL;
          miPila->tamanio = 0;
           return (OK);
       }
}

//PRECONDICION: Que exista una Pila.
//ENTRADA: Una Pila
//SALIDA: Un entero.
//POSCONDICION: Se elimina una Pila.
Dato obtenerElemento(Pila *miPila){
   Dato error;
   error.numero = ERROR;
     if (PilaVacia(miPila) == OK){
        return error;
        }else{
           Dato unDato;
           Nodo *nodoAux;
           nodoAux = miPila->cima;
           unDato = nodoAux->midato;
             return unDato;
        }
}

//PRECONDICION: Que exista una Pila con nodos.
//ENTRADA: Una Pila.
//SALIDA: Un Dato.
//POSTCONDICION: Obtenemos el primer dato de una pila si lo hay.
