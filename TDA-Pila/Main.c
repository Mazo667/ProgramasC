#include "Main.h"
int main (void){
  int opcion;
  int tamanio = 0;
  Dato miDato;

  Pila miPila = inicializarPila();

  Nodo *miNodo;
  do{
      opcion = menu(opcion);
      switch (opcion){
        case 1:
             printf ("Ingrese el Elemento a guardar: ");
             scanf("%d", &miDato);
             miNodo = CrearNodo(miDato);
               if (Apilar(&miPila,miNodo) == OK){
                 printf("El Elemento se agrego Correctamente\n");
                  }else {
                    printf("ERROR\n");
               }
                break;

        case 2:
             tamanio = CantidadElementos(miPila);
               if (CantidadElementos == ERROR){
                 printf("La Pila esta vacia\n ");
                   }else{
                      printf("La Pila tiebe %d elementos\n", tamanio);
               }
                break;

        case 3:
             if (EliminarElemento(&miPila) == OK){
                printf("El elemento se elimino correctamente\n");
               }
                break;

        case 4:
              imprimir(&miPila);
                break;

        case 5:
             if (eliminarPila(&miPila) == OK){
                printf("La Pila se elimino correctamente");
              }else{
                 printf("No hay Pila a eliminar");
               }
                 break;

        case 6:
             miDato.numero = obtenerElemento(miPila);
               if (miDato.numero != ERROR){
                 printf("El elemento es %d\n", miDato);
               }else{
                 printf("Error no se encontro elemento a obtener\n");
               }
                break;

        case 7:
             if (PilaVacia(PilaVacia) == OK){
                printf("La Pila esta Vacia\n");
              }else{
                printf("La Pila tiene elementos\n");
               }
                break;

    }

  }while (opcion < 8);

}
int menu(int opcion){
   printf("\n****TRABAJO PRACTICO N° 4 ****\n\t 1- Apilar.\n""\t2- Cantidad Elemento.\n""\t3- Eliminarde Elementos.\n""\t4- Imprimir.\n"
          "\t5- Eliminar Elemento.\n""\t6- Obtener Elemento.\n""\t7- Consulta Pila Vacia.\n""\t8- Salir del Programa.\n""Ingrese una Opcion: ");
   scanf("%d", opcion);
   return opcion;
}
